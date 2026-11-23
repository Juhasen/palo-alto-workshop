# Build 2 repository notes

- C++17 only; the legacy target is MSVC 19.16 (Visual Studio 2017). No C++20 features.
- Build and test with `build.bat` (detects `cl`, `clang++`, or `g++`). Warnings are errors.
- `include/timeout_parser.hpp` is the public contract; keep its signatures.
- `unsigned long` and `long` are 32-bit on Windows (x86 and x64); `size_t` is 32-bit on x86. Check overflow before multiplying or adding, not after.
- Tickets and specs live under `.scratch/` (see `docs/agents/issue-tracker.md`). No network calls.
