extern "C" {
#include "data-structures/arrays/c/cvector.h"
}

#include "gtest/gtest.h"

class CVectorTest : public ::testing::Test {
 protected:
  void SetUp() override { obj_ = cvector_new(); }

  void TearDown() override { cvector_delete(obj_); }

  cvector *obj_;
};

TEST_F(CVectorTest, Init) { EXPECT_EQ(cvector_size_ints(obj_), 0); }

TEST_F(CVectorTest, Resize) {
  cvector_resize_ints(obj_, 1);
  EXPECT_EQ(cvector_size_ints(obj_), 1);

  // Write something, resize enough to force new data to be allocated and
  // ensure old data was copied over.
  cvector_set_int(obj_, 0, 1);
  cvector_resize_ints(obj_, 1024);
  EXPECT_EQ(cvector_at_int(obj_, 0), 1);
}

TEST_F(CVectorTest, Capacity) {
  EXPECT_GE(cvector_capacity_ints(obj_), 0);
  cvector_resize_ints(obj_, 1);
  EXPECT_GE(cvector_capacity_ints(obj_), 1);
}

TEST_F(CVectorTest, IsEmpty) {
  EXPECT_TRUE(cvector_is_empty(obj_));
  cvector_resize_ints(obj_, 1);
  EXPECT_FALSE(cvector_is_empty(obj_));
}

TEST_F(CVectorTest, AtIndex) {
  EXPECT_DEATH(cvector_at_int(obj_, 0),
               "Assertion failed:.*function cvector_at");
  cvector_resize_ints(obj_, 1);
  EXPECT_EQ(cvector_at_int(obj_, 0), 0);

  for (int i = 0; i < 10; i++) {
    cvector_set_int(obj_, i, i);
  }

  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(cvector_at_int(obj_, i), i) << "i=" << i;
  }
}

TEST_F(CVectorTest, SetIndex) {
  cvector_set_int(obj_, 0, 1);
  EXPECT_EQ(cvector_at_int(obj_, 0), 1);
}

TEST_F(CVectorTest, SetGetBytes) {
  cvector_set_byte(obj_, 1, 1);
  ASSERT_EQ(cvector_size_bytes(obj_), 2);
}

TEST(CVectorUtilTest, RoundUpToPowerOfTwo) {
  EXPECT_EQ(cvector_util_round_up_to_power_of_two(0), 1);
  EXPECT_EQ(cvector_util_round_up_to_power_of_two(1), 1);
  EXPECT_EQ(cvector_util_round_up_to_power_of_two(2), 2);
}

TEST(CVectorUtilTest, DetermineCapacity) {
  EXPECT_EQ(cvector_util_determine_min_capacity_ints_from_size_bytes(0), 0);
}

TEST_F(CVectorTest, ResizeBytes) {
  cvector_resize_bytes(obj_, 1);
  EXPECT_EQ(cvector_size_bytes(obj_), 1);

  cvector_resize_bytes(obj_, 0);
  EXPECT_EQ(cvector_size_bytes(obj_), 0);

  // Something not evenly divisible into sizeof(int).
  cvector_resize_bytes(obj_, 9);
  EXPECT_EQ(cvector_size_bytes(obj_), 9);

  // Write something, resize enough to force new data to be allocated and
  // ensure old data was copied over.
  cvector_set_byte(obj_, 0, 1);
  cvector_resize_bytes(obj_, 1024);
  EXPECT_EQ(cvector_at_byte(obj_, 0), 1);
}

TEST_F(CVectorTest, AtByteIndex) {
  EXPECT_DEATH(cvector_at_byte(obj_, 0),
               "Assertion failed:.*function cvector_at");
  cvector_resize_bytes(obj_, 1);
  EXPECT_EQ(cvector_at_byte(obj_, 0), 0);

  for (int i = 0; i < 10; i++) {
    cvector_set_byte(obj_, i, i);
  }

  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(cvector_at_byte(obj_, i), i) << "i=" << i;
  }
}

TEST_F(CVectorTest, PushInt) {
  for (int i = 0; i < 10; i++) {
    cvector_push_int(obj_, i);
  }

  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(cvector_at_int(obj_, i), i) << "i=" << i;
  }
}

TEST_F(CVectorTest, PushByte) {
  for (int i = 0; i < 10; i++) {
    cvector_push_byte(obj_, i);
  }

  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(cvector_at_byte(obj_, i), i) << "i=" << i;
  }
}

TEST_F(CVectorTest, PushMixed) {
  cvector_push_int(obj_, 0xABCDEF);
  cvector_push_byte(obj_, 1);
  EXPECT_EQ(cvector_at_int(obj_, 0), 0xABCDEF);
  EXPECT_EQ(cvector_at_byte(obj_, sizeof(int)), 1);
  EXPECT_EQ(cvector_size_bytes(obj_), sizeof(int) + 1);
  EXPECT_EQ(cvector_size_ints(obj_), 1);

  for (int i = 1; i < sizeof(int); i++) {
    cvector_push_byte(obj_, i + 1);
  }

  EXPECT_EQ(cvector_size_ints(obj_), 2);
  EXPECT_EQ(cvector_size_bytes(obj_), sizeof(int) * 2);

  for (int i = 0; i < sizeof(int); i++) {
    EXPECT_EQ(cvector_at_byte(obj_, i + sizeof(int)), i + 1) << "i=" << i;
  }
}

TEST_F(CVectorTest, InsertInt) {
  cvector_set_int(obj_, 0, 1);
  cvector_set_int(obj_, 1, 3);

  cvector_insert_int(obj_, 1, 2);

  EXPECT_EQ(cvector_at_int(obj_, 0), 1);
  EXPECT_EQ(cvector_at_int(obj_, 1), 2);
  EXPECT_EQ(cvector_at_int(obj_, 2), 3);
}

TEST_F(CVectorTest, InsertByte) {
  cvector_set_byte(obj_, 0, 1);
  cvector_set_byte(obj_, 1, 3);

  cvector_insert_byte(obj_, 1, 2);

  EXPECT_EQ(cvector_at_byte(obj_, 0), 1);
  EXPECT_EQ(cvector_at_byte(obj_, 1), 2);
  EXPECT_EQ(cvector_at_byte(obj_, 2), 3);
}

TEST_F(CVectorTest, InsertMixed) {
  cvector_set_int(obj_, 0, UINT_MAX);  // All 0xF.
  cvector_insert_byte(obj_, 1, 0);

  EXPECT_EQ(cvector_at_byte(obj_, 0), 0xFF);
  EXPECT_EQ(cvector_at_byte(obj_, 1), 0);
  EXPECT_EQ(cvector_at_byte(obj_, 2), 0xFF);
  EXPECT_EQ(cvector_at_byte(obj_, 3), 0xFF);
  EXPECT_EQ(cvector_at_byte(obj_, 4), 0xFF);

  cvector_insert_int(obj_, 1, 1);

  EXPECT_EQ(cvector_at_byte(obj_, 0), 0xFF);
  EXPECT_EQ(cvector_at_byte(obj_, 1), 0);
  EXPECT_EQ(cvector_at_byte(obj_, 2), 0xFF);
  EXPECT_EQ(cvector_at_byte(obj_, 3), 0xFF);

  EXPECT_EQ(cvector_at_int(obj_, 1), 1);
}

TEST_F(CVectorTest, PrependInt) {
  cvector_push_int(obj_, UINT_MAX);
  cvector_prepend_int(obj_, 1);
  EXPECT_EQ(cvector_at_int(obj_, 0), 1);
  EXPECT_EQ(cvector_at_int(obj_, 1), UINT_MAX);
}

TEST_F(CVectorTest, PrependByte) {
  cvector_push_byte(obj_, UCHAR_MAX);
  cvector_prepend_byte(obj_, 1);
  EXPECT_EQ(cvector_at_byte(obj_, 0), 1);
  EXPECT_EQ(cvector_at_byte(obj_, 1), UCHAR_MAX);
}

TEST_F(CVectorTest, PrependMixed) {
  cvector_prepend_int(obj_, 0);
  cvector_prepend_byte(obj_, 1);
  EXPECT_EQ(cvector_at_byte(obj_, 0), 1);
  EXPECT_EQ(cvector_at_byte(obj_, 1), 0);
}

TEST_F(CVectorTest, PopInt) {
  for (auto i = 0; i < 10; i++) {
    cvector_push_int(obj_, i);
  }

  for (auto i = 9; i >= 0; i--) {
    EXPECT_EQ(cvector_pop_int(obj_), i);
  }
}

TEST_F(CVectorTest, PopByte) {
  for (auto i = 0; i < 10; i++) {
    cvector_push_byte(obj_, i);
  }

  for (auto i = 9; i >= 0; i--) {
    EXPECT_EQ(cvector_pop_byte(obj_), i);
  }
}

TEST_F(CVectorTest, PopMixed) {
  cvector_push_int(obj_, UINT_MAX);
  cvector_push_byte(obj_, 1);

  EXPECT_EQ(cvector_pop_byte(obj_), 1);
  EXPECT_EQ(cvector_pop_int(obj_), UINT_MAX);
}