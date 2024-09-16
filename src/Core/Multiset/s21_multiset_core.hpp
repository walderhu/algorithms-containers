#ifndef __S21_MULTISET_CORE_HPP__
#define __S21_MULTISET_CORE_HPP__

#include <iostream>

#include "s21_multiset.hpp"

template <class value_type>
inline s21::multiset<value_type>::multiset() noexcept
    : set<value_type>::set(){};

template <class value_type>
inline s21::multiset<value_type>::multiset(
    std::initializer_list<value_type> const &items) noexcept
    : set<value_type>::set(items) {}

template <class value_type>
inline s21::multiset<value_type>::multiset(const multiset &s)
    : set<value_type>::set(s) {}

template <class value_type>
inline s21::multiset<value_type>::multiset(multiset &&s)
    : set<value_type>::set(std::move(s)) {}

template <class value_type>
inline s21::multiset<value_type>::~multiset() noexcept {
  set<value_type>::clear();
}

template <class value_type>
inline auto s21::multiset<value_type>::operator=(multiset &&s) noexcept
    -> multiset<value_type> & {
  return set<value_type>::operator=(std::move(s));
}

template <class value_type>
inline auto s21::multiset<value_type>::operator=(const multiset &s) noexcept
    -> multiset<value_type> & {
  return set<value_type>::operator=(s);
}

template <class value_type>
inline auto s21::multiset<value_type>::insert(value_type value, Node *&current,
                                              Node *parent)
    -> std::pair<iterator, bool> {
  if (current == nullptr) {
    current = new Node(value);
    current->parent = parent;
    s21::set<value_type>::_size++;
    return std::make_pair(iterator(current), true);
  }
  if (value >= current->value) return insert(value, current->right, current);
  if (value < current->value) return insert(value, current->left, current);
  return std::make_pair(iterator(current), false);
}

#endif  // __S21_MULTISET_CORE_HPP__