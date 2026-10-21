#include "s21_test.h"

TEST(map, create_map) {
  s21::map<int, int> m;
  std::map<int, int> orig_m;

  EXPECT_EQ(m.size(), orig_m.size());
}

TEST(map, create_map_with_data) {
  s21::map<int, char> m = {{1, 'a'}, {2, 'b'}, {3, 'c'}, {5, 'e'}, {4, 'd'}};
  std::map<int, char> orig_m = {
      {1, 'a'}, {2, 'b'}, {3, 'c'}, {5, 'e'}, {4, 'd'}};

  EXPECT_EQ(m.size(), orig_m.size());

  m.print();
}

TEST(map, move_map) {
  s21::map<int, char> m = {{1, 'a'}, {2, 'b'}, {3, 'c'}, {5, 'e'}, {4, 'd'}};
  s21::map<int, char> m_2 = std::move(m);

  EXPECT_EQ(m.size(), 0);
  EXPECT_EQ(m_2.size(), 5);

  m_2.print();
}

TEST(map, insert_map) {
  s21::map<int, char> m = {{1, 'a'}, {2, 'b'}, {3, 'c'}, {5, 'e'}, {4, 'd'}};
  std::map<int, char> orig_m = {
      {1, 'a'}, {2, 'b'}, {3, 'c'}, {5, 'e'}, {4, 'd'}};

  m.insert({6, 'f'});
  orig_m.insert({6, 'f'});

  m.insert({1, 'f'});
  orig_m.insert({1, 'f'});

  m.insert({7, 'a'});
  orig_m.insert({7, 'a'});

  EXPECT_EQ(m.size(), orig_m.size());

  m.print();
}

TEST(map, insert_empty_map) {
  s21::map<int, char> m = {};
  std::map<int, char> orig_m = {};

  m.insert({6, 'f'});
  orig_m.insert({6, 'f'});

  m.insert({1, 'w'});
  orig_m.insert({1, 'w'});

  m.insert({7, 'a'});
  orig_m.insert({7, 'a'});

  EXPECT_EQ(m.size(), orig_m.size());

  m.print();
}

TEST(map, map_at_true) {
  s21::map<int, char> m = {{1, 'a'}, {2, 'b'}, {3, 'c'}, {5, 'e'}, {4, 'd'}};
  std::map<int, char> orig_m = {
      {1, 'a'}, {2, 'b'}, {3, 'c'}, {5, 'e'}, {4, 'd'}};

  EXPECT_TRUE(m.at(1) == orig_m.at(1));

  m.print();
}

TEST(map, map_at_false) {
  s21::map<int, char> m = {{1, 'a'}, {2, 'b'}, {3, 'c'}, {5, 'e'}, {4, 'd'}};
  std::map<int, char> orig_m = {
      {1, 'a'}, {2, 'b'}, {3, 'c'}, {5, 'e'}, {4, 'd'}};

  EXPECT_THROW(m.at(10), std::out_of_range);
}

TEST(map, map_oper_true) {
  s21::map<int, char> m = {{1, 'a'}, {2, 'b'}, {3, 'c'}, {5, 'e'}, {4, 'd'}};
  std::map<int, char> orig_m = {
      {1, 'a'}, {2, 'b'}, {3, 'c'}, {5, 'e'}, {4, 'd'}};

  m[1] = 'b';
  orig_m[1] = 'b';

  EXPECT_TRUE(m[1] == orig_m[1]);
  m.print();
}

TEST(map, map_oper_false) {
  s21::map<int, char> m = {{1, 'a'}, {2, 'b'}, {3, 'c'}, {5, 'e'}, {4, 'd'}};
  std::map<int, char> orig_m = {
      {1, 'a'}, {2, 'b'}, {3, 'c'}, {5, 'e'}, {4, 'd'}};

  m[10] = 'b';
  orig_m[10] = 'b';

  EXPECT_TRUE(m[10] == orig_m[10]);
  m.print();
}

TEST(map, map_insert_or_assign_false) {
  s21::map<int, char> my_map;
  std::map<int, char> orig_map;
  my_map.insert(1, 'a');
  my_map.insert(2, 'a');
  my_map.insert(3, 'a');
  orig_map.insert(std::make_pair(1, 'a'));
  orig_map.insert(std::make_pair(2, 'a'));
  orig_map.insert(std::make_pair(3, 'a'));

  EXPECT_TRUE(my_map.insert_or_assign(1, 'a').second ==
              orig_map.insert_or_assign(1, 'a').second);
}

TEST(map, map_insert_or_assign_true) {
  s21::map<int, char> my_map;
  std::map<int, char> orig_map;
  my_map.insert(1, 'a');
  my_map.insert(2, 'a');
  my_map.insert(3, 'a');
  orig_map.insert(std::make_pair(1, 'a'));
  orig_map.insert(std::make_pair(2, 'a'));
  orig_map.insert(std::make_pair(3, 'a'));

  EXPECT_TRUE(my_map.insert_or_assign(4, 'a').second ==
              orig_map.insert_or_assign(4, 'a').second);
}

TEST(map, map_erase) {
  s21::map<int, char> my_map = {{1, 'x'}, {2, 'b'}, {3, 'z'}, {4, 'y'}};
  std::map<int, char> orig_map = {{1, 'x'}, {2, 'b'}, {3, 'z'}, {4, 'y'}};

  EXPECT_EQ(my_map.size(), orig_map.size());
  my_map.erase(my_map.begin());
  orig_map.erase(orig_map.begin());
  EXPECT_EQ(my_map.size(), orig_map.size());

  auto my_it = my_map.begin();
  auto orig_it = orig_map.begin();

  for (; my_it != my_map.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE((*my_it).second == (*orig_it).second);
  }
}

TEST(map, map_find) {
  s21::map<int, char> my_map = {{1, 'x'}, {2, 'b'}, {3, 'z'}, {4, 'y'}};
  std::map<int, char> orig_map = {{1, 'x'}, {2, 'b'}, {3, 'z'}, {4, 'y'}};

  EXPECT_TRUE((*my_map.find(2)).first == (*orig_map.find(2)).first);
  EXPECT_TRUE((*my_map.find(2)).second == (*orig_map.find(2)).second);
}

TEST(map, insert_or_assign) {
  s21::map<int, char> my_map;
  std::map<int, char> orig_map;

  my_map.insert(1, 'a');
  my_map.insert(2, 'a');
  my_map.insert(3, 'a');
  orig_map.insert(std::make_pair(1, 'a'));
  orig_map.insert(std::make_pair(2, 'a'));
  orig_map.insert(std::make_pair(3, 'a'));

  auto my_it = my_map.begin();
  auto orig_it = orig_map.begin();
  for (; my_it != my_map.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE((*my_it).second == (*orig_it).second);
  }

  auto pr1 = my_map.insert_or_assign(1, 'b');
  auto i = orig_map.begin();
  EXPECT_TRUE((*pr1.first).first == (*i).first);
}

TEST(map, swap_map) {
  s21::map<int, int> my_map = {{1, 1}};
  s21::map<int, int> my_swap_map = {{3, 3}, {4, 4}};

  my_map.swap(my_swap_map);
  EXPECT_EQ(my_map.size(), 2);
  EXPECT_EQ(my_swap_map.size(), 1);

  auto x = (*(my_map.begin())).first;
  auto y = (*(my_swap_map.begin())).first;

  EXPECT_EQ(x, 3);
  EXPECT_EQ(y, 1);
}

TEST(map, contains_map) {
  s21::map<int, char> my_map = {{1, 'x'}, {2, 'b'}, {3, 'z'}, {4, 'y'}};
  std::map<int, char> orig_map = {{1, 'x'}, {2, 'b'}, {3, 'z'}, {4, 'y'}};

  EXPECT_EQ(my_map.contains(1), true);
}

TEST(map, insert_many_map) {
  s21::map<int, std::string> m;
  auto results = m.insert_many(std::pair<int, std::string>(1, "one"),
                               std::pair<int, std::string>(2, "two"),
                               std::pair<int, std::string>(3, "three"));

  ASSERT_EQ(m.size(), 3);
  EXPECT_TRUE(results[0].second);
  EXPECT_TRUE(results[1].second);
  EXPECT_TRUE(results[2].second);
  EXPECT_EQ(m[1], "one");
  EXPECT_EQ(m[2], "two");
  EXPECT_EQ(m[3], "three");
}