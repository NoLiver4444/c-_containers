#ifndef S21_SET_H_
#define S21_SET_H_

#include <vector>

#include "../s21_AVL_Tree/s21_AVL_Tree.h"

namespace s21 {

template <typename Key>
class set : public AVL_Tree<Key, Key> {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const Key &;
  using iterator = typename AVL_Tree<Key, Key>::Iterator;
  using const_iterator = typename AVL_Tree<Key, Key>::ConstIterator;
  using size_type = size_t;

  set();
  set(std::initializer_list<value_type> const &items);
  set(const set &s);
  set(set &&s);
  ~set() = default;

  set &operator=(set &&s) noexcept;
  iterator find(const Key &key);

  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);
};

#include "s21_set.tpp"

}  // namespace s21

#endif