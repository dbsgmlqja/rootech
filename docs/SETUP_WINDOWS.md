# Windows 환경 셋업 가이드

## 1. 필수 도구 설치

### 1.1 LLVM (clang, clangd, clang-format, clang-tidy, lldb)

권장: 공식 인스톨러 사용. 설치 시 **"Add LLVM to the system PATH"** 옵션을 반드시 선택한다.

- 다운로드: <https://github.com/llvm/llvm-project/releases>
- 또는 `winget install LLVM.LLVM`
- 또는 Chocolatey: `choco install llvm`

설치 검증:
```powershell
clang --version
clangd --version
clang-format --version
clang-tidy --version
```

### 1.2 CMake (3.20 이상)

- <https://cmake.org/download/>
- 또는 `winget install Kitware.CMake`
- 또는 `choco install cmake`

### 1.3 Ninja

- `winget install Ninja-build.Ninja`
- 또는 `choco install ninja`

### 1.4 VSCode 확장

본 프로젝트의 `.vscode/extensions.json` 에 추천 확장이 정의되어 있다.

- `llvm-vs-code-extensions.vscode-clangd` (필수)
- `ms-vscode.cmake-tools` (필수)
- `twxs.cmake` (CMake 문법 하이라이트)
- `vadimcn.vscode-lldb` (디버거)

> Microsoft 의 `ms-vscode.cpptools` 는 clangd 와 충돌하므로 **비활성화 / 미설치** 권장 (`extensions.json` 에 unwantedRecommendations 로 명시되어 있다).

## 2. 빌드 / 테스트

### 2.1 명령줄

```powershell
cd week02-missions

# 첫 빌드
cmake --preset windows-clang-debug
cmake --build build/windows-clang-debug --parallel

# 단위 테스트 일괄 실행
ctest --preset debug

# 특정 테스트만 실행
ctest --preset debug -R test_bitops --output-on-failure
```

### 2.2 VSCode

1. `week02-missions` 폴더를 연다.
2. `Ctrl+Shift+P` → `CMake: Select Configure Preset` → `windows-clang-debug`.
3. `Ctrl+Shift+B` (Build All) 로 빌드.
4. `Ctrl+Shift+P` → `Tasks: Run Test Task` 로 모든 테스트 실행.
5. 개별 실행 파일은 `build/windows-clang-debug/test_xxx.exe` 에 생성된다.

## 3. 디버깅

VSCode 에서 `F5` 를 누르면 어떤 테스트 실행 파일을 디버깅할지 묻는다 (예: `test_bitops`).
LLDB 가 자동으로 시작되며, 브레이크포인트 / 워치 / 콜스택을 사용할 수 있다.

## 4. clangd 와 compile_commands.json

- CMake 가 `compile_commands.json` 을 빌드 디렉터리에 자동 생성한다 (CMakePresets 에서 `CMAKE_EXPORT_COMPILE_COMMANDS=ON`).
- `.vscode/settings.json` 의 `--compile-commands-dir` 가 이 경로를 가리킨다.
- 첫 빌드 후에야 clangd 가 정확한 인텔리센스를 제공하므로, 코드 분석 전에 한 번은 빌드를 완료해야 한다.

## 5. 자주 발생하는 문제

### 5.1 `'cmake' 명령을 찾을 수 없음`
PATH 확인. PowerShell 재시작.

### 5.2 clangd 가 헤더를 찾지 못함
- 빌드를 한 번 완료했는지 확인 (`compile_commands.json` 생성 필요).
- `Ctrl+Shift+P` → `clangd: Restart language server` 실행.

### 5.3 한글 출력이 깨짐
PowerShell 에서 `chcp 65001` 실행 또는 Windows Terminal 의 인코딩을 UTF-8 로 설정.

### 5.4 빌드는 되는데 테스트 실행 시 ASAN 관련 에러
Windows clang 의 ASAN 은 일부 환경에서 불안정. CMakeLists.txt 의 `if(... NOT WIN32)` 분기로 Windows 에서는 자동 비활성화되어 있다.

## 6. 참고

- LLVM on Windows: <https://clang.llvm.org/docs/MSVCCompatibility.html>
- CMake Presets: <https://cmake.org/cmake/help/latest/manual/cmake-presets.7.html>
- clangd: <https://clangd.llvm.org/>
