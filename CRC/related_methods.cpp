#include <intrin.h>

// poly 0x04C11DB7
// https://developer.arm.com/documentation/dui0801/h/A64-General-Instructions/CRC32B--CRC32H--CRC32W--CRC32X
uint32_t option_aa_hardware_8_bytes_aarch64_poly1(const void* M, uint32_t bytes, uint32_t prev/* = 0*/)
{
    uint64_t pA = (uint64_t)M;
    //uint64_t crcA = (uint64_t)(uint32_t)(~prev); // if you want to invert prev
    uint64_t crcA = prev;
    uint32_t toAlign = ((uint64_t)-(int64_t)pA) & 7;

    for (; toAlign && bytes; ++pA, --bytes, --toAlign)
        crcA = __crc32b((uint32_t)crcA, *(uint8_t*)pA);

    for (; bytes >= 8; bytes -= 8, pA += 8)
        crcA = __crc32d(crcA, *(uint64_t*)(pA));

    for (; bytes; --bytes, ++pA)
        crcA = __crc32b((uint32_t)crcA, *(uint8_t*)(pA));

    //return ~(uint32_t)crcA; // if you want to invert the result
    return (uint32_t)crcA;
}

// poly 0x1EDC6F41
// https://developer.arm.com/documentation/dui0801/h/A64-General-Instructions/CRC32CB--CRC32CH--CRC32CW--CRC32CX
uint32_t option_aa_hardware_8_bytes_aarch64_poly2(const void* M, uint32_t bytes, uint32_t prev/* = 0*/)
{
    uint64_t pA = (uint64_t)M;
    //uint64_t crcA = (uint64_t)(uint32_t)(~prev); // if you want to invert prev
    uint64_t crcA = prev;
    uint32_t toAlign = ((uint64_t)-(int64_t)pA) & 7;

    for (; toAlign && bytes; ++pA, --bytes, --toAlign)
        crcA = __crc32cb((uint32_t)crcA, *(uint8_t*)pA);

    for (; bytes >= 8; bytes -= 8, pA += 8)
        crcA = __crc32cd(crcA, *(uint64_t*)(pA));

    for (; bytes; --bytes, ++pA)
        crcA = __crc32cb((uint32_t)crcA, *(uint8_t*)(pA));

    //return ~(uint32_t)crcA; // if you want to invert the result
    return (uint32_t)crcA;
}
