/* ============================================================================
 * 미션 2 - 메모리 영역 추적기
 *
 * TODO (멘티 작성):
 *  1. .data / .bss / .rodata / stack / heap 에 배치되는 변수를 추가한다.
 *  2. 각 변수의 주소를 printf 로 출력한다.
 *  3. 결과를 분석하여 README 에 어떤 변수가 어느 섹션에 배치되었는지 정리한다.
 *  4. `objdump -h memlayout.exe` (또는 llvm-objdump) 출력을 README 에 첨부한다.
 * ========================================================================== */

#include <stdio.h>
#include <stdlib.h>
void func(void);

int        g_init = 10;   // 초기값이 있는 전역 변수
int        g_uninit;      // 초기값이 없는 전역 변수
const int  g_const  = 20; // 상수 변수 (값 변경 X)
static int s_static = 30; // file scope static 변수

void func(void) {

    int        local    = 40;                  // 지역 변수(stack)
    static int s_local  = 50;                  // 지역 변수(stack)
    int       *heap_var = malloc(sizeof(int)); // 동적 할당 (Heap)

    printf("local       : %p\n", (void *)&local);
    printf("s_local     : %p\n", (void *)&s_local);
    printf("heap_var    : %p\n", (void *)heap_var);
    printf("heap_var_point : %p\n", (void *)&heap_var);
    free(heap_var);
}

int main(void) {
    /* TODO:s
     *  - 지역 변수 (스택)
     *  - 함수 내 static 변수
     *  - malloc 으로 할당한 힙 변수
     *  를 만들고 모두 주소를 출력하라.
     */
    int x = 1;

    printf("x = %p\n", (void *)&x);
    printf("g_uninit = %p\n", (void *)&g_uninit);
    printf("g_const = %p\n", (void *)&g_const);
    printf("s_static = %p\n", (void *)&s_static);
    printf("func() = %p\n", (void *)&func);
    // printf("x = %p\n", (void *)&x);
    func();
    // printf("memlayout: TODO - 변수 주소를 출력하도록 구현하라.\n");
    return 0;
}
