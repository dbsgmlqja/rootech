/* ============================================================================
 * 미션 1 - SPSC Lock-free 링버퍼
 * - 크기는 2의 거듭제곱 (모듈러를 비트 마스크로 처리)
 * ========================================================================== */
#ifndef RINGBUF_H
#define RINGBUF_H

#include <stdbool.h>
#include <stdint.h>

#define RB_SIZE 64U

_Static_assert((RB_SIZE & (RB_SIZE - 1U)) == 0U, "RB_SIZE 는 2의 거듭제곱이어야 한다");

typedef struct {
    uint8_t           buf[RB_SIZE];
    volatile uint16_t head; /* producer 만 수정 */
    volatile uint16_t tail; /* consumer 만 수정 */
} RingBuf_t;

void     rb_init (RingBuf_t *rb);
bool     rb_push (RingBuf_t *rb, uint8_t d);
bool     rb_pop  (RingBuf_t *rb, uint8_t *out);
uint16_t rb_size (const RingBuf_t *rb);
bool     rb_empty(const RingBuf_t *rb);
bool     rb_full (const RingBuf_t *rb);

#endif /* RINGBUF_H */
