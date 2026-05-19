/* ============================================================================
 * dispatcher.c
 *
 * TODO (멘티 작성):
 *  - 정적 배열 기반 등록 / 해제 / 디스패치를 구현한다.
 *  - 동일 이벤트에 최대 4개 콜백이 등록 순서대로 호출되어야 한다.
 *  - register 가 가득 차면 false 를 반환한다.
 *  - dispatch 는 event_id 가 범위를 벗어나면 무시한다.
 * ========================================================================== */
#include "dispatcher.h"

// 구조체 생성

typedef struct {
    EventHandler_t handler;
    void          *ctx;
} Callback_t;

typedef struct {
    Callback_t callback[DISPATCHER_MAX_CHAIN_PER_EV];
    uint8_t    count;
} Event_t;

// 한 이벤트에 4개의 callback을 가지게 하기위해서

Event_t static Event_table[DISPATCHER_MAX_EVENTS] = {0};
// Event_table 생성 : Event_t 안에 구조체를 가리키는 테이블 - 초기화

void dispatcher_init(void) {

    /* TODO */
}

bool dispatcher_register(uint8_t event_id, EventHandler_t h, void *ctx) {

    /* TODO */
    if (event_id >= DISPATCHER_MAX_EVENTS) {
        return false;
    }

    if (Event_table[event_id].count >= DISPATCHER_MAX_CHAIN_PER_EV) {
        return false;
    }

    uint8_t index = Event_table[event_id].count;

    if (Event_table[event_id].callback[index].handler == NULL) {
        Event_table[event_id].callback[index].handler = h;
        Event_table[event_id].callback[index].ctx     = ctx;
        Event_table[event_id].count++;
    }

    return true;
}
// 크기, 길이, 배열 인덱스, 메모리 크기 등에 size_t 사용 : 부호 없는 정수 타입

bool dispatcher_unregister(uint8_t event_id, EventHandler_t h) {

    /* TODO */

    if (event_id >= DISPATCHER_MAX_EVENTS) {
        return false;
    }

    for (size_t i = 0; i < DISPATCHER_MAX_CHAIN_PER_EV; i++) {

        if (Event_table[event_id].callback[i].handler == h &&
            Event_table[event_id].callback[i].handler != NULL) {
            Event_table[event_id].callback[i].handler = NULL;
            Event_table[event_id].callback[i].ctx     = NULL;
            Event_table[event_id].count--;
        }
    }
    return true;
}

void dispatcher_dispatch(uint8_t event_id) {

    /* TODO */
    for (size_t i = 0; i < DISPATCHER_MAX_CHAIN_PER_EV; i++) {
        if (Event_table[event_id].callback[i].handler != NULL) {
            Event_table[event_id].callback[i].handler(event_id,
                                                      Event_table[event_id].callback[i].ctx);
        }
    }
}
