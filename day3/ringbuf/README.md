# Day 3 - 미션 1: SPSC Lock-free 링버퍼

크기는 2의 거듭제곱(`RB_SIZE = 64`). 모듈러는 비트 마스크로 처리한다.

## 빌드 / 테스트
```powershell
cmake --build build/windows-clang-debug --target test_ringbuf
ctest --preset debug -R test_ringbuf
```
