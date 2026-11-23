#include "record_file.hpp"

namespace legacy {

std::int64_t rf_off(std::uint32_t idx, std::uint32_t rsz) {
    long o = static_cast<long>(idx) * static_cast<long>(rsz);
    return RF_HDR + o;
}

std::uint32_t rf_cnt(std::int64_t fsz, std::uint32_t rsz) {
    if (rsz == 0 || fsz < RF_HDR) return 0;
    return static_cast<std::uint32_t>((fsz - RF_HDR) / rsz);
}

bool rf_ok(std::int64_t fsz, std::uint32_t rsz) {
    if (rsz == 0 || fsz < RF_HDR) return false;
    return (fsz - RF_HDR) % rsz == 0;
}

std::uint16_t rf_sum(const unsigned char* p, std::size_t n) {
    std::uint32_t s = 0;
    for (std::size_t i = 0; i < n; ++i) s = (s + p[i]) & 0xFFFFu;
    return static_cast<std::uint16_t>(s);
}

}  // namespace legacy
