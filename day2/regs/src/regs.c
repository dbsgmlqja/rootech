/* ============================================================================
 * regs.c
 *
 * TODO (멘티 작성):
 *  - PC 환경에서 UART0 을 정적 메모리로 흉내내고, send / recv / status 를 구현한다.
 *  - volatile 의 효과를 분석 노트(notes/day2.md) 에 기록한다.
 *  - _Static_assert 를 의도적으로 위반시켜 빌드 실패 메시지를 캡처한다.
 * ========================================================================== */
#include "regs.h"

static UartRegs_t s_uart0_storage; /* PC 시뮬레이션용 */
UartRegs_t *const UART0 = &s_uart0_storage;

void uart_send_byte(UartRegs_t *u, uint8_t b) {

    (*u).DR = b;
    /* TODO: u->DR 에 b 를 쓴다 */
}

uint8_t uart_recv_byte(UartRegs_t *u) {
    (void)u;
    /* TODO: u->DR 을 읽어 반환한다 */
    return (uint8_t)(*u).DR;
}

uint32_t uart_get_status(const UartRegs_t *u) {
    (void)u;
    /* TODO: u->SR 을 반환한다 */
    return (*u).SR;
}
