#include "record_file.hpp"

#include <cstdint>
#include <iostream>

int main() {
    int failures = 0;
    int checks = 0;
    auto expect = [&](const char* name, bool ok) {
        ++checks;
        if (!ok) { std::cerr << "FAIL: " << name << "\n"; ++failures; }
    };

    expect("first record", legacy::rf_off(0, 512) == 64);
    expect("tenth record", legacy::rf_off(10, 512) == 64 + 5120);
    expect("count", legacy::rf_cnt(64 + 3 * 512, 512) == 3);
    expect("count ignores partial", legacy::rf_cnt(64 + 3 * 512 + 7, 512) == 3);
    expect("ok", legacy::rf_ok(64 + 2 * 100, 100));
    expect("not ok", !legacy::rf_ok(64 + 2 * 100 + 1, 100));
    const unsigned char bytes[] = {1, 2, 3, 250};
    expect("checksum", legacy::rf_sum(bytes, 4) == 256);

    if (failures == 0) { std::cout << "OK: " << checks << " checks passed\n"; return 0; }
    std::cerr << failures << " of " << checks << " check(s) failed\n";
    return 1;
}
