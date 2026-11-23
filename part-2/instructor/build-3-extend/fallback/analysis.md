# AUD-877 analysis (fallback output of pa-diagnosing-bugs)

## Feedback loop

Command: `build.bat` with one added check in `tests/record_file_test.cpp`:

```cpp
expect("record past 2 GB", legacy::rf_off(3000000, 1024) == 64 + 3072000000LL);
```

Expected on MSVC x64, Clang, or MinGW on Windows: `FAIL: record past 2 GB` (red). Not run: x86, Linux. *(Instructor-written fallback, not a recorded run.)*

## Hypotheses (ranked)

1. `rf_off` overflows a 32-bit intermediate. If so, the check fails for any product above 2^31 and passes below it. **Held:** `rf_off(2097151, 1024)` passes, `rf_off(2097152, 1024)` fails.
2. `rf_cnt` truncates the record count. If so, `rf_cnt` returns less than 3000001 for a 3,072,001,088-byte file. Ruled out: it returns 3000001.
3. The checksum `rf_sum` is wrong for large records. If so, it fails on a 1024-byte buffer. Ruled out: matches a hand-computed sum.

## Cause

`long` is 32-bit on Windows, so `static_cast<long>(idx) * static_cast<long>(rsz)` overflows above 2 GB. Linux CI uses a 64-bit `long` and never sees it.

## Fix and regression test

Compute in `std::int64_t`. The new check is red before the fix and green after on Windows. Linux: green before and after, so CI alone cannot guard this; the PR should ask for a Windows CI job.
