#ifndef __S21_SET_CORE_HPP__
#define __S21_SET_CORE_HPP__

#include "s21_set.hpp"

template <class value_type>
s21::set<value_type>::set(const set &s) {
  if (this == &s) return;
  this->root = nullptr;
  this->_size = 0;
  for (auto it = s.cbegin(); it != s.cend(); ++it) this->insert(*it);
}

template <class value_type>
inline s21::set<value_type>::set(set &&s) {
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

template <class value_type>
inline s21::set<value_type>::Node::Node(value_type value)
    : left(nullptr), right(nullptr), parent(nullptr), value(value) {}

template <class Key>
inline s21::set<Key>::Node::Node(const Node &other) noexcept
    : left(other.left),
      right(other.right),
      parent(other.parent),
      value(other.value) {}

template <class Key>
inline s21::set<Key>::Node::Node(Node &&other) {
  if (this != &other) {
    s21::set<Key>::Node new_node(other);
    other.left = nullptr;
    other.right = nullptr;
    other.parent = nullptr;
    other.value = Key();
  }
}

template <class Key>
inline auto s21::set<Key>::Node::operator=(const Node &other) noexcept
    -> Node & {
  s21::set<Key>::Node new_node(other);
  *this = std::move(new_node);
  return *this;
}

template <class Key>
inline auto s21::set<Key>::Node::operator=(set &&other) noexcept -> Node & {
  s21::set<Key>::Node(std::move(other));
  return *this;
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
inline auto s21::set<value_type>::insert(const value_type value)
    -> std::pair<iterator, bool> {
  return insert(static_cast<value_type>(value), root, nullptr);
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
inline auto s21::set<value_type>::max_size() -> size_type {
  return (std::numeric_limits<size_t>::max() / sizeof(value_type));
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

template <class Key>
inline auto s21::set<Key>::find(const Key &key) -> iterator {
  if (root != nullptr) {
    Node *current = root;
    while (current) {
      if (current->value > key) current = current->left;
      if (current->value < key) current = current->right;
      if (current->value == key) return iterator(current, this);
    }
  }
  return this->end();
}

// template <class Key>
// inline auto s21::set<Key>::find(const Key &key) -> iterator {
//   iterator it;
//   for (it = this->begin(); it != this->end(); ++it)
//     if (*it == key) break;
//   return it;
// }

template <class Key>
inline auto s21::set<Key>::contains(const Key &key) -> bool {
  for (auto it = this->begin(); it != this->end(); ++it)
    if (*it == key) return true;
  return false;
}

template <class value_type>
inline s21::set<value_type>::~set() noexcept {
  this->clear();
}

template <class value_type>
inline auto s21::set<value_type>::clear() -> void {
  clear(root);
  _size = 0;
}

template <class value_type>
inline auto s21::set<value_type>::clear(Node *&current) -> void {
  if (!current) return;
  clear(current->left);
  clear(current->right);
  delete current;
  current = nullptr;
}

template <class value_type>
inline auto s21::set<value_type>::swap(set &other) -> void {
  std::swap(this->root, other.root);
  std::swap(this->_size, other._size);
}

template <class value_type>
inline auto s21::set<value_type>::merge(set &other) -> void {
  for (auto it = other.cbegin(); it != other.cend(); ++it) this->insert(*it);
  other.clear();
}

template <class value_type>
inline auto s21::set<value_type>::erase(iterator pos) -> void {
  if (pos.current == nullptr) return;

  value_type value = *pos;
  root = deleteNode(root, value);
  --_size;
}

template <class value_type>
inline auto s21::set<value_type>::deleteNode(Node *current,
                                             value_type value) -> Node * {
  if (current == nullptr)
    return nullptr;  // Если узел не найден, возвращаем nullptr

  // Рекурсивный поиск узла для удаления
  if (value < current->value) {
    current->left = deleteNode(current->left, value);
  } else if (value > current->value) {
    current->right = deleteNode(current->right, value);
  } else {
    // Узел найден
    // Случай 1: узел не имеет потомков (лист)
    if (current->left == nullptr && current->right == nullptr) {
      delete current;  // Удаляем узел
      return nullptr;  // Возвращаем nullptr
    }
    // Случай 2: узел имеет одного потомка
    else if (current->left == nullptr) {
      Node *temp = current->right;  // Сохраняем указатель на правого потомка
      temp->parent = current->parent;  // ???
      delete current;                  // Удаляем узел
      return temp;  // Возвращаем правого потомка
    } else if (current->right == nullptr) {
      Node *temp = current->left;  // Сохраняем указатель на левого потомка
      temp->parent = current->parent;  // ???
      delete current;                  // Удаляем узел
      return temp;  // Возвращаем левого потомка
    }
    // Случай 3: узел имеет двух потомков
    Node *temp = current->right;
    while (temp && temp->left != nullptr) {
      temp = temp->left;
    }
    // Находим минимальный элемент в правом поддереве
    current->value = temp->value;  // Копируем значение минимального узла

    // Удаляем минимальный узел из правого поддерева
    current->right = deleteNode(current->right, temp->value);
  }
  return current;  // Возвращаем изменённый корень
}

#endif  // __S21_SET_CORE_HPP__