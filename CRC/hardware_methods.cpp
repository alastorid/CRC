#include <cstdint>
#if defined(_M_ARM64)
#include "sse2neon.h"
#elif defined(_M_ARM64EC)
#include <intrin.h>
#else
#include <immintrin.h>
#endif

// for these approaches, the poly CANNOT be changed, because these approaches
// use x86 hardware instructions which hardcode this poly internally.
static constexpr uint32_t P = 0x82f63b78U;

// x86 helper
#ifdef _M_IX86
__forceinline uint64_t _mm_crc32_u64(uint64_t crc, uint64_t value) {
    uint32_t low = value & 0xFFFFFFFF;
    uint32_t high = (value >> 32) & 0xFFFFFFFF;

    crc = _mm_crc32_u32((uint32_t)crc, low);
    crc = _mm_crc32_u32((uint32_t)crc, high);

    return crc;
}
// Extracts the lower 64 bits from a 128-bit SIMD (__m128i) register
__forceinline int64_t _mm_cvtsi128_si64(__m128i a) {
    int64_t result;
    _mm_storel_epi64((__m128i*) & result, a);
    return result;
}
// Loads a 64-bit integer into the lower part of a 128-bit SIMD
__forceinline __m128i _mm_cvtsi64_si128(int64_t a) {
    __m128i result = _mm_setzero_si128();
    return _mm_loadl_epi64((__m128i*) & a);
}
#endif

// OPTION 11
uint32_t option_11_hardware_1_byte(const void* M, uint32_t bytes)
{
    const uint8_t* M8 = (const uint8_t*)M;
    uint32_t R = 0;
    for (uint32_t i = 0; i < bytes; ++i)
    {
        R = _mm_crc32_u8(R, M8[i]);
    }
    return R;
}

// OPTION 12
uint32_t option_12_hardware_8_bytes(const void* M, uint32_t bytes)
{
    const uint64_t* M64 = (const uint64_t*)M;
    uint64_t R = 0;
    for (uint32_t i = 0; i < bytes >> 3; ++i)
    {
        R = _mm_crc32_u64(R, M64[i]);
    }
    return (uint32_t)R;
}
