# Build 2 — Instructor material

| File | Use |
|---|---|
| `ticket-to-pr/SKILL.md` | Reference pipeline skill. Show it at about 1:15, after participants have run their own. |
| `timeout_parser.cpp` | Reference solution for NET-1502. Replace `participant/build-2-pipeline/src/timeout_parser.cpp` to check it. |
| `timeout_parser_test.cpp` | 35 checks covering every acceptance criterion. Replace the participant test file to grade a solution. |
| `fallback/spec.md` | A ready spec. If a participant's spec step fails, they save it as `.scratch/NET-1502/spec.md` and continue from stage 3. |

Verified with GCC 13 and Clang on Linux x64 (`-Wall -Wextra -Wconversion -Werror`). Not run: MSVC, x86.
