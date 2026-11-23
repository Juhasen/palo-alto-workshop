# NET-1502 spec (fallback output of pa-to-spec)

*Use if the live spec step fails. Saved by the pipeline as `.scratch/NET-1502/spec.md`.*

## Problem Statement

Operators cannot write combined timeouts such as `1h30m`; the parser rejects them. On Windows, very large values such as `5000000h` wrap and become a short timeout instead of an error.

## Solution

`parse_timeout` accepts one or more number-unit parts in descending unit order, sums them, and returns `Overflow` for any total above 4294967295 ms on every build.

## User Stories

1. As an operator, I want to write `1h30m`, so that I do not convert to minutes by hand.
2. As an operator, I want `30m1h` and `1m1m` rejected, so that a typo is not silently accepted.
3. As an operator, I want `5000000h` rejected, so that a typo never becomes a short timeout.
4. As a maintainer, I want existing single-unit values unchanged, so that current configurations keep working.

## Implementation Decisions

- The public function and types in `timeout_parser.hpp` stay as declared.
- Parsing accumulates in a 64-bit unsigned integer and saturates the number before multiplying, so no step can wrap regardless of the width of `long`.
- Units are ranked `h > m > s > ms`; each part's rank must be strictly lower than the previous one.

## Testing Decisions

- One seam: `parse_timeout`, through the public header. Tests assert error and milliseconds together.
- Boundary cases: `4294967295ms`, `4294967296ms`, `1193h` (fits), `1194h` (overflows), `1193h2m47s295ms` (exactly max), a 20-digit number.
- Prior art: the existing checks in `tests/timeout_parser_test.cpp`.

## Out of Scope

Days and weeks, fractional values, reading the configuration file.

## Further Notes

Verify on the x86 MSVC build if one is available; otherwise list it under targets not run.
