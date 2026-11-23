# Glossary: audit record files

**Record file** — An audit log file: a 64-byte header followed by fixed-size records. Format v2 (1998).
**Header** (`RF_HDR`) — The first 64 bytes of a record file.
**Record size** (`rsz`) — Bytes per record, fixed for one file. Never 0.
**File size** (`fsz`) — Total bytes in the file, header included. 64-bit: files exceed 4 GB.
**Record index** (`idx`) — Zero-based position of a record. 32-bit unsigned.
**Record offset** (`rf_off`) — Byte position of a record: header plus index times record size.
**Record count** (`rf_cnt`) — Number of whole records after the header; a partial trailing record is not counted.
**Well-formed file** (`rf_ok`) — A file whose size is exactly the header plus a whole number of records.
**Record checksum** (`rf_sum`) — 16-bit additive sum of a record's bytes, modulo 65536.
