extern "C" {
#include "data-structures/arrays/c/cvector.h"
}

#include "gtest/gtest.h"

class VectorTest : public ::testing::Test {
 protected:
  void SetUp() override { obj_ = cvector_new(); }

  void TearDown() override { cvector_delete(obj_); }

  cvector *obj_;
};

TEST_F(VectorTest, Init) { EXPECT_EQ(cvector_size(obj_), 0); }

TEST_F(VectorTest, Resize) {
  cvector_resize(obj_, 1);
  EXPECT_EQ(cvector_size(obj_), 1);
}

TEST_F(VectorTest, Capacity) {
  EXPECT_GE(cvector_capacity(obj_), 0);
  cvector_resize(obj_, 1);
  EXPECT_GE(cvector_capacity(obj_), 1);
}

TEST_F(VectorTest, IsEmpty) {
  EXPECT_TRUE(cvector_is_empty(obj_));
  cvector_resize(obj_, 1);
  EXPECT_FALSE(cvector_is_empty(obj_));
}

TEST_F(VectorTest, AtIndex) {
  EXPECT_DEATH(cvector_at(obj_, 0), "Assertion failed:.*function cvector_at");
  cvector_resize(obj_, 1);
  EXPECT_EQ(cvector_at(obj_, 0), 0);
}

TEST_F(VectorTest, SetIndex) {
  cvector_set(obj_, 0, 1);
  EXPECT_EQ(cvector_at(obj_, 0), 1);
}