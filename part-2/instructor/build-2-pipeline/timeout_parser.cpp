#include "timeout_parser.hpp"

#include <cctype>
#include <cstdint>
#include <limits>
#include <string>

namespace timeouts {
namespace {

constexpr std::uint64_t kMaxMillis = std::numeric_limits<std::uint32_t>::max();

bool is_space(char c) { return std::isspace(static_cast<unsigned char>(c)) != 0; }
bool is_digit(char c) { return c >= '0' && c <= '9'; }
bool is_alpha(char c) { return std::isalpha(static_cast<unsigned char>(c)) != 0; }

// Rank orders units from largest to smallest; 0 means unknown.
int unit_rank(const std::string& unit, std::uint64_t& factor) {
    if (unit == "h") { factor = 3600000; return 4; }
    if (unit == "m") { factor = 60000; return 3; }
    if (unit == "s") { factor = 1000; return 2; }
    if (unit == "ms") { factor = 1; return 1; }
    return 0;
}

}  // namespace

ParseResult parse_timeout(const std::string& text) {
    std::size_t begin = 0;
    std::size_t end = text.size();
    while (begin < end && is_space(text[begin])) ++begin;
    while (end > begin && is_space(text[end - 1])) --end;
    if (begin == end) return {ParseError::Empty, 0};

    std::uint64_t total = 0;
    int previous_rank = 5;  // larger than any unit
    bool overflow = false;
    std::size_t i = begin;

    while (i < end) {
        // Number: digits only. Saturate instead of wrapping; any value above
        // kMaxMillis is already an overflow whatever the unit.
        const std::size_t digits_begin = i;
        std::uint64_t value = 0;
        while (i < end && is_digit(text[i])) {
            if (value <= kMaxMillis) value = value * 10 + static_cast<std::uint64_t>(text[i] - '0');
            ++i;
        }
        if (i == digits_begin) return {ParseError::InvalidToken, 0};

        // Unit: letters only.
        const std::size_t unit_begin = i;
        while (i < end && is_alpha(text[i])) ++i;
        if (i == unit_begin) return {ParseError::InvalidToken, 0};

        std::uint64_t factor = 0;
        const int rank = unit_rank(text.substr(unit_begin, i - unit_begin), factor);
        if (rank == 0) return {ParseError::UnknownUnit, 0};
        if (rank >= previous_rank) return {ParseError::InvalidToken, 0};
        previous_rank = rank;

        // value <= kMaxMillis + 9 fits easily, and factor <= 3600000, so the product fits in 64 bits.
        if (value > kMaxMillis) overflow = true;
        else {
            total += value * factor;
            if (total > kMaxMillis) overflow = true;
        }
    }

    if (overflow) return {ParseError::Overflow, 0};
    return {ParseError::None, static_cast<std::uint32_t>(total)};
}

}  // namespace timeouts
