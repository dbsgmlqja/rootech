# Day 1 - 미션 2: 메모리 영역 추적기

## 목표
변수의 스토리지 클래스에 따라 어느 섹션(.text/.rodata/.data/.bss/Stack/Heap)에 배치되는지 직접 관찰한다.

## 빌드 / 실행

```powershell
cmake --preset windows-clang-debug
cmake --build build/windows-clang-debug --target memlayout
./build/windows-clang-debug/memlayout.exe
```

## 분석 도구 (Windows + LLVM)

```powershell
# 섹션 헤더 출력
llvm-objdump.exe -h build/windows-clang-debug/memlayout.exe

# 심볼 테이블
llvm-nm.exe build/windows-clang-debug/memlayout.exe
```

## 제출 사항

- [ ] 각 변수가 어느 섹션에 배치되었는지 표 형태로 정리
- [ ] llvm-objdump 출력 첨부
- [ ] g_init / g_uninit 의 주소 차이 분석 (1문단 이상)
