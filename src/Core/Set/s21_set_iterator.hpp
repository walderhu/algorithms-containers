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
  return !this->operator==(other);
}

template <class value_type>
inline s21::set<value_type>::Iterator::Iterator(const Iterator& other) noexcept
    : current(other.current), set(other.set) {}

template <class value_type>
inline auto s21::set<value_type>::Iterator::operator<(
    const Iterator& other) const -> bool {
  for (auto it = set->begin(); it != set->end(); ++it) {
    if (it == current) return true;
    if (it == other) return false;
  }
  throw std::out_of_range("Disabled iterator. Not exist");
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

// hight
template <class value_type>
auto s21::set<value_type>::Iterator::operator++() -> Iterator& {
  // если nullptr  в начале, то элемента не существует
  if (current == nullptr)
    throw std::out_of_range("Disabled iterator. Not exist");

  // правый потомок всегда больше текущего
  if (current->right != nullptr) {
    current = current->right;
  } else {
    // если потомков нету, то поднимаемся к родителям в поисках большего
    Node* new_node = current->parent;
    while (new_node) {
      if (new_node->value > current->value) {
        current = new_node;
        break;
      } else
        new_node = new_node->parent;
    }

    // дошли до root и не нашли большего элемента?
    // начинаем спускаться вправо снова но уже от корня
    // если и там нету, то конец (а как же проверить левые от правого????)
    // надо тестить это что есть пока что
    if (current->right != nullptr) {
      current = current->right;
    } else {
      throw std::out_of_range("Disabled iterator. Not exist");
    }
  }
  return *this;
}

// template <class value_type>
// inline auto s21::set<value_type>::Iterator::operator--() -> Iterator& {
//   current = current ? current->prev : set->tail;
//   return *this;
// }

#endif  // __S21_SET_ITERATOR__