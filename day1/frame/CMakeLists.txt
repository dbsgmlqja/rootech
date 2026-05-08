add_library(frame STATIC src/frame.c)
target_include_directories(frame PUBLIC include)
target_link_libraries(frame PRIVATE week02_common)

add_executable(test_frame tests/test_frame.c)
target_link_libraries(test_frame PRIVATE frame week02_common week02_test)

add_test(NAME test_frame COMMAND test_frame)
