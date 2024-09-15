#ifndef S21_LIST_ITERATOR_HPP
#define S21_LIST_ITERATOR_HPP

#include "s21_list.hpp"

template <class value_type>
inline s21::list<value_type>::Iterator::Iterator(
    Node* node, s21::list<value_type>* list) noexcept
    : current(node), list(list) {}

template <class value_type>
inline s21::list<value_type>::Iterator::Iterator() noexcept
    : current(nullptr), list(nullptr) {}

template <class value_type>
inline s21::list<value_type>::Iterator::Iterator(const Iterator& other) noexcept
    : current(other.current), list(other.list) {}

template <class value_type>
inline auto s21::list<value_type>::Iterator::operator==(
    const Iterator& other) const -> bool {
  return current == other.current;
}

template <class value_type>
inline auto s21::list<value_type>::Iterator::operator!=(
    const Iterator& other) const -> bool {
  return !(*this == other);
}

template <class value_type>
inline auto s21::list<value_type>::Iterator::operator<(
    const Iterator& other) const -> bool {
  for (auto it = list->begin(); it != list->end(); ++it) {
    if (it == current) return true;
    if (it == other) return false;
  }
  throw std::out_of_range("Disabled iterator. Not exist");
}

template <class value_type>
inline auto s21::list<value_type>::Iterator::operator<=(
    const Iterator& other) const -> bool {
  return this->operator==(other) || this->operator<(other);
}

template <class value_type>
inline auto s21::list<value_type>::Iterator::operator>(
    const Iterator& other) const -> bool {
  return !this->operator<(other);
}

template <class value_type>
inline auto s21::list<value_type>::Iterator::operator>=(
    const Iterator& other) const -> bool {
  return this->operator==(other) || this->operator>(other);
}

template <class value_type>
inline auto s21::list<value_type>::Iterator::operator*() const -> reference {
  return current->value;
}

template <class value_type>
inline auto s21::list<value_type>::ConstIterator::operator*() const
    -> const_reference {
  return static_cast<const_reference>(Iterator::operator*());
}

template <class value_type>
inline s21::list<value_type>::ConstIterator::ConstIterator(
    Node* node, const s21::list<value_type>* lst) noexcept
    : Iterator(node, const_cast<s21::list<value_type>*>(lst)) {}

template <class value_type>
inline s21::list<value_type>::ConstIterator::ConstIterator(
    iterator it) noexcept {
  Iterator::current = it.current;
  Iterator::list = it.list;
}

template <class value_type>
inline auto s21::list<value_type>::ConstIterator::operator=(
    const Iterator& other) -> Iterator& {
  (void)other;
  throw std::out_of_range("Cannot modify value through const_iterator");
  return *this;
}

template <class value_type>
auto s21::list<value_type>::Iterator::operator++() -> Iterator& {
  if (current) current = current->next;
  return *this;
}

template <class value_type>
inline auto s21::list<value_type>::Iterator::operator--() -> Iterator& {
  current = current ? current->prev : list->tail;
  return *this;
}

template <class value_type>
inline auto s21::list<value_type>::Iterator::operator=(const Iterator& other)
    -> Iterator& {
  current = other.current;
  list = other.list;
  return *this;
}

// begin/end cbegin/cend

template <class value_type>
inline auto s21::list<value_type>::begin() noexcept -> Iterator {
  return Iterator(s21::deque<value_type>::head, this);
}

template <class value_type>
inline auto s21::list<value_type>::end() noexcept -> Iterator {
  return Iterator(nullptr, this);
}

template <class value_type>
inline auto s21::list<value_type>::cbegin() const -> ConstIterator {
  return ConstIterator(s21::deque<value_type>::head, this);
}

template <class value_type>
inline auto s21::list<value_type>::cend() const -> ConstIterator {
  return ConstIterator(nullptr, this);
}

#endif  // S21_LIST_ITERATOR_HPP