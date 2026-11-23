# Build 3 — Instructor notes

## Root cause (AUD-877)

`rf_off` multiplies in `long`. `long` is 32-bit on Windows (LLP64) and 64-bit on Linux (LP64). For record 3000000 with record size 1024, the product 3,072,000,000 exceeds `LONG_MAX` (2,147,483,647) on Windows: signed overflow, undefined behaviour, in practice a wrap to -1,222,967,296, so the reader seeks to a negative offset. Linux CI computes it correctly, which is why the tests and the collector look fine.

The fix: compute in `std::int64_t`. See `rf_off_fixed.cpp`.

Regression test (red on Windows with MSVC, Clang, or MinGW g++; green on Linux before and after the fix):

```cpp
expect("record past 2 GB", legacy::rf_off(3000000, 1024) == 64 + 3072000000LL);
```

## Points to raise

- The red loop only exists on the platform that has the bug. A participant on Linux or WSL must say "could not reproduce here", not "fixed".
- `rf_cnt` is fine: it divides an `int64_t`. Diagnosis should rule it out with a test, not by reading.
- Option B: the reference skill is `document-module/SKILL.md` (with `SOURCE.md`); a fallback module doc is `fallback/record_file.md`. The best moment is the fact-check removing a confident wrong claim such as "offsets are 64-bit" and the doc then stating the `long` multiplication plainly: good documentation surfaces AUD-877 without anyone debugging.
- Option B: good glossary lines name units (bytes, records) and widths. Bad ones restate the function name.
- Option B: if `domain-modeling` asks many questions, tell participants to answer two and skip the rest; the fact-check is the part to protect.
