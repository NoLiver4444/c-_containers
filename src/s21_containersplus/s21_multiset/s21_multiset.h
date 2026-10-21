#ifndef S21_MULTISET_H_
#define S21_MULTISET_H_

#include <vector>

#include "../../s21_containers/s21_AVL_Tree/s21_AVL_Tree.h"

namespace s21 {

template <typename Key>
class multiset : public AVL_Tree<Key, Key> {
 public:
  class MultisetIterator;
  class MultisetConstIterator;

  using key_type = Key;
  using value_type = Key;
  using reference = value_type;
  using const_reference = const value_type;
  using iterator = typename AVL_Tree<Key, Key>::iterator;
  using const_iterator = typename AVL_Tree<Key, Key>::const_iterator;
  using size_type = size_t;
  using node_type = typename AVL_Tree<Key, Key>::Node;

  multiset();
  multiset(std::initializer_list<value_type> const &items);
  multiset(const multiset &ms);
  multiset(multiset &&ms);
  ~multiset() = default;

  multiset &operator=(multiset &&ms);

  iterator insert(const value_type &value);
  void merge(multiset &other);

  size_type count(const Key &key);
  std::pair<iterator, iterator> equal_range(const Key &key);
  iterator lower_bound(const Key &key);
  iterator upper_bound(const Key &key);

  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);

 private:
  bool insert_place_find(node_type *node, const value_type &value);
  void count_duplicate(const Key &key, size_type *answ, node_type *node);
};

#include "s21_multiset.tpp"

}  // namespace s21

#endif