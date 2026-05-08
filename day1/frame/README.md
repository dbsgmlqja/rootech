# Day 1 - 미션 3: Packed 통신 프레임 직렬화 / 역직렬화

## 목표
호스트 엔디언과 무관하게 동작하는 9-byte 통신 프레임의 직렬화 / 역직렬화 함수를 구현한다.

## 구현 위치
- `src/frame.c` 의 `TODO` 표시된 두 함수

## 빌드 / 테스트
```powershell
cmake --build build/windows-clang-debug --target test_frame
ctest --preset debug -R test_frame
```

## 검증 케이스
- 정상 round-trip (직렬화 → 역직렬화)
- STX 누락
- 길이 부족
- CKSM 불일치
