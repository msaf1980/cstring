# Build tests for cstring
add_executable(test_cstring cstring_test.c cstring_number_test.c)
target_link_libraries(test_cstring cstring)
add_test(test_cstring ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_cstring)

add_executable(bench_cstring cstring_bench.c)
target_link_libraries(bench_cstring cstring profiler)

# Build tests for cstring
add_executable(test_number number_test.c)
target_link_libraries(test_number cstring)
add_test(test_number ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_number)

add_executable(bench_number number_bench.c)
target_link_libraries(bench_number cstring)
