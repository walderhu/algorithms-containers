#ifndef __S21_VECTOR_MEMBER_FUNC_H__
#define __S21_VECTOR_MEMBER_FUNC_H__

#include "s21_vector.hpp"

namespace s21 {

// Базовый конструктор
template <typename T>
vector<T>::vector() {
  _m_size = 0U;
  _m_capacity = 0U;
  arr = nullptr;
}

// Конструктор заданной длины
template <typename T>
vector<T>::vector(size_t n) {
  _m_size = n;
  // _m_capacity = n * 2;
  _m_capacity = n;
  arr = new T[_m_capacity];
}

// Конструктор списков инициализаторов
template <typename T>
vector<T>::vector(std::initializer_list<value_type> const& items) {
  arr = new T[items.size()];
  int i = 0;
  for (auto it = items.begin(); it != items.end(); it++) {
    arr[i] = *it;
    i++;
  }
  _m_size = items.size();
  _m_capacity = items.size();
}

// Конструктор копирования
template <typename T>
vector<T>::vector(const vector& v)
    : _m_size(v._m_size), _m_capacity(v._m_capacity), arr(nullptr) {
  arr = new T[_m_capacity];
  for (size_t i = 0; i < _m_size; i++) {
    arr[i] = v.arr[i];
  }
}

// Перегрузка = (копирование)
template <typename T>
vector<T>& vector<T>::operator=(const vector& v) {
  T* new_arr = new T[v._m_capacity];
  for (size_t i = 0; i < v._m_size; i++) {
    new_arr[i] = v.arr[i];
  }
  delete[] arr;
  _m_size = v._m_size;
  _m_capacity = v._m_capacity;
  return *this;
}

// Конструктор перемещения
// пример: vector<int> obj_2 = std::move(obj_1)
template <typename T>
vector<T>::vector(vector&& v) noexcept
    : _m_size(v._m_size), _m_capacity(v._m_capacity), arr(v.arr) {
  v.arr = nullptr;
  v._m_size = 0;
  v._m_capacity = 0;
}

// Перегрузка = (перемещение)
// пример: obj_2 = std::move(obj_1)
template <typename T>
vector<T>& vector<T>::operator=(vector&& v) {
  if (this != &v) {  // Проверка на самоприсваивание
    delete[] arr;    // Освобождение старой памяти

    arr = v.arr;
    _m_size = v._m_size;
    _m_capacity = v._m_capacity;

    v.arr = nullptr;
    v._m_size = 0;
    v._m_capacity = 0;
  }
  return *this;
}

// Деструктор
template <typename T>
vector<T>::~vector() {
  delete[] arr;
}
}  // namespace s21

#endif  // __S21_VECTOR_MEMBER_FUNC_H__