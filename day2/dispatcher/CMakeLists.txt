add_library(dispatcher STATIC src/dispatcher.c)
target_include_directories(dispatcher PUBLIC include)
target_link_libraries(dispatcher PRIVATE week02_common)

add_executable(test_dispatcher tests/test_dispatcher.c)
target_link_libraries(test_dispatcher PRIVATE dispatcher week02_common week02_test)

add_test(NAME test_dispatcher COMMAND test_dispatcher)
