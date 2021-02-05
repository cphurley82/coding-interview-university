extern "C" {
#include "data-structures/arrays/c/cvector.h"
}

#include "gtest/gtest.h"

TEST(Vector, Init) {
  cvector* obj = cvector_new();
  EXPECT_EQ(cvector_size(obj), 0);
}