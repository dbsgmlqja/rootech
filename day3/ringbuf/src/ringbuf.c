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

    /* TODO */

    rb->head = 0;
    rb->tail = 0;
}

bool rb_push(RingBuf_t *rb, uint8_t d) {

    /* TODO */
    uint16_t next = (uint16_t)((rb->head + 1U) & (RB_SIZE - 1U));
    if (next == rb->tail) {
        return false;
    }
    rb->buf[rb->head] = d;
    rb->head          = next;

    return true;
}

bool rb_pop(RingBuf_t *rb, uint8_t *out) {

    /* TODO */
    if (rb->head == rb->tail) {
        return false;
    }

    *out = rb->buf[rb->tail];

    rb->tail = (uint16_t)((rb->tail + 1U) & (RB_SIZE - 1U));

    return true;
}

uint16_t rb_size(const RingBuf_t *rb) {

    /* TODO */
    return ((rb->head - rb->tail) & (RB_SIZE - 1U));
}

bool rb_empty(const RingBuf_t *rb) {

    /* TODO */
    return (rb->head == rb->tail); // empty, 즉 비어있으면 true
}

bool rb_full(const RingBuf_t *rb) {

    /* TODO */
    uint16_t next = (uint16_t)((rb->head + 1U) & (RB_SIZE - 1U));
    return (next == rb->tail); // full, 즉 가득 찼으면 true
}
