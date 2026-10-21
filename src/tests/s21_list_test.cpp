#include "s21_test.h"

TEST(list, create_list) {
  s21::list<int> l;

  EXPECT_EQ(l.size(), 0);
}

TEST(list, create_with_len_list) {
  s21::list<int> l(5);

  EXPECT_EQ(l.size(), 5);
}

TEST(list, create_data_list) {
  s21::list<int> l = {1, 2, 3, 4, 5};

  EXPECT_EQ(l.size(), 5);
}

TEST(list, copy_list) {
  s21::list<int> l = {1, 2, 3, 4, 5};
  s21::list<int> l_2(l);

  EXPECT_EQ(l.size(), l_2.size());
}

TEST(list, move_list) {
  s21::list<int> l = {1, 2, 3, 4, 5};
  s21::list<int> l_2(std::move(l));

  EXPECT_EQ(l.size(), 0);
  EXPECT_EQ(l_2.size(), 5);
}

TEST(list, operator_eq_move_list_1) {
  s21::list<int> l = {1, 2, 3, 4, 5};
  s21::list<int> l_2 = std::move(l);

  EXPECT_EQ(l.size(), 0);
  EXPECT_EQ(l_2.size(), 5);
}

TEST(list, begin_list) {
  s21::list<int> l = {1, 2, 3, 4, 5};

  l.push_front(12);

  EXPECT_EQ(*l.begin(), 12);
}

TEST(list, end_list) {
  s21::list<int> l = {1, 2, 3, 4, 5};

  l.push_back(254);

  EXPECT_EQ(*l.end(), 254);
}

TEST(list, nullptr_iterator_list) {
  s21::list<int> l = {1, 2, 3, 4, 5};

  s21::list<int>::ListIterator iter;

  EXPECT_THROW(*iter;, std::logic_error);
}

TEST(list, pop_back_list_1) {
  s21::list<int> l = {1, 2, 3, 4, 5};

  l.pop_back();
  l.pop_back();

  EXPECT_EQ(*l.end(), 3);
}

TEST(list, pop_back_list_2) {
  s21::list<int> l = {1};

  l.pop_back();

  EXPECT_EQ(l.size(), 0);
}

TEST(list, operator_eq_list_1) {
  s21::list<int> l = {1, 2, 3, 4, 5};
  s21::list<int> l_2;

  l_2 = l;

  EXPECT_EQ(l.size(), 5);
  EXPECT_EQ(l_2.size(), 5);
}

TEST(list, operator_eq_list_2) {
  s21::list<int> l = {1, 2, 3, 4, 5};
  s21::list<int> l_2;

  l_2 = std::move(l);

  EXPECT_EQ(l.size(), 0);
  EXPECT_EQ(l_2.size(), 5);
}

TEST(list, operator_eq_list_3) {
  s21::list<int> l = {1, 2, 3, 4, 5};
  s21::list<int> l_2 = {6, 7, 8, 9, 10};

  l_2 = l;

  EXPECT_EQ(l.size(), 5);
  EXPECT_EQ(l_2.size(), 5);
}

TEST(list, operator_eq_list_4) {
  s21::list<int> l = {1, 2, 3, 4, 5};
  s21::list<int> l_2 = {6, 7, 8, 9, 10};

  l_2 = std::move(l);

  EXPECT_EQ(l.size(), 0);
  EXPECT_EQ(l_2.size(), 5);
}

TEST(list, pop_front_list) {
  s21::list<int> l = {};

  l.pop_front();

  EXPECT_EQ(l.size(), 0);
}

TEST(list, nullptr_const_iterator_list) {
  s21::list<int> l = {1, 2, 3, 4, 5};

  s21::list<int>::ListConstIterator iter;

  EXPECT_THROW(*iter;, std::logic_error);
}

TEST(list, front_list) {
  s21::list<int> l = {1, 2, 3, 4, 5};

  l.push_front(12);

  EXPECT_EQ(l.front(), 12);
}

TEST(list, back_list) {
  s21::list<int> l = {1, 2, 3, 4, 5};

  l.push_back(254);

  EXPECT_EQ(l.back(), 254);
}

TEST(list, empty_begin_list) {
  s21::list<int> l = {};

  EXPECT_THROW(l.begin();, std::logic_error);
}

TEST(list, empty_end_list) {
  s21::list<int> l = {};

  EXPECT_THROW(l.end();, std::logic_error);
}

TEST(list, empty_front_list) {
  s21::list<int> l = {};

  EXPECT_THROW(l.front();, std::logic_error);
}

TEST(list, empty_back_list) {
  s21::list<int> l = {};

  EXPECT_THROW(l.back();, std::logic_error);
}

TEST(list, insert_list_1) {
  s21::list<int> l = {1, 2, 3, 4, 5};

  l.insert(l.begin(), 20);

  EXPECT_EQ(l.front(), 20);
}

TEST(list, insert_list_2) {
  s21::list<int> l = {1, 2, 3, 4, 5};

  l.insert(l.end(), 20);

  EXPECT_EQ(l.back(), 20);
}

TEST(list, insert_list_3) {
  s21::list<int> l = {1, 2, 3, 4, 5};

  l.insert(++(++l.begin()), 20);

  EXPECT_EQ(*++(++l.begin()), 20);
}

TEST(list, insert_list_4) {
  s21::list<int> l = {1, 2, 3, 4, 5};

  l.insert(--(--l.end()), 20);

  EXPECT_EQ(*--(--(--l.end())), 20);
}

TEST(list, operator_list_1) {
  s21::list<int> l = {1, 2, 3, 4, 5};

  s21::list<int>::iterator iter;

  EXPECT_THROW(++iter;, std::logic_error);
}

TEST(list, operator_list_2) {
  s21::list<int> l = {1, 2, 3, 4, 5};

  s21::list<int>::iterator iter;

  EXPECT_THROW(--iter;, std::logic_error);
}

TEST(list, operator_list_3) {
  s21::list<int> l = {1, 2, 3, 4, 5};

  s21::list<int>::iterator iter;

  EXPECT_THROW(*(iter++);, std::logic_error);
}

TEST(list, operator_list_4) {
  s21::list<int> l = {1, 2, 3, 4, 5};

  s21::list<int>::iterator iter;

  EXPECT_THROW(*(iter--);, std::logic_error);
}

TEST(list, operator_list_5) {
  s21::list<int> l = {1, 2, 3, 4, 5};

  s21::list<int>::iterator iter = l.begin();

  EXPECT_EQ(*(iter++), 1);
  EXPECT_EQ(*iter, 2);
}

TEST(list, operator_list_6) {
  s21::list<int> l = {1, 2, 3, 4, 5};

  s21::list<int>::iterator iter = l.end();

  EXPECT_EQ(*(iter--), 5);
  EXPECT_EQ(*iter, 4);
}

TEST(list, erase_list_1) {
  s21::list<int> l = {1, 2, 3, 4, 5};

  l.erase(l.begin());

  EXPECT_EQ(l.size(), 4);
  EXPECT_EQ(l.front(), 2);
}

TEST(list, erase_list_2) {
  s21::list<int> l = {1, 2, 3, 4, 5};

  l.erase(l.end());

  EXPECT_EQ(l.size(), 4);
  EXPECT_EQ(*l.end(), 4);
}

TEST(list, erase_list_3) {
  s21::list<int> l = {1, 2, 3, 4, 5};

  l.erase(++(++l.begin()));

  EXPECT_EQ(l.size(), 4);
}

TEST(list, swap_list_1) {
  s21::list<int> l_1 = {1, 2, 3, 4, 5};
  s21::list<int> l_2 = {6, 7, 8, 9};

  l_1.swap(l_2);

  EXPECT_EQ(l_1.size(), 4);
  EXPECT_EQ(l_2.size(), 5);
}

TEST(list, swap_list_2) {
  s21::list<int> l_1 = {1, 2, 3, 4, 5};
  s21::list<int> l_2 = {};

  l_1.swap(l_2);

  EXPECT_EQ(l_1.size(), 0);
  EXPECT_EQ(l_2.size(), 5);
}
