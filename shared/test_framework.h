/* ============================================================================
 * 단순 단위 테스트 프레임워크 (헤더만 포함)
 * - 각 test_xxx.c 의 main 에서 매크로를 사용하여 케이스를 작성한다.
 * - 의존성 없이 stdio.h / stdint.h 만 사용한다.
 * ========================================================================== */
#ifndef WEEK02_TEST_FRAMEWORK_H
#define WEEK02_TEST_FRAMEWORK_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>

static int g_test_passed = 0;
static int g_test_failed = 0;

#define TEST_BEGIN(name)                                                                           \
    do {                                                                                           \
        printf("\n[TEST] %s\n", (name));                                                           \
    } while (0)

#define TEST_ASSERT(cond)                                                                          \
    do {                                                                                           \
        if (cond) {                                                                                \
            ++g_test_passed;                                                                       \
            printf("  PASS  %s\n", #cond);                                                         \
        } else {                                                                                   \
            ++g_test_failed;                                                                       \
            printf("  FAIL  %s   (line %d)\n", #cond, __LINE__);                                   \
        }                                                                                          \
    } while (0)

#define TEST_ASSERT_EQ_U32(actual, expected)                                                       \
    do {                                                                                           \
        const uint32_t _a = (uint32_t)(actual);                                                    \
        const uint32_t _e = (uint32_t)(expected);                                                  \
        if (_a == _e) {                                                                            \
            ++g_test_passed;                                                                       \
            printf("  PASS  %s == 0x%08X\n", #actual, _e);                                         \
        } else {                                                                                   \
            ++g_test_failed;                                                                       \
            printf("  FAIL  %s : got 0x%08X, expected 0x%08X (line %d)\n", #actual, _a, _e,        \
                   __LINE__);                                                                      \
        }                                                                                          \
    } while (0)

#define TEST_ASSERT_EQ_INT(actual, expected)                                                       \
    do {                                                                                           \
        const long _a = (long)(actual);                                                            \
        const long _e = (long)(expected);                                                          \
        if (_a == _e) {                                                                            \
            ++g_test_passed;                                                                       \
            printf("  PASS  %s == %ld\n", #actual, _e);                                            \
        } else {                                                                                   \
            ++g_test_failed;                                                                       \
            printf("  FAIL  %s : got %ld, expected %ld (line %d)\n", #actual, _a, _e, __LINE__);   \
        }                                                                                          \
    } while (0)

#define TEST_SUMMARY_AND_RETURN()                                                                  \
    do {                                                                                           \
        printf("\n[SUMMARY] passed=%d  failed=%d\n", g_test_passed, g_test_failed);                \
        return (g_test_failed == 0) ? 0 : 1;                                                       \
    } while (0)

#endif /* WEEK02_TEST_FRAMEWORK_H */
