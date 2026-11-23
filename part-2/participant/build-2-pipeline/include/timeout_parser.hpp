#pragma once

#include <cstdint>
#include <string>

namespace timeouts {

enum class ParseError {
    None,
    Empty,         // text is empty or only whitespace
    InvalidToken,  // missing number, missing unit, sign, decimal point, or units out of order
    UnknownUnit,   // a unit other than ms, s, m, h
    Overflow       // total exceeds 4294967295 ms
};

struct ParseResult {
    ParseError error;
    std::uint32_t millis;  // total milliseconds; 0 on error
};

// Parses an agent timeout such as "30s", "500ms" or "1h30m" into milliseconds.
ParseResult parse_timeout(const std::string& text);

}  // namespace timeouts
