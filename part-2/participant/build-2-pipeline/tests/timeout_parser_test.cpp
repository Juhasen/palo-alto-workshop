#include "timeout_parser.hpp"

#include <cstdint>
#include <iostream>
#include <string>

using timeouts::ParseError;

int main() {
    int failures = 0;
    int checks = 0;

    auto check = [&](const char* name, const std::string& text, ParseError expected_error,
                     std::uint32_t expected_millis) {
        ++checks;
        const timeouts::ParseResult result = timeouts::parse_timeout(text);
        if (result.error != expected_error || result.millis != expected_millis) {
            std::cerr << "FAIL: " << name << " (\"" << text << "\") -> error "
                      << static_cast<int>(result.error) << ", " << result.millis << " ms\n";
            ++failures;
        }
    };

    // Existing behaviour that callers rely on today.
    check("seconds", "30s", ParseError::None, 30000);
    check("milliseconds", "500ms", ParseError::None, 500);
    check("minutes", "5m", ParseError::None, 300000);
    check("hours", "2h", ParseError::None, 7200000);
    check("surrounding whitespace", "  15s\t", ParseError::None, 15000);
    check("empty", "", ParseError::Empty, 0);
    check("whitespace only", "   ", ParseError::Empty, 0);
    check("no number", "abc", ParseError::InvalidToken, 0);
    check("unknown unit", "5d", ParseError::UnknownUnit, 0);

    // NET-1502 acceptance criteria: add tests here.

    if (failures == 0) {
        std::cout << "OK: " << checks << " checks passed\n";
        return 0;
    }
    std::cerr << failures << " of " << checks << " check(s) failed\n";
    return 1;
}
