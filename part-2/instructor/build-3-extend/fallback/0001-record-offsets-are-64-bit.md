# 1. Record offsets are computed in 64 bits

**Status:** Accepted (AUD-877)

**Context:** Audit files grew past 2 GB. `rf_off` multiplied in `long`, which is 32-bit on Windows and 64-bit on Linux, so Windows agents read wrong records while Linux CI passed.

**Decision:** All byte offsets and sizes in `record_file` use `std::int64_t`. Never use `long` or `unsigned long` for sizes or offsets.

**Consequences:** One fix covers x86 and x64 Windows. CI on Linux cannot catch a regression, so the module needs a Windows build in CI.
