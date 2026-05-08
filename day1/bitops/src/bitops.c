/* ============================================================================
 * bitops.c - 레퍼런스 구현
 * 다른 미션은 이 모듈의 패턴을 참고하여 본인이 직접 작성한다.
 * ========================================================================== */
#include "bitops.h"

#include <assert.h>
#include <stddef.h>

void bit_set(uint32_t *reg, uint8_t pos) {
    assert(reg != NULL);
    assert(pos < 32U);
    *reg |= ((uint32_t)1U << pos);
}

void bit_clear(uint32_t *reg, uint8_t pos) {
    assert(reg != NULL);
    assert(pos < 32U);
    *reg &= ~((uint32_t)1U << pos);
}

void bit_toggle(uint32_t *reg, uint8_t pos) {
    assert(reg != NULL);
    assert(pos < 32U);
    *reg ^= ((uint32_t)1U << pos);
}

bool bit_check(uint32_t reg, uint8_t pos) {
    assert(pos < 32U);
    return ((reg >> pos) & 1U) != 0U;
}

uint32_t field_read(uint32_t reg, uint8_t start, uint8_t width) {
    assert(width > 0U);
    assert((uint16_t)start + (uint16_t)width <= 32U);

    const uint32_t mask = (width == 32U) ? 0xFFFFFFFFU : (((uint32_t)1U << width) - 1U);
    return (reg >> start) & mask;
}

uint32_t field_write(uint32_t reg, uint8_t start, uint8_t width, uint32_t val) {
    assert(width > 0U);
    assert((uint16_t)start + (uint16_t)width <= 32U);

    const uint32_t field_mask = (width == 32U) ? 0xFFFFFFFFU : (((uint32_t)1U << width) - 1U);
    const uint32_t shifted    = (val & field_mask) << start;
    return (reg & ~(field_mask << start)) | shifted;
}

uint16_t swap16(uint16_t v) {
    return (uint16_t)((uint16_t)(v << 8) | (uint16_t)(v >> 8));
}

uint32_t swap32(uint32_t v) {
    return ((v & 0x000000FFU) << 24) | ((v & 0x0000FF00U) << 8) | ((v & 0x00FF0000U) >> 8) |
           ((v & 0xFF000000U) >> 24);
}
