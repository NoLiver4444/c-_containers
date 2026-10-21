#include "s21_test.h"

TEST(array, create_array) {
  s21::array<int, 0> a;
  std::array<int, 0> orig_a;

  EXPECT_EQ(a.size(), orig_a.size());
}

TEST(array, create_data_array) {
  s21::array<int, 5> a = {1, 2, 3, 4, 5};

  EXPECT_EQ(a.size(), 5);
}

TEST(array, copy_array) {
  s21::array<int, 5> a = {1, 2, 3, 4, 5};
  s21::array<int, 5> a_2(a);

  EXPECT_EQ(a.size(), a_2.size());
}

TEST(array, move_array) {
  s21::array<int, 5> a = {1, 2, 3, 4, 5};
  s21::array<int, 5> a_2(std::move(a));

  EXPECT_EQ(a.size(), 0);
  EXPECT_EQ(a_2.size(), 5);
}

TEST(array, operator_eq_move_array_1) {
  s21::array<int, 5> a = {1, 2, 3, 4, 5};
  s21::array<int, 5> a_2 = std::move(a);

  EXPECT_EQ(a.size(), 0);
  EXPECT_EQ(a_2.size(), 5);
}

TEST(array, operator_eq_move_array_2) {
  s21::array<int, 5> const a = {1, 2, 3, 4, 5};
  s21::array<int, 5> a_2 = std::move(a);

  EXPECT_EQ(a_2.size(), 5);
}

TEST(array, operator_eq_move_array_3) {
  s21::array<int, 5> a = {1, 2, 3, 4, 5};
  s21::array<int, 5> a_2 = {1, 2, 3, 4, 5};
  a = std::move(a_2);

  EXPECT_EQ(a.size(), 5);
}

TEST(array, swap_array) {
  s21::array<int, 5> a_1 = {1, 2, 3, 4, 5};
  s21::array<int, 5> a_2 = {6, 7, 8, 9, 10};

  std::array<int, 5> orig_a_1 = {1, 2, 3, 4, 5};
  std::array<int, 5> orig_a_2 = {6, 7, 8, 9, 10};

  a_1.swap(a_2);
  orig_a_1.swap(orig_a_2);

  EXPECT_EQ(a_1.size(), orig_a_1.size());
  EXPECT_EQ(a_2.size(), orig_a_2.size());

  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(a_1[i], orig_a_1[i]);
  }

  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(a_2[i], orig_a_2[i]);
  }
}

TEST(array, index_out_range_array) {
  s21::array<int, 5> a = {1, 2, 3, 4, 5};

  EXPECT_THROW(a[10];, std::logic_error);
}

TEST(array, at_array) {
  s21::array<int, 5> a = {1, 2, 3, 4, 5};
  std::array<int, 5> orig_a = {1, 2, 3, 4, 5};

  EXPECT_EQ(a.at(3), orig_a.at(3));
}

TEST(array, at_out_range_array) {
  s21::array<int, 5> a = {1, 2, 3, 4, 5};

  EXPECT_THROW(a.at(10);, std::logic_error);
}

TEST(array, front_array) {
  s21::array<int, 5> a = {1, 2, 3, 4, 5};
  std::array<int, 5> orig_a = {1, 2, 3, 4, 5};

  EXPECT_EQ(a.front(), orig_a.front());
}

TEST(array, back_array) {
  s21::array<int, 5> a = {1, 2, 3, 4, 5};
  std::array<int, 5> orig_a = {1, 2, 3, 4, 5};

  EXPECT_EQ(a.back(), orig_a.back());
}

TEST(array, data_array) {
  s21::array<int, 5> a = {1, 2, 3, 4, 5};
  std::array<int, 5> orig_a = {1, 2, 3, 4, 5};

  EXPECT_EQ(a.data()[1], orig_a.data()[1]);
}

TEST(array, iterator_array_1) {
  s21::array<int, 5> a = {1, 2, 3, 4, 5};
  std::array<int, 5> orig_a = {1, 2, 3, 4, 5};

  auto iter = a.begin();
  auto orig_iter = orig_a.begin();

  EXPECT_EQ(*iter, *orig_iter);

  ++iter;
  ++orig_iter;

  EXPECT_EQ(*iter, *orig_iter);

  EXPECT_EQ(*(iter++), 2);
}

TEST(array, iterator_array_2) {
  s21::array<int, 5> a = {1, 2, 3, 4, 5};
  std::array<int, 5> orig_a = {1, 2, 3, 4, 5};

  auto iter = a.end();
  auto orig_iter = orig_a.end();

  --iter;
  --orig_iter;

  EXPECT_EQ(*iter, *orig_iter);

  --iter;
  --orig_iter;

  EXPECT_EQ(*iter, *orig_iter);

  EXPECT_EQ(*(iter--), 4);
}

TEST(array, iterator_array_3) {
  s21::array<int, 5> a_1 = {1, 2, 3, 4, 5};

  auto iter_1 = a_1.begin();
  auto iter_2 = a_1.begin();

  ++iter_1;
  ++iter_2;

  EXPECT_TRUE(iter_1 == iter_2);

  ++iter_2;

  EXPECT_TRUE(iter_1 != iter_2);
}

TEST(array, empty_array_1) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  EXPECT_FALSE(arr.empty());
}

TEST(array, empty_array_2) {
  s21::array<int, 0> arr;
  EXPECT_TRUE(arr.empty());
}

TEST(array, operator_array) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};

  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_EQ(arr[i], static_cast<int>(i) + 1);
  }

  arr[2] = 10;
  EXPECT_EQ(arr[2], 10);
}

TEST(array, fill_array) {
  s21::array<int, 5> a_1 = {1, 2, 3, 4, 5};
  std::array<int, 5> orig_a_1 = {1, 2, 3, 4, 5};

  a_1.fill(0);
  orig_a_1.fill(0);

  EXPECT_EQ(a_1.size(), orig_a_1.size());

  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(a_1[i], orig_a_1[i]);
  }
}