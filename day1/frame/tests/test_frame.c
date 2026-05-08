#include "frame.h"
#include "test_framework.h"

#include <string.h>

int main(void) {
    /* ---- 정상 직렬화 / 역직렬화 ---- */
    TEST_BEGIN("serialize -> deserialize round trip");
    {
        Frame_t in  = {.stx = FRAME_STX, .cmd = 0x10, .seq = 0xABCD, .value = 0xDEADBEEF};
        in.cksm     = 0x10 ^ 0xAB ^ 0xCD ^ 0xDE ^ 0xAD ^ 0xBE ^ 0xEF;
        uint8_t buf[FRAME_SIZE] = {0};

        TEST_ASSERT_EQ_INT(frame_serialize(&in, buf, sizeof(buf)), FRAME_SIZE);
        TEST_ASSERT_EQ_U32(buf[0], FRAME_STX);
        TEST_ASSERT_EQ_U32(buf[2], 0xABU); /* seq high (big-endian) */
        TEST_ASSERT_EQ_U32(buf[3], 0xCDU); /* seq low */
        TEST_ASSERT_EQ_U32(buf[4], 0xDEU); /* value MSB */
        TEST_ASSERT_EQ_U32(buf[7], 0xEFU); /* value LSB */

        Frame_t out = {0};
        TEST_ASSERT(frame_deserialize(buf, FRAME_SIZE, &out));
        TEST_ASSERT_EQ_U32(out.cmd, in.cmd);
        TEST_ASSERT_EQ_U32(out.seq, in.seq);
        TEST_ASSERT_EQ_U32(out.value, in.value);
    }

    /* ---- 비정상 케이스 ---- */
    TEST_BEGIN("invalid frames return false");
    {
        Frame_t out                = {0};
        const uint8_t no_stx[FRAME_SIZE]   = {0xFF};
        const uint8_t too_short[3]         = {FRAME_STX, 0x10, 0x00};
        uint8_t       bad_cksm[FRAME_SIZE] = {FRAME_STX, 0x10, 0xAB, 0xCD, 0xDE, 0xAD, 0xBE,
                                              0xEF,      0x00};

        TEST_ASSERT(!frame_deserialize(no_stx,    FRAME_SIZE, &out));
        TEST_ASSERT(!frame_deserialize(too_short, sizeof(too_short), &out));
        TEST_ASSERT(!frame_deserialize(bad_cksm,  FRAME_SIZE, &out));
    }

    TEST_SUMMARY_AND_RETURN();
}
