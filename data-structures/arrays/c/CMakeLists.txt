add_library(cvector cvector.c cvector.h)
set_target_properties(cvector PROPERTIES LINKER_LANGUAGE C)

add_executable(cvector-test cvector_test.cc)
target_link_libraries(cvector-test gtest_main cvector)

add_executable(cvector-benchmark cvector_benchmark.cc)
target_link_libraries(cvector-benchmark benchmark::benchmark cvector)
set_target_properties(cvector-benchmark PROPERTIES CXX_STANDARD 20)