add_library(cvector cvector.c cvector.h)

add_executable(cvector-test cvector_test.cc)
target_link_libraries(cvector-test gtest_main cvector)
