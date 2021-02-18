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

TEST_F(VectorTest, Init) { EXPECT_EQ(cvector_size_ints(obj_), 0); }

TEST_F(VectorTest, Resize) {
  cvector_resize_ints(obj_, 1);
  EXPECT_EQ(cvector_size_ints(obj_), 1);
}

TEST_F(VectorTest, Capacity) {
  EXPECT_GE(cvector_capacity_ints(obj_), 0);
  cvector_resize_ints(obj_, 1);
  EXPECT_GE(cvector_capacity_ints(obj_), 1);
}

TEST_F(VectorTest, IsEmpty) {
  EXPECT_TRUE(cvector_is_empty(obj_));
  cvector_resize_ints(obj_, 1);
  EXPECT_FALSE(cvector_is_empty(obj_));
}

TEST_F(VectorTest, AtIndex) {
  EXPECT_DEATH(cvector_at_int(obj_, 0),
               "Assertion failed:.*function cvector_at");
  cvector_resize_ints(obj_, 1);
  EXPECT_EQ(cvector_at_int(obj_, 0), 0);
}

TEST_F(VectorTest, SetIndex) {
  cvector_set_int(obj_, 0, 1);
  EXPECT_EQ(cvector_at_int(obj_, 0), 1);
}

TEST(VectorUtilTest, RoundUpToPowerOfTwo) {
  EXPECT_EQ(cvector_round_up_to_power_of_two(0), 1);
  EXPECT_EQ(cvector_round_up_to_power_of_two(1), 1);
  EXPECT_EQ(cvector_round_up_to_power_of_two(2), 2);
}