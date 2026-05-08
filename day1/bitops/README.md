# Day 1 - 미션 1: 비트 연산 라이브러리

본 미션은 **레퍼런스 구현이 포함된 미션**이다. 다른 8개 미션의 코드 작성 패턴을 학습하기 위해 먼저 본 미션의 코드를 읽고 빌드해 본다.

## 빌드 / 테스트

```powershell
cmake --preset windows-clang-debug
cmake --build build/windows-clang-debug --target test_bitops
ctest --preset debug -R test_bitops
```

## 학습 포인트

- assert 로 사전 조건을 표현하는 패턴
- 32비트 폭 마스크 작성 시 `(width == 32) ? 0xFFFFFFFFU : ((1U << width) - 1U)` 같은 경계 처리
- `1U`, `0xFFU` 같은 unsigned 리터럴 사용으로 부호 변환 경고 회피
- 엔디언 변환의 정석 코드
