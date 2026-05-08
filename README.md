# 2주차 미션 프로젝트 (Windows + clang)

신입 임베디드 엔지니어 멘토링 2주차 (3일 진행)의 9개 미션을 빌드·테스트하기 위한 프로젝트이다.
Windows 환경에서 LLVM clang + Ninja + CMake + VSCode (clangd / clang-format / clang-tidy) 조합으로 동작한다.

## 디렉터리 구조

```
week02-missions/
├── .clang-format            clang-format 스타일 정의
├── .clang-tidy              clang-tidy 검사 규칙
├── .gitignore
├── .vscode/                 VSCode 설정 (clangd, tasks, launch, extensions)
├── CMakeLists.txt           루트 빌드 스크립트
├── CMakePresets.json        Windows clang Debug/Release 프리셋
├── docs/SETUP_WINDOWS.md    윈도우 환경 셋업 가이드
├── shared/
│   └── test_framework.h     단순 단위 테스트 프레임워크
├── day1/
│   ├── bitops/              [참조 구현 포함]  비트 연산 라이브러리
│   ├── memlayout/           메모리 영역 추적기
│   └── frame/               Packed 프레임 직렬화/역직렬화
├── day2/
│   ├── dispatcher/          콜백 디스패처
│   ├── regs/                레지스터 추상화 (volatile / _Static_assert)
│   └── container_of/        container_of 매크로
└── day3/
    ├── ringbuf/             SPSC lock-free 링버퍼
    ├── fsm/                 테이블 기반 상태머신
    └── pool/                정적 메모리 풀
```

## 빠른 시작 (Windows)

상세 셋업은 `docs/SETUP_WINDOWS.md` 를 참고한다.

```powershell
# 1. 환경 확인
clang --version
ninja --version
cmake --version

# 2. 빌드
cmake --preset windows-clang-debug
cmake --build build/windows-clang-debug --parallel

# 3. 테스트
ctest --preset debug

# 4. 특정 미션만 테스트
ctest --preset debug -R test_bitops
```

## VSCode 사용

1. 본 폴더(`week02-missions`)를 VSCode 로 연다.
2. 추천 확장 설치 안내가 뜨면 모두 수락한다 (clangd / CMake Tools / LLDB).
3. `Ctrl+Shift+P` → `CMake: Select Configure Preset` → `windows-clang-debug` 선택.
4. `Ctrl+Shift+B` 로 빌드, `Tasks: Run Test Task` 로 ctest 실행.
5. 코드 저장 시 자동으로 clang-format 이 적용된다.

## 미션 진행 순서

| 일자 | 미션 디렉터리 | 상태 |
|------|--------------|-----|
| 1일차 | day1/bitops      | **레퍼런스 구현 완료** (학습용 참고) |
| 1일차 | day1/memlayout   | TODO |
| 1일차 | day1/frame       | TODO |
| 2일차 | day2/dispatcher  | TODO |
| 2일차 | day2/regs        | TODO |
| 2일차 | day2/container_of| TODO |
| 3일차 | day3/ringbuf     | TODO |
| 3일차 | day3/fsm         | TODO |
| 3일차 | day3/pool        | TODO |

각 미션 디렉터리의 `README.md` 와 `src/*.c` 의 `TODO` 주석을 따라 구현한다.

## 코드 품질 도구

- **clang-format**: 저장 시 자동 적용 (수동: `Tasks: clang-format: Format current file`)
- **clang-tidy**: 빌드 후 `Tasks: clang-tidy: Run on current file` 또는 clangd 가 자동 수행
- **컴파일러 경고**: `-Wall -Wextra -Wpedantic -Wshadow -Wconversion` 등 strict 모드
