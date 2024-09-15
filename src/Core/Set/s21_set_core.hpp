#ifndef __S21_SET_CORE_HPP__
#define __S21_SET_CORE_HPP__

#include "s21_set.hpp"

template <class value_type>
inline s21::set<value_type>::Node::Node(value_type value) {
  this->left = nullptr;
  this->right = nullptr;
  this->value = value;
}

template <class value_type>
inline auto s21::set<value_type>::empty() const -> bool {
  return this->_size == 0;
}

template <class value_type>
inline s21::set<value_type>::set() noexcept : root(nullptr), _size(0) {}

template <class value_type>
inline auto s21::set<value_type>::insert(value_type value) -> Iterator {
  return insert(value, root);
}

template <class value_type>
inline auto s21::set<value_type>::insert(value_type value,
                                         Node*& current) -> Iterator {
  if (current == nullptr) {
    current = new Node(value);
    _size++;
    return Iterator(current);
  }
  if (value > current->value) return insert(value, current->right);
  if (value < current->value) return insert(value, current->left);
  return Iterator(current);
}

template <class value_type>
inline auto s21::set<value_type>::size() const -> size_type {
  return this->_size;
}

template <class value_type>
inline auto s21::set<value_type>::begin() -> Iterator {
  return Iterator(s21::set<value_type>::root, this);
}

template <class value_type>
inline auto s21::set<value_type>::end() -> Iterator {
  return Iterator(nullptr, this);
}

template <class value_type>
inline auto s21::set<value_type>::push_left(value_type value) -> void {}

template <class value_type>
inline auto s21::set<value_type>::push_right(value_type value) -> void {}

#endif  // __S21_SET_CORE_HPP__