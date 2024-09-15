#ifndef __S21_SET_ITERATOR__
#define __S21_SET_ITERATOR__
#include "s21_set.hpp"

template <class value_type>
inline s21::set<value_type>::Iterator::Iterator() noexcept
    : current(nullptr), set(nullptr) {}

template <class value_type>
inline s21::set<value_type>::Iterator::Iterator(
    Node* node, s21::set<value_type>* set) noexcept
    : current(node), set(set) {}

template <class value_type>
inline auto s21::set<value_type>::Iterator::operator*() const -> reference {
  return current->value;
}

template <class value_type>
inline auto s21::set<value_type>::Iterator::operator=(const Iterator& other)
    -> Iterator& {
  current = other.current;
  set = other.set;
  return *this;
}

template <class value_type>
inline auto s21::set<value_type>::Iterator::operator==(
    const Iterator& other) const -> bool {
  return current == other.current;
}

template <class value_type>
inline auto s21::set<value_type>::Iterator::operator!=(
    const Iterator& other) const -> bool {
  return current != other.current;
}

template <class value_type>
inline s21::set<value_type>::Iterator::Iterator(const Iterator& other) noexcept
    : current(other.current), set(other.set) {}

template <class value_type>
inline auto s21::set<value_type>::Iterator::operator<(
    const Iterator& other) const -> bool {
  if (other == set->end()) return this->operator!=(other);
  for (auto it = set->begin(); it != set->end(); ++it) {
    if (it == current) return true;
    if (it == other) return false;
  }
  return false;
}

template <class value_type>
inline auto s21::set<value_type>::Iterator::operator<=(
    const Iterator& other) const -> bool {
  return this->operator==(other) || this->operator<(other);
}

template <class value_type>
inline auto s21::set<value_type>::Iterator::operator>(
    const Iterator& other) const -> bool {
  return !this->operator<(other);
}

template <class value_type>
inline auto s21::set<value_type>::Iterator::operator>=(
    const Iterator& other) const -> bool {
  return this->operator==(other) || this->operator>(other);
}

template <class value_type>
auto s21::set<value_type>::Iterator::operator++() -> Iterator& {
  if (current == nullptr)
    throw std::out_of_range("Disabled iterator. Not exist");
  // Если есть правое поддерево, идем к самому левому узлу
  if (current->right) {
    current = current->right;
    while (current->left) current = current->left;
  } else {
    // Поднимаемся к родителю, пока не найдем узел, который больше текущего
    Node* new_node = current->parent;
    while (new_node && current == new_node->right) {
      current = new_node;           // Поднимаемся
      new_node = new_node->parent;  // Переходим к родителю
    }
    current = new_node;  // Устанавливаем текущий узел на родителя
  }
  return *this;
}

template <class value_type>
auto s21::set<value_type>::Iterator::operator--() -> Iterator& {
  if (current == nullptr)
    throw std::out_of_range("Disabled iterator. Not exist");
  // Если есть левое поддерево, идем к самому правому узлу
  if (current->left) {
    current = current->left;
    while (current->right) current = current->right;
  } else {
    // Поднимаемся к родителю, пока не найдем узел, который меньше текущего
    Node* new_node = current->parent;
    while (new_node && current == new_node->left) {
      current = new_node;           // Поднимаемся
      new_node = new_node->parent;  // Переходим к родителю
    }
    current = new_node;  // Устанавливаем текущий узел на родителя
  }
  return *this;
}

#endif  // __S21_SET_ITERATOR__