#include "prx/libc/include/general/VabiMacros.hpp"

#include <cstdint>
#include <cstdio>
#include <cstdlib>

extern "C" {
std::int32_t APS5_VABI sceDiscMapIsRequestOnHDD(const char* path, std::int64_t offset, std::int64_t size, std::int32_t* result);
std::int32_t APS5_VABI sceDiscMapUnknown_ioKMruft1ek(const char* path, std::int64_t offset, std::int64_t size, std::uint64_t* flags, std::uint64_t* out1, std::uint64_t* out2);
std::int32_t APS5_VABI sceDiscMapUnknown_fJgP_wqifno(const char* path, std::int64_t offset, std::int64_t size, std::int64_t* location, std::int64_t* lba, std::int64_t* lbaCount);
}

namespace {

constexpr std::int32_t noBitmapInfo = static_cast<std::int32_t>(0x81100004);

void Require(bool condition, const char* message) {
    if (!condition) {
        std::fprintf(stderr, "DiscMap: %s\n", message);
        std::abort();
    }
}

}

int main() {
    std::int32_t result = 0x5a5a5a5a;
    Require(sceDiscMapIsRequestOnHDD("/app0/data.bin", 0, 0x10000, &result) == noBitmapInfo, "sceDiscMapIsRequestOnHDD did not report the missing bitmap");
    Require(result == 0x5a5a5a5a, "sceDiscMapIsRequestOnHDD wrote its result");
    std::uint64_t flags = ~0ull;
    std::uint64_t out1 = ~0ull;
    std::uint64_t out2 = ~0ull;
    Require(sceDiscMapUnknown_ioKMruft1ek("/app0/data.bin", 0x8000, 0x10000, &flags, &out1, &out2) == noBitmapInfo, "ioKMruft1ek did not report the missing bitmap");
    Require(flags == ~0ull && out1 == ~0ull && out2 == ~0ull, "ioKMruft1ek wrote an output");
    std::int64_t location = -1;
    std::int64_t lba = -1;
    std::int64_t lbaCount = -1;
    Require(sceDiscMapUnknown_fJgP_wqifno("/app0/data.bin", 0x8000, 0x10000, &location, &lba, &lbaCount) == noBitmapInfo, "fJgP+wqifno did not report the missing bitmap");
    Require(location == -1 && lba == -1 && lbaCount == -1, "fJgP+wqifno wrote an output");
    std::puts("DiscMap tests passed");
    return 0;
}
