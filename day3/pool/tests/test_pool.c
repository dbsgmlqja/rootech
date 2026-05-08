#include "pool.h"
#include "test_framework.h"

int main(void) {
    pool_init();

    TEST_BEGIN("alloc all + 1 returns NULL");
    {
        void *blocks[POOL_BLOCKS] = {0};
        for (uint16_t i = 0; i < POOL_BLOCKS; ++i) {
            blocks[i] = pool_alloc();
            TEST_ASSERT(blocks[i] != NULL);
        }
        TEST_ASSERT(pool_alloc() == NULL); /* 33번째 */

        for (uint16_t i = 0; i < POOL_BLOCKS; ++i) {
            TEST_ASSERT(pool_free(blocks[i]));
        }
    }

    TEST_BEGIN("free + alloc again");
    {
        void *p = pool_alloc();
        TEST_ASSERT(p != NULL);
        TEST_ASSERT(pool_free(p));

        void *q = pool_alloc();
        TEST_ASSERT(q != NULL);
        pool_free(q);
    }

    TEST_BEGIN("double-free is detected");
    {
        void *p = pool_alloc();
        TEST_ASSERT(p != NULL);
        TEST_ASSERT(pool_free(p));
        TEST_ASSERT(!pool_free(p));     /* 두 번째 free 는 거부되어야 함 */
    }

    TEST_BEGIN("free of non-pool pointer is rejected");
    {
        int local = 0;
        TEST_ASSERT(!pool_free(&local));
    }

    TEST_SUMMARY_AND_RETURN();
}
