#ifndef __S21_VECTOR_ELEMENT_ACCESS_H__
#define __S21_VECTOR_ELEMENT_ACCESS_H__

#include "s21_vector.hpp"

namespace s21 {

// Неконстантная версия оператора []
template <typename T>
T& vector<T>::operator[](size_t index) {
  if (index >= _m_size) {
    throw std::out_of_range("Index out of range");
  }
  return arr[index];
}

// Константная версия оператора []
template <typename T>
const T& vector<T>::operator[](size_t index) const {
  if (index >= _m_size) {
    throw std::out_of_range("Index out of range");
  }
  return arr[index];
}

// элемент по индексу
template <typename T>
T vector<T>::at(size_t i) {
  return arr[i];
}

// доступ к первому элементу
template <typename T>
const T& vector<T>::front() const {
  if (_m_size == 0) {
    throw std::out_of_range("vector is empty");
  }
  return arr[0];
}

// доступ к последнему элементу
template <typename T>
const T& vector<T>::back() const {
  if (_m_size == 0) {
    throw std::out_of_range("vector is empty");
  }
  return arr[_m_size - 1];
}

// прямой доступ к базовому массиву
template <typename T>
T* vector<T>::data() {
  return arr;
}
}  // namespace s21
#endif  // __S21_VECTOR_ELEMENT_ACCESS_H__