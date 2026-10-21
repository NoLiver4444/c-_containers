#include "s21_multiset.h"

template <typename Key>
multiset<Key>::multiset() : AVL_Tree<Key, Key>() {}

template <typename Key>
multiset<Key>::multiset(std::initializer_list<value_type> const &items)
    : AVL_Tree<Key, Key>() {
  for (auto i = items.begin(); i != items.end(); ++i) {
    insert(*i);
  }
}

template <typename Key>
multiset<Key>::multiset(const multiset &ms) : AVL_Tree<Key, Key>(ms) {}

template <typename Key>
multiset<Key>::multiset(multiset &&ms) : AVL_Tree<Key, Key>(std::move(ms)) {}

template <typename Key>
multiset<Key> &multiset<Key>::operator=(multiset &&ms) {
  if (this != &ms) {
    AVL_Tree<Key, Key>::operator=(std::move(ms));
  }
  return *this;
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::insert(
    const value_type &value) {
  if (this->root == nullptr) {
    this->root = new node_type(value, value);
    return iterator(this->root);
  }
  insert_place_find(this->root, value);
  return this->find(value);
}

template <typename Key>
bool multiset<Key>::insert_place_find(node_type *node,
                                      const value_type &value) {
  bool answ = false;

  if (value < node->value) {
    if (node->left == nullptr) {
      node->left = new node_type(value, value, node);
      answ = true;
    } else {
      answ = insert_place_find(node->left, value);
    }
  } else {
    // Для multiset разрешаем дубликаты
    if (node->right == nullptr) {
      node->right = new node_type(value, value, node);
      answ = true;
    } else {
      answ = insert_place_find(node->right, value);
    }
  }

  this->update_height(node);
  this->balance_Tree(node);
  return answ;
}

template <typename Key>
void multiset<Key>::merge(multiset &other) {
  multiset<Key> const_tree(other);
  iterator const_it = const_tree.begin();

  for (; const_it != const_tree.end(); ++const_it) {
    iterator pr = insert(*const_it);
    other.erase(pr);
  }
}

template <typename Key>
typename multiset<Key>::size_type multiset<Key>::count(const Key &key) {
  size_type answ = 0;

  if (this->root != nullptr) {
    count_duplicate(key, &answ, this->root);
  }

  return answ;
}

template <typename Key>
void multiset<Key>::count_duplicate(const Key &key, size_type *answ,
                                    node_type *node) {
  if (node == nullptr) {
    return;
  }

  if (key < node->key) {
    count_duplicate(key, answ, node->left);
  } else if (key > node->key) {
    count_duplicate(key, answ, node->right);
  } else {
    *answ += 1;
    count_duplicate(key, answ, node->left);
    count_duplicate(key, answ, node->right);
  }
}

template <typename Key>
std::pair<typename multiset<Key>::iterator, typename multiset<Key>::iterator>
multiset<Key>::equal_range(const Key &key) {
  iterator lower = this->lower_bound(key);
  iterator upper = this->upper_bound(key);
  return std::make_pair(lower, upper);
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::lower_bound(const Key &key) {
  node_type *current = this->root;
  node_type *result = nullptr;

  while (current != nullptr) {
    if (current->key >= key) {
      result = current;
      current = current->left;
    } else {
      current = current->right;
    }
  }

  return iterator(result);
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::upper_bound(const Key &key) {
  node_type *current = this->root;
  node_type *result = nullptr;

  while (current != nullptr) {
    if (current->key > key) {
      result = current;
      current = current->left;
    } else {
      current = current->right;
    }
  }

  return iterator(result);
}

template <typename Key>
template <class... Args>
std::vector<std::pair<typename multiset<Key>::iterator, bool>>
multiset<Key>::insert_many(Args &&...args) {
  std::vector<std::pair<typename multiset<Key>::iterator, bool>> vec;
  for (const auto &arg : {args...}) {
    vec.push_back(std::pair(insert(arg), true));
  }
  return vec;
}