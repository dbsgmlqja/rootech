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

/* TODO: 전역 변수들을 선언하라.
 *  - 초기값 있는 전역  (기대 섹션: .data)
 *  - 초기값 없는 전역  (기대 섹션: .bss)
 *  - const 전역        (기대 섹션: .rodata)
 *  - file scope static (기대 섹션: .data 또는 .bss)
 */

int main(void) {
    /* TODO:
     *  - 지역 변수 (스택)
     *  - 함수 내 static 변수
     *  - malloc 으로 할당한 힙 변수
     *  를 만들고 모두 주소를 출력하라.
     */

    printf("memlayout: TODO - 변수 주소를 출력하도록 구현하라.\n");
    return 0;
}
