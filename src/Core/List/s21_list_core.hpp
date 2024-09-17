#ifndef __S21_LIST_CORE_HPP__
#define __S21_LIST_CORE_HPP__

#include "s21_list.hpp"

template <class value_type>
inline s21::list<value_type>::list(const list &other) noexcept
    : s21::deque<value_type>::deque(other) {}

template <class value_type>
inline s21::list<value_type>::list(list &&other) noexcept
    : s21::deque<value_type>::deque(std::move(other)) {}

template <class value_type>
s21::list<value_type> &s21::list<value_type>::operator=(
    s21::list<value_type> &&other) noexcept {
  s21::deque<value_type>::operator=(std::move(other));
  return *this;
}

template <class value_type>
s21::list<value_type> &s21::list<value_type>::operator=(
    const s21::list<value_type> &other) noexcept {
  s21::deque<value_type>::operator=(other);
  return *this;
}

template <class value_type>
inline s21::list<value_type>::list(
    std::initializer_list<value_type> const &items) noexcept
    : s21::deque<value_type>(items) {}

template <class value_type>
inline auto s21::list<value_type>::operator[](const int index) const
    -> reference {
  if (index < 0 || index >= deque<value_type>::_size)
    throw std::out_of_range("Index out of range");
  Node *current = s21::deque<value_type>::head;
  for (int i = 0; i < index; ++i) current = current->next;
  return current->value;
}

template <class value_type>
inline auto s21::list<value_type>::reverse() -> void {
  if (this->size() < 2) return;
  list<value_type> new_list;
  for (auto it = this->begin(); it != this->end(); ++it)
    new_list.push_front(*it);
  *this = std::move(new_list);
}

template <class value_type>
inline auto s21::list<value_type>::sort() -> void {
  Node *current = s21::deque<value_type>::head;
  bool swapped = true;

  while (swapped) {
    swapped = false;
    current = s21::deque<value_type>::head;

    while (current && current->next) {
      Node *next_node = current->next;
      if (current->value > next_node->value) {
        std::swap(current->value, next_node->value);
        swapped = true;
      }
      current = current->next;
    }
  }
}

template <class value_type>
inline auto s21::list<value_type>::swap(list &other) noexcept -> void {
  std::swap(s21::deque<value_type>::head, other.head);
  std::swap(s21::deque<value_type>::tail, other.tail);
  std::swap(s21::deque<value_type>::_size, other._size);
}

template <class value_type>
inline auto s21::list<value_type>::merge(list &other) -> void {
  Node *current = other.head;
  this->push_back(current);
  s21::deque<value_type>::tail = other.tail;
  this->deque<value_type>::_size += other.deque<value_type>::_size - 1;

  other.head = nullptr;
  other.tail = nullptr;
  other.deque<value_type>::_size = 0;
}

template <class value_type>
inline auto s21::list<value_type>::insert(iterator pos,
                                          const_reference value) -> iterator {
  Node *new_node = new Node(value);

  if (pos == this->begin()) {
    this->push_front(new_node);
  } else if (pos == this->end()) {
    this->push_back(new_node);
  } else {
    Node *current = pos.current;
    Node *previous = current->prev;

    new_node->next = current;
    new_node->prev = previous;

    if (previous) previous->next = new_node;
    if (current) current->prev = new_node;

    this->deque<value_type>::_size++;
  }
  return new_node;
}

template <class value_type>
inline auto s21::list<value_type>::insert(
    iterator pos, std::initializer_list<value_type> const &items) -> iterator {
  for (auto item = items.end(); item != items.begin();) {
    --item;
    pos = insert(pos, *item);
  }
  return pos;
}

template <class value_type>
inline auto s21::list<value_type>::erase(iterator pos) -> void {
  if (pos == end()) throw std::out_of_range("Cannot erase end iterator");

  Node *current = pos.current;
  Node *prev = current->prev;
  Node *next = current->next;

  if (prev == nullptr)
    s21::deque<value_type>::head = next;
  else
    prev->next = next;

  if (next == nullptr)
    s21::deque<value_type>::tail = prev;
  else
    next->prev = prev;

  delete current;
  deque<value_type>::_size -= 1;
}

template <class value_type>
inline auto s21::list<value_type>::splice(const_iterator pos,
                                          list &other) -> void {
  if (pos == end()) throw std::out_of_range("Cannot splice at end iterator");
  if (other.empty()) return;
  auto other_begin = other.begin();
  auto other_end = other.end();

  for (auto it = other_begin; it != other_end; ++it) insert(pos, *it);
  other.clear();
}

template <class value_type>
inline auto s21::list<value_type>::splice(iterator pos, list &other) -> void {
  const_iterator it(pos);
  this->splice(it, other);
}

template <class value_type>
inline auto s21::list<value_type>::unique() -> void {
  if (this->empty()) return;

  for (iterator it = this->begin(); it != this->end();) {
    Node *current = it.current;

    if (current->next && current->value == current->next->value) {
      Node *next = current->next;
      this->erase(it);
      it = iterator(next);
    } else {
      ++it;
    }
  }
}

template <class T>
template <typename... Args>
typename s21::list<T>::iterator s21::list<T>::insert_many(const_iterator pos,
                                                          Args &&...args) {
  iterator var_pos = iterator(const_cast<Node *>(pos.current));
  (this->insert(var_pos, std::forward<Args>(args)), ...);
  return var_pos;
}

template <class T>
template <typename... Args>
void s21::list<T>::insert_many_back(Args &&...args) {
  (this->push_back(std::forward<Args>(args)), ...);
}

template <class T>
template <typename... Args>
void s21::list<T>::insert_many_front(Args &&...args) {
  (this->push_front(std::forward<Args>(args)), ...);
}

template <class value_type>
inline s21::list<value_type>::list() noexcept
    : s21::deque<value_type>::deque() {}

template <class value_type>
inline s21::list<value_type>::list(size_type n) noexcept
    : s21::deque<value_type>::deque(n) {}

template <class value_type>
inline s21::list<value_type>::~list() noexcept {
  s21::deque<value_type>::clear();
}

#endif  // __S21_LIST_CORE_HPP__