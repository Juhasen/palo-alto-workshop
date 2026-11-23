# record_file: how it works today

*Fallback output of `document-module` for Build 3 option B, written by the instructor. Saved by the skill as `docs/modules/record_file.md`.*

## Summary

`record_file` describes audit log files in format v2: a 64-byte header followed by records of one fixed size. It computes where a record starts, how many whole records a file holds, whether a file size is well formed, and a 16-bit checksum of a record's bytes. It does no I/O; callers pass sizes and buffers in.

## Findings

### Record offsets are the 64-byte header plus index times record size, multiplied in `long`

`rf_off(idx, rsz)` returns `RF_HDR + idx * rsz` (`src/record_file.cpp:5-8`). The product is computed in `long` (`src/record_file.cpp:6`) and returned as `std::int64_t`. `long` is 32-bit on Windows (x86 and x64) and 64-bit on Linux, so on Windows the product overflows once it exceeds 2,147,483,647 bytes.

### Record count ignores a partial trailing record

`rf_cnt(fsz, rsz)` returns `(fsz - RF_HDR) / rsz` in 64-bit arithmetic, cast to `std::uint32_t` (`src/record_file.cpp:10-13`). It returns 0 when `rsz` is 0 or the file is smaller than the header.

### A well-formed file is exactly the header plus whole records

`rf_ok(fsz, rsz)` is true when `(fsz - RF_HDR) % rsz == 0`, and false for `rsz` 0 or a file smaller than the header (`src/record_file.cpp:15-18`).

### The checksum is a 16-bit additive sum of the bytes

`rf_sum(p, n)` adds each byte modulo 65536 (`src/record_file.cpp:20-24`).

## Tests

`tests/record_file_test.cpp` covers small offsets, counts with and without a partial record, `rf_ok` true and false, and one checksum (7 checks, read; run with `build.bat`). No test covers offsets above 2 GB, `rsz` of 0, or files smaller than the header. CI runs on Linux only (`CLAUDE.md`), where `long` is 64-bit.

## Open questions

- Why the header is 64 bytes and whether format v1 differs: not recorded in the code.
- Whether callers ever pass `rsz` 0.

## Fact-check

| Claim | Verdict | Evidence |
|---|---|---|
| Offset is header plus index times record size | verified | `src/record_file.cpp:6-7` |
| Product computed in `long` | verified | `src/record_file.cpp:6` |
| Count ignores a partial record | verified | `src/record_file.cpp:12`, test "count ignores partial" |
| `rf_ok` false for `rsz` 0 | verified | `src/record_file.cpp:16` |
| Checksum modulo 65536 | verified | `src/record_file.cpp:22` |
| ~~Offsets are 64-bit on every platform~~ | wrong, removed | `src/record_file.cpp:6` uses `long` |
