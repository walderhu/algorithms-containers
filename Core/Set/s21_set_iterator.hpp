#ifndef __S21_SET_ITERATOR__
#define __S21_SET_ITERATOR__
#include "s21_set.hpp"

namespace s21 {

template <class value_type>
inline set<value_type>::Iterator::Iterator() noexcept
    : current(nullptr), set(nullptr) {}

template <class value_type>
inline set<value_type>::Iterator::Iterator(Node* node,
                                           s21::set<value_type>* st) noexcept
    : current(node), set(st) {}

template <class value_type>
inline auto set<value_type>::Iterator::operator*() const -> reference {
  return current->value;
}

template <class value_type>
inline auto set<value_type>::Iterator::operator=(const Iterator& other)
    -> Iterator& {
  current = other.current;
  set = other.set;
  return *this;
}

template <class value_type>
inline auto set<value_type>::Iterator::operator==(
    const Iterator& other) const noexcept -> bool {
  return current == other.current;
}

template <class value_type>
inline auto set<value_type>::Iterator::operator!=(
    const Iterator& other) const noexcept -> bool {
  return current != other.current;
}

template <class value_type>
inline set<value_type>::Iterator::Iterator(const Iterator& other) noexcept
    : current(other.current), set(other.set) {}

template <class value_type>
inline auto set<value_type>::Iterator::operator<(
    const Iterator& other) const noexcept -> bool {
  if (other == set->end()) return this->operator!=(other);
  for (auto it = set->begin(); it != set->end(); ++it) {
    if (it == current) return true;
    if (it == other) return false;
  }
  return false;
}

template <class value_type>
inline auto set<value_type>::Iterator::operator<=(
    const Iterator& other) const noexcept -> bool {
  return this->operator==(other) || this->operator<(other);
}

template <class value_type>
inline auto set<value_type>::Iterator::operator>(
    const Iterator& other) const noexcept -> bool {
  return !this->operator<(other);
}

template <class value_type>
inline auto set<value_type>::Iterator::operator>=(
    const Iterator& other) const noexcept -> bool {
  return this->operator==(other) || this->operator>(other);
}

template <class value_type>
inline auto set<value_type>::Iterator::last() -> Iterator {
  if (!set->root) return set->end();
  Node* cur = set->root;
  while (cur->right) cur = cur->right;
  return Iterator(cur);
}

template <class value_type>
auto set<value_type>::Iterator::operator++() -> Iterator& {
  if (!current) throw std::out_of_range("Disabled iterator. Not exist");
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
auto set<value_type>::Iterator::operator--() -> Iterator& {
  if (*this == set->end()) {
    if (set->empty())
      throw std::out_of_range(
          "Attempt to decrement end iterator of empty container");
    *this = this->last();
    return *this;
  }

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

template <class value_type>
auto set<value_type>::Iterator::operator++(int) -> Iterator {
  Iterator temp = *this;
  ++(*this);
  return temp;
}

template <class value_type>
auto set<value_type>::Iterator::operator--(int) -> Iterator {
  Iterator temp = *this;
  --(*this);
  return temp;
}

// const_iterator

template <class value_type>
inline auto set<value_type>::ConstIterator::operator*() const
    -> const_reference {
  return static_cast<const_reference>(Iterator::operator*());
}

template <class value_type>
inline set<value_type>::ConstIterator::ConstIterator(
    Node* node, const set<value_type>* set_) noexcept
    : Iterator(node, const_cast<set<value_type>*>(set_)) {}

template <class value_type>
inline set<value_type>::ConstIterator::ConstIterator(iterator it) noexcept {
  Iterator::current = it.current;
  Iterator::set = it.set;
}

template <class value_type>
inline auto set<value_type>::ConstIterator::operator=(const Iterator& other)
    -> Iterator& {
  (void)other;
  throw std::out_of_range("Cannot modify value through const_iterator");
  return *this;
}

template <class value_type>
inline auto set<value_type>::Iterator::get_value() const -> value_type {
  if (!current) return value_type();
  return this->operator*();
}

// begin/end cbegin/ceng

template <class value_type>
inline auto set<value_type>::begin() noexcept -> Iterator {
  if (!root) return Iterator(nullptr, this);
  Node* smallest_member = root;
  while (smallest_member->left) smallest_member = smallest_member->left;
  return Iterator(smallest_member, this);
}

template <class value_type>
inline auto set<value_type>::end() noexcept -> Iterator {
  return Iterator(nullptr, this);
}

template <class value_type>
inline auto set<value_type>::cbegin() const noexcept -> ConstIterator {
  if (!root) return ConstIterator(nullptr, this);
  Node* smallest_member = root;
  while (smallest_member->left) smallest_member = smallest_member->left;
  return ConstIterator(smallest_member, this);
}

template <class value_type>
inline auto set<value_type>::cend() const noexcept -> ConstIterator {
  return ConstIterator(nullptr, this);
};
}  // namespace s21
#endif  // __S21_SET_ITERATOR__
