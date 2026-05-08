add_library(pool STATIC src/pool.c)
target_include_directories(pool PUBLIC include)
target_link_libraries(pool PRIVATE week02_common)

add_executable(test_pool tests/test_pool.c)
target_link_libraries(test_pool PRIVATE pool week02_common week02_test)

add_test(NAME test_pool COMMAND test_pool)
