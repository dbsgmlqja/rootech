# ============================================================================
# 2주차 임베디드 C 미션 - 루트 빌드 스크립트
# ============================================================================
cmake_minimum_required(VERSION 3.20)
project(week02_missions
    VERSION  1.0.0
    LANGUAGES C)

# ----------------------------------------------------------------------------
# 표준 / 출력 / compile_commands.json (clangd 가 사용)
# ----------------------------------------------------------------------------
set(CMAKE_C_STANDARD            11)
set(CMAKE_C_STANDARD_REQUIRED   ON)
set(CMAKE_C_EXTENSIONS          ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)
endif()

# ----------------------------------------------------------------------------
# 공통 컴파일 옵션 - INTERFACE 라이브러리로 모든 타깃에 전파
# ----------------------------------------------------------------------------
add_library(week02_common INTERFACE)
target_compile_options(week02_common INTERFACE
    -Wall
    -Wextra
    -Wpedantic
    -Wshadow
    -Wconversion
    -Wstrict-prototypes
    -Wmissing-prototypes
    -Wpointer-arith
    -Wcast-align
    -Wnull-dereference
    -Wno-unused-parameter
)

# Debug 빌드에서 sanitizer (Windows clang 은 ASAN 만 안정적)
if(CMAKE_BUILD_TYPE STREQUAL "Debug" AND NOT WIN32)
    target_compile_options(week02_common INTERFACE -fsanitize=address,undefined -g)
    target_link_options   (week02_common INTERFACE -fsanitize=address,undefined)
endif()

# ----------------------------------------------------------------------------
# 공통 테스트 프레임워크 (헤더만 있는 INTERFACE 라이브러리)
# ----------------------------------------------------------------------------
add_library(week02_test INTERFACE)
target_include_directories(week02_test INTERFACE ${CMAKE_SOURCE_DIR}/shared)

# ----------------------------------------------------------------------------
# 테스트 활성화
# ----------------------------------------------------------------------------
enable_testing()

# ----------------------------------------------------------------------------
# 미션 서브디렉터리
# ----------------------------------------------------------------------------
add_subdirectory(day1/bitops)
add_subdirectory(day1/memlayout)
add_subdirectory(day1/frame)

add_subdirectory(day2/dispatcher)
add_subdirectory(day2/regs)
add_subdirectory(day2/container_of)

add_subdirectory(day3/ringbuf)
add_subdirectory(day3/fsm)
add_subdirectory(day3/pool)

# ----------------------------------------------------------------------------
# 요약 출력
# ----------------------------------------------------------------------------
message(STATUS "")
message(STATUS "============================================================")
message(STATUS "  week02_missions  (build type: ${CMAKE_BUILD_TYPE})")
message(STATUS "  Compiler:    ${CMAKE_C_COMPILER_ID} ${CMAKE_C_COMPILER_VERSION}")
message(STATUS "  Generator:   ${CMAKE_GENERATOR}")
message(STATUS "  Build dir:   ${CMAKE_BINARY_DIR}")
message(STATUS "============================================================")
