/* ============================================================================
 * 미션 1 - 비트 연산 라이브러리
 * ========================================================================== */
#ifndef BITOPS_H
#define BITOPS_H

#include <stdbool.h>
#include <stdint.h>

/* 단일 비트 조작 (pos: 0 ~ 31) */
void bit_set   (uint32_t *reg, uint8_t pos);
void bit_clear (uint32_t *reg, uint8_t pos);
void bit_toggle(uint32_t *reg, uint8_t pos);
bool bit_check (uint32_t  reg, uint8_t pos);

/* 비트 필드 read/write
 *  - start: LSB 위치 (0 ~ 31)
 *  - width: 비트 폭   (1 ~ 32, start + width <= 32)
 */
uint32_t field_read (uint32_t reg, uint8_t start, uint8_t width);
uint32_t field_write(uint32_t reg, uint8_t start, uint8_t width, uint32_t val);

/* 엔디언 변환 */
uint16_t swap16(uint16_t v);
uint32_t swap32(uint32_t v);

#endif /* BITOPS_H */
