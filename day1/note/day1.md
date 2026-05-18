***비트 연산***

/* pos : n번 째 비트를 설정
   start : 사용되는 가장 작은 bit, 읽기/쓰기 시작하는 bit (shift써 LSB로 이동시키기 위함)
   width : 해당 bit들의 넓이
   val : 넣고 싶은 값

1. bit set
reg |= (1U << pos);        //pos번 째 bit에 1을 shift하고 reg와 or해 1로 set

2. bit clear
reg ~= ~(1U << pos);       //pos번 째 bit에 ~1 = 0을 shift하고 reg와 and해 0으로 clear

3. bit toggle
reg ^= (1U << pos);        //pos번 째 bit에 1을 shift하고 ^=로 toggle

4. bit check
(reg >> pos) & 1U != 0;    //pos번 째 bit를 LSB로 shift하고 1U와 and 했을 때 참/거짓

5. bit field read
   1. (reg >> start)       //reg에서 읽기시작하는 bit를 LSB로 shift
   2. (reg >> start) & mask  //mask와 and해서 원하는 부분만 나오게
   3. mask = ((1U << width) - 1)  //1U를 width만큼 이동시키고 1을 뺴줘서 읽기원하는 bit넓이만큼 maks를 해줌

6. bit field write
   1.  reg &= ~((1U << width) - 1)  //먼저 write할 비트만큼 ~mask해 0으로 clear
   2.  | (val << start)   //넣고싶은 값을 start만큼 shift하고 or연산해 write

7. Big Endian vs Little Endian

Endian ? : 여러 byte를 메모리에 어떤 순서로 저장할 것인가?

ex) 0x12 34 56 78
     MSB       LSB

Big Endian : 큰 바이트를 먼저 저장 (MSB 부터 저장)
주소 : 1000  1001  1002  1003
       0x12  0x34  0x56  0x78

Little Endian : 작은 바이트를 먼저 저장 (LSB 부터 저장)
주소 : 1000  1001  1002  1003
       0x78  0x56  0x34  0x12


ARM Cortex-M은 Little Endian 사용
통신 프로토콜은 일반적으로 Big Endian 사용
-> 두 방향에서의 data를 송수신하려면 Little Endain <-> Big Endian 변환해 바이트 순서를 맞춰야 함.

7. 16bit swap
   ex) v = 0x1234;

   (v << 8) | (v >> 8)

8. 32bit swap
   ex) v = 0x12345678

   ((v & 0x000000FF) << 24  |
   (v & 0x0000FF00) << 8    |
   (v & 0x00FF0000) >> 8    |
   (v & 0xFF000000) >> 24)



***메모리 구조 및 포인터***

.text    : 실행코드. Flash에 위치하며 읽기 전용으로 동작
           컴파일된 함수들이 저장. main()에서 foo(); 등 함수들.

.rodata  : 상수 데이터(const 전역). Flash에 위치함
           const 전역 변수, printf("hello")에서 "hello"도 .rodata에 저장

.data    : 초기값이 있는 전역/static 변수. 부팅 시 Flash에서 RAM으로 복사
           실행 중 수정이 가능해야되서 Flahs -> RAM

.bss     : 초기값이 없는 전역/static 변수. 부팅 시 0으로 초기화

<static 변수에 초기값 있으면 .data section / 초기값 없으면 .bss section>

Stack    : 함수 호출/지역 변수. ARM Cortex-M에서는 RAM 상단(고주소) or 하단에서 생성됨
           함수 호출 시 자동 사용되는 메모리. 즉, 함수 호출 시 필요한 것들을 임시 저장.
           ex) void foo(void) { int x;} 에서 x는 Stack임.
           대표적으로,
           1. 지역 변수
           2. 함수 끝나고 돌아갈 주소
           3. 함수 인자 일부 (인자가 적으면 레지스터에 저장, but 인자가 많아지면 stack 사용)
           4. 레지스터 백업 (함수 호출 전에 CPU 레지스터에 중요한 값들을 함수 시작 시에 미리 stack에 push하고 함수 끝나면 pop)
           5. 인터럽트 context 저장
           ex) UART 인터럽트 발생
            1. 현재 상태 stack 저장
            2. ISR 실행
            3. 상태 복원
            4. 원래 while 계속 실행

           so, stack은 함수 생성 시 만들어지고, 함수 끝나면 자동으로 제거
           즉, 함수 호출 = stack 사용

Heap     : 동적 할당 영역. 임베디드에서는 가능한 사용하지 않거나 정적 풀로 대체
           작은 용량의 stack <-> heap 상대적으로 더 넓은 범위
        - Heap이 사용되는 방법
        큰 용량 데이터를 Heap에 놓고 주소만을 stack에서 관리함.

왜 임베디드에서느 Heap을 지향하지 않는가?
1. 임베디드는 메모리가 작음 -> malloc(), free() 시에 메모리 단편화(fragmentation) 발생
   (처음 [AAAAA] -> 중간 부분 free [A___A] -> 새로운 malloc(4) 시에 실패..)
2. 메모리 누수 : malloc 후에 free 안할 시에..


#static이 붙으면 : 프로그램 시작 ~ 종료까지 메모리가 유지



***정렬 / 패딩 / Packed 구조체***
패딩? : 컴파일러가 메모리 접근 속도를 높이기위해 구조체 안에 자동으로 넣는 빈 공간.
컴파일러는 '자료형의 정렬 규칙'에 맞춰 구조체 멤버 사이에 패딩 삽입
ex)
typedef struct {
    uint8_t a;  //1byte
    uint32_t b; //4byte
    uint8_t c;  //1byte
} Aligned_t;

라는 구조체가 있을 때, 각각의 패딩은
typedef struct {
    uint8_t a;  //1byte
    *padding 3 byte*
    uint32_t b; //4byte
    uint8_t c;  //1byte
    *padding 3 byte*
} Aligned_t;

해서 겉으로 보기에는 6byte지만 sizeof시 12byte로 나옴.

패딩을 왜 줄여야 하는가?
임베디드에서는 작은 메모리의 시스템인데, 패딩 제거 시에 메모리를 절약할 수 있음
패딩 줄이는 방법.
1. 멤버 순서 변경
ex) typedef struct {
    uint8_t a;  //1byte
    *padding 3 byte*
    uint32_t b; //4byte
    uint8_t c;  //1byte
    *padding 3 byte*
} Aligned_t;                => 12byte

typedef struct {
    uint32_t b; //4byte
    uint8_t a;  //1byte
    uint8_t c;  //1byte
    *padding 2 byte*
} Aligned_t;                => 8byte


2. Packed 사용
typedef struct {
    uint8_t a;  //1byte
    uint32_t b; //4byte
    uint8_t c;  //1byte
} __attribute__((packed)) Packed_t;     => 6byte

padding 제거됨. but, 비정렬 접근이기 때문에 MCU에 hard fault를 일으킬 위험있음
=> 통신 / 레지스터 매핑 / Flash 저장 구조
통신에서는 byte 구조가 정확하게 맞아 떨어져야되기 때문에 패딩 발생 시 통신 오류할 수 있음.
레지스터 매핑 또한, 하드웨어 주소와 정확히 맞아야 함.
Flash 저장 시 구조체 크기 최소화를 위해.
