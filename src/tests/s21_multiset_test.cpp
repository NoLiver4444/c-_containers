#include "s21_test.h"

TEST(multiset, create_multiset) {
  s21::multiset<int> ms;
  std::multiset<int> orig_ms;

  EXPECT_EQ(ms.size(), orig_ms.size());
}

TEST(multiset, create_with_el_multiset) {
  s21::multiset<int> ms = {1, 2, 3};
  std::multiset<int> orig_ms = {1, 2, 3};

  EXPECT_EQ(ms.size(), orig_ms.size());
}

TEST(multiset, move_multiset) {
  s21::multiset<int> ms = {1, 2, 3};
  s21::multiset<int> ms_2 = std::move(ms);

  EXPECT_EQ(ms.size(), 0);
  EXPECT_EQ(ms_2.size(), 3);
}

TEST(multiset, copy_multiset) {
  s21::multiset<int> ms = {1, 2, 3};
  s21::multiset<int> ms_2(ms);

  EXPECT_EQ(ms.size(), ms_2.size());

  auto it_1 = ms.begin();
  auto it_2 = ms_2.begin();
  for (; it_1 != ms.end(); ++it_1, ++it_2) {
    EXPECT_TRUE(*it_2 == *it_1);
  }
}

TEST(multiset, create_duplicate_multiset) {
  s21::multiset<int> ms = {1, 2, 3, 4, 5, 2};
  std::multiset<int> orig_ms = {1, 2, 3, 4, 5, 2};

  EXPECT_EQ(ms.size(), orig_ms.size());

  auto it_1 = ms.begin();
  auto it_2 = orig_ms.begin();
  for (; it_1 != ms.end(); ++it_1, ++it_2) {
    EXPECT_TRUE(*it_2 == *it_1);
  }
  ms.print();
}

TEST(multiset, create_duplicate_hard_multiset) {
  s21::multiset<int> ms = {1, 2, 3, 4, 5, 2, 2, 2, 2, 2, 2,  2, 2,
                           2, 2, 2, 2, 2, 2, 2, 2, 4, 4, 4,  4, 4,
                           4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 10, 1};
  std::multiset<int> orig_ms = {1, 2, 3, 4, 5, 2, 2, 2, 2, 2, 2,  2, 2,
                                2, 2, 2, 2, 2, 2, 2, 2, 4, 4, 4,  4, 4,
                                4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 10, 1};

  EXPECT_EQ(ms.size(), orig_ms.size());

  auto it_1 = ms.begin();
  auto it_2 = orig_ms.begin();
  for (; it_1 != ms.end(); ++it_1, ++it_2) {
    EXPECT_TRUE(*it_2 == *it_1);
  }
  ms.print();
}

TEST(multiset, multiset_insert) {
  s21::multiset<int> ms = {1, 2, 3, 4, 5, 2};
  std::multiset<int> orig_ms = {1, 2, 3, 4, 5, 2};

  ms.insert(2);
  ms.insert(3);
  ms.insert(4);
  ms.insert(11);
  ms.insert(1);

  orig_ms.insert(2);
  orig_ms.insert(3);
  orig_ms.insert(4);
  orig_ms.insert(11);
  orig_ms.insert(1);

  EXPECT_EQ(ms.size(), orig_ms.size());

  auto it_1 = ms.begin();
  auto it_2 = orig_ms.begin();
  for (; it_1 != ms.end(); ++it_1, ++it_2) {
    EXPECT_TRUE(*it_2 == *it_1);
  }
  ms.print();
}

TEST(multiset, multiset_oper) {
  s21::multiset<int> ms = {1, 2, 3, 4, 5, 2};
  s21::multiset<int> ms_2 = std::move(ms);
  s21::multiset<int> answ = {1, 2, 3, 4, 5, 2};

  EXPECT_EQ(ms.size(), 0);
  EXPECT_EQ(ms_2.size(), answ.size());

  auto it_1 = answ.begin();
  auto it_2 = ms_2.begin();
  for (; it_1 != answ.end(); ++it_1, ++it_2) {
    EXPECT_TRUE(*it_2 == *it_1);
  }
  ms_2.print();
}

TEST(multiset, multiset_erase) {
  s21::multiset<int> ms = {1, 2, 3, 4, 5, 2};
  std::multiset<int> orig_ms = {1, 2, 3, 4, 5, 2};

  ms.erase(ms.find(2));
  orig_ms.erase(orig_ms.find(2));

  EXPECT_EQ(ms.size(), orig_ms.size());

  auto it_1 = ms.begin();
  auto it_2 = orig_ms.begin();
  for (; it_1 != ms.end(); ++it_1, ++it_2) {
    EXPECT_TRUE(*it_2 == *it_1);
  }
  ms.print();
}

TEST(multiset, multiset_erase_all) {
  s21::multiset<int> ms = {1, 2, 2};
  std::multiset<int> orig_ms = {1, 2, 2};

  ms.erase(ms.find(2));
  ms.erase(ms.find(2));
  ms.erase(ms.find(1));

  orig_ms.erase(orig_ms.find(2));
  orig_ms.erase(orig_ms.find(2));
  orig_ms.erase(orig_ms.find(1));

  EXPECT_EQ(ms.size(), orig_ms.size());
  EXPECT_EQ(ms.empty(), orig_ms.empty());

  auto it_1 = ms.begin();
  auto it_2 = orig_ms.begin();
  for (; it_1 != ms.end(); ++it_1, ++it_2) {
    EXPECT_TRUE(*it_2 == *it_1);
  }
  ms.print();
}

TEST(multiset, multiset_erase_many) {
  s21::multiset<int> ms = {1, 2, 2, 4, 5, 6, 7, 8, 9, 10};
  std::multiset<int> orig_ms = {1, 2, 2, 4, 5, 6, 7, 8, 9, 10};

  ms.erase(ms.find(2));
  ms.erase(ms.find(2));
  ms.erase(ms.find(1));
  ms.erase(ms.find(10));
  ms.erase(ms.find(7));
  ms.erase(ms.find(5));

  orig_ms.erase(orig_ms.find(2));
  orig_ms.erase(orig_ms.find(2));
  orig_ms.erase(orig_ms.find(1));
  orig_ms.erase(orig_ms.find(10));
  orig_ms.erase(orig_ms.find(7));
  orig_ms.erase(orig_ms.find(5));

  EXPECT_EQ(ms.size(), orig_ms.size());

  auto it_1 = ms.begin();
  auto it_2 = orig_ms.begin();
  for (; it_1 != ms.end(); ++it_1, ++it_2) {
    EXPECT_TRUE(*it_2 == *it_1);
  }
  ms.print();
}

TEST(multiset, multiset_swap) {
  s21::multiset<int> ms = {1, 2, 2, 4, 5, 6, 7, 8, 9, 10};
  s21::multiset<int> ms_2 = {9, 8, 7, 6, 5, 4, 3, 2, 1};

  s21::multiset<int> answ = {1, 2, 2, 4, 5, 6, 7, 8, 9, 10};
  s21::multiset<int> answ_2 = {9, 8, 7, 6, 5, 4, 3, 2, 1};

  ms.swap(ms_2);

  EXPECT_EQ(ms.size(), 9);
  EXPECT_EQ(ms_2.size(), 10);

  auto it_1 = ms.begin();
  auto it_2 = answ_2.begin();
  for (; it_1 != ms.end(); ++it_1, ++it_2) {
    EXPECT_TRUE(*it_2 == *it_1);
  }

  it_1 = ms_2.begin();
  it_2 = answ.begin();
  for (; it_1 != ms.end(); ++it_1, ++it_2) {
    EXPECT_TRUE(*it_2 == *it_1);
  }
  ms.print();
}

TEST(multiset, multiset_merge) {
  s21::multiset<int> ms = {1, 2, 2, 4, 5, 6, 7, 8, 9, 10};
  s21::multiset<int> ms_2 = {9, 8, 7, 6, 5, 4, 3, 2, 1};

  std::multiset<int> answ = {1, 2, 2, 4, 5, 6, 7, 8, 9, 10};
  std::multiset<int> answ_2 = {9, 8, 7, 6, 5, 4, 3, 2, 1};

  ms.merge(ms_2);
  answ.merge(answ_2);

  EXPECT_EQ(ms.size(), answ.size());
  EXPECT_EQ(ms_2.size(), answ_2.size());

  auto it_1 = ms.begin();
  auto it_2 = answ.begin();
  for (; it_1 != ms.end(); ++it_1, ++it_2) {
    EXPECT_TRUE(*it_2 == *it_1);
  }

  it_1 = ms_2.begin();
  it_2 = answ_2.begin();
  for (; it_1 != ms.end(); ++it_1, ++it_2) {
    EXPECT_TRUE(*it_2 == *it_1);
  }
  ms.print();
}

TEST(multiset, multiset_count) {
  s21::multiset<int> ms = {1, 2, 3, 4, 5, 2, 2, 2, 2, 2, 2, 2, 2,
                           2, 2, 2, 2, 2, 2, 2, 2, 4, 4, 4, 4, 4,
                           4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 10};
  std::multiset<int> orig_ms = {1, 2, 3, 4, 5, 2, 2, 2, 2, 2, 2, 2, 2,
                                2, 2, 2, 2, 2, 2, 2, 2, 4, 4, 4, 4, 4,
                                4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 10};

  EXPECT_EQ(ms.count(2), orig_ms.count(2));
  EXPECT_EQ(ms.count(4), orig_ms.count(4));

  ms.print();
}

TEST(multiset, multiset_contains) {
  s21::multiset<int> ms = {1, 2, 3, 4, 5, 2, 2, 2, 2, 2, 2, 2, 2,
                           2, 2, 2, 2, 2, 2, 2, 2, 4, 4, 4, 4, 4,
                           4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 10};

  EXPECT_EQ(ms.contains(2), true);
  EXPECT_EQ(ms.contains(20), false);

  ms.print();
}

TEST(multiset, multiset_equal_range) {
  s21::multiset<int> ms = {1, 2, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                           2, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4};
  std::multiset<int> orig_ms = {1, 2, 4, 2, 2, 2, 2, 2, 2, 2, 2,
                                2, 2, 2, 2, 2, 2, 2, 2, 4, 4, 4,
                                4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4};

  EXPECT_EQ(*ms.equal_range(2).first, *orig_ms.equal_range(2).first);
  EXPECT_EQ(*ms.equal_range(2).second, *orig_ms.equal_range(2).second);
}

TEST(multiset, multiset_equal_range_2) {
  s21::multiset<int> ms = {1, 2, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                           2, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 10};
  std::multiset<int> orig_ms = {1, 2, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                                2, 2, 2, 2, 2, 2, 2, 4, 4, 4, 4, 4,
                                4, 4, 4, 4, 4, 4, 4, 4, 4, 10};

  EXPECT_EQ(*ms.equal_range(5).first, *orig_ms.equal_range(5).first);
  EXPECT_EQ(*ms.equal_range(5).second, *orig_ms.equal_range(5).second);
}

TEST(multiset, multiset_insert_many) {
  s21::multiset<char> multiset = {'a', 'b', 'c', 'd'};

  multiset.print();

  multiset.insert_many('f', 'e', 'a', 'h', 'c');

  multiset.print();

  EXPECT_TRUE(multiset.size() == 9);
}
