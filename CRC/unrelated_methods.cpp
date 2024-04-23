#include <cstdint>
#include <cstdio>

// OPTION aa
uint32_t option_aa_not_crc_but_xor1b(const void* M, uint32_t bytes) {
    const uint8_t* data = (const uint8_t*)M;
    uint8_t R = 0;

    for (uint32_t i = 0; i < bytes; ++i) {
        R ^= data[i];
    }

    return R;
}
