#ifndef __S21_VECTOR_ITERATOR_H__
#define __S21_VECTOR_ITERATOR_H__

#include <iostream>

#include "s21_vector.h"

namespace s21 {

// Конструктор
template <typename T>
vector<T>::VectorIterator::VectorIterator(T* p) : ptr(p) {}

// разыменование итератора
template <typename T>
T& vector<T>::VectorIterator::operator*() const {
  return *ptr;
}

// // разыменование итератора
// template <typename T>
// T& vector<T>::VectorIterator::operator*() const {
//     if (ptr < vec->arr || ptr >= vec->arr + vec->_m_size) {
//         throw std::out_of_range("Iterator out of range");
//     }
//     return *ptr;
// }

// доступа к членам объекта
template <typename T>
T* vector<T>::VectorIterator::operator->() const {
  return ptr;
}

// перегрузка +
template <typename T>
typename vector<T>::VectorIterator vector<T>::VectorIterator::operator+(
    size_t n) const {
  return VectorIterator(ptr + n);
}

// перегрузка -
template <typename T>
typename vector<T>::VectorIterator vector<T>::VectorIterator::operator-(
    size_t n) const {
  return VectorIterator(ptr - n);
}

// Префиксный инкремент ++it (увеличивает отдаёт)
template <typename T>
typename vector<T>::VectorIterator& vector<T>::VectorIterator::operator++() {
  ++ptr;
  return *this;
}

// Постфиксный инкремент it++ (увеличивает но отдаёт копию до увеличения)
template <typename T>
typename vector<T>::VectorIterator vector<T>::VectorIterator::operator++(int) {
  VectorIterator tmp = *this;
  ++ptr;
  return tmp;
}

// Префиксный декремент --it (уменьшает отдаёт)
template <typename T>
typename vector<T>::VectorIterator& vector<T>::VectorIterator::operator--() {
  --ptr;
  return *this;
}

// Постфиксный декремент it-- (уменьшает но отдаёт копию до уменьшения)
template <typename T>
typename vector<T>::VectorIterator vector<T>::VectorIterator::operator--(int) {
  VectorIterator tmp = *this;
  --ptr;
  return tmp;
}

// сдвиг инератора + n
template <typename T>
typename vector<T>::VectorIterator& vector<T>::VectorIterator::operator+=(
    size_t n) {
  ptr += n;
  return *this;
}

// сдвиг инератора - n
template <typename T>
typename vector<T>::VectorIterator& vector<T>::VectorIterator::operator-=(
    size_t n) {
  ptr -= n;
  return *this;
}

// инераторы равны
template <typename T>
bool vector<T>::VectorIterator::operator==(const VectorIterator& other) const {
  return ptr == other.ptr;
}

// инераторы не равны
template <typename T>
bool vector<T>::VectorIterator::operator!=(const VectorIterator& other) const {
  return ptr != other.ptr;
}

// возвращает итератор на начало
template <typename T>
typename vector<T>::VectorIterator vector<T>::begin() {
  return vector<T>::VectorIterator(arr);
}

// // возвращает итератор на конец
template <typename T>
typename vector<T>::VectorIterator vector<T>::end() {
  return vector<T>::VectorIterator(arr + _m_size);
}

// вычитание одного итератора из другого
template <typename T>
ptrdiff_t vector<T>::VectorIterator::operator-(
    const VectorIterator& other) const {
  return ptr - other.ptr;
}

// сравнение итераторов <
template <typename T>
bool vector<T>::VectorIterator::operator<(const VectorIterator& other) const {
  return ptr < other.ptr;
}

// сравнение итераторов >
template <typename T>
bool vector<T>::VectorIterator::operator>(const VectorIterator& other) const {
  return ptr > other.ptr;
}
}  // namespace s21

#endif  // __S21_VECTOR_ITERATOR_H__
