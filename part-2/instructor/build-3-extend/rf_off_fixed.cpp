// Reference fix for AUD-877: replace rf_off in src/record_file.cpp with this.
std::int64_t rf_off(std::uint32_t idx, std::uint32_t rsz) {
    // 64-bit on every platform: long is 32-bit on Windows.
    return RF_HDR + static_cast<std::int64_t>(idx) * static_cast<std::int64_t>(rsz);
}
