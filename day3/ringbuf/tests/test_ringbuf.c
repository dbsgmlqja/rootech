#include "ringbuf.h"
#include "test_framework.h"

int main(void) {
    RingBuf_t rb;
    rb_init(&rb);

    TEST_BEGIN("empty / full / size");
    {
        TEST_ASSERT(rb_empty(&rb));
        TEST_ASSERT(!rb_full(&rb));
        TEST_ASSERT_EQ_INT(rb_size(&rb), 0);
    }

    TEST_BEGIN("push / pop FIFO order");
    {
        TEST_ASSERT(rb_push(&rb, 0x10U));
        TEST_ASSERT(rb_push(&rb, 0x20U));
        TEST_ASSERT(rb_push(&rb, 0x30U));
        TEST_ASSERT_EQ_INT(rb_size(&rb), 3);

        uint8_t v = 0;
        TEST_ASSERT(rb_pop(&rb, &v));
        TEST_ASSERT_EQ_U32(v, 0x10U);
        TEST_ASSERT(rb_pop(&rb, &v));
        TEST_ASSERT_EQ_U32(v, 0x20U);
        TEST_ASSERT(rb_pop(&rb, &v));
        TEST_ASSERT_EQ_U32(v, 0x30U);
        TEST_ASSERT(rb_empty(&rb));
    }

    TEST_BEGIN("full / wrap-around");
    {
        rb_init(&rb);
        for (uint16_t i = 0; i < RB_SIZE - 1U; ++i) {
            TEST_ASSERT(rb_push(&rb, (uint8_t)i));
        }
        TEST_ASSERT(rb_full(&rb));
        TEST_ASSERT(!rb_push(&rb, 0xFFU));

        uint8_t v = 0;
        TEST_ASSERT(rb_pop(&rb, &v));
        TEST_ASSERT_EQ_U32(v, 0x00U);
        /* 한 칸 빈 상태에서 다시 push 가능 */
        TEST_ASSERT(rb_push(&rb, 0xAAU));
    }

    TEST_BEGIN("pop on empty returns false");
    {
        rb_init(&rb);
        uint8_t v = 0;
        TEST_ASSERT(!rb_pop(&rb, &v));
    }

    TEST_SUMMARY_AND_RETURN();
}
