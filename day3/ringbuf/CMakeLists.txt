add_library(ringbuf STATIC src/ringbuf.c)
target_include_directories(ringbuf PUBLIC include)
target_link_libraries(ringbuf PRIVATE week02_common)

add_executable(test_ringbuf tests/test_ringbuf.c)
target_link_libraries(test_ringbuf PRIVATE ringbuf week02_common week02_test)

add_test(NAME test_ringbuf COMMAND test_ringbuf)
