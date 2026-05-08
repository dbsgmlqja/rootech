/* ============================================================================
 * fsm.c
 *
 * TODO (멘티 작성):
 *  - 천이 함수 테이블 s_table[ST_MAX][EV_MAX] 를 작성하여 상태 천이를 데이터로 표현한다.
 *  - 정상 / STX 누락 / LEN 비정상 / 페이로드 부족 시나리오에서 정확히 동작해야 한다.
 *  - 천이가 일어날 때마다 printf 로 [from]--ev-->[to] 를 출력한다.
 * ========================================================================== */
#include "fsm.h"

void fsm_init(Fsm_t *fsm) {
    (void)fsm;
    /* TODO */
}

void fsm_step(Fsm_t *fsm, Event_t ev, uint8_t byte) {
    (void)fsm;
    (void)ev;
    (void)byte;
    /* TODO */
}
