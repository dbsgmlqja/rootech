/* ============================================================================
 * 미션 3 - 정적 메모리 풀 (고정 크기 블록)
 * - 동적 할당(malloc/free) 사용 금지
 * - double-free 감지
 * ========================================================================== */
#ifndef POOL_H
#define POOL_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define POOL_BLOCK_SIZE 64U
#define POOL_BLOCKS     32U

void  pool_init (void);
void *pool_alloc(void);
bool  pool_free (void *p);

#endif /* POOL_H */
