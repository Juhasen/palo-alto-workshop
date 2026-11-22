#pragma once
// rf: fixed-size record files (audit log format v2, 1998).
#include <cstddef>
#include <cstdint>

namespace legacy {

const std::int64_t RF_HDR = 64;  // header bytes

std::int64_t rf_off(std::uint32_t idx, std::uint32_t rsz);           // byte offset of record idx
std::uint32_t rf_cnt(std::int64_t fsz, std::uint32_t rsz);           // whole records in file
bool rf_ok(std::int64_t fsz, std::uint32_t rsz);                     // size is hdr + n*rsz
std::uint16_t rf_sum(const unsigned char* p, std::size_t n);         // additive checksum

}  // namespace legacy
