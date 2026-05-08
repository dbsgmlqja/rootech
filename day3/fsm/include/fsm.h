/* ============================================================================
 * 미션 2 - 테이블 기반 상태머신 (간이 프레임 수신기)
 * 프레임: STX(0x02) | LEN | PAYLOAD[LEN] | ETX(0x03)
 * ========================================================================== */
#ifndef FSM_H
#define FSM_H

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    ST_IDLE = 0,
    ST_RECV_LEN,
    ST_RECV_PAYLOAD,
    ST_DONE,
    ST_MAX
} State_t;

typedef enum { EV_BYTE = 0, EV_RESET, EV_MAX } Event_t;

#define FSM_PAYLOAD_MAX 32U

typedef struct {
    State_t state;
    uint8_t payload[FSM_PAYLOAD_MAX];
    uint8_t payload_len;
    uint8_t recv_idx;
    bool    frame_ready;
} Fsm_t;

void fsm_init(Fsm_t *fsm);
void fsm_step(Fsm_t *fsm, Event_t ev, uint8_t byte);

#endif /* FSM_H */
