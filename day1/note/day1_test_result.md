***bitops***

void bit_set((uint32_t *reg, uint8_t pos)){
    assert(pos < 32);
    assert(reg != NULL);
    *reg |= (1U << pos);
}

void bit_clear((uint32_t *reg, uint8_t pos)){
    assert(pos < 32);
    assert(reg != NULL);
    *reg &= ~(1U << pos);
}

void bit_toggle((uint32_t *reg, uint8_t pos)){
    assert(pos < 32);
    assert(reg != NULL);
    *reg ^= (1U << pos);
}

void bit_check((uint32_t *reg, uint8_t pos)){
    assert(pos < 32);
    assert(reg != NULL);
    ((*reg >> start) & 1U ) != 0;
}

uint32_t field_read (uint32_t reg, uint8_t start, uint8_t width){
    assert(uint16_t (start+width) <= 32);
    assert(uint8_t width > 0);
    /*1. read할 reg 부분을 LSB로 shift
    (reg >> start)
    2. (reg >> start) & mask LSB로 shift한 값과 mask해서 read할 부분만 남기기
    mask = (1U << width) - 1
    */

    const uint32_t read_mask = (width == 32U) ? 0xFFFFFFFFU : (1U << width) - 1;
    return (reg >> start) & read_mask;

    //여기서 const uint32_t mask는 stack에 해당
    //앞에서 크기 정의 해주는 것은 그냥 가독성을 키우기 위해?

}

uint32_t field_write (uint32_t reg, uint8_t start, uint8_t width, uint32_t val){
    assert(uint16_t (start+width) <= 32);
    assert(uint8_t width > 0);
    /*1. write할 reg 부분을 clear 해주기
    (reg & (1U << width) - 1) << start
    2. clear한 부분에 val값 shift 통해 넣어주기 (or연산 통해서)
    | (uint32_t val & ((1U << width) - 1) << start)
    */

    const uint32_t write_mask = (width == 32U) ? 0xFFFFFFFFU : (1U << width) - 1;
    return (reg & (write_mask << start)) | (val & read_mask) << start;
}

uint16_t Endian_swap16(uint16_t v) {
    return (uint16_t)((v >> 8) | (v << 8));
}


uint32_t Endian_swap32(uint32_t v) {
    return (uint32_t)((v & 0x000000FFU) << 24 |
                      (v & 0x0000FF00U) <<  8 |
                      (v & 0x00FF0000U) >>  8 |
                      (v & 0xFF000000U) >> 24 );
}


***memlayout***


    int g_init = 10; //초기값이 있는 전역 변수 -> .data
    int g_uninit;    //초기값이 없는 전역 변수 -> .bss
    const int g_const = 20; //상수 변수 (값 변경 X) -> .rodata
    static int s_static = 30; //file scope static 변수 -> .data

void func(void){

        int local = 40;    //지역 변수 -> stack
        static int s_local =50;     //지역 변수이지만 stack이 아닌 -> .data
        int *heap_var = malloc(sizeof(int));
        //int *heap_var : 포인트 변수 자체임 -> stack
        //malloc(sizeof(int)) 여기서 반환된 메모리가 -> heap

        printf("local       : %p\n", (void*)&local);
        printf("s_local     : %p\n", (void*)&s_local);
        printf("heap_var    : %p\n", (void*)heap_var);
        free(heap_var);    //free()는 함수 코드이기 때문에 -> .text
    }

    int main(void) {

    printf("g_init = %p\n", (void*)&g_init);
    printf("g_uninit = %p\n", (void*)&g_uninit);
    printf("g_const = %p\n", (void*)&g_const);
    printf("s_static = %p\n", (void*)&s_static);
    printf("func() = %p\n", (void*)&func);
    func(); // 함수 코드이므로 -> .text

    return 0;
}

//printf 함수 코드는 -> .text
//printf 내부 문자열 -> .rodata
//왜 %p 호출 시, 변수 앞에 (void*)를 적는가?
ex)
int a;
printf("a = %d", a); 에서 %d는 int 타입을 받으려고 함.

똑같이
int b;
printf("a = %p", &b); 에서 %p는 void 타입을 받으려고 함.
하지만 &b는 int* 타입임. 그래서 -> 인자의 타입을 (void*)로 변경해줌

int*	int의 주소 저장
char*	char의 주소 저장
float*	float의 주소 저장
void*	아무 타입 주소나 저장 가능

heap_var의 경우에도
int *heap_var = malloc(sizeof(int))
-> int 타입의 포인터 변수 heap_var 생성 -> 지역 변수니까 stack에 저장
-> 2. malloc(sizeof(int)) -> heap 영역에 int 크기만큼 메모리 생성
-> 3. malloc이 생성된 heap 주소(예: 0x5000)를 반환
-> 4. heap_var 안에 그 heap 주소값 저장

heap_var : 포인터 변수 안에 저장된 값. = heap 주소
*heap_var : heap 주소 안에 실제 값
&heap_var : 포인터 변수 자신의 주소값 = stack 주소

