add_library(regs STATIC src/regs.c)
target_include_directories(regs PUBLIC include)
target_link_libraries(regs PRIVATE week02_common)

add_executable(test_regs tests/test_regs.c)
target_link_libraries(test_regs PRIVATE regs week02_common week02_test)

add_test(NAME test_regs COMMAND test_regs)
