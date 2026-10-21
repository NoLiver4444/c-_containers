#include "s21_set.h"

template <typename Key>
set<Key>::set() : AVL_Tree<Key, Key>() {}

template <typename Key>
set<Key>::set(std::initializer_list<value_type> const &items)
    : AVL_Tree<Key, Key>() {
  for (auto i = items.begin(); i != items.end(); ++i) {
    AVL_Tree<Key, Key>::insert(*i);
  }
}

template <typename Key>
set<Key>::set(const set &s) : AVL_Tree<Key, Key>(s) {}

template <typename Key>
set<Key>::set(set &&s) : AVL_Tree<Key, Key>(std::move(s)) {}

template <typename Key>
set<Key> &set<Key>::operator=(set &&s) noexcept {
  if (this != &s) {
    AVL_Tree<Key, Key>::operator=(std::move(s));
  }
  return *this;
}

template <typename Key>
typename set<Key>::iterator set<Key>::find(const Key &key) {
  return AVL_Tree<Key, Key>::find(key);
}

template <typename Key>
template <class... Args>
std::vector<std::pair<typename set<Key>::iterator, bool>> set<Key>::insert_many(
    Args &&...args) {
  std::vector<std::pair<typename set<Key>::iterator, bool>> vec;
  for (const auto &arg : {args...}) {
    vec.push_back(AVL_Tree<Key, Key>::insert(arg));
  }
  return vec;
}