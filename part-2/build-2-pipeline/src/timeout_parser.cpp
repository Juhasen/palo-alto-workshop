#include "timeout_parser.hpp"

#include <cctype>
#include <string>

namespace timeouts {

// Legacy behaviour, moved here unchanged from agent_config.cpp:
// one number followed by one unit, for example "30s".
ParseResult parse_timeout(const std::string& text) {
    std::size_t begin = 0;
    std::size_t end = text.size();
    while (begin < end && std::isspace(static_cast<unsigned char>(text[begin]))) ++begin;
    while (end > begin && std::isspace(static_cast<unsigned char>(text[end - 1]))) --end;
    if (begin == end) return {ParseError::Empty, 0};

    unsigned long value = 0;
    std::size_t i = begin;
    while (i < end && std::isdigit(static_cast<unsigned char>(text[i]))) {
        value = value * 10 + static_cast<unsigned long>(text[i] - '0');
        ++i;
    }
    if (i == begin) return {ParseError::InvalidToken, 0};

    const std::string unit = text.substr(i, end - i);
    unsigned long factor = 0;
    if (unit == "ms") factor = 1;
    else if (unit == "s") factor = 1000;
    else if (unit == "m") factor = 60UL * 1000;
    else if (unit == "h") factor = 60UL * 60 * 1000;
    if (factor == 0) return {ParseError::UnknownUnit, 0};

    return {ParseError::None, static_cast<std::uint32_t>(value * factor)};
}

}  // namespace timeouts
