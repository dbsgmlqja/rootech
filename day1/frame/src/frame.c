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

#define CRC16_INIT_VALUE 0xFFFF
#define CRC16_XOR_VALUE  0x0000

uint8_t read_8bit(uint8_t h);
uint8_t read_16bit(uint16_t h, uint8_t pos);
uint8_t read_32bit(uint32_t h, uint8_t pos);

uint8_t  write_8bit(uint8_t in);
uint16_t write_16bit(uint8_t in, uint8_t pos);
uint32_t write_32bit(uint8_t in, uint8_t pos);

uint16_t CRC16(const uint8_t *data, size_t len);
void     make_CRC_table(void);

size_t frame_serialize(const Frame_t *f, uint8_t *out, size_t out_size) {

    /* TODO */
    make_CRC_table();

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

    // out[8] = (uint8_t)(out[1] ^ out[2] ^ out[3] ^ out[4] ^ out[5] ^ out[6] ^ out[7]);
    uint16_t out_crc = CRC16(out, 8);
    out[8]           = (out_crc >> 8) & 0xFF;
    out[9]           = out_crc & 0xFF;
    // CRC 값도 Big-Endian으로 변환

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

    // out->cksm = (uint8_t)(in[1] ^ in[2] ^ in[3] ^ in[4] ^ in[5] ^ in[6] ^ in[7]);
    uint16_t in_crc = (uint16_t)((in[8] << 8) | in[9]);

    uint16_t calc_crc = CRC16(in, 8);

    if (in_crc != calc_crc) {
        return false;
    }

    return true;
    /* TODO */
}

// read & write 함수
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

// CRC Table 생성 함수
static unsigned short CRCtable[256];

// 16 CRC polynomial : x^16 + x^12 + x^5 + 1 임.

void make_CRC_table(void) {

    int i, j;

    unsigned long poly, c;

    static const uint8_t p[] = {0, 5, 12}; // 16은 최고차항이라 제외

    poly = 0L;

    for (i = 0; i < sizeof(p) / sizeof(uint8_t); i++) {
        poly |= 1L << p[i];
    }

    for (i = 0; i < 256; i++) {
        c = i << 8;

        for (j = 0; j < 8; j++) {

            c = (c & 0x8000) ? poly ^ (c << 1) : (c << 1);
        }

        CRCtable[i] = (unsigned short)c;
    }
}

// Table에서 값 가져오는 함수
uint16_t CRC16(const uint8_t *data, size_t len) {

    uint16_t CRC = 0xFFFF;

    for (size_t i = 0; i < len; i++) {

        uint8_t index = ((CRC >> 8) ^ data[i] & 0xFF);

        CRC = (CRC << 8) ^ CRCtable[index];
    }

    return CRC;
}
