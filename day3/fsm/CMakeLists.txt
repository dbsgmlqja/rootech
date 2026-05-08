add_library(fsm STATIC src/fsm.c)
target_include_directories(fsm PUBLIC include)
target_link_libraries(fsm PRIVATE week02_common)

add_executable(test_fsm tests/test_fsm.c)
target_link_libraries(test_fsm PRIVATE fsm week02_common week02_test)

add_test(NAME test_fsm COMMAND test_fsm)
