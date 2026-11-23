# Build 3 repository notes

- Legacy module from 1998: keep the `rf_*` names and signatures in `include/record_file.hpp`.
- C++17 only; the legacy target is MSVC 19.16 (Visual Studio 2017). Build and test with `build.bat`. Warnings are errors.
- `long` and `unsigned long` are 32-bit on Windows x86 and x64; 64-bit on Linux. CI runs Linux only.
- Tickets, analysis, and specs live under `.scratch/`. No network calls.
