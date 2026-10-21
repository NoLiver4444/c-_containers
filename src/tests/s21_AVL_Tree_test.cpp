#include "s21_test.h"

TEST(AVL_Tree, eq_Tree) {
  s21::AVL_Tree<int, int> tree_1;
  s21::AVL_Tree<int, int> *tree_2 = new s21::AVL_Tree<int, int>();

  EXPECT_TRUE(tree_1.eq_Tree(tree_2));
  delete tree_2;
}

TEST(AVL_Tree, eq_Tree_insert) {
  s21::AVL_Tree<int, int> tree_1;
  s21::AVL_Tree<int, int> *tree_2 = new s21::AVL_Tree<int, int>();

  tree_1.insert(2);
  tree_1.insert(1);
  tree_1.insert(3);
  tree_1.insert(4);
  tree_1.insert(5);
  tree_1.insert(1);

  tree_2->insert(2);
  tree_2->insert(1);
  tree_2->insert(3);
  tree_2->insert(4);
  tree_2->insert(5);
  tree_2->insert(1);

  EXPECT_TRUE(tree_1.eq_Tree(tree_2));
  delete tree_2;
}

TEST(AVL_Tree, eq_Tree_insert_erase) {
  s21::AVL_Tree<int, int> tree_1;
  s21::AVL_Tree<int, int> *tree_2 = new s21::AVL_Tree<int, int>();

  tree_1.insert(2);
  tree_1.insert(1);
  tree_1.insert(3);
  tree_1.insert(4);
  tree_1.insert(5);
  tree_1.insert(1);

  tree_2->insert(2);
  tree_2->insert(1);
  tree_2->insert(3);
  tree_2->insert(4);
  tree_2->insert(5);
  tree_2->insert(1);

  tree_1.erase(tree_1.find(2));
  tree_2->erase(tree_2->find(2));

  EXPECT_TRUE(tree_1.eq_Tree(tree_2));
  delete tree_2;
}

TEST(AVL_Tree, print_and_test_Tree) {
  s21::AVL_Tree<int, int> tree_1;

  tree_1.insert(2);
  tree_1.insert(1);
  tree_1.insert(3);
  tree_1.insert(4);
  tree_1.insert(5);
  tree_1.insert(1);
  tree_1.insert(7);
  tree_1.insert(9);
  tree_1.insert(6);
  tree_1.insert(8);

  s21::AVL_Tree<int, int> *tree_answ = new s21::AVL_Tree<int, int>();

  tree_answ->insert(2);
  tree_answ->insert(1);
  tree_answ->insert(4);
  tree_answ->insert(3);
  tree_answ->insert(7);
  tree_answ->insert(5);
  tree_answ->insert(9);
  tree_answ->insert(6);
  tree_answ->insert(8);

  EXPECT_TRUE(tree_1.eq_Tree(tree_answ));

  tree_1.print();
  delete tree_answ;
}

TEST(AVL_Tree, Tree_copy) {
  s21::AVL_Tree<int, int> tree_1;

  tree_1.insert(2);
  tree_1.insert(1);
  tree_1.insert(3);
  tree_1.insert(4);
  tree_1.insert(5);
  tree_1.insert(1);

  s21::AVL_Tree<int, int> *tree_2 = new s21::AVL_Tree<int, int>(tree_1);

  EXPECT_TRUE(tree_1.eq_Tree(tree_2));

  delete tree_2;
}

TEST(AVL_Tree, Tree_move) {
  s21::AVL_Tree<int, int> tree_1;

  tree_1.insert(2);
  tree_1.insert(1);
  tree_1.insert(3);
  tree_1.insert(4);
  tree_1.insert(5);
  tree_1.insert(1);

  s21::AVL_Tree<int, int> tree_2 = std::move(tree_1);

  tree_1.insert(2);
  tree_1.insert(1);
  tree_1.insert(3);
  tree_1.insert(4);
  tree_1.insert(5);
  tree_1.insert(1);

  EXPECT_TRUE(tree_1.eq_Tree(&tree_2));
}

TEST(AVL_Tree, empty_Tree_find) {
  s21::AVL_Tree<int, int> tree_1;

  EXPECT_TRUE(tree_1.find(2) == nullptr);
}

TEST(AVL_Tree, empty_Tree_erase) {
  s21::AVL_Tree<int, int> tree_1;

  tree_1.erase(tree_1.find(2));

  EXPECT_TRUE(tree_1.find(2) == nullptr);
}

TEST(AVL_Tree, find_erase_Node) {
  s21::AVL_Tree<int, int> tree_1;

  tree_1.insert(2);
  tree_1.insert(1);
  tree_1.insert(3);
  tree_1.insert(4);
  tree_1.insert(5);

  tree_1.erase(tree_1.find(2));

  EXPECT_TRUE(tree_1.find(2) == nullptr);
}

TEST(AVL_Tree, erase_root) {
  s21::AVL_Tree<int, int> tree_1;
  s21::AVL_Tree<int, int> *tree_2 = new s21::AVL_Tree<int, int>();

  tree_1.insert(2);
  tree_1.insert(1);
  tree_1.insert(3);

  tree_1.erase(tree_1.find(2));

  tree_2->insert(3);
  tree_2->insert(1);

  EXPECT_TRUE(tree_1.eq_Tree(tree_2));

  delete tree_2;
}

TEST(AVL_Tree, double_erase_Node) {
  s21::AVL_Tree<int, int> tree_1;

  tree_1.insert(2);
  tree_1.insert(1);
  tree_1.insert(3);
  tree_1.insert(4);
  tree_1.insert(5);

  tree_1.erase(tree_1.find(2));
  tree_1.erase(tree_1.find(2));

  EXPECT_TRUE(tree_1.find(2) == nullptr);
}