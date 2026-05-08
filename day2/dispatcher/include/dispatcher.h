/* ============================================================================
 * 미션 1 - 콜백 기반 이벤트 디스패처
 * - 최대 32 종 이벤트
 * - 이벤트당 최대 4개 콜백 체이닝
 * ========================================================================== */
#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <stdbool.h>
#include <stdint.h>

#define DISPATCHER_MAX_EVENTS         32U
#define DISPATCHER_MAX_CHAIN_PER_EV   4U

typedef void (*EventHandler_t)(uint8_t event_id, void *ctx);

void dispatcher_init   (void);
bool dispatcher_register   (uint8_t event_id, EventHandler_t h, void *ctx);
bool dispatcher_unregister (uint8_t event_id, EventHandler_t h);
void dispatcher_dispatch   (uint8_t event_id);

#endif /* DISPATCHER_H */
