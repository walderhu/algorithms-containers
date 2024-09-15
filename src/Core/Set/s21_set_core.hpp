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
inline s21::set<value_type>::set(
    std::initializer_list<value_type> const &items) noexcept
    : s21::set<value_type>() {
  for (auto it = items.begin(); it != items.end(); ++it) this->insert(*it);
}

template <class value_type>
inline auto s21::set<value_type>::insert(value_type value)
    -> std::pair<iterator, bool> {
  return insert(value, root);
}

template <class value_type>
inline auto s21::set<value_type>::insert(value_type value, Node *&current)
    -> std::pair<iterator, bool> {
  if (current == nullptr) {
    current = new Node(value);
    _size++;
    return std::make_pair(Iterator(current), true);
  }
  if (value > current->value) return insert(value, current->right);
  if (value < current->value) return insert(value, current->left);
  return std::make_pair(Iterator(current), false);
}

template <class value_type>
template <typename... Args>
inline auto s21::set<value_type>::insert_many(Args &&...args)
    -> std::vector<std::pair<iterator, bool>> {
  std::vector<std::pair<iterator, bool>> results;
  (results.emplace_back(this->insert(std::forward<Args>(args))), ...);
  return results;
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

template <class value_type>
inline auto s21::set<value_type>::clear() -> void {
  this->clear(root);
}

template <class value_type>
inline s21::set<value_type>::~set() noexcept {
  this->clear();
}

template <class value_type>
inline auto s21::set<value_type>::clear(Node *&current) -> void {
  if (!current) return;
  clear(current->left);
  clear(current->right);
  delete current;
  current = nullptr;
}

#endif  // __S21_SET_CORE_HPP__