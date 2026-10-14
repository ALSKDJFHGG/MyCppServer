#include <cstdlib>
#include <limits>
#include <cassert>
#include <hs/macros.h>

static_assert(sizeof(u8) == 1 && std::is_unsigned_v<u8>);
static_assert(sizeof(s8) == 1 && std::is_signed_v<s8>);
static_assert(sizeof(u16) == 2 && std::is_unsigned_v<u16>);
static_assert(sizeof(s16) == 2 && std::is_signed_v<s16>);
static_assert(sizeof(u32) == 4 && std::is_unsigned_v<u32>);
static_assert(sizeof(s32) == 4 && std::is_signed_v<s32>);
static_assert(sizeof(u64) == 8 && std::is_unsigned_v<u64>);
static_assert(sizeof(s64) == 8 && std::is_signed_v<s64>);
static_assert(INVALID8 == MAX_U8);
static_assert(INVALID16 == MAX_U16);
static_assert(INVALID32 == MAX_U32);
static_assert(INVALID64 == MAX_U64);
static_assert(MAX_U8 == std::numeric_limits<u8>::max());
static_assert(MAX_U16 == std::numeric_limits<u16>::max());
static_assert(MAX_U32 == std::numeric_limits<u32>::max());
static_assert(MAX_U64 == std::numeric_limits<u64>::max());

void test_runtime() {
    ASSERT_NOEFFECT(sizeof(u8) == 1 && std::is_unsigned_v<u8>);
    ASSERT_NOEFFECT(sizeof(s8) == 1 && std::is_signed_v<s8>);
    ASSERT_NOEFFECT(sizeof(u16) == 2 && std::is_unsigned_v<u16>);
    ASSERT_NOEFFECT(sizeof(s16) == 2 && std::is_signed_v<s16>);
    ASSERT_NOEFFECT(sizeof(u32) == 4 && std::is_unsigned_v<u32>);
    ASSERT_NOEFFECT(sizeof(s32) == 4 && std::is_signed_v<s32>);
    ASSERT_NOEFFECT(sizeof(u64) == 8 && std::is_unsigned_v<u64>);
    ASSERT_NOEFFECT(sizeof(s64) == 8 && std::is_signed_v<s64>);
    ASSERT_NOEFFECT(INVALID8 == MAX_U8);
    ASSERT_NOEFFECT(INVALID16 == MAX_U16);
    ASSERT_NOEFFECT(INVALID32 == MAX_U32);
    ASSERT_NOEFFECT(INVALID64 == MAX_U64);
    ASSERT_RETNONE(MAX_U8 == std::numeric_limits<u8>::max());
    ASSERT_RETNONE(MAX_U16 == std::numeric_limits<u16>::max());
    ASSERT_RETNONE_INFO(MAX_U32 == std::numeric_limits<u32>::max(), "max number");
    ASSERT_RETNONE_INFO(MAX_U64 == std::numeric_limits<u64>::max(), "max number");
}

int main() {
    test_runtime();

    return EXIT_SUCCESS;
}