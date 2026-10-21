#ifndef S21_AVL_TREE_H_
#define S21_AVL_TREE_H_

#include <iostream>
#include <string>

namespace s21 {

template <typename Key, typename Value>
class AVL_Tree {
 protected:
  struct Node;
  Node *root;

 private:
 public:
  class Iterator;
  class ConstIterator;

  using key_type = Key;
  using value_type = Value;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = Iterator;
  using const_iterator = ConstIterator;
  using size_type = size_t;

  class Iterator {
   public:
    Iterator();
    Iterator(Node *current_node, Node *past_node = nullptr);
    Iterator &operator++();
    Iterator &operator--();
    Key &operator*();
    bool operator!=(const Iterator &other) const;
    bool operator==(const Iterator &other) const;
    Node *operator->() const;
    friend class AVL_Tree<Key, Value>;

   protected:
    Node *current_node;
    Node *past_node;
    Node *move_forward(Node *node);
    Node *move_back(Node *node);
  };

  class ConstIterator : public Iterator {
   public:
    ConstIterator();
    const_reference operator*() const;
  };

  AVL_Tree();
  AVL_Tree(const AVL_Tree &other);
  AVL_Tree(AVL_Tree &&other) noexcept;
  ~AVL_Tree();

  Iterator begin();
  Iterator end();

  bool empty();
  size_type size();
  size_t max_size();

  void clear();
  std::pair<typename AVL_Tree<Key, Value>::Iterator, bool> insert(
      const Key &key);
  void erase(iterator pos);
  void swap(AVL_Tree &other);
  void merge(AVL_Tree &other);

  Iterator find(const Key &key);
  bool contains(const Key &key);

  void print();
  bool eq_Tree(AVL_Tree *other);

 protected:
  struct Node {
    // Конструкторы
    Node(Key key, value_type value);
    Node(Key key, value_type value, Node *parent);
    bool eq_Node(Node *other);
    Key key;
    value_type value;
    Node *parent = nullptr;
    Node *left = nullptr;
    Node *right = nullptr;
    int height = 0;
    friend class AVL_Tree<Key, Value>;
  };

  bool insert_place_find(AVL_Tree::Node *node, const Key &key, Value value);
  Node *remove_node_find(Node *node, Key key);

  Node *copy_Tree(Node *copy_node, Node *parent);

  void remove_Tree(Node *node);

  static Node *get_min(Node *node);
  static Node *get_max(Node *node);
  void update_height(Node *node);
  int balance_factor(Node *node);
  Node *balance_Tree(Node *node);
  Node *Left_Left(Node *node);
  Node *Right_Right(Node *node);
  Node *Left_Right(Node *node);
  Node *Right_Left(Node *node);
  void print_tree(Node *node, int indent, bool last);
  Node *find_node(const Key &key, Node *node);
};

#include "s21_AVL_Tree.tpp"

}  // namespace s21

#endif