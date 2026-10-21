#include "s21_vector.h"

template <typename T>
vector<T>::vector()
    : data_vector(nullptr), size_vector(0), capacity_vector(0) {}

template <typename T>
vector<T>::vector(size_type n) {
  data_vector = new value_type[n];
  size_vector = n;
  capacity_vector = n;
  std::fill_n(data_vector, n, value_type());
}

template <typename T>
vector<T>::vector(std::initializer_list<value_type> const &items) {
  data_vector = new value_type[items.size()];
  size_vector = items.size();
  capacity_vector = items.size();
  std::copy(items.begin(), items.end(), data_vector);
}

template <typename T>
vector<T>::vector(const vector &v) {
  data_vector = new value_type[v.capacity_vector];
  size_vector = v.size_vector;
  capacity_vector = v.capacity_vector;
  std::copy(v.data_vector, v.data_vector + v.size_vector, data_vector);
}

template <typename T>
vector<T>::vector(vector &&v) {
  size_vector = std::exchange(v.size_vector, 0);
  capacity_vector = std::exchange(v.capacity_vector, 0);
  data_vector = std::exchange(v.data_vector, nullptr);
}

template <typename T>
vector<T>::~vector() {
  delete[] data_vector;

  data_vector = nullptr;
  size_vector = 0;
  capacity_vector = 0;
}

template <typename T>
vector<T> &vector<T>::operator=(vector &&v) {
  if (this != &v) {
    this->swap(v);

    v.~vector();
  }
  return *this;
}

template <typename T>
vector<T>::reference vector<T>::at(size_type pos) {
  if (pos >= size_vector) {
    throw std::out_of_range("at: Index out of range");
  }
  return data_vector[pos];
}

template <typename T>
vector<T>::reference vector<T>::operator[](size_type pos) {
  if (pos >= size_vector) {
    throw std::out_of_range("IndexError: Index out of range");
  }
  return data_vector[pos];
}

template <typename T>
typename vector<T>::size_type vector<T>::size() {
  return size_vector;
}

template <typename T>
typename vector<T>::size_type vector<T>::capacity() {
  return capacity_vector;
}

template <typename T>
typename vector<T>::const_reference vector<T>::front() {
  if (size_vector == 0) {
    throw std::out_of_range("FrontError: vector is empty");
  }

  return data_vector[0];
}

template <typename T>
typename vector<T>::const_reference vector<T>::back() {
  if (size_vector == 0) {
    throw std::out_of_range("BackError: vector is empty");
  }

  return data_vector[size_vector - 1];
}

template <typename T>
typename vector<T>::iterator_pointer vector<T>::data() {
  return data_vector;
}

template <typename T>
void vector<T>::swap(vector &other) {
  std::swap(data_vector, other.data_vector);
  std::swap(size_vector, other.size_vector);
  std::swap(capacity_vector, other.capacity_vector);
}

template <typename T>
vector<T>::iterator::VectorIterator() : current_iterator(nullptr) {}

template <typename T>
vector<T>::iterator::VectorIterator(iterator_pointer ptr)
    : current_iterator(ptr) {}

template <typename T>
typename vector<T>::iterator &vector<T>::iterator::operator++() {
  ++current_iterator;

  return *this;
}

template <typename T>
typename vector<T>::iterator &vector<T>::iterator::operator--() {
  --current_iterator;

  return *this;
}

template <typename T>
typename vector<T>::iterator vector<T>::iterator::operator++(int) {
  iterator tmp(*this);
  ++current_iterator;

  return *this;
}

template <typename T>
typename vector<T>::iterator vector<T>::iterator::operator--(int) {
  iterator tmp(*this);
  --current_iterator;

  return *this;
}

template <typename T>
typename vector<T>::iterator vector<T>::iterator::operator+(int n) const {
  VectorIterator tmp(*this);
  for (int i = 0; i < n; i++) {
    tmp++;
  };

  return tmp;
}

template <typename T>
typename vector<T>::iterator vector<T>::iterator::operator-(int n) const {
  VectorIterator tmp(*this);
  for (int i = 0; i < n; i++) {
    tmp--;
  };

  return tmp;
}

template <typename T>
ptrdiff_t vector<T>::VectorIterator::operator-(
    const VectorIterator &other) const {
  return current_iterator - other.current_iterator;
}

template <typename T>
bool vector<T>::iterator::operator!=(const iterator &other) const {
  return current_iterator != other.current_iterator;
}

template <typename T>
bool vector<T>::iterator::operator==(const iterator &other) const {
  return current_iterator == other.current_iterator;
}

template <typename T>
typename vector<T>::reference vector<T>::iterator::operator*() {
  return *current_iterator;
}

template <typename T>
vector<T>::VectorConstIterator::VectorConstIterator()
    : current_iterator(nullptr) {}

template <typename T>
vector<T>::VectorConstIterator::VectorConstIterator(
    vector<T>::const_iterator_pointer ptr)
    : current_iterator(ptr) {}

template <typename T>
typename vector<T>::VectorConstIterator &
vector<T>::VectorConstIterator::operator++() {
  ++current_iterator;

  return *this;
}

template <typename T>
typename vector<T>::VectorConstIterator &
vector<T>::VectorConstIterator::operator--() {
  --current_iterator;

  return *this;
}

template <typename T>
typename vector<T>::VectorConstIterator
vector<T>::VectorConstIterator::operator++(int) {
  const_iterator tmp(*this);
  ++current_iterator;

  return *this;
}

template <typename T>
typename vector<T>::VectorConstIterator
vector<T>::VectorConstIterator::operator--(int) {
  const_iterator tmp(*this);
  --current_iterator;

  return *this;
}

template <typename T>
typename vector<T>::VectorConstIterator
vector<T>::VectorConstIterator::operator+(int n) const {
  VectorConstIterator tmp(*this);
  for (int i = 0; i < n; i++) {
    tmp++;
  };

  return tmp;
}

template <typename T>
typename vector<T>::VectorConstIterator
vector<T>::VectorConstIterator::operator-(int n) const {
  VectorConstIterator tmp(*this);
  for (int i = 0; i < n; i++) {
    tmp--;
  };

  return tmp;
}

template <typename T>
ptrdiff_t vector<T>::VectorConstIterator::operator-(
    const VectorConstIterator &other) const {
  return current_iterator - other.current_iterator;
}

template <typename T>
bool vector<T>::VectorConstIterator::operator!=(
    const VectorConstIterator &other) const {
  return current_iterator != other.current_iterator;
}

template <typename T>
bool vector<T>::VectorConstIterator::operator==(
    const VectorConstIterator &other) const {
  return current_iterator == other.current_iterator;
}

template <typename T>
typename vector<T>::const_reference
vector<T>::VectorConstIterator::operator*() {
  return *current_iterator;
}

template <typename T>
typename vector<T>::iterator vector<T>::begin() {
  iterator iter(data_vector);
  return iter;
}

template <typename T>
typename vector<T>::iterator vector<T>::end() {
  iterator iter(data_vector + size_vector);
  return iter;
}

template <typename T>
typename vector<T>::const_iterator vector<T>::cbegin() const {
  return const_iterator(data_vector);
}

template <typename T>
typename vector<T>::const_iterator vector<T>::cend() const {
  return const_iterator(data_vector + size_vector);
}

template <typename T>
bool vector<T>::empty() {
  return size_vector == 0;
}

template <typename T>
typename vector<T>::size_type vector<T>::max_size() {
  return std::numeric_limits<std::size_t>::max() / sizeof(value_type);
}

template <typename T>
void vector<T>::reserve(size_type size) {
  if (size <= capacity_vector) {
    return;
  }

  if (size > max_size()) {
    throw std::out_of_range("ReserveError: Too large size for a new capacity");
  }

  iterator_pointer new_data = new value_type[size];
  std::copy(data_vector, data_vector + size_vector, new_data);
  delete[] data_vector;
  data_vector = new_data;
  capacity_vector = size;
}

template <typename T>
void vector<T>::shrink_to_fit() {
  if (size_vector < capacity_vector) {
    iterator_pointer new_data = new value_type[size];
    std::copy(data_vector, data_vector + size_vector, new_data);
    delete[] data_vector;
    data_vector = new_data;
    capacity_vector = size;
  }
}

template <typename T>
void vector<T>::clear() {
  ~vector();
}

template <typename T>
typename vector<T>::iterator vector<T>::insert(iterator pos,
                                               const_reference value) {
  size_type idx = pos - begin();

  if (idx > size_vector) {
    throw std::out_of_range(
        "InsertError: The insertion position is out of range of the vector "
        "memory");
  }

  if (size_vector == capacity_vector) {
    reserve(capacity_vector ? capacity_vector * 2 : 1);
  }

  iterator new_pos = begin() + idx;

  for (iterator it = end(); it != new_pos; --it) {
    *it = *(it - 1);
  }
  *new_pos = value;
  ++size_vector;

  return new_pos;
}

template <typename T>
void vector<T>::erase(iterator pos) {
  size_type position = pos - data_vector;

  if (position > size_vector) {
    throw std::out_of_range(
        "EraseError: The insertion position is out of range of the vector "
        "memory");
  }

  for (iterator it = pos; it != end() - 1; ++it) {
    *it = *(it + 1);
  }

  --size_vector;
}

template <typename T>
void vector<T>::push_back(const_reference value) {
  insert(end(), value);
}

template <typename T>
void vector<T>::pop_back() {
  erase(--end());
}

template <typename T>
template <typename... Args>
typename vector<T>::iterator vector<T>::insert_many(const_iterator pos,
                                                    Args &&...args) {
  vector<value_type> tmp{args...};
  iterator cur_pos = begin() + (pos - cbegin());
  for (size_t i = 0; i < tmp.size(); ++i) {
    cur_pos = insert(cur_pos, tmp[i]);
    ++cur_pos;
  }

  return cur_pos;
}

template <typename T>
template <typename... Args>
void vector<T>::insert_many_back(Args &&...args) {
  insert_many(cend(), args...);
}