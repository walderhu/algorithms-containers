#ifndef __S21_SET_CORE_HPP__
#define __S21_SET_CORE_HPP__

#include "s21_set.hpp"

namespace s21 {

template <class value_type>
set<value_type>::set(const set &s) noexcept {
  if (this == &s) return;
  this->root = nullptr;
  this->_size = 0u;
  for (auto it = s.cbegin(); it != s.cend(); ++it) this->insert(*it);
}

template <class value_type>
inline set<value_type>::set(set &&s) noexcept {
  this->root = s.root;
  this->_size = s._size;
  s.root = nullptr;
  s._size = 0u;
}

template <class value_type>
inline auto set<value_type>::operator=(set &&s) noexcept -> set<value_type> & {
  set<value_type>::set(std::move(s));
  return *this;
}

template <class value_type>
inline auto set<value_type>::operator=(const set &s) noexcept
    -> set<value_type> & {
  set<value_type> new_set(s);
  *this = std::move(new_set);
  return *this;
}

template <class value_type>
inline set<value_type>::Node::Node(value_type val) noexcept
    : left(nullptr), right(nullptr), parent(nullptr), value(val) {}

template <class value_type>
inline auto set<value_type>::empty() const noexcept -> bool {
  return this->_size == 0u;
}

template <class value_type>
inline set<value_type>::set() noexcept : root(nullptr), _size(0u) {}

template <class value_type>
inline set<value_type>::set(
    std::initializer_list<value_type> const &items) noexcept
    : set<value_type>() {
  for (auto it = items.begin(); it != items.end(); ++it) this->insert(*it);
}

template <class value_type>
inline auto set<value_type>::insert(const value_type value) noexcept
    -> std::pair<iterator, bool> {
  return insert_in(static_cast<value_type>(value), root, nullptr);
}

template <class value_type>
inline auto set<value_type>::insert_in(value_type value, Node *&current,
                                       Node *parent) noexcept
    -> std::pair<iterator, bool> {
  if (current == nullptr) {
    current = new Node(value);
    current->parent = parent;
    _size++;
    return std::make_pair(Iterator(current), true);
  }
  if (value > current->value) return insert_in(value, current->right, current);
  if (value < current->value) return insert_in(value, current->left, current);
  return std::make_pair(Iterator(current), false);
}

template <class value_type>
inline auto set<value_type>::max_size() const noexcept -> size_type {
  return (std::numeric_limits<size_t>::max() / sizeof(value_type));
}

template <class value_type>
template <typename... Args>
inline auto set<value_type>::insert_many(Args &&...args)
    -> std::vector<std::pair<iterator, bool>> {
  std::vector<std::pair<iterator, bool>> results;
  (results.emplace_back(this->insert(std::forward<Args>(args))), ...);
  return results;
}

template <class value_type>
inline auto set<value_type>::size() const noexcept -> size_type {
  return this->_size;
}

template <class Key>
inline auto set<Key>::find(const Key &key) noexcept -> iterator {
  if (root) {
    Node *current = root;
    while (current) {
      if (current->value > key) current = current->left;
      if (current->value < key) current = current->right;
      if (current->value == key) return iterator(current, this);
    }
  }
  return this->end();
}

template <class Key>
inline auto set<Key>::contains(const Key &key) noexcept -> bool {
  for (auto it = this->begin(); it != this->end(); ++it)
    if (*it == key) return true;
  return false;
}

template <class value_type>
inline set<value_type>::~set() noexcept {
  this->clear();
}

template <class value_type>
inline auto set<value_type>::clear() noexcept -> void {
  clear(root);
  _size = 0u;
}

template <class value_type>
inline auto set<value_type>::clear(Node *&current) -> void {
  if (!current) return;
  clear(current->left);
  clear(current->right);
  delete current;
  current = nullptr;
}

template <class value_type>
inline auto set<value_type>::swap(set &other) noexcept -> void {
  std::swap(this->root, other.root);
  std::swap(this->_size, other._size);
}

template <class value_type>
inline auto set<value_type>::merge(set &other) noexcept -> void {
  for (auto it = other.cbegin(); it != other.cend(); ++it) this->insert(*it);
  other.clear();
}

template <class value_type>
inline auto set<value_type>::erase(iterator pos) noexcept -> void {
  if (!pos.current) return;

  value_type value = *pos;
  root = deleteNode(root, value);
  --_size;
}

template <class value_type>
inline auto set<value_type>::deleteNode(Node *current,
                                        value_type value) -> Node * {
  if (!current) return nullptr;  // Если узел не найден

  // Рекурсивный поиск узла для удаления
  if (value < current->value) {
    current->left = deleteNode(current->left, value);
  } else if (value > current->value) {
    current->right = deleteNode(current->right, value);
  } else {
    // Узел найден
    // Случай 1: узел не имеет потомков (лист)
    if (current->left == nullptr && current->right == nullptr) {
      delete current;
      return nullptr;
    }
    // Случай 2: узел имеет одного потомка
    else if (!current->left) {
      Node *temp = current->right;
      temp->parent = current->parent;
      delete current;
      return temp;  // Возвращаем правого потомка
    } else if (!current->right) {
      Node *temp = current->left;
      temp->parent = current->parent;
      delete current;
      return temp;  // Возвращаем левого потомка
    }
    // Случай 3: узел имеет двух потомков
    Node *temp = current->right;
    while (temp && temp->left) {
      temp = temp->left;
    }
    // Находим минимальный элемент в правом поддереве
    current->value = temp->value;  // Копируем значение минимального узла

    // Удаляем минимальный узел из правого поддерева
    current->right = deleteNode(current->right, temp->value);
  }
  return current;  // Возвращаем изменённый корень
}

template <class Key>
set<Key>::operator deque<Key>() const noexcept {
  deque<Key> lst;
  for (auto it = this->begin(); it != this->end(); ++it) lst.push_back(*it);
  return lst;
}

template <class Key>
set<Key>::operator list<Key>() const noexcept {
  return this->operator deque<Key>();
}

template <class Key>
set<Key>::operator multiset<Key>() const noexcept {
  set<Key> mst;
  for (auto it = this->begin(); it != this->end(); ++it) mst.insert(*it);
  return mst;
}
}  // namespace s21
#endif  // __S21_SET_CORE_HPP__