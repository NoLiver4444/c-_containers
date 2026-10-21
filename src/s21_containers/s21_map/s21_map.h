#ifndef S21_MAP_H_
#define S21_MAP_H_

#include <vector>

#include "../s21_AVL_Tree/s21_AVL_Tree.h"

namespace s21 {

template <typename Key, typename T>
class map : public AVL_Tree<Key, T> {
 public:
  class MapIterator;
  class ConstMapIterator;

  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = MapIterator;
  using const_iterator = ConstMapIterator;
  using size_type = size_t;

  map();
  map(std::initializer_list<value_type> const &items);
  map(const map &m);
  map(map &&m);
  ~map() = default;

  map &operator=(map &&s) noexcept;
  map &operator=(const map &other);

  std::pair<iterator, bool> insert(const value_type &value);
  std::pair<iterator, bool> insert(const Key &key, const T &obj);
  std::pair<iterator, bool> insert_or_assign(const Key &key, const T &obj);

  iterator find(const Key &key);

  class MapIterator : public AVL_Tree<Key, T>::Iterator {
   public:
    friend class map;
    MapIterator() : AVL_Tree<Key, T>::Iterator(){};
    MapIterator(typename AVL_Tree<Key, T>::Node *node,
                typename AVL_Tree<Key, T>::Node *past_node = nullptr)
        : AVL_Tree<Key, T>::Iterator(node, past_node = nullptr){};
    value_type &operator*();

   protected:
    T &return_value();
  };

  class ConstMapIterator : public MapIterator {
   public:
    friend class map;
    ConstMapIterator() : MapIterator(){};
    ConstMapIterator(typename AVL_Tree<Key, T>::Node *node,
                     typename AVL_Tree<Key, T>::Node *past_node = nullptr)
        : MapIterator(node, past_node = nullptr){};
    const_reference operator*() const { return MapIterator::operator*(); };
  };

  T &at(const Key &key);
  T &operator[](const Key &key);

  iterator begin();
  iterator end();
  void erase(iterator pos);
  void merge(map &other);

  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);
};

#include "s21_map.tpp"

}  // namespace s21

#endif