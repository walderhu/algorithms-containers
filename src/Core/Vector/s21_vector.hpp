#ifndef __S21_VECTOR_H__
#define __S21_VECTOR_H__

#include "../s21_containers.hpp"
namespace s21 {

template <typename T>
class vector {
 private:
  size_t _m_size;
  size_t _m_capacity;
  T* arr;

 public:
  // подкласс итератора
  class VectorIterator {
   private:
    T* ptr;

   public:
    VectorIterator(T* p);
    T& operator*() const;
    T* operator->() const;
    VectorIterator operator+(size_t n) const;
    VectorIterator operator-(size_t n) const;
    bool operator==(const VectorIterator& other) const;
    bool operator!=(const VectorIterator& other) const;
    bool operator<(const VectorIterator& other) const;
    bool operator>(const VectorIterator& other) const;
    VectorIterator& operator++();
    VectorIterator operator++(int);
    VectorIterator& operator--();
    VectorIterator operator--(int);
    VectorIterator& operator+=(size_t n);
    VectorIterator& operator-=(size_t n);
    ptrdiff_t operator-(const VectorIterator& other) const;
  };

  // переопределения типов
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = VectorIterator;
  using const_iterator = const T*;
  using size_type = size_t;

  vector();
  vector(size_t n);
  vector(std::initializer_list<value_type> const& items);
  vector(const vector& v);
  vector(vector&& v) noexcept;
  ~vector();
  void push_back(const T& value);
  size_t size() const;
  size_t capacity() const;
  T at(size_t i);
  const T& front() const;
  const T& back() const;
  T* data();
  bool empty() const;
  size_type max_size();
  void reserve(size_type size);
  void shrink_to_fit();
  void clear();
  VectorIterator insert(VectorIterator pos, const_reference value);
  VectorIterator begin();
  VectorIterator end();
  void erase(VectorIterator pos);
  void pop_back();
  void swap(vector& other);
  T& operator[](size_t index);
  const T& operator[](size_t index) const;
  vector& operator=(const vector& v);
  vector& operator=(vector&& v);
  template <typename... Args>
  VectorIterator insert_many(VectorIterator pos, Args&&... args);
  template <typename... Args>
  void insert_many_back(Args&&... args);

 private:
  void resize(size_t new_capacity);
};
}  // namespace s21

#include "s21_vector_capacity.hpp"
#include "s21_vector_element_access.hpp"
#include "s21_vector_iterator.hpp"
#include "s21_vector_member_func.hpp"
#include "s21_vector_modifiers.hpp"

#endif  // __S21_VECTOR_H__