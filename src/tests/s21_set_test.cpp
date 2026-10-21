#include "s21_test.h"

TEST(set, create_set) {
  s21::set<int> s;
  std::set<int> orig_s;

  EXPECT_EQ(s.size(), orig_s.size());
}

TEST(set, size_set) {
  s21::set<char> my_set = {'x', 'b', 'z', 'y'};
  std::set<char> orig_set = {'x', 'b', 'z', 'y'};

  EXPECT_EQ(my_set.size(), orig_set.size());

  my_set.print();
  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  for (; my_it != my_set.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST(set, size_set_big) {
  s21::set<char> my_set = {'a', 'b', 'c', 'd', 'f', 'e', 'g', 'h', 'i',
                           'j', 'k', 'l', 'm', 'n', 'o', 'q', 'r', 'p'};
  std::set<char> orig_set = {'a', 'b', 'c', 'd', 'f', 'e', 'g', 'h', 'i',
                             'j', 'k', 'l', 'm', 'n', 'o', 'q', 'r', 'p'};

  EXPECT_EQ(my_set.size(), orig_set.size());

  my_set.print();
  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  for (; my_it != my_set.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST(set, copy_set) {
  s21::set<char> set_1 = {'x', 'b', 'z', 'y'};

  s21::set<char> set_2(set_1);

  EXPECT_EQ(set_1.size(), set_2.size());

  set_1.print();
  set_2.print();

  auto it_1 = set_1.begin();
  auto it_2 = set_2.begin();
  for (; it_1 != set_1.end(); ++it_1, ++it_2) {
    EXPECT_TRUE(*it_2 == *it_1);
  }
}

TEST(set, move_set) {
  s21::set<char> set_1 = {'x', 'b', 'z', 'y'};
  s21::set<char> empty_set = {};
  s21::set<char> moved_set = {'x', 'b', 'z', 'y'};

  s21::set<char> set_2(std::move(set_1));

  EXPECT_EQ(set_1.size(), 0);
  EXPECT_EQ(set_2.size(), 4);

  set_1.print();
  set_2.print();

  auto it_1 = set_1.begin();
  auto it_2 = empty_set.begin();
  for (; it_1 != set_1.end(); ++it_1, ++it_2) {
    EXPECT_TRUE(*it_2 == *it_1);
  }

  it_1 = set_2.begin();
  it_2 = moved_set.begin();
  for (; it_1 != set_1.end(); ++it_1, ++it_2) {
    EXPECT_TRUE(*it_2 == *it_1);
  }
}

TEST(set, eq_move_set) {
  s21::set<char> set_1 = {'x', 'b', 'z', 'y'};
  s21::set<char> empty_set = {};
  s21::set<char> moved_set = {'x', 'b', 'z', 'y'};

  s21::set<char> set_2 = std::move(set_1);

  EXPECT_EQ(set_1.size(), 0);
  EXPECT_EQ(set_2.size(), 4);

  set_1.print();
  set_2.print();

  auto it_1 = set_1.begin();
  auto it_2 = empty_set.begin();
  for (; it_1 != set_1.end(); ++it_1, ++it_2) {
    EXPECT_TRUE(*it_2 == *it_1);
  }

  it_1 = set_2.begin();
  it_2 = moved_set.begin();
  for (; it_1 != set_1.end(); ++it_1, ++it_2) {
    EXPECT_TRUE(*it_2 == *it_1);
  }
}

TEST(set, set_find_less) {
  s21::set<char> set = {'x', 'b', 'z', 'y'};
  std::set<char> orig_set = {'x', 'b', 'z', 'y'};

  EXPECT_TRUE(*set.find('b') == *orig_set.find('b'));
}

TEST(set, set_find_more) {
  s21::set<char> set = {'x', 'b', 'z', 'y'};
  std::set<char> orig_set = {'x', 'b', 'z', 'y'};
  set.print();
  EXPECT_TRUE(*set.find('z') == *orig_set.find('z'));
}

TEST(set, set_find_deep) {
  s21::set<char> set = {'a', 'b', 'c', 'd', 'f', 'e', 'g', 'h', 'i'};
  std::set<char> orig_set = {'a', 'b', 'c', 'd', 'f', 'e', 'g', 'h', 'i'};

  set.print();

  EXPECT_TRUE(*set.find('g') == *orig_set.find('g'));
}

TEST(set, set_find_root) {
  s21::set<char> set = {'a', 'b', 'c', 'd', 'f', 'e', 'g', 'h', 'i'};
  std::set<char> orig_set = {'a', 'b', 'c', 'd', 'f', 'e', 'g', 'h', 'i'};

  set.print();

  EXPECT_TRUE(*set.find('d') == *orig_set.find('d'));
}

TEST(set, set_insert) {
  s21::set<char> my_set = {'a', 'b', 'c', 'd'};
  std::set<char> orig_set = {'a', 'b', 'c', 'd'};

  my_set.print();

  my_set.insert('f');
  orig_set.insert('f');

  my_set.print();

  EXPECT_TRUE(my_set.size() == orig_set.size());

  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  for (; my_it != my_set.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST(set, set_erase) {
  s21::set<char> my_set = {'a', 'b', 'c', 'd', 'f'};
  std::set<char> orig_set = {'a', 'b', 'c', 'd', 'f'};

  my_set.print();

  my_set.erase(my_set.find('f'));
  orig_set.erase(orig_set.find('f'));

  my_set.print();

  EXPECT_TRUE(my_set.size() == orig_set.size());

  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  for (; my_it != my_set.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST(set, set_insert_many) {
  s21::set<char> set = {'a', 'b', 'c', 'd'};

  set.print();

  set.insert_many('f', 'e', 'g', 'h', 'i');

  set.print();

  EXPECT_TRUE(set.size() == 9);
}

TEST(set, set_empty_false) {
  s21::set<char> my_set = {'a', 'b', 'c', 'd', 'f'};
  std::set<char> orig_set = {'a', 'b', 'c', 'd', 'f'};

  EXPECT_TRUE(my_set.empty() == orig_set.empty());
}

TEST(set, set_empty_true) {
  s21::set<char> my_set = {};
  std::set<char> orig_set = {};

  EXPECT_TRUE(my_set.empty() == orig_set.empty());
}

TEST(set, set_max_size_1) {
  s21::set<int> set;
  std::set<int> std_set;

  // Проверяем, что max_size() возвращает значение того же порядка
  EXPECT_GT(set.max_size(), 0);
  EXPECT_LE(set.max_size(), std::numeric_limits<size_t>::max());

  // Можно сравнить с std::set (но не обязательно точное совпадение)
  EXPECT_GT(set.max_size(), std_set.size());  // Всегда true
}

TEST(set, set_max_size_2) {
  s21::set<int> set_1;
  s21::set<double> set_2;

  // Для одного типа должен возвращать одинаковое значение
  EXPECT_EQ(set_1.max_size(), s21::set<int>().max_size());

  // Для разных типов может возвращать разное (из-за разного размера Node)
  EXPECT_NE(set_1.max_size(), set_2.max_size());
}

TEST(set, set_max_size_3) {
  s21::set<int> set_1;
  const size_t initial_max = set_1.max_size();

  set_1.insert(1);
  set_1.insert(2);
  set_1.erase(set_1.find(1));

  EXPECT_EQ(set_1.max_size(), initial_max);
}

TEST(set, set_merg) {
  s21::set<int> my_set = {1, 2, 3};
  std::set<int> orig_set = {1, 2, 3};

  s21::set<int> my_merge = {3, 4, 5};
  std::set<int> orig_merge = {3, 4, 5};

  my_set.merge(my_merge);
  orig_set.merge(orig_merge);

  my_set.print();

  EXPECT_EQ(my_set.size(), orig_set.size());

  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  for (; my_it != my_set.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST(set, set_merg_empty) {
  s21::set<int> my_set = {1, 2, 3};
  std::set<int> orig_set = {1, 2, 3};

  s21::set<int> my_merge = {};
  std::set<int> orig_merge = {};

  my_set.merge(my_merge);
  orig_set.merge(orig_merge);

  my_set.print();

  EXPECT_EQ(my_set.size(), orig_set.size());

  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  for (; my_it != my_set.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST(set, set_swap) {
  s21::set<int> my_set = {1, 2, 3};
  std::set<int> orig_set = {1, 2, 3};

  s21::set<int> my_swap = {3, 4, 5};
  std::set<int> orig_swap = {3, 4, 5};

  my_set.swap(my_swap);
  orig_set.swap(orig_swap);

  my_set.print();

  EXPECT_EQ(my_set.size(), orig_set.size());

  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  for (; my_it != my_set.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }

  my_swap.print();

  EXPECT_EQ(my_swap.size(), orig_swap.size());

  my_it = my_swap.begin();
  orig_it = orig_swap.begin();
  for (; my_it != my_swap.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST(set, set_swap_empty) {
  s21::set<int> my_set = {1, 2, 3};
  std::set<int> orig_set = {1, 2, 3};

  s21::set<int> my_swap = {};
  std::set<int> orig_swap = {};

  my_set.swap(my_swap);
  orig_set.swap(orig_swap);

  my_set.print();

  EXPECT_EQ(my_set.size(), orig_set.size());

  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  for (; my_it != my_set.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }

  my_swap.print();

  EXPECT_EQ(my_swap.size(), orig_swap.size());

  my_it = my_swap.begin();
  orig_it = orig_swap.begin();
  for (; my_it != my_swap.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST(set, set_contains_true) {
  s21::set<int> my_set = {1, 2, 3};

  my_set.print();

  EXPECT_EQ(my_set.contains(3), true);
}

TEST(set, set_contains_false) {
  s21::set<int> my_set = {1, 2, 3};

  my_set.print();

  EXPECT_EQ(my_set.contains(4), false);
}

TEST(set, set_merge) {
  s21::set<int> my_set = {1};
  s21::set<int> my_merge_set = {3, 4, 5};
  my_set.merge(my_merge_set);

  std::set<int> orig_set = {1};
  std::set<int> orig_merge_set = {3, 4, 5};
  orig_set.merge(orig_merge_set);
  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  for (; my_it != my_set.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
  EXPECT_EQ(orig_set.size(), my_set.size());
  EXPECT_EQ(my_merge_set.size(), orig_merge_set.size());
}

TEST(set, set_erase_2) {
  s21::set<char> my_set = {'a', 'b', 'c', 'd', 'f'};
  std::set<char> orig_set = {'a', 'b', 'c', 'd', 'f'};

  my_set.print();

  my_set.erase(my_set.begin());
  orig_set.erase(orig_set.begin());

  my_set.print();

  EXPECT_TRUE(my_set.size() == orig_set.size());

  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  for (; my_it != my_set.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}