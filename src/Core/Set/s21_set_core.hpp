#ifndef __S21_SET_CORE_HPP__
#define __S21_SET_CORE_HPP__

#include "s21_set.hpp"

template <class value_type>
inline s21::set<value_type>::set(const set &s) {
  for (auto it = s.cbegin(); it < s.cend(); ++it) this->insert(*it);
}

template <class value_type>
inline s21::set<value_type>::set(set &&s) {
  this->clear();
  this->root = s.root;
  this->_size = s._size;

  s.root = nullptr;
  s._size = 0;
}

template <class value_type>
inline auto s21::set<value_type>::operator=(set &&s) noexcept
    -> s21::set<value_type> & {
  s21::set<value_type>::set(std::move(s));
  return *this;
}

template <class value_type>
inline auto s21::set<value_type>::operator=(const set &s) noexcept
    -> s21::set<value_type> & {
  s21::set<value_type> new_set(s);
  *this = std::move(new_set);
  return *this;
}

//
template <class value_type>
inline s21::set<value_type>::Node::Node(value_type value)
    : left(nullptr), right(nullptr), parent(nullptr), value(value) {}

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
  return insert(value, root, nullptr);
}

template <class value_type>
inline auto s21::set<value_type>::insert(value_type value, Node *&current,
                                         Node *parent)
    -> std::pair<iterator, bool> {
  if (current == nullptr) {
    current = new Node(value);
    current->parent = parent;
    _size++;
    return std::make_pair(Iterator(current), true);
  }
  if (value > current->value) return insert(value, current->right, current);
  if (value < current->value) return insert(value, current->left, current);
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
inline auto s21::set<value_type>::push_left(value_type value) -> void {}

template <class value_type>
inline auto s21::set<value_type>::push_right(value_type value) -> void {}

template <class value_type>
inline auto s21::set<value_type>::clear() -> void {
  this->clear(root);
}

template <class Key>
inline auto s21::set<Key>::find(const Key &key) -> iterator {
  auto it = this->begin();
  for (; it != this->end(); ++it)
    if (*it == key) break;
  return it;
}

template <class Key>
inline auto s21::set<Key>::contains(const Key &key) -> bool {
  return (this->find(key) == this->end());
}

template <class value_type>
inline s21::set<value_type>::~set() noexcept {
  this->clear();
}

template <class value_type>
inline auto s21::set<value_type>::clear(Node *&current) -> void {
  if (!current) {
    _size = 0;
    return;
  }
  clear(current->left);
  clear(current->right);
  delete current;
  current = nullptr;
}

#endif  // __S21_SET_CORE_HPP__