/* ============================================================================
 * fsm.c
 *
 * TODO (멘티 작성):
 *  - 천이 함수 테이블 s_table[ST_MAX][EV_MAX] 를 작성하여 상태 천이를 데이터로 표현한다.
 *  - 정상 / STX 누락 / LEN 비정상 / 페이로드 부족 시나리오에서 정확히 동작해야 한다.
 *  - 천이가 일어날 때마다 printf 로 [from]--ev-->[to] 를 출력한다.
 * ========================================================================== */
#include "fsm.h"
static State_t idle(Fsm_t *fsm, Event_t ev, uint8_t byte);
static State_t recv_len(Fsm_t *fsm, Event_t ev, uint8_t byte);
static State_t recv_payload(Fsm_t *fsm, Event_t ev, uint8_t byte);
static State_t done(Fsm_t *fsm, Event_t ev, uint8_t byte);

void fsm_init(Fsm_t *fsm) {

    fsm->state                    = ST_IDLE;
    fsm->frame_ready              = false;
    fsm->payload[FSM_PAYLOAD_MAX] = 0;
    fsm->payload_len              = 0;
    fsm->recv_idx                 = 0;

    /* TODO */
}

typedef State_t (*Trans_t)(Fsm_t *fsm, Event_t ev, uint8_t byte);

static const Trans_t s_table[ST_MAX][EV_MAX] = {
    //  EV_BYTE   EV_RESET   EV_MAX
    [ST_IDLE]         = {idle, done},
    [ST_RECV_LEN]     = {recv_len, done},
    [ST_RECV_PAYLOAD] = {recv_payload, done},
    [ST_DONE]         = {0, done},
};

void fsm_step(Fsm_t *fsm, Event_t ev, uint8_t byte) {

    /* TODO */
    Trans_t t = s_table[fsm->state][ev];
    if (t) {

        State_t next = t(fsm, ev, byte);

        printf("%d --%d--> %d\n", fsm->state, ev, next);

        fsm->state = next;
    }
}

static State_t idle(Fsm_t *fsm, Event_t ev, uint8_t byte) {
    if (ev == EV_BYTE) {
        if (byte == 0x02) {
            return ST_RECV_LEN;
        }
    }
    return ST_IDLE;
}

static State_t recv_len(Fsm_t *fsm, Event_t ev, uint8_t byte) {
    if (ev == EV_BYTE) {
        if (byte > FSM_PAYLOAD_MAX) {
            return ST_IDLE;
        }

        fsm->payload_len = byte;
        fsm->recv_idx    = 0;
        return ST_RECV_PAYLOAD;
    }
    return ST_RECV_LEN;
}

static State_t recv_payload(Fsm_t *fsm, Event_t ev, uint8_t byte) {
    if (ev == EV_BYTE) {

        fsm->payload[fsm->recv_idx] = byte;
        fsm->recv_idx++;

        if (fsm->recv_idx >= fsm->payload_len) {

            fsm->frame_ready = true;
            return ST_DONE;
        }
    }
    return ST_RECV_PAYLOAD;
}

static State_t done(Fsm_t *fsm, Event_t ev, uint8_t dyte) {
    if (ev == EV_RESET) {

        fsm->frame_ready = false;
        return ST_IDLE;
    }
    return ST_DONE;
}
