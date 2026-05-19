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
uint8_t read_8bit(uint8_t h);
uint8_t read_16bit(uint16_t h, uint8_t pos);
uint8_t read_32bit(uint32_t h, uint8_t pos);

uint8_t  write_8bit(uint8_t in);
uint16_t write_16bit(uint8_t in, uint8_t pos);
uint32_t write_32bit(uint8_t in, uint8_t pos);

size_t frame_serialize(const Frame_t *f, uint8_t *out, size_t out_size) {

    /* TODO */
    if (out_size < FRAME_SIZE) {
        return 0;
    }

    uint8_t  width = 8;
    uint16_t mask  = (uint16_t)(1U << width) - 1;
    /*
     out[0] = (uint8_t)(f->stx & mask);
     out[1] = (uint8_t)(f->cmd & mask);
     out[2] = (uint8_t)(f->seq >> 8 & mask);
     out[3] = (uint8_t)(f->seq & mask);
     out[4] = (uint8_t)(f->value >> 24 & mask);
     out[5] = (uint8_t)(f->value >> 16 & mask);
     out[6] = (uint8_t)(f->value >> 8 & mask);
     out[7] = (uint8_t)(f->value & mask);
     */
    // 이것들이 bit_read.

    out[0] = read_8bit(f->stx);
    out[1] = read_8bit(f->cmd);
    out[2] = read_16bit(f->seq, 1);
    out[3] = read_16bit(f->seq, 0);
    out[4] = read_32bit(f->value, 3);
    out[5] = read_32bit(f->value, 2);
    out[6] = read_32bit(f->value, 1);
    out[7] = read_32bit(f->value, 0);

    out[8] = (uint8_t)(out[1] ^ out[2] ^ out[3] ^ out[4] ^ out[5] ^ out[6] ^ out[7]);

    return out_size;
}

bool frame_deserialize(const uint8_t *in, size_t in_len, Frame_t *out) {

    if (in_len > FRAME_SIZE) {
        return false;
    }

    if (in[0] != FRAME_STX) {
        return false;
    }

    uint8_t width = 8;
    uint8_t start = 8;

    /*
    out->stx   = (uint8_t)in[0];
    out->cmd   = (uint8_t)in[1];
    out->seq   = (uint16_t)((in[2] << 8) | in[3]);
    out->value = (uint32_t)(in[4] << 24 | in[5] << 16 | in[6] << 8 | in[7]);
    out->cksm  = (uint8_t)(in[1] ^ in[2] ^ in[3] ^ in[4] ^ in[5] ^ in[6] ^ in[7]);
    */

    // write_16bit(&out->seq, in[2], 1);
    // write_16bit(&out->seq, in[3], 0);

    out->stx   = write_8bit(in[0]);
    out->cmd   = write_8bit(in[1]);
    out->seq   = write_16bit(in[2], 1) | write_16bit(in[3], 0);
    out->value = write_32bit(in[4], 3) | write_32bit(in[5], 2) | write_32bit(in[6], 1) |
                 write_32bit(in[7], 0);

    out->cksm = (uint8_t)(in[1] ^ in[2] ^ in[3] ^ in[4] ^ in[5] ^ in[6] ^ in[7]);

    /*이 부분에서 비트연산에서 read나 write를 쓸 필요가 있을까?
    기존에 reg같은 부분을 read/write하는 게 아니라 각 데이터를 그냥 넣어주는 의미의 함수인데
    더 복잡해질 것 같은데
    */

    if (out->cksm != in[8]) {
        return false;
    }

    return true;
    /* TODO */
}

uint8_t read_8bit(uint8_t h) {
    return (uint8_t)(h & 0xFFU);
}
uint8_t read_16bit(uint16_t h, uint8_t pos) {
    return (uint16_t)((h >> (pos * 8U)) & 0xFFU);
}
uint8_t read_32bit(uint32_t h, uint8_t pos) {
    return (uint32_t)((h >> (pos * 8U)) & 0xFFU);
}

uint8_t write_8bit(uint8_t in) {
    return in;
}
uint16_t write_16bit(uint8_t in, uint8_t pos) {

    return (uint16_t)(in << (pos * 8U));
    //*h |= ((uint16_t)in << (pos * 8U)); : 바로 struct 참조해서 값 넣는 방식
}
uint32_t write_32bit(uint8_t in, uint8_t pos) {
    return (uint32_t)(in << (pos * 8U));
}
