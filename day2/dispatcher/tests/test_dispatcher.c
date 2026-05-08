#include "dispatcher.h"
#include "test_framework.h"

static int g_call_count_a = 0;
static int g_call_count_b = 0;
static int g_last_ctx_val = 0;

static void handler_a(uint8_t ev, void *ctx) {
    (void)ev;
    (void)ctx;
    ++g_call_count_a;
}

static void handler_b(uint8_t ev, void *ctx) {
    (void)ev;
    if (ctx) {
        g_last_ctx_val = *(int *)ctx;
    }
    ++g_call_count_b;
}

int main(void) {
    dispatcher_init();

    TEST_BEGIN("register / dispatch");
    {
        int ctx_val = 42;
        TEST_ASSERT(dispatcher_register(3U, handler_a, NULL));
        TEST_ASSERT(dispatcher_register(3U, handler_b, &ctx_val));

        dispatcher_dispatch(3U);
        TEST_ASSERT_EQ_INT(g_call_count_a, 1);
        TEST_ASSERT_EQ_INT(g_call_count_b, 1);
        TEST_ASSERT_EQ_INT(g_last_ctx_val, 42);
    }

    TEST_BEGIN("unregister");
    {
        TEST_ASSERT(dispatcher_unregister(3U, handler_a));
        dispatcher_dispatch(3U);
        TEST_ASSERT_EQ_INT(g_call_count_a, 1); /* 더 이상 증가하지 않음 */
        TEST_ASSERT_EQ_INT(g_call_count_b, 2);
    }

    TEST_BEGIN("chain limit");
    {
        TEST_ASSERT(dispatcher_register(5U, handler_a, NULL));
        TEST_ASSERT(dispatcher_register(5U, handler_a, NULL));
        TEST_ASSERT(dispatcher_register(5U, handler_a, NULL));
        TEST_ASSERT(dispatcher_register(5U, handler_a, NULL));
        TEST_ASSERT(!dispatcher_register(5U, handler_a, NULL)); /* 5번째는 거부 */
    }

    TEST_BEGIN("event_id out of range");
    {
        TEST_ASSERT(!dispatcher_register(99U, handler_a, NULL));
    }

    TEST_SUMMARY_AND_RETURN();
}
