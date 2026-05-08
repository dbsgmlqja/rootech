add_executable(memlayout src/memlayout.c)
target_link_libraries(memlayout PRIVATE week02_common)

# memlayout 은 단순 출력 프로그램이지만 CTest에서 실행하여 정상 종료를 검증한다
add_test(NAME memlayout_runs COMMAND memlayout)
