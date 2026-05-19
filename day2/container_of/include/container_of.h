/* ============================================================================
 * 미션 3 - container_of 매크로
 * ========================================================================== */
#ifndef CONTAINER_OF_H
#define CONTAINER_OF_H

#include <stddef.h>

/* TODO: container_of 매크로를 정의하라.
 *
 * 힌트:
 *   #define container_of(ptr, type, member) \
 *       ((type *)((char *)(ptr) - offsetof(type, member)))
 */

#define container_of(ptr, type, member) ((type *)((char *)(ptr) - offsetof(type, member)))

#endif /* CONTAINER_OF_H */

/*
    container_of(ptr, type, member) 매크로는 무엇을 수행하냐?
    구조체 멤버의 주소로부터, 원래 구조체 전체의 주소를 역산하는 매크로.
    -> 멤버의 주소만 알고 있을 때, 그 멤버를 포함하는 구조체 처음 주소를 복원하기위해.

    (type *)(char *)(ptr) : (char *) 은 계산 시에 1byte 씩 빼주기 위해서 타입 변환
                            (type *) 은 계산이 다 끝나고 다시 구조체 포인터로 캐스팅해줌
    offset(type, member) : 구조체에서 member와 구조체 시작의 위치를 뺀 값.

    1. char* 로 1byte 계산으로 변환
    2. offsetof 통해서 member의 위치 얻고
    3. 그 값을 빼줘서 구조체의 첫 주소를 얻고
    4. 다 했으면 다시 원래 구조체 포인터로 캐스팅.

*/
