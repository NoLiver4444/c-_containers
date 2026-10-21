#include "s21_test.h"

TEST(vector, create_vector) {
  s21::vector<int> v;
  std::vector<int> orig_v;

  EXPECT_EQ(v.size(), orig_v.size());
}

TEST(vector, create_with_size_vector) {
  s21::vector<int> v(10);
  std::vector<int> orig_v(10);

  EXPECT_EQ(v.size(), orig_v.size());
}

TEST(vector, create_data_vector) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  std::vector<int> orig_v = {1, 2, 3, 4, 5};

  EXPECT_EQ(v.size(), orig_v.size());
}

TEST(vector, copy_vector) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  s21::vector<int> v_2(v);

  EXPECT_EQ(v.size(), v_2.size());
}

TEST(vector, move_vector) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  s21::vector<int> v_2(std::move(v));

  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v_2.size(), 5);
}

TEST(vector, operator_eq_move_vector_1) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  s21::vector<int> v_2 = std::move(v);

  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v_2.size(), 5);
}

TEST(vector, operator_eq_move_vector_2) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  s21::vector<int> v_2 = {1, 2, 3, 4, 5};
  v = std::move(v_2);

  EXPECT_EQ(v.size(), 5);
}

TEST(vector, capacity_vector) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  std::vector<int> orig_v = {1, 2, 3, 4, 5};

  EXPECT_EQ(v.capacity(), orig_v.capacity());
}

TEST(vector, swap_vector) {
  s21::vector<int> v_1 = {1, 2, 3, 4, 5};
  s21::vector<int> v_2 = {6, 7, 8, 9, 10, 11, 12};

  std::vector<int> orig_v_1 = {1, 2, 3, 4, 5};
  std::vector<int> orig_v_2 = {6, 7, 8, 9, 10, 11, 12};

  v_1.swap(v_2);
  orig_v_1.swap(orig_v_2);

  EXPECT_EQ(v_1.capacity(), orig_v_1.capacity());
  EXPECT_EQ(v_2.capacity(), orig_v_2.capacity());

  for (int i = 0; i < 7; ++i) {
    EXPECT_EQ(v_1[i], orig_v_1[i]);
  }

  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(v_2[i], orig_v_2[i]);
  }
}

TEST(vector, index_out_range_vector) {
  s21::vector<int> v = {1, 2, 3, 4, 5};

  EXPECT_THROW(v[10];, std::logic_error);
}

TEST(vector, at_vector) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  std::vector<int> orig_v = {1, 2, 3, 4, 5};

  EXPECT_EQ(v.at(3), orig_v.at(3));
}

TEST(vector, at_out_range_vector) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  std::vector<int> orig_v = {1, 2, 3, 4, 5};

  EXPECT_THROW(v.at(10);, std::logic_error);
}

TEST(vector, front_vector) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  std::vector<int> orig_v = {1, 2, 3, 4, 5};

  EXPECT_EQ(v.front(), orig_v.front());
}

TEST(vector, empty_front_vector) {
  s21::vector<int> v = {};

  EXPECT_THROW(v.front();, std::logic_error);
}

TEST(vector, back_vector) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  std::vector<int> orig_v = {1, 2, 3, 4, 5};

  EXPECT_EQ(v.back(), orig_v.back());
}

TEST(vector, empty_back_vector) {
  s21::vector<int> v = {};

  EXPECT_THROW(v.back();, std::logic_error);
}

TEST(vector, data_vector) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  std::vector<int> orig_v = {1, 2, 3, 4, 5};

  EXPECT_EQ(v.data()[1], orig_v.data()[1]);
}

TEST(vector, iterator_vector_1) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  std::vector<int> orig_v = {1, 2, 3, 4, 5};

  auto iter = v.begin();
  auto orig_iter = orig_v.begin();

  EXPECT_EQ(*iter, *orig_iter);

  ++iter;
  ++orig_iter;

  EXPECT_EQ(*iter, *orig_iter);

  *iter = 20;
  *orig_iter = 20;

  EXPECT_EQ(*iter, 20);
  EXPECT_EQ(*iter, *orig_iter);

  EXPECT_EQ(*(iter++), 3);
}

TEST(vector, iterator_vector_2) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  std::vector<int> orig_v = {1, 2, 3, 4, 5};

  auto iter = v.end();
  auto orig_iter = orig_v.end();

  --iter;
  --orig_iter;

  EXPECT_EQ(*iter, *orig_iter);

  --iter;
  --orig_iter;

  EXPECT_EQ(*iter, *orig_iter);

  *iter = 40;
  *orig_iter = 40;

  EXPECT_EQ(*iter, 40);
  EXPECT_EQ(*iter, *orig_iter);

  EXPECT_EQ(*(iter--), 3);
}

TEST(vector, iterator_vector_3) {
  s21::vector<int> v_1 = {1, 2, 3, 4, 5};

  auto iter_1 = v_1.begin();
  auto iter_2 = v_1.begin();

  ++iter_1;
  ++iter_2;

  EXPECT_TRUE(iter_1 == iter_2);

  ++iter_2;

  EXPECT_TRUE(iter_1 != iter_2);
}

TEST(vector, const_iterator_vector_1) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  std::vector<int> orig_v = {1, 2, 3, 4, 5};

  auto iter = v.cbegin();
  auto orig_iter = orig_v.cbegin();

  EXPECT_EQ(*iter, *orig_iter);

  ++iter;
  ++orig_iter;

  EXPECT_EQ(*iter, *orig_iter);

  EXPECT_EQ(*(iter++), 3);
}

TEST(vector, const_iterator_vector_2) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  std::vector<int> orig_v = {1, 2, 3, 4, 5};

  auto iter = v.cend();
  auto orig_iter = orig_v.cend();

  --iter;
  --orig_iter;

  EXPECT_EQ(*iter, *orig_iter);

  --iter;
  --orig_iter;

  EXPECT_EQ(*iter, *orig_iter);

  EXPECT_EQ(*(iter--), 3);
}

TEST(vector, const_iterator_vector_3) {
  s21::vector<int> v_1 = {1, 2, 3, 4, 5};

  auto iter_1 = v_1.cbegin();
  auto iter_2 = v_1.cbegin();

  ++iter_1;
  ++iter_2;

  EXPECT_TRUE(iter_1 == iter_2);

  ++iter_2;

  EXPECT_TRUE(iter_1 != iter_2);
}

TEST(vector, empty_vector) {
  s21::vector<int> v;
  std::vector<int> orig_v;

  EXPECT_TRUE(v.empty() == orig_v.empty());
}

TEST(vector, not_empty_vector) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  std::vector<int> orig_v = {1, 2, 3, 4, 5};

  EXPECT_TRUE(v.empty() == orig_v.empty());
}

TEST(vector, insert_vector_1) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  std::vector<int> orig_v = {1, 2, 3, 4, 5};

  v.insert(++v.begin(), 6);
  orig_v.insert(++orig_v.begin(), 6);

  EXPECT_TRUE(*(++v.begin()) == *(++orig_v.begin()));
}

TEST(vector, insert_vector_2) {
  s21::vector<int> v = {1, 2, 3, 4, 5};

  EXPECT_THROW(v.insert(++v.end(), 6);, std::logic_error);
}

TEST(vector, insert_vector_3) {
  s21::vector<int> v = {1, 2, 3, 4, 5};

  EXPECT_THROW(v.insert(--v.begin(), 6);, std::logic_error);
}

TEST(vector, erase_vector_1) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  std::vector<int> orig_v = {1, 2, 3, 4, 5};

  v.erase(v.begin());
  orig_v.erase(orig_v.begin());

  EXPECT_TRUE(v.size() == orig_v.size());

  for (int i = 0; i < 4; ++i) {
    EXPECT_TRUE(v[i] == orig_v[i]);
  }
}

TEST(vector, erase_vector_2) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  std::vector<int> orig_v = {1, 2, 3, 4, 5};

  v.erase(--v.end());
  orig_v.erase(--orig_v.end());

  EXPECT_TRUE(v.size() == orig_v.size());

  for (int i = 0; i < 4; ++i) {
    EXPECT_TRUE(v[i] == orig_v[i]);
  }
}

TEST(vector, erase_vector_3) {
  s21::vector<int> v = {1, 2, 3, 4, 5};

  EXPECT_THROW(v.erase(++v.end());, std::logic_error);
}

TEST(vector, push_back_vector_1) {
  s21::vector<int> v;
  std::vector<int> orig_v;

  v.push_back(1);
  orig_v.push_back(1);

  EXPECT_TRUE(v.size() == orig_v.size());

  for (size_t i = 0; i < v.size(); ++i) {
    EXPECT_TRUE(v[i] == orig_v[i]);
  }
}

TEST(vector, push_back_vector_2) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  std::vector<int> orig_v = {1, 2, 3, 4, 5};

  v.push_back(6);
  orig_v.push_back(6);

  EXPECT_TRUE(v.size() == orig_v.size());

  for (size_t i = 0; i < v.size(); ++i) {
    EXPECT_TRUE(v[i] == orig_v[i]);
  }
}

TEST(vector, push_back_vector_3) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  std::vector<int> orig_v = {1, 2, 3, 4, 5};

  for (int i = 6; i < 10001; ++i) {
    v.push_back(i);
    orig_v.push_back(i);
  }

  EXPECT_TRUE(v.size() == orig_v.size());

  for (size_t i = 0; i < v.size(); ++i) {
    EXPECT_TRUE(v[i] == orig_v[i]);
  }
}

TEST(vector, pop_back_vector_1) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  std::vector<int> orig_v = {1, 2, 3, 4, 5};

  for (int i = 0; i < 5; ++i) {
    v.pop_back();
    orig_v.pop_back();
  }

  EXPECT_TRUE(v.size() == orig_v.size());
  EXPECT_TRUE(v.size() == 0);

  for (size_t i = 0; i < v.size(); ++i) {
    EXPECT_TRUE(v[i] == orig_v[i]);
  }
}

TEST(vector, pop_back_vector_2) {
  s21::vector<int> v = {1, 2, 3, 4, 5};

  for (int i = 0; i < 5; ++i) {
    v.pop_back();
  }

  EXPECT_THROW(v.pop_back();, std::logic_error);
}

TEST(vector, pop_back_vector_3) {
  s21::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::vector<int> orig_v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  for (int i = 0; i < 5; ++i) {
    v.pop_back();
    orig_v.pop_back();

    v.push_back(i);
    orig_v.push_back(i);

    v.pop_back();
    orig_v.pop_back();
  }

  EXPECT_TRUE(v.size() == orig_v.size());

  for (size_t i = 0; i < v.size(); ++i) {
    EXPECT_TRUE(v[i] == orig_v[i]);
  }
}

TEST(vector, reserve_vector_1) {
  s21::vector<int> v;
  size_t initialCapacity = v.capacity();
  size_t newCapacity = initialCapacity + 10;
  v.reserve(newCapacity);
  EXPECT_GE(v.capacity(), newCapacity);
}

TEST(vector, reserve_vector_2) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  size_t initialCapacity = v.capacity();
  size_t newCapacity = initialCapacity - 2;
  v.reserve(newCapacity);
  EXPECT_LE(v.capacity(), initialCapacity);
  EXPECT_GE(v.capacity(), newCapacity);
}

TEST(vector, reserve_vector_3) {
  s21::vector<int> v = {1, 2, 3, 4, 5};

  EXPECT_THROW(v.reserve(v.max_size() + 1);, std::logic_error);
}

TEST(vector, insert_many_vector) {
  s21::vector<int> v = {1, 2, 5, 6};
  auto it = v.insert_many(v.cbegin() + 2, 3, 4);

  ASSERT_EQ(v.size(), 6);
  EXPECT_EQ(*it, 5);
}

TEST(vector, insert_many_back_vector) {
  s21::vector<double> v = {1.1, 2.2};
  v.insert_many_back(3.3, 4.4);

  ASSERT_EQ(v.size(), 4);
  EXPECT_DOUBLE_EQ(v[2], 3.3);
  EXPECT_DOUBLE_EQ(v[3], 4.4);
}