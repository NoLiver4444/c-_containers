#include "s21_map.h"

template <typename Key, typename T>
map<Key, T>::map() : AVL_Tree<Key, T>() {}

template <typename Key, typename T>
map<Key, T>::map(std::initializer_list<value_type> const &items) {
  for (auto i = items.begin(); i != items.end(); ++i) {
    insert(*i);
  }
}

template <typename Key, typename T>
map<Key, T>::map(const map &m) : AVL_Tree<Key, T>(m) {}

template <typename Key, typename T>
map<Key, T>::map(map &&m) : AVL_Tree<Key, T>(std::move(m)) {}

template <typename Key, typename T>
map<Key, T> &map<Key, T>::operator=(map &&other) noexcept {
  if (this != &other) {
    AVL_Tree<Key, T>::operator=(std::move(other));
  }
  return *this;
}

template <typename Key, typename T>
map<Key, T> &map<Key, T>::operator=(const map &other) {
  if (this != &other) {
    AVL_Tree<Key, T>::operator=(other);
  }
  return *this;
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::MapIterator, bool> map<Key, T>::insert(
    const value_type &value) {
  return insert(value.first, value.second);
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::MapIterator, bool> map<Key, T>::insert(
    const Key &key, const T &obj) {
  std::pair<typename map<Key, T>::MapIterator, bool> answ_pair;

  // typename AVL_Tree<Key, T>::Node *new_node =
  //     new typename AVL_Tree<Key, T>::Node(key, obj);
  if (AVL_Tree<Key, T>::root == nullptr) {
    AVL_Tree<Key, T>::root = new typename AVL_Tree<Key, T>::Node(key, obj);
    answ_pair.first = iterator(AVL_Tree<Key, T>::root);
    answ_pair.second = true;
  } else {
    bool inserted =
        AVL_Tree<Key, T>::insert_place_find(AVL_Tree<Key, T>::root, key, obj);
    answ_pair.first = find(key);
    answ_pair.second = inserted;
  }

  return answ_pair;
}

template <typename Key, typename T>
typename map<Key, T>::value_type &map<Key, T>::MapIterator::operator*() {
  if (AVL_Tree<Key, T>::Iterator::current_node == nullptr) {
    static value_type fake_value{};
    return fake_value;
  }

  // Выделяем память с правильным выравниванием
  static std::aligned_storage_t<sizeof(value_type), alignof(value_type)>
      storage;

  // Создаём новую пару на месте
  value_type &temp_storage = *reinterpret_cast<value_type *>(&storage);
  new (&temp_storage)
      value_type(AVL_Tree<Key, T>::Iterator::current_node->key,
                 AVL_Tree<Key, T>::Iterator::current_node->value);

  return temp_storage;
}

template <typename Key, typename T>
T &map<Key, T>::MapIterator::return_value() {
  if (AVL_Tree<Key, T>::Iterator::current_node == nullptr) {
    static T fake_value{};
    return fake_value;
  }
  return AVL_Tree<Key, T>::Iterator::current_node->value;
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::find(const Key &key) {
  typename AVL_Tree<Key, T>::Node *node =
      AVL_Tree<Key, T>::find_node(key, AVL_Tree<Key, T>::root);
  return iterator(node);
}

template <typename Key, typename T>
T &map<Key, T>::at(const Key &key) {
  auto iter = find(key);

  if (iter == nullptr) {
    throw std::out_of_range("does not have element");
  }
  return iter.return_value();
}

template <typename Key, typename T>
T &map<Key, T>::operator[](const Key &key) {
  auto iter = find(key);

  if (iter == nullptr) {
    auto new_iter = insert(std::make_pair(key, T()));
    iter = new_iter.first;
  }

  return iter.return_value();
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::begin() {
  return map<Key, T>::MapIterator(
      AVL_Tree<Key, T>::get_min(AVL_Tree<Key, T>::root));
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::end() {
  if (AVL_Tree<Key, T>::root == nullptr) return begin();

  typename AVL_Tree<Key, T>::Node *last_node =
      AVL_Tree<Key, T>::get_max(AVL_Tree<Key, T>::root);
  MapIterator test(nullptr, last_node);
  return test;
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert_or_assign(
    const Key &key, const T &obj) {
  map<Key, T>::MapIterator iter = find(key);
  if (iter != nullptr) {
    erase(iter);
    auto pr = insert(key, obj);
    pr.second = false;
    return pr;
  }
  return insert(key, obj);
}

template <typename Key, typename T>
void map<Key, T>::erase(map::iterator pos) {
  if (AVL_Tree<Key, T>::root == nullptr || pos.current_node == nullptr) return;
  AVL_Tree<Key, T>::root = AVL_Tree<Key, T>::remove_node_find(
      AVL_Tree<Key, T>::root, pos.current_node->key);
}

template <typename Key, typename T>
void map<Key, T>::merge(map &other) {
  map const_tree(other);
  iterator const_it = const_tree.begin();
  for (; const_it != const_tree.end(); ++const_it) {
    auto key = (*const_it).first;
    auto obj = (*const_it).second;
    std::pair<iterator, bool> pr = insert(key, obj);
    if (pr.second) other.erase(pr.first);
  }
}

template <typename Key, typename T>
template <class... Args>
std::vector<std::pair<typename map<Key, T>::MapIterator, bool>>
map<Key, T>::insert_many(Args &&...args) {
  std::vector<std::pair<typename map<Key, T>::iterator, bool>> vec;
  for (const auto &arg : {args...}) {
    vec.push_back(insert(arg));
  }
  return vec;
}