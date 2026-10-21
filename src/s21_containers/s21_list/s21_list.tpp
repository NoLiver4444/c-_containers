#include "s21_list.h"

template <typename T>
list<T>::list() : size_list(0), head(nullptr), tail(nullptr) {}

template <typename T>
list<T>::list(size_type n) : list() {
  if (n > 0) {
    for (size_type i = 0; i < n; ++i) {
      push_front(value_type());
    }
  }
}

template <typename T>
list<T>::list(std::initializer_list<value_type> const &items) : list() {
  for (auto i = items.begin(); i != items.end(); ++i) {
    push_back(*i);
  }
}

template <typename T>
list<T>::list(const list &l) : size_list(0), head(nullptr), tail(nullptr) {
  Node *current = l.head;
  while (current) {
    push_back(current->value);
    current = current->next;
  }
}

template <typename T>
list<T>::list(list &&l) {
  size_list = std::exchange(l.size_list, 0);
  head = std::exchange(l.head, nullptr);
  tail = std::exchange(l.tail, nullptr);
}

template <typename T>
list<T>::~list() {
  clear();
}

template <class T>
void list<T>::clear() {
  while (!empty()) {
    pop_front();
  }
}

template <typename T>
list<T> &list<T>::operator=(list &&l) {
  if (this != &l) {
    clear();
    size_list = std::exchange(l.size_list, 0);
    head = std::exchange(l.head, nullptr);
    tail = std::exchange(l.tail, nullptr);
  }
  return *this;
}

// Оператор копирующего присваивания (должен быть добавлен)
template <typename T>
list<T> &list<T>::operator=(const list &l) {
  if (this != &l) {
    list<T> temp(l);
    std::swap(size_list, temp.size_list);
    std::swap(head, temp.head);
    std::swap(tail, temp.tail);
  }
  return *this;
}

template <typename T>
bool list<T>::empty() {
  return size_list == 0;
}

template <typename T>
typename list<T>::size_type list<T>::size() {
  return size_list;
}

template <class T>
typename list<T>::size_type list<T>::max_size() {
  return std::numeric_limits<size_type>::max() / sizeof(Node) / 2;
}

template <typename T>
list<T>::Node::Node(value_type val, Node *prev_node, Node *next_node)
    : value(val), prev(prev_node), next(next_node) {}

template <typename T>
void list<T>::push_front(const_reference value) {
  Node *node = new Node(value);
  node->next = head;
  node->prev = nullptr;
  if (head) {
    head->prev = node;
  }
  head = node;
  if (tail == nullptr) {
    tail = node;
  }
  ++size_list;
}

template <typename T>
void list<T>::pop_front() {
  if (empty()) return;

  Node *to_delete = head;
  head = head->next;
  if (head) {
    head->prev = nullptr;
  } else {
    tail = nullptr;
  }
  delete to_delete;
  --size_list;
}

template <typename T>
void list<T>::push_back(const_reference value) {
  Node *node = new Node(value);
  node->prev = tail;
  node->next = nullptr;
  if (tail) {
    tail->next = node;
  }
  tail = node;
  if (head == nullptr) {
    head = node;
  }
  ++size_list;
}

template <typename T>
void list<T>::pop_back() {
  if (empty()) return;

  Node *to_delete = tail;
  tail = tail->prev;
  if (tail) {
    tail->next = nullptr;
  } else {
    head = nullptr;
  }
  delete to_delete;
  --size_list;
}

template <typename T>
list<T>::ListIterator::ListIterator() : current_node(nullptr) {}

template <typename T>
list<T>::ListIterator::ListIterator(Node *ptr) : current_node(ptr) {}

template <typename T>
typename list<T>::reference list<T>::ListIterator::operator*() {
  if (current_node == nullptr) {
    throw std::out_of_range("*: pointer nullptr");
  }
  return current_node->value;
}

template <typename T>
typename list<T>::iterator &list<T>::ListIterator::operator++() {
  if (current_node == nullptr) {
    throw std::out_of_range("++: pointer nullptr");
  }
  current_node = current_node->next;
  return *this;
}

template <typename T>
typename list<T>::iterator &list<T>::ListIterator::operator--() {
  if (current_node == nullptr) {
    throw std::out_of_range("--: pointer nullptr");
  }
  current_node = current_node->prev;
  return *this;
}

template <typename T>
typename list<T>::iterator list<T>::ListIterator::operator++(int) {
  if (current_node == nullptr) {
    throw std::out_of_range("Iterator::operator++(int): pointer is nullptr");
  }
  ListIterator temp = *this;
  current_node = current_node->next;
  return temp;
}

template <typename T>
typename list<T>::iterator list<T>::ListIterator::operator--(int) {
  if (current_node == nullptr) {
    throw std::out_of_range("Iterator::operator--(int): pointer is nullptr");
  }
  ListIterator temp = *this;
  current_node = current_node->prev;
  return temp;
}

template <typename T>
bool list<T>::ListIterator::operator==(const iterator &other) const {
  return current_node == other.current_node;
}

template <typename T>
bool list<T>::ListIterator::operator!=(const iterator &other) const {
  return current_node != other.current_node;
}

template <typename T>
list<T>::ListConstIterator::ListConstIterator() : current_node() {}

template <typename T>
list<T>::ListConstIterator::ListConstIterator(Node *ptr) : current_node(ptr) {}

template <typename T>
typename list<T>::const_reference list<T>::ListConstIterator::operator*()
    const {
  if (current_node == nullptr) {
    throw std::out_of_range("*: pointer nullptr");
  }
  return current_node->value;
}

template <typename T>
typename list<T>::iterator list<T>::begin() {
  if (empty()) {
    throw std::out_of_range("list::begin(): list is empty");
  }
  return head;
}

template <typename T>
typename list<T>::iterator list<T>::end() {
  if (empty()) {
    throw std::out_of_range("list::end(): list is empty");
  }
  return tail;
}

template <typename T>
typename list<T>::const_iterator list<T>::const_begin() {
  return const_iterator(head);
}

template <typename T>
typename list<T>::const_iterator list<T>::const_end() {
  return const_iterator(nullptr);
}

template <typename T>
typename list<T>::const_reference list<T>::front() {
  if (empty()) {
    throw std::out_of_range("list::front(): list is empty");
  }
  return *begin();
}

template <typename T>
typename list<T>::const_reference list<T>::back() {
  if (empty()) {
    throw std::out_of_range("list::front(): list is empty");
  }
  return tail->value;
}

template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos,
                                           const_reference value) {
  iterator answ;

  if (pos == end()) {
    push_back(value);
    answ = tail;
  } else if (pos == begin()) {
    push_front(value);
    answ = head;
  } else {
    Node *new_node = new Node(value, pos.current_node->prev, pos.current_node);
    new_node->next = pos.current_node;
    new_node->prev = pos.current_node->prev;
    pos.current_node->prev->next = new_node;
    pos.current_node->prev = new_node;
    ++size_list;
    answ = iterator(new_node);
  }

  return answ;
}

template <typename T>
void list<T>::erase(iterator pos) {
  if (pos == begin()) {
    pop_front();
  } else if (pos == end()) {
    pop_back();
  } else {
    Node *to_delete = pos.current_node;

    to_delete->prev->next = to_delete->next;
    to_delete->next = to_delete->prev;
    delete to_delete;
    --size_list;
  }
}

template <typename T>
void list<T>::swap(list &other) {
  std::swap(size_list, other.size_list);
  std::swap(tail, other.tail);
  std::swap(head, other.head);
}

template <class T>
void list<T>::merge(list &other) {
  sort();
  other.sort();

  auto it1 = begin();
  auto it2 = other.begin();

  while (it1 != end() && it2 != other.end()) {
    if (*it2 < *it1) {
      insert(it1, *it2);
      ++it2;
    } else {
      ++it1;
    }
  }

  while (it2 != other.end()) {
    insert(end(), *it2);
    ++it2;
  }

  insert(end(), *it2);
  sort();
  other.clear();
}

template <typename T>
void list<T>::splice(const_iterator pos, list &other) {
  if (!other.empty()) {
    for (iterator it = other.begin(); it != other.end(); ++it) {
      insert(pos, *it);
    }
  }
}

template <class T>
void list<T>::sort() {
  this->head = MergeSort(this->head);
  this->tail = this->head;
  while (this->tail->next != nullptr) {
    this->tail = this->tail->next;
  }
}

template <class T>
typename list<T>::Node *list<T>::MergeSort(typename list<T>::Node *head) {
  if (head == nullptr || head->next == nullptr) {
    return head;
  }
  typename list<T>::Node *middle = GetMiddle(head);
  typename list<T>::Node *nextOfMiddle = middle->next;
  middle->next = nullptr;
  typename list<T>::Node *left = MergeSort(head);
  typename list<T>::Node *right = MergeSort(nextOfMiddle);
  return Merge(left, right);
}

template <class T>
typename list<T>::Node *list<T>::GetMiddle(typename list<T>::Node *head) {
  typename list<T>::Node *slow = head;
  typename list<T>::Node *fast = head;
  while (fast->next != nullptr && fast->next->next != nullptr) {
    slow = slow->next;
    fast = fast->next->next;
  }
  return slow;
}

template <class T>
typename list<T>::Node *list<T>::Merge(typename list<T>::Node *left,
                                       typename list<T>::Node *right) {
  typename list<T>::Node *result = nullptr;
  if (left == nullptr) {
    return right;
  } else if (right == nullptr) {
    return left;
  }
  if (left->value <= right->value) {
    result = left;
    result->next = Merge(left->next, right);
  } else {
    result = right;
    result->next = Merge(left, right->next);
  }
  return result;
}

template <typename T>
void list<T>::print_list() {
  iterator iter = begin();

  while (iter != end()) {
    std::cout << *iter << " ";
    ++iter;
  }
  std::cout << *iter << "\n";
}

template <typename T>
void list<T>::reverse() {
  if (size_list <= 1) return;

  Node *current = head;
  while (current != nullptr) {
    std::swap(current->next, current->prev);
    current = current->prev;
  }

  std::swap(head, tail);
}

template <class T>
void list<T>::unique() {
  if (!this->empty()) {
    for (iterator it_last = begin(); it_last != end();) {
      iterator it_next = it_last;
      ++it_next;
      if (it_next.current_node == nullptr) {
        return;
      } else if (*it_last == *it_next) {
        erase(it_next);
      } else {
        ++it_last;
      }
    }
  }
}

template <class T>
template <class... Args>
typename list<T>::iterator list<T>::insert_many(iterator pos, Args &&...args) {
  for (const auto &arg : {args...}) {
    insert(pos, arg);
  }
  return pos;
}

template <class T>
template <class... Args>
void list<T>::insert_many_back(Args &&...args) {
  for (const auto &arg : {args...}) {
    push_back(arg);
  }
}

template <class T>
template <class... Args>
void list<T>::insert_many_front(Args &&...args) {
  for (const auto &arg : {args...}) {
    push_front(arg);
  }
}
