#ifndef __S21_MULTISET_CORE_HPP__
#define __S21_MULTISET_CORE_HPP__

#include <iostream>

#include "s21_multiset.hpp"
template <class value_type>
inline auto s21::multiset<value_type>::insert(value_type value, Node *&current,
                                              Node *parent)
    -> std::pair<iterator, bool> {
  std::cout << "hello" << std::endl;
  if (current == nullptr) {
    current = new Node(value);
    current->parent = parent;
    s21::set<value_type>::_size++;
    return std::make_pair(Iterator(current), true);
  }
  if (value >= current->value) return insert(value, current->right, current);
  if (value < current->value) return insert(value, current->left, current);
}

#endif  // __S21_MULTISET_CORE_HPP__