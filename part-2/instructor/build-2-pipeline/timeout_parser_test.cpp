// Reference tests for NET-1502. Copy over tests/timeout_parser_test.cpp to check a solution.
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
    const ParseError N = ParseError::None, E = ParseError::Empty, I = ParseError::InvalidToken,
                     U = ParseError::UnknownUnit, O = ParseError::Overflow;

    // 8. Existing behaviour.
    check("seconds", "30s", N, 30000);
    check("milliseconds", "500ms", N, 500);
    check("minutes", "5m", N, 300000);
    check("hours", "2h", N, 7200000);
    check("surrounding whitespace", "  15s\t", N, 15000);
    // 1-2. Combined parts.
    check("1h30m", "1h30m", N, 5400000);
    check("2m15s", "2m15s", N, 135000);
    check("1s500ms", "1s500ms", N, 1500);
    check("all units", "1h1m1s1ms", N, 3661001);
    check("zero", "0s", N, 0);
    check("leading zeros", "007s", N, 7000);
    check("space inside", "1h 30m", I, 0);
    // 3. Order and repetition.
    check("ascending", "30m1h", I, 0);
    check("repeated", "1m1m", I, 0);
    check("ms before s", "500ms1s", I, 0);
    // 4. Empty.
    check("empty", "", E, 0);
    check("whitespace only", " \t ", E, 0);
    // 5. Malformed and unknown.
    check("no unit", "30", I, 0);
    check("no number", "ms", I, 0);
    check("trailing number", "1h30", I, 0);
    check("minus", "-5s", I, 0);
    check("plus", "+5s", I, 0);
    check("decimal", "1.5s", I, 0);
    check("days", "5d", U, 0);
    check("sec", "5sec", U, 0);
    check("unknown second part", "1h5x", U, 0);
    // 6. Overflow at the 32-bit boundary and beyond.
    check("max", "4294967295ms", N, 4294967295u);
    check("max plus one", "4294967296ms", O, 0);
    check("1193h fits", "1193h", N, 4294800000u);
    check("1194h overflows", "1194h", O, 0);
    check("field report", "5000000h", O, 0);
    check("sum overflow", "1193h2m47s296ms", O, 0);
    check("sum at max", "1193h2m47s295ms", N, 4294967295u);
    check("2^64 digits", "18446744073709551616ms", O, 0);
    check("very long", "99999999999999999999999999999999s", O, 0);

    if (failures == 0) {
        std::cout << "OK: " << checks << " checks passed\n";
        return 0;
    }
    std::cerr << failures << " of " << checks << " check(s) failed\n";
    return 1;
}
