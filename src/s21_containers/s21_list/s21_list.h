#ifndef S21_LIST_H_
#define S21_LIST_H_

namespace s21 {

template <typename T>
class list {
 public:
  class ListIterator;
  class ListConstIterator;
  struct Node;

  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = list<T>::ListIterator;
  using const_iterator = list<T>::ListConstIterator;
  using size_type = size_t;

  list();
  list(size_type n);
  list(std::initializer_list<value_type> const &items);
  list(const list &l);
  list(list &&l);
  ~list();
  list &operator=(list &&l);
  list &operator=(const list &l);

  const_reference front();
  const_reference back();

  iterator begin();
  iterator end();

  const_iterator const_begin();
  const_iterator const_end();

  bool empty();
  size_type size();
  size_type max_size();

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(list &other);
  void merge(list &other);
  void splice(const_iterator pos, list &other);
  void reverse();
  void unique();
  void sort();

  template <class... Args>
  iterator insert_many(iterator pos, Args &&...args);
  template <class... Args>
  void insert_many_back(Args &&...args);
  template <class... Args>
  void insert_many_front(Args &&...args);

  void print_list();

  struct Node {
   protected:
    value_type value;
    Node *prev = nullptr;
    Node *next = nullptr;
    Node(value_type val = value_type(), Node *prev_node = nullptr,
         Node *next_node = nullptr);
    friend class list;
  };

  class ListIterator {
   public:
    ListIterator();
    ListIterator(Node *ptr);
    reference operator*();
    iterator &operator++();
    iterator &operator--();
    iterator operator++(int);
    iterator operator--(int);
    bool operator==(const iterator &other) const;
    bool operator!=(const iterator &other) const;
    friend class list;

   protected:
    Node *current_node;
  };

  class ListConstIterator : public ListIterator {
   public:
    ListConstIterator();
    ListConstIterator(Node *ptr);
    const_reference operator*() const;
    friend class list;

   private:
    Node *current_node;
  };

 private:
  size_type size_list;
  Node *head;
  Node *tail;

  Node *MergeSort(Node *head);
  Node *GetMiddle(Node *head);
  Node *Merge(Node *left, Node *right);
};

#include "s21_list.tpp"

}  // namespace s21

#endif