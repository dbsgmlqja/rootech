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

void dispatcher_init(void) {
    /* TODO */
}

bool dispatcher_register(uint8_t event_id, EventHandler_t h, void *ctx) {
    (void)event_id;
    (void)h;
    (void)ctx;
    /* TODO */
    return false;
}

bool dispatcher_unregister(uint8_t event_id, EventHandler_t h) {
    (void)event_id;
    (void)h;
    /* TODO */
    return false;
}

void dispatcher_dispatch(uint8_t event_id) {
    (void)event_id;
    /* TODO */
}
