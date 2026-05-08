/* ============================================================================
 * ringbuf.c
 *
 * TODO (멘티 작성):
 *  - SPSC lock-free 패턴: producer 는 head 만, consumer 는 tail 만 갱신한다.
 *  - 모듈러는 (idx + 1) & (RB_SIZE - 1) 로 처리한다.
 *  - rb_push 는 head 가 tail 을 따라잡으면 false (full).
 *  - rb_pop 은 head == tail 이면 false (empty).
 * ========================================================================== */
#include "ringbuf.h"

void rb_init(RingBuf_t *rb) {
    (void)rb;
    /* TODO */
}

bool rb_push(RingBuf_t *rb, uint8_t d) {
    (void)rb;
    (void)d;
    /* TODO */
    return false;
}

bool rb_pop(RingBuf_t *rb, uint8_t *out) {
    (void)rb;
    (void)out;
    /* TODO */
    return false;
}

uint16_t rb_size(const RingBuf_t *rb) {
    (void)rb;
    /* TODO */
    return 0U;
}

bool rb_empty(const RingBuf_t *rb) {
    (void)rb;
    /* TODO */
    return true;
}

bool rb_full(const RingBuf_t *rb) {
    (void)rb;
    /* TODO */
    return false;
}
