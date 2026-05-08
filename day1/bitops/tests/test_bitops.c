#include "bitops.h"
#include "test_framework.h"

int main(void) {
    /* ---- 단일 비트 ---- */
    TEST_BEGIN("bit_set / bit_clear / bit_toggle / bit_check");
    {
        uint32_t reg = 0x00000000U;
        bit_set(&reg, 5U);
        TEST_ASSERT_EQ_U32(reg, 0x00000020U);

        bit_set(&reg, 31U);
        TEST_ASSERT_EQ_U32(reg, 0x80000020U);

        bit_clear(&reg, 5U);
        TEST_ASSERT_EQ_U32(reg, 0x80000000U);

        bit_toggle(&reg, 0U);
        TEST_ASSERT_EQ_U32(reg, 0x80000001U);

        TEST_ASSERT(bit_check(reg, 0U) == true);
        TEST_ASSERT(bit_check(reg, 1U) == false);
        TEST_ASSERT(bit_check(reg, 31U) == true);
    }

    /* ---- 비트 필드 ---- */
    TEST_BEGIN("field_read / field_write");
    {
        TEST_ASSERT_EQ_U32(field_read(0xABCD1234U, 8U, 8U), 0x12U);
        TEST_ASSERT_EQ_U32(field_read(0xABCD1234U, 0U, 16U), 0x1234U);
        TEST_ASSERT_EQ_U32(field_read(0xFFFFFFFFU, 0U, 32U), 0xFFFFFFFFU);

        TEST_ASSERT_EQ_U32(field_write(0x00000000U, 4U, 4U, 0xAU), 0x000000A0U);
        TEST_ASSERT_EQ_U32(field_write(0xFFFFFFFFU, 4U, 4U, 0x0U), 0xFFFFFF0FU);
        /* 폭 초과 비트는 자동으로 잘려야 함 */
        TEST_ASSERT_EQ_U32(field_write(0x00000000U, 0U, 4U, 0xFFU), 0x0000000FU);
    }

    /* ---- 엔디언 ---- */
    TEST_BEGIN("swap16 / swap32");
    {
        TEST_ASSERT_EQ_U32(swap16(0x1234U), 0x3412U);
        TEST_ASSERT_EQ_U32(swap16(0xFF00U), 0x00FFU);
        TEST_ASSERT_EQ_U32(swap32(0x12345678U), 0x78563412U);
        TEST_ASSERT_EQ_U32(swap32(0xDEADBEEFU), 0xEFBEADDEU);
        TEST_ASSERT_EQ_U32(swap32(0x00000000U), 0x00000000U);
    }

    TEST_SUMMARY_AND_RETURN();
}
