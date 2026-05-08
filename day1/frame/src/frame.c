/* ============================================================================
 * frame.c
 *
 * TODO (멘티 작성):
 *  1. frame_serialize() 를 구현하라.
 *     - seq, value 는 big-endian 으로 직렬화한다.
 *     - cksm 은 cmd ~ value 마지막 바이트까지의 8-bit XOR 이다.
 *  2. frame_deserialize() 를 구현하라.
 *     - in_len 이 FRAME_SIZE 보다 작으면 false.
 *     - in[0] != FRAME_STX 면 false.
 *     - cksm 불일치 시 false.
 *
 * 주의: 호스트 엔디언에 의존하지 말 것. 직접 byte shift 로 처리한다.
 * ========================================================================== */
#include "frame.h"

#include <string.h>

size_t frame_serialize(const Frame_t *f, uint8_t *out, size_t out_size) {
    (void)f;
    (void)out;
    (void)out_size;
    /* TODO */
    return 0;
}

bool frame_deserialize(const uint8_t *in, size_t in_len, Frame_t *out) {
    (void)in;
    (void)in_len;
    (void)out;
    /* TODO */
    return false;
}
