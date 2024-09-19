#ifndef __S21_BASE_ITERATOR_CORE_HPP__
#define __S21_BASE_ITERATOR_CORE_HPP__

#include "s21_base_iterator.hpp"

template <typename value_type>
inline s21::BaseNode<value_type>::BaseNode(value_type val) : value(val) {}

template <class value_type, class object_type>
inline auto s21::BaseIterator<value_type, object_type>::operator==(
    const BaseIterator<value_type, object_type>& other) const -> bool {
  return current == other.current;
}

template <class value_type, class object_type>
inline auto s21::BaseIterator<value_type, object_type>::operator!=(
    const s21::BaseIterator<value_type, object_type>& other) const -> bool {
  return current != other.current;
}

template <class value_type, class object_type>
inline auto s21::BaseIterator<value_type, object_type>::operator<=(
    const s21::BaseIterator<value_type, object_type>& other) const -> bool {
  return this->operator==(other) || this->operator<(other);
}

template <class value_type, class object_type>
inline auto s21::BaseIterator<value_type, object_type>::operator>(
    const s21::BaseIterator<value_type, object_type>& other) const -> bool {
  return !this->operator<(other);
}

template <class value_type, class object_type>
inline auto s21::BaseIterator<value_type, object_type>::operator>=(
    const s21::BaseIterator<value_type, object_type>& other) const -> bool {
  return this->operator==(other) || this->operator>(other);
}

template <class value_type, class object_type>
inline auto s21::BaseIterator<value_type, object_type>::operator*() const
    -> value_type& {
  return current->value;
}

template <class value_type, class object_type>
inline auto s21::BaseIterator<value_type, object_type>::operator++(int)
    -> s21::BaseIterator<value_type, object_type> {
  s21::BaseIterator<value_type, object_type> temp = *this;
  ++(*this);
  return temp;
}

template <class value_type, class object_type>
inline auto s21::BaseIterator<value_type, object_type>::operator--(int)
    -> s21::BaseIterator<value_type, object_type> {
  s21::BaseIterator<value_type, object_type> temp = *this;
  --(*this);
  return temp;
}

template <class value_type, class object_type>
inline auto s21::BaseIterator<value_type, object_type>::operator=(
    const s21::BaseIterator<value_type, object_type>& other)
    -> s21::BaseIterator<value_type, object_type>& {
  current = other.current;
  object = other.object;
  return *this;
}

#endif  // __S21_BASE_ITERATOR_CORE_HPP__