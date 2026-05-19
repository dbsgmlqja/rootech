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

    fsm->state                    = ST_IDLE;
    fsm->frame_ready              = false;
    fsm->payload[FSM_PAYLOAD_MAX] = 0;
    fsm->payload_len              = 0;
    fsm->recv_idx                 = 0;

    /* TODO */
}

void fsm_step(Fsm_t *fsm, Event_t ev, uint8_t byte) {

    /* TODO */

    switch (fsm->state) {
    case ST_IDLE:
        if (ev == EV_BYTE) {
            if (byte == 0x02) {
                fsm->state = ST_RECV_LEN;
                printf("ST_IDLE --ev--> ST_RECV_LEN\n");
            }
        }

        else {
            fsm->state = ST_IDLE;
        }

        break;

    case ST_RECV_LEN:
        if (ev == EV_BYTE) {
            if (byte > FSM_PAYLOAD_MAX) {
                fsm_init(fsm);
            }
            fsm->payload_len = byte;
            fsm->recv_idx    = 0U;
            fsm->state       = ST_RECV_PAYLOAD;
            printf("ST_RECV_LEN --ev--> ST_RECV_PAYLOAD\n");
        }

        else {
            fsm->state = ST_IDLE;
        }

        break;

    case ST_RECV_PAYLOAD:
        if (ev == EV_BYTE) {
            fsm->payload[fsm->recv_idx] = byte;
            fsm->recv_idx++;

            if (fsm->recv_idx >= fsm->payload_len) {

                fsm->state       = ST_DONE;
                fsm->frame_ready = true;
                printf("ST_RECV_PAYLOAD --ev--> ST_DONE\n");
            }
        }

        else {
            fsm->state = ST_IDLE;
        }

        break;

    case ST_DONE:
        if (ev == EV_RESET) {
            fsm->state       = ST_MAX;
            fsm->frame_ready = false;
            printf("ST_DONE --ev--> ST_IDLE\n");
        }

        else {
            fsm->state = ST_IDLE;
        }

        break;
    }
}
