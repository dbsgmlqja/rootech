/* ============================================================================
 * pool.c
 *
 * TODO (멘티 작성):
 *  - 32 개의 64-byte 블록을 정적 배열로 확보한다.
 *  - free list 를 단방향 링크드 리스트로 관리한다.
 *  - pool_alloc 는 풀 고갈 시 NULL 반환.
 *  - pool_free 는 double-free 또는 풀 외부 포인터를 감지하여 false 반환.
 * ========================================================================== */
#include "pool.h"

typedef union block {

    union block *next;
    uint8_t      data[POOL_BLOCK_SIZE]; // 64비트의 데이터

} Block_t;

static Block_t  pool[POOL_BLOCKS]; // 32개의 블록
static Block_t *s_free_list;

void pool_init(void) {
    /* TODO */
    for (size_t i = 0; i < POOL_BLOCKS; i++) {

        pool[i].next = &pool[i + 1];
    }
    pool[POOL_BLOCKS - 1].next = NULL;

    s_free_list = &pool[0];
}

void *pool_alloc(void) {
    /* TODO */
    if (s_free_list == NULL) {
        return false;
    }

    Block_t *block = s_free_list;
    /*
    block이라는 Block_t를 가리키는 포인터 변수 하나 생성
    = s_free_list를 시켜줘서 맨 앞 블록에 위치하게 만들어 줌
    ( init에서 s_free_list = &pool[0] )
    */

    s_free_list = s_free_list->next;
    /*
    next는 다음 블록을 말함 (init에서 pool[i].next = pool[i+1])
    그래서 s_free_list를 다음 칸으로 이동
    */

    return block->data;
    /*
    첫 번째 칸 block이 data에 접근해서 반환한다. -> 이건 free에서 인자로 들어감 (data 주소로)
    */
}

bool pool_free(void *p) {

    /* TODO */

    Block_t *block = (Block_t *)p;
    /*
    p는 Block_t에서 data에 대한 멤버.
    block은 Block_t를 가리키는 포인터 변수
    Union 사용하므로 두 개가 가리키는 메모리는 같음.
    즉, block을 data를 가리키는 주소로 쓰겠다.
    즉 block = p(data 주소)
    */

    if (block < &pool[0] | block >= &pool[POOL_BLOCKS]) {
        return false;
    }
    // block이 배열에 있는지 확인.

    if (block == s_free_list) {
        return false;
    }
    // double free check

    block->next = s_free_list;
    /*
    현재 block은 첫 블록 pool[0]이고 block->next는 pool[1] 임.
    즉 s_free_list를 block->next인 pool[1]에 위치
    ***윗 설명 틀림
    -> alloc 직후 특성이라 위 설명이 일반화가 안됨.

    반납할 block 뒤에 기존 free_list를 연결하겠다 라는 의미/
    해주는 이유가 순서대로 쓰는 것이 아니라, 원하는 비어있는 블록 목록에 쓰고 빼야하기 때문에 반납할
    block을 free list 맨 앞에 다시 연결.
    */

    s_free_list = block;
    // free list의 시작점을 새로 반납할 block으로 변경

    return true;
}
