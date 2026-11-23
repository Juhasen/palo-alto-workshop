# AUD-877: Windows agents read wrong audit records in large files

*Plain-text copy of a Jira bug. With the Jira connector, use a real bug ticket of yours in Build 4.*

**Type:** Bug · **Priority:** High · **Component:** audit-reader · **Affects:** Windows agent 7.4

## Description

Since audit files started passing 2 GB, the Windows agent shows corrupted entries when an operator opens late records (around record 3,000,000 in the nightly file, record size 1024 bytes). The checksum check then fails and the entry is dropped.

The Linux collector reads the same file correctly. Small files are fine on both.

## Steps to reproduce

1. Take a nightly audit file larger than 2 GB (record size 1024).
2. On a Windows agent, open record 3000000.
3. Observe the checksum error in the agent log: `rf_sum mismatch at record 3000000`.

## Expected

The record at byte offset 64 + 3000000 × 1024 = 3072000064 is read, on every platform.

## Notes

The reading code is `legacy::rf_off` / `rf_cnt` in `record_file.cpp`. No one on the team has touched it in years. Unit tests pass on CI (Linux).
