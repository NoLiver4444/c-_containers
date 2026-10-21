#ifndef S21_VECTOR_H_
#define S21_VECTOR_H_

namespace s21 {

template <typename T>
class vector {
 public:
  class VectorIterator;
  class VectorConstIterator;

  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator_pointer = T *;
  using const_iterator_pointer = const T *;
  using iterator = vector<T>::VectorIterator;
  using const_iterator = vector<T>::VectorConstIterator;
  using size_type = size_t;

  vector();
  vector(size_type n);
  vector(std::initializer_list<value_type> const &items);
  vector(const vector &v);
  vector(vector &&v);
  ~vector();
  vector &operator=(vector &&v);

  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  iterator_pointer data();

  iterator begin();
  iterator end();
  const_iterator cbegin() const;
  const_iterator cend() const;

  bool empty();
  size_type size();
  size_type max_size();
  void reserve(size_type size);
  size_type capacity();
  void shrink_to_fit();

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector &other);

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);
  template <typename... Args>
  void insert_many_back(Args &&...args);

  class VectorIterator {
   public:
    VectorIterator();
    VectorIterator(iterator_pointer ptr);
    iterator &operator++();
    iterator &operator--();
    iterator operator++(int);
    iterator operator--(int);
    iterator operator+(int n) const;
    iterator operator-(int n) const;
    ptrdiff_t operator-(const VectorIterator &other) const;
    bool operator!=(const iterator &other) const;
    bool operator==(const iterator &other) const;
    reference operator*();

   private:
    iterator_pointer current_iterator;
  };

  class VectorConstIterator {
   public:
    VectorConstIterator();
    VectorConstIterator(const_iterator_pointer ptr);

    const_iterator &operator++();
    const_iterator &operator--();
    const_iterator operator++(int);
    const_iterator operator--(int);
    const_iterator operator+(int n) const;
    const_iterator operator-(int n) const;
    bool operator==(const VectorConstIterator &other) const;
    bool operator!=(const VectorConstIterator &other) const;
    const_reference operator*();
    ptrdiff_t operator-(const VectorConstIterator &other) const;

   private:
    const_iterator_pointer current_iterator;
  };

 private:
  iterator_pointer data_vector;
  size_type size_vector;
  size_type capacity_vector;
};

#include "s21_vector.tpp"

}  // namespace s21

#endif