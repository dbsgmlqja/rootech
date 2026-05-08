#include "fsm.h"
#include "test_framework.h"

static void feed(Fsm_t *f, const uint8_t *bytes, uint8_t n) {
    for (uint8_t i = 0; i < n; ++i) {
        fsm_step(f, EV_BYTE, bytes[i]);
    }
}

int main(void) {
    Fsm_t fsm;
    fsm_init(&fsm);

    TEST_BEGIN("normal frame");
    {
        const uint8_t frame[] = {0x02, 0x03, 0xAA, 0xBB, 0xCC, 0x03};
        feed(&fsm, frame, sizeof(frame));
        TEST_ASSERT(fsm.frame_ready);
        TEST_ASSERT_EQ_INT(fsm.payload_len, 3);
        TEST_ASSERT_EQ_U32(fsm.payload[0], 0xAAU);
    }

    TEST_BEGIN("missing STX");
    {
        fsm_init(&fsm);
        const uint8_t frame[] = {0xFF, 0x02, 0xAA, 0x03};
        feed(&fsm, frame, sizeof(frame));
        TEST_ASSERT(!fsm.frame_ready);
    }

    TEST_BEGIN("reset event returns to IDLE");
    {
        fsm_init(&fsm);
        fsm_step(&fsm, EV_BYTE, 0x02);
        fsm_step(&fsm, EV_BYTE, 0x05);
        fsm_step(&fsm, EV_RESET, 0x00);
        TEST_ASSERT_EQ_INT((int)fsm.state, (int)ST_IDLE);
    }

    TEST_SUMMARY_AND_RETURN();
}
