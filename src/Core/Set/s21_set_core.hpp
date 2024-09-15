#ifndef __S21_SET_CORE_HPP__
#define __S21_SET_CORE_HPP__

#include "s21_set.hpp"

template <class value_type>
inline s21::set<value_type>::BinaryNode::BinaryNode(value_type value)
    : Node::Node() {
  this->left = Node::prev;
  this->right = Node::next;
  this->value = Node::value;
}

template <class value_type>
inline s21::set<value_type>::set() noexcept
    : s21::deque<value_type>::deque(), root(nullptr) {}

template <class value_type>
inline auto s21::set<value_type>::insert(value_type& value) -> Iterator {
  return insert(value, root);
}

template <class value_type>
inline auto s21::set<value_type>::insert(value_type& value,
                                         BinaryNode* current) -> Iterator {
  if (current == nullptr) {
    current = new BinaryNode(value);
    s21::deque<value_type>::_size++;
    return Iterator(current);
  }
  if (value > current->value) return insert(value, current->right);
  if (value < current->value) return insert(value, current->left);
  return Iterator(current);
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