#include "s21_array.h"

template <typename T, std::size_t N>
array<T, N>::array() : data_array(nullptr), size_array(N) {}

template <typename T, std::size_t N>
array<T, N>::array(std::initializer_list<value_type> const &items) {
  data_array = new value_type[items.size()];
  size_array = items.size();
  std::copy(items.begin(), items.end(), data_array);
}

template <typename T, std::size_t N>
array<T, N>::array(const array &a) {
  data_array = new value_type[a.size_array];
  size_array = a.size_array;
  std::copy(a.data_array, a.data_array + a.size_array, data_array);
}

template <typename T, std::size_t N>
array<T, N>::array(array &&a) {
  size_array = std::exchange(a.size_array, 0);
  data_array = std::exchange(a.data_array, nullptr);
}

template <typename T, std::size_t N>
array<T, N>::~array() {
  delete[] data_array;

  data_array = nullptr;
  size_array = 0;
}

template <typename T, std::size_t N>
typename array<T, N>::array &array<T, N>::operator=(const array<T, N> &a) {
  std::copy(a.data_array, a.data_array + N, data_array);

  return *this;
}

template <typename T, std::size_t N>
typename array<T, N>::array &array<T, N>::operator=(array<T, N> &&a) noexcept {
  for (size_t i = 0; i < N; ++i) {
    data_array[i] = std::move(a.data_array[i]);
  }

  return *this;
}

template <typename T, std::size_t N>
typename array<T, N>::size_type array<T, N>::size() {
  return size_array;
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::begin() {
  iterator iter(data_array);
  return iter;
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::end() {
  iterator iter(data_array + size_array);
  return iter;
}

template <typename T, std::size_t N>
bool array<T, N>::empty() {
  return size_array == 0;
}

template <typename T, std::size_t N>
typename array<T, N>::size_type array<T, N>::max_size() {
  return std::numeric_limits<std::size_t>::max() / sizeof(value_type);
}

template <typename T, std::size_t N>
void array<T, N>::swap(array &other) {
  std::swap(data_array, other.data_array);
  std::swap(size_array, other.size_array);
}

template <typename T, std::size_t N>
array<T, N>::reference array<T, N>::at(size_type pos) {
  if (pos >= size_array) {
    throw std::out_of_range("at: Index out of range");
  }
  return data_array[pos];
}

template <typename T, std::size_t N>
array<T, N>::reference array<T, N>::operator[](size_type pos) {
  if (pos >= size_array) {
    throw std::out_of_range("IndexError: Index out of range");
  }
  return data_array[pos];
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::front() {
  return data_array[0];
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::back() {
  return data_array[size_array - 1];
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::data() {
  return data_array;
}

template <typename T, std::size_t N>
void array<T, N>::fill(const_reference value) {
  std::fill(data_array, data_array + N, value);
}
