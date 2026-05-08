add_library(bitops STATIC src/bitops.c)
target_include_directories(bitops PUBLIC include)
target_link_libraries(bitops PRIVATE week02_common)

add_executable(test_bitops tests/test_bitops.c)
target_link_libraries(test_bitops PRIVATE bitops week02_common week02_test)

add_test(NAME test_bitops COMMAND test_bitops)
