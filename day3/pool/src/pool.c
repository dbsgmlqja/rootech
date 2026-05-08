/* ============================================================================
 * pool.c
 *
 * TODO (멘티 작성):
 *  - 32 개의 64-byte 블록을 정적 배열로 확보한다.
 *  - free list 를 단방향 링크드 리스트로 관리한다.
 *  - pool_alloc 는 풀 고갈 시 NULL 반환.
 *  - pool_free 는 double-free 또는 풀 외부 포인터를 감지하여 false 반환.
 * ========================================================================== */
#include "pool.h"

void pool_init(void) {
    /* TODO */
}

void *pool_alloc(void) {
    /* TODO */
    return NULL;
}

bool pool_free(void *p) {
    (void)p;
    /* TODO */
    return false;
}
