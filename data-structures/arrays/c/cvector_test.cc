extern "C" {
#include "data-structures/arrays/c/cvector.h"
}

#include "gtest/gtest.h"

class CVectorFixture : public ::testing::Test {
 protected:
  void SetUp() override { obj_ = cvector_new(); }

  void TearDown() override { cvector_delete(obj_); }

  cvector *obj_;
};

TEST_F(CVectorFixture, Init) { EXPECT_EQ(cvector_size_ints(obj_), 0); }

TEST_F(CVectorFixture, Resize) {
  cvector_resize_ints(obj_, 1);
  EXPECT_EQ(cvector_size_ints(obj_), 1);

  // Write something, resize enough to force new data to be allocated and
  // ensure old data was copied over.
  cvector_set_int(obj_, 0, 1);
  cvector_resize_ints(obj_, 1024);
  EXPECT_EQ(cvector_at_int(obj_, 0), 1);
}

TEST_F(CVectorFixture, CapacityDoublesWhenPushing) {
  EXPECT_EQ(cvector_capacity_ints(obj_), 0);

  cvector_push_int(obj_, 0);  // Size 1.
  EXPECT_EQ(cvector_capacity_ints(obj_), 1);

  cvector_push_int(obj_, 0);  // Size 2.
  EXPECT_EQ(cvector_capacity_ints(obj_), 2);

  cvector_push_int(obj_, 0);  // Size 3.
  EXPECT_EQ(cvector_capacity_ints(obj_), 4);

  cvector_push_int(obj_, 0);  // Size 4.
  EXPECT_EQ(cvector_capacity_ints(obj_), 4);

  cvector_push_int(obj_, 0);  // Size 5.
  EXPECT_EQ(cvector_capacity_ints(obj_), 8);
}

TEST_F(CVectorFixture, CapacityShrinksToHalfWhenPoppingToQuarterFull) {
  cvector_push_int(obj_, 1);
  cvector_push_int(obj_, 2);
  cvector_push_int(obj_, 3);
  cvector_push_int(obj_, 4);
  cvector_push_int(obj_, 5);
  EXPECT_EQ(cvector_capacity_ints(obj_), 8);

  cvector_pop_int(obj_);  // Size 4.
  EXPECT_EQ(cvector_capacity_ints(obj_), 8);

  cvector_pop_int(obj_);  // Size 3.
  EXPECT_EQ(cvector_capacity_ints(obj_), 8);

  cvector_pop_int(obj_);  // Size 2.
  EXPECT_EQ(cvector_capacity_ints(obj_), 4);
}

TEST_F(CVectorFixture, Capacity) {
  EXPECT_GE(cvector_capacity_ints(obj_), 0);
  cvector_resize_ints(obj_, 1);
  EXPECT_GE(cvector_capacity_ints(obj_), 1);
}

TEST_F(CVectorFixture, IsEmpty) {
  EXPECT_TRUE(cvector_is_empty(obj_));
  cvector_resize_ints(obj_, 1);
  EXPECT_FALSE(cvector_is_empty(obj_));
}

TEST_F(CVectorFixture, AtIndex) {
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

TEST_F(CVectorFixture, SetIndex) {
  cvector_set_int(obj_, 0, 1);
  EXPECT_EQ(cvector_at_int(obj_, 0), 1);
}

TEST_F(CVectorFixture, SetGetBytes) {
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

TEST_F(CVectorFixture, ResizeBytes) {
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

TEST_F(CVectorFixture, AtByteIndex) {
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

TEST_F(CVectorFixture, PushInt) {
  for (int i = 0; i < 10; i++) {
    cvector_push_int(obj_, i);
  }

  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(cvector_at_int(obj_, i), i) << "i=" << i;
  }
}

TEST_F(CVectorFixture, PushByte) {
  for (int i = 0; i < 10; i++) {
    cvector_push_byte(obj_, i);
  }

  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(cvector_at_byte(obj_, i), i) << "i=" << i;
  }
}

TEST_F(CVectorFixture, PushMixed) {
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

TEST_F(CVectorFixture, InsertInt) {
  cvector_set_int(obj_, 0, 1);
  cvector_set_int(obj_, 1, 3);

  cvector_insert_int(obj_, 1, 2);

  EXPECT_EQ(cvector_at_int(obj_, 0), 1);
  EXPECT_EQ(cvector_at_int(obj_, 1), 2);
  EXPECT_EQ(cvector_at_int(obj_, 2), 3);
}

TEST_F(CVectorFixture, InsertByte) {
  cvector_set_byte(obj_, 0, 1);
  cvector_set_byte(obj_, 1, 3);

  cvector_insert_byte(obj_, 1, 2);

  EXPECT_EQ(cvector_at_byte(obj_, 0), 1);
  EXPECT_EQ(cvector_at_byte(obj_, 1), 2);
  EXPECT_EQ(cvector_at_byte(obj_, 2), 3);
}

TEST_F(CVectorFixture, InsertMixed) {
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

TEST_F(CVectorFixture, PrependInt) {
  cvector_push_int(obj_, UINT_MAX);
  cvector_prepend_int(obj_, 1);
  EXPECT_EQ(cvector_at_int(obj_, 0), 1);
  EXPECT_EQ(cvector_at_int(obj_, 1), UINT_MAX);
}

TEST_F(CVectorFixture, PrependByte) {
  cvector_push_byte(obj_, UCHAR_MAX);
  cvector_prepend_byte(obj_, 1);
  EXPECT_EQ(cvector_at_byte(obj_, 0), 1);
  EXPECT_EQ(cvector_at_byte(obj_, 1), UCHAR_MAX);
}

TEST_F(CVectorFixture, PrependMixed) {
  cvector_prepend_int(obj_, 0);
  cvector_prepend_byte(obj_, 1);
  EXPECT_EQ(cvector_at_byte(obj_, 0), 1);
  EXPECT_EQ(cvector_at_byte(obj_, 1), 0);
}

TEST_F(CVectorFixture, PopInt) {
  for (auto i = 0; i < 10; i++) {
    cvector_push_int(obj_, i);
  }

  for (auto i = 9; i >= 0; i--) {
    EXPECT_EQ(cvector_pop_int(obj_), i);
  }
}

TEST_F(CVectorFixture, PopByte) {
  for (auto i = 0; i < 10; i++) {
    cvector_push_byte(obj_, i);
  }

  for (auto i = 9; i >= 0; i--) {
    EXPECT_EQ(cvector_pop_byte(obj_), i);
  }
}

TEST_F(CVectorFixture, PopMixed) {
  cvector_push_int(obj_, UINT_MAX);
  cvector_push_byte(obj_, 1);

  EXPECT_EQ(cvector_pop_byte(obj_), 1);
  EXPECT_EQ(cvector_pop_int(obj_), UINT_MAX);
}

TEST_F(CVectorFixture, DeleteInt) {
  cvector_push_int(obj_, 0xA);
  cvector_push_int(obj_, 0xB);
  cvector_push_int(obj_, 0xC);
  cvector_push_int(obj_, 0xD);

  cvector_delete_int(obj_, 1);

  EXPECT_EQ(cvector_at_int(obj_, 0), 0xA);
  EXPECT_EQ(cvector_at_int(obj_, 1), 0xC);
  EXPECT_EQ(cvector_at_int(obj_, 2), 0xD);
}

TEST_F(CVectorFixture, DeleteByte) {
  cvector_push_byte(obj_, 0xA);
  cvector_push_byte(obj_, 0xB);
  cvector_push_byte(obj_, 0xC);
  cvector_push_byte(obj_, 0xD);

  cvector_delete_byte(obj_, 1);

  EXPECT_EQ(cvector_at_byte(obj_, 0), 0xA);
  EXPECT_EQ(cvector_at_byte(obj_, 1), 0xC);
  EXPECT_EQ(cvector_at_byte(obj_, 2), 0xD);
}

TEST_F(CVectorFixture, RemoveInt) {
  cvector_push_int(obj_, 0);
  cvector_push_int(obj_, 1);
  cvector_push_int(obj_, 2);
  cvector_push_int(obj_, 2);
  cvector_push_int(obj_, 3);
  cvector_push_int(obj_, 4);
  cvector_push_int(obj_, 0);

  cvector_remove_int(obj_, 3);
  EXPECT_EQ(cvector_at_int(obj_, 4), 4);
  EXPECT_EQ(cvector_size_ints(obj_), 6);

  cvector_remove_int(obj_, 2);
  EXPECT_EQ(cvector_at_int(obj_, 2), 4);
  EXPECT_EQ(cvector_size_ints(obj_), 4);

  cvector_remove_int(obj_, 0);
  EXPECT_EQ(cvector_at_int(obj_, 0), 1);
  EXPECT_EQ(cvector_at_int(obj_, 1), 4);
  EXPECT_EQ(cvector_size_ints(obj_), 2);
}

TEST_F(CVectorFixture, RemoveByte) {
  cvector_push_byte(obj_, 0);
  cvector_push_byte(obj_, 1);
  cvector_push_byte(obj_, 2);
  cvector_push_byte(obj_, 2);
  cvector_push_byte(obj_, 3);
  cvector_push_byte(obj_, 4);
  cvector_push_byte(obj_, 0);

  cvector_remove_byte(obj_, 3);
  EXPECT_EQ(cvector_at_byte(obj_, 4), 4);
  EXPECT_EQ(cvector_size_bytes(obj_), 6);

  cvector_remove_byte(obj_, 2);
  EXPECT_EQ(cvector_at_byte(obj_, 2), 4);
  EXPECT_EQ(cvector_size_bytes(obj_), 4);

  cvector_remove_byte(obj_, 0);
  EXPECT_EQ(cvector_at_byte(obj_, 0), 1);
  EXPECT_EQ(cvector_at_byte(obj_, 1), 4);
  EXPECT_EQ(cvector_size_bytes(obj_), 2);
}

TEST_F(CVectorFixture, FindInt) {
  cvector_push_int(obj_, 0);
  cvector_push_int(obj_, 1);
  cvector_push_int(obj_, 2);
  cvector_push_int(obj_, 2);
  cvector_push_int(obj_, 3);
  cvector_push_int(obj_, 4);
  cvector_push_int(obj_, 0);

  EXPECT_EQ(cvector_find_int(obj_, 0xA), -1);

  EXPECT_EQ(cvector_find_int(obj_, 0), 0);
  EXPECT_EQ(cvector_find_int(obj_, 1), 1);
  EXPECT_EQ(cvector_find_int(obj_, 2), 2);
  EXPECT_EQ(cvector_find_int(obj_, 3), 4);
  EXPECT_EQ(cvector_find_int(obj_, 4), 5);

  cvector_remove_int(obj_, 2);
  EXPECT_EQ(cvector_find_int(obj_, 2), -1);

  cvector_remove_int(obj_, 0);
  EXPECT_EQ(cvector_find_int(obj_, 0), -1);
}

TEST_F(CVectorFixture, FindByte) {
  cvector_push_byte(obj_, 0);
  cvector_push_byte(obj_, 1);
  cvector_push_byte(obj_, 2);
  cvector_push_byte(obj_, 2);
  cvector_push_byte(obj_, 3);
  cvector_push_byte(obj_, 4);
  cvector_push_byte(obj_, 0);

  EXPECT_EQ(cvector_find_byte(obj_, 0xA), -1);

  EXPECT_EQ(cvector_find_byte(obj_, 0), 0);
  EXPECT_EQ(cvector_find_byte(obj_, 1), 1);
  EXPECT_EQ(cvector_find_byte(obj_, 2), 2);
  EXPECT_EQ(cvector_find_byte(obj_, 3), 4);
  EXPECT_EQ(cvector_find_byte(obj_, 4), 5);

  cvector_remove_byte(obj_, 2);
  EXPECT_EQ(cvector_find_byte(obj_, 2), -1);

  cvector_remove_byte(obj_, 0);
  EXPECT_EQ(cvector_find_byte(obj_, 0), -1);
}
