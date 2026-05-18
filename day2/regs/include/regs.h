/* ============================================================================
 * 미션 2 - 컴파일 타임 검증을 적용한 레지스터 추상화
 * ========================================================================== */
#ifndef REGS_H
#define REGS_H

#include <assert.h>
#include <stdint.h>

typedef struct {
    volatile uint32_t       CR1; /* 0x00 control 1 */
    volatile uint32_t       CR2; /* 0x04 control 2 */
    volatile const uint32_t SR;  /* 0x08 status (read-only) */
    volatile uint32_t       DR;  /* 0x0C data */
    volatile uint8_t        AA;
} UartRegs_t;

_Static_assert(sizeof(UartRegs_t) == 16U, "UartRegs_t 크기 가정 위반");

/* PC 환경에서 UART0 을 정적 배열로 시뮬레이션 */
extern UartRegs_t *const UART0;

void     uart_send_byte(UartRegs_t *u, uint8_t b);
uint8_t  uart_recv_byte(UartRegs_t *u);
uint32_t uart_get_status(const UartRegs_t *u);

#endif /* REGS_H */
