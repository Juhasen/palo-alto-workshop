# NET-1502: Accept combined units in agent timeouts

*Plain-text copy of a Jira ticket. With the Jira connector, your pipeline reads your own ticket instead; this file is the sample and the paste-in fallback.*

**Type:** Story · **Priority:** Medium · **Component:** agent-config · **Reporter:** platform team

## Description

The agent configuration accepts timeouts such as `connect_timeout = 30s`. Operators now want combined values like `1h30m` and `2m15s`, which today fail with `UnknownUnit`.

There is also a field report that `50d`-style typos are caught, but `5000000h` is accepted on the Windows build and produces a short timeout of a few minutes instead of an error.

Extend `timeouts::parse_timeout(text)` in `include/timeout_parser.hpp`. Keep the declared signature and types.

## Acceptance criteria

1. A timeout is one or more parts, each a decimal number immediately followed by a unit: `ms`, `s`, `m`, `h`. No spaces inside the value; whitespace around the whole value is allowed.
2. Parts are added together: `1h30m` is 5400000 ms, `2m15s` is 135000, `1s500ms` is 1500.
3. Units must appear in strictly descending order (`h`, `m`, `s`, `ms`) and each at most once. `30m1h` and `1m1m` return `InvalidToken`.
4. An empty or whitespace-only value returns `Empty`.
5. A number with no unit (`30`), a unit with no number (`ms`), a sign (`-5s`, `+5s`), or a decimal point (`1.5s`) returns `InvalidToken`. An unknown unit (`5d`, `5sec`) returns `UnknownUnit`.
6. A total above 4294967295 ms returns `Overflow`. This includes digit strings too long for any integer type, and it must hold on 32-bit and 64-bit builds alike.
7. On any error `millis` is 0.
8. Existing single-unit values keep their current results.
9. No new dependency. Builds clean with `/W4 /WX` (MSVC) or `-Wall -Wextra -Wconversion -Werror` (Clang, GCC), C++17.

## Out of scope

Days and weeks, fractional values, reading the value from the configuration file.

## Verification

`build.bat` runs the unit tests. Record the compiler and architecture you ran; a pass on x64 does not prove x86.
