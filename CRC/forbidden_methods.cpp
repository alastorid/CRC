#include <cstdint>
#include <cstdio>
#include <windows.h>

#pragma comment(lib, "ntdll.lib")
uint32_t
(__stdcall *RtlComputeCrc32)(
    uint32_t PartialCrc,
    const void* Buffer,
    uint32_t Length
);

// OPTION ms
uint32_t option_ms_RtlCrc32(const void* M, uint32_t bytes, uint32_t prev/* = 0*/) {
    return RtlCrc32(M, bytes, prev);
}

// OPTION ms2
uint32_t option_ms2_RtlComputeCrc32(const void* M, uint32_t bytes, uint32_t prev/* = 0*/) {
    if (!RtlComputeCrc32)
    {
        auto ntdll = GetModuleHandleA("ntdll.dll");
        if (ntdll)
        {
            RtlComputeCrc32 = decltype(RtlComputeCrc32)(GetProcAddress(ntdll, "RtlComputeCrc32"));
            if (!RtlComputeCrc32)
                __debugbreak();
        }
        else
        {
            __debugbreak();
        }
    }

    return RtlComputeCrc32(prev, M, bytes);
}
