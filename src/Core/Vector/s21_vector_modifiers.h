#ifndef __S21_VECTOR_MODIFERS_H__
#define __S21_VECTOR_MODIFERS_H__

#include <iostream>

#include "s21_vector.h"

namespace s21 {

// Метод добавления элемента
template <typename T>
void vector<T>::push_back(const T& value) {
  if (_m_size == _m_capacity) {
    resize(_m_capacity == 0 ? 1 : _m_capacity * 2);
  }
  arr[_m_size++] = value;
}

// Очищает содержимое. Вместимость вектора при этом не изменяется
template <typename T>
void vector<T>::clear() {
  _m_size = 0;
}

// (приватный) метод изменения размера
template <typename T>
void vector<T>::resize(size_t new_capacity) {
  T* new_arr = new T[new_capacity];
  for (size_t i = 0; i < _m_size; i++) {
    new_arr[i] = arr[i];
  }
  delete[] arr;
  arr = new_arr;
  _m_capacity = new_capacity;
}

// вставляет элементы в конкретную позицию и возвращает итератор, указывающий на
// новый элемент. Пример: std::vector<int>::iterator it =
// obj_1.insert(obj_1.begin() + 2, 777)
template <typename T>
typename vector<T>::VectorIterator vector<T>::insert(VectorIterator pos,
                                                     const_reference value) {
  if (pos < begin() || pos > end()) {
    throw std::out_of_range("Iterator out of range");
  }

  size_t index = pos - begin();

  if (_m_size >= _m_capacity) {
    reserve(_m_capacity == 0 ? 1 : _m_capacity * 2);
  }

  for (size_t i = _m_size; i > index; --i) {
    arr[i] = arr[i - 1];
  }

  arr[index] = value;
  ++_m_size;

  return begin() + index;
}

// стирает элемент в позиции pos
template <typename T>
void vector<T>::erase(VectorIterator pos) {
  if (pos < begin() || pos > end() || pos == end()) {
    throw std::out_of_range("Iterator out of range");
  }
  size_t index = pos - begin();

  for (size_t i = index; i < _m_size; ++i) {
    arr[i] = arr[i + 1];
  }
  _m_size -= 1;
}

// удаляет последний элемент
template <typename T>
void vector<T>::pop_back() {
  if (_m_size > 0) {
    // Уничтожаем последний элемент с помощью аллокатора
    // _alloc.destroy(arr + _m_size - 1);
    _m_size -= 1;
  }
}

// меняет содержимое местами
template <typename T>
void vector<T>::swap(vector& other) {
  // Обмениваем указатели на массивы
  T* temp_arr = arr;
  arr = other.arr;
  other.arr = temp_arr;

  // Обмениваем размеры векторов
  size_t temp_size = _m_size;
  _m_size = other._m_size;
  other._m_size = temp_size;

  // Обмениваем вместимости векторов
  size_t temp_capacity = _m_capacity;
  _m_capacity = other._m_capacity;
  other._m_capacity = temp_capacity;
}

// Вставляет новые элементы в контейнер непосредственно перед pos.
// Пример: obj_1.insert_many(it, 777, 888, 999);
template <typename T>
template <typename... Args>
typename vector<T>::VectorIterator vector<T>::insert_many(VectorIterator pos,
                                                          Args&&... args) {
  const size_t num_elements = sizeof...(Args);
  const size_t insert_pos = pos - begin();

  reserve(size() + num_elements);

  // Сдвиг существующих элементов, чтобы освободить место для новых
  for (size_t i = size(); i > insert_pos; --i) {
    arr[i + num_elements - 1] = arr[i - 1];
  }

  // Присвоить новые значения массиву
  size_t index = insert_pos;
  ((arr[index++] = std::forward<Args>(args)), ...);

  _m_size += num_elements;

  return begin() + insert_pos;
}

// Добавляет новые элементы в конец контейнера.
template <typename T>
template <typename... Args>
void vector<T>::insert_many_back(Args&&... args) {
  const size_t num_elements = sizeof...(Args);

  reserve(size() + num_elements);

  // Присвоить новые значения массиву
  size_t index = size();
  ((arr[index++] = std::forward<Args>(args)), ...);

  _m_size += num_elements;
}

}  // namespace s21
#endif  // __S21_VECTOR_MODIFERS_H__