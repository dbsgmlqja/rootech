/* ============================================================================
 * 미션 2 - 테이블 기반 상태머신 (간이 프레임 수신기)
 * 프레임: STX(0x02) | LEN | PAYLOAD[LEN] | ETX(0x03)
 * ========================================================================== */
#ifndef FSM_H
#define FSM_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

typedef enum {
    ST_IDLE = 0,     // STX 데이터 기다리는 상태
    ST_RECV_LEN,     // LEN Byte 데이터 기다리는 상태
    ST_RECV_PAYLOAD, // payload 데이터 받는중
    ST_DONE,         // 프레임 수신 완료 상태
    ST_MAX           // 상태 개수
} State_t;           // 현재 상태

typedef enum { EV_BYTE = 0, EV_RESET, EV_MAX } Event_t;
// 상태를 변화시키는 이벤트
// EV_BYTE : 바이트 하나 들어옴 / EV_RESET : 상태머신 초기화 / EV_MAX : 이벤트 개수

#define FSM_PAYLOAD_MAX 32U

typedef struct {
    State_t state;
    uint8_t payload[FSM_PAYLOAD_MAX];
    uint8_t payload_len;
    uint8_t recv_idx;
    bool    frame_ready;
} Fsm_t; // 현재 프레임 수신 상태 전체를 저장

void fsm_init(Fsm_t *fsm);
void fsm_step(Fsm_t *fsm, Event_t ev, uint8_t byte);

#endif /* FSM_H */
