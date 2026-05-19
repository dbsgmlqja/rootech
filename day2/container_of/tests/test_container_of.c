#include "container_of.h"
#include "test_framework.h"

#include <stddef.h>
#include <stdint.h>

typedef struct ListNode {
    struct ListNode *next;
} ListNode_t;

typedef struct {
    int        id;
    ListNode_t link; //= n
    char       name[16];
} Task_t; //= t

typedef struct {
    ListNode_t link;
    int        priority;
} PriorityNode_t;

int main(void) {
    TEST_BEGIN("container_of recovers struct from member");
#ifdef container_of
    {
        Task_t      t   = {.id = 7, .link = {NULL}, .name = "led"};
        ListNode_t *n   = &t.link;
        Task_t     *got = container_of(n, Task_t, link);
        TEST_ASSERT(got == &t);
        TEST_ASSERT_EQ_INT(got->id, 7);

        PriorityNode_t  pn  = {.link = {NULL}, .priority = 99};
        ListNode_t     *pl  = &pn.link;
        PriorityNode_t *gpn = container_of(pl, PriorityNode_t, link);
        TEST_ASSERT(gpn == &pn);
        TEST_ASSERT_EQ_INT(gpn->priority, 99);
    }
#else
    TEST_BEGIN("container_of macro is not defined yet (TODO)");
    g_test_failed++;
#endif

    TEST_SUMMARY_AND_RETURN();
}
