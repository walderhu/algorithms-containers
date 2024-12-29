#ifndef __S21_VECTOR_CAPACITY_H__
#define __S21_VECTOR_CAPACITY_H__

#include "s21_vector.hpp"

namespace s21 {

// Получение размера
template <typename T>
size_t vector<T>::size() const {
  return _m_size;
}

// Получение емкости
template <typename T>
size_t vector<T>::capacity() const {
  return _m_capacity;
}

// проверяет, пуст ли контейнер
template <typename T>
bool vector<T>::empty() const {
  return _m_size == 0;
}

// возвращает максимально возможное количество элементов
template <typename T>
typename vector<T>::size_type vector<T>::max_size() {
  return (std::numeric_limits<size_t>::max() / sizeof(T)) / 2;
}

// выделяет хранилище элементов size и копирует текущие элементы массива в новый
// выделенный массив
template <typename T>
void vector<T>::reserve(size_type size) {
  if (size > _m_capacity) {
    resize(size);
  }
}

// уменьшает использование памяти, освобождая неиспользуемую память
template <typename T>
void vector<T>::shrink_to_fit() {
  if (_m_size < _m_capacity) {
    resize(_m_size);
  }
}
}  // namespace s21
#endif  // __S21_VECTOR_CAPACITY_H__