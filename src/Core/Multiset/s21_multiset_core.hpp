#ifndef __S21_MULTISET_CORE_HPP__
#define __S21_MULTISET_CORE_HPP__

#include <iostream>

#include "s21_multiset.hpp"

template <class value_type>
inline s21::multiset<value_type>::multiset() noexcept
    : set<value_type>::set(){};

template <class value_type>
inline s21::multiset<value_type>::multiset(
    std::initializer_list<value_type> const &items) noexcept {
  for (auto it = items.begin(); it != items.end(); ++it) insert(*it);
}

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
  if (this != &s) {
    s21::multiset<value_type>::clear();
    this->root = std::move(s.root);
    this->_size = std::move(s._size);
    s.root = nullptr;
    s._size = 0;
  }
  return *this;
}

template <class value_type>
inline auto s21::multiset<value_type>::operator=(const multiset &s) noexcept
    -> multiset<value_type> & {
  return set<value_type>::operator=(s);
}

template <class value_type>
inline auto s21::multiset<value_type>::insert(const value_type &value)
    -> std::pair<iterator, bool> {
  return s21::set<value_type>::insert(value);
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

template <class Key>
inline auto s21::multiset<Key>::count(const Key &key) const -> size_type {
  size_type _count = 0;
  for (auto it = s21::set<Key>::cbegin(); it != s21::set<Key>::cend();
       ++it, _count++);
  return _count;
}

#endif  // __S21_MULTISET_CORE_HPP__