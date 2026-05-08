/* ============================================================================
 * 미션 3 - Packed 통신 프레임 직렬화 / 역직렬화
 *
 * 프레임 형식 (네트워크 바이트 오더, big-endian):
 *   +-----+-----+-----+-----+-----+
 *   | STX | CMD | SEQ | VAL | CKSM|
 *   |  1  |  1  |  2  |  4  |  1  |   = 9 bytes
 *   +-----+-----+-----+-----+-----+
 * ========================================================================== */
#ifndef FRAME_H
#define FRAME_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define FRAME_STX  0x02U
#define FRAME_SIZE 9U

typedef struct __attribute__((packed)) {
    uint8_t  stx;   /* always FRAME_STX */
    uint8_t  cmd;
    uint16_t seq;   /* big-endian on wire */
    uint32_t value; /* big-endian on wire */
    uint8_t  cksm;  /* XOR(cmd, seq high, seq low, value 4 bytes) */
} Frame_t;

/* 직렬화: 호스트 엔디언과 무관하게 동일한 9바이트 출력
 * 반환값: 작성된 바이트 수 (성공 시 FRAME_SIZE), 실패 시 0
 */
size_t frame_serialize(const Frame_t *f, uint8_t *out, size_t out_size);

/* 역직렬화: stx / 길이 / cksm 을 모두 검증한다
 * 반환값: 성공 시 true, 실패 시 false
 */
bool frame_deserialize(const uint8_t *in, size_t in_len, Frame_t *out);

#endif /* FRAME_H */
