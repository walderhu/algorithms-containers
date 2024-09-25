#ifndef __S21_LIST_CORE_HPP__
#define __S21_LIST_CORE_HPP__

#include "s21_list.hpp"
namespace s21 {

template <class value_type>
inline list<value_type>::list(const list &other) noexcept
    : deque<value_type>::deque(other) {}

template <class value_type>
inline list<value_type>::list(list &&other) noexcept
    : deque<value_type>::deque(std::move(other)) {}

template <class value_type>
list<value_type> &list<value_type>::operator=(
    list<value_type> &&other) noexcept {
  deque<value_type>::operator=(std::move(other));
  return *this;
}

template <class value_type>
list<value_type> &list<value_type>::operator=(
    const list<value_type> &other) noexcept {
  deque<value_type>::operator=(other);
  return *this;
}

template <class value_type>
inline list<value_type>::list(
    std::initializer_list<value_type> const &items) noexcept
    : deque<value_type>(items) {}

template <class value_type>
inline auto list<value_type>::operator[](const unsigned index) const
    -> reference {
  if (index >= this->_size) throw std::out_of_range("Index out of range");
  Node *current = this->head;
  for (unsigned i = 0u; i < index; ++i) current = current->next;
  return current->value;
}

template <class value_type>
inline auto list<value_type>::reverse() noexcept -> void {
  if (this->size() < 2) return;
  list<value_type> new_list;
  for (iterator it = this->begin(); it != this->end(); ++it)
    new_list.push_front(*it);
  *this = std::move(new_list);
}

template <class value_type>
inline auto list<value_type>::sort() noexcept -> void {
  Node *current = this->head;
  bool swapped = true;

  while (swapped) {
    swapped = false;
    current = this->head;

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
inline auto list<value_type>::swap(list &other) noexcept -> void {
  std::swap(this->head, other.head);
  std::swap(this->tail, other.tail);
  std::swap(this->_size, other._size);
}

template <class value_type>
inline auto list<value_type>::merge(list &other) noexcept -> void {
  Node *current = other.head;
  this->push_back(current);
  this->tail = other.tail;
  this->_size += other._size - 1u;

  other.head = nullptr;
  other.tail = nullptr;
  other._size = 0u;
}

template <class value_type>
inline auto list<value_type>::insert(
    iterator pos, const_reference value) noexcept -> iterator {
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

    this->_size++;
  }
  return new_node;
}

template <class value_type>
inline auto list<value_type>::insert(
    iterator pos,
    std::initializer_list<value_type> const &items) noexcept -> iterator {
  for (iterator item = items.end(); item != items.begin();) {
    --item;
    pos = insert(pos, *item);
  }
  return pos;
}

template <class value_type>
inline auto list<value_type>::erase(iterator pos) -> void {
  if (pos == end()) throw std::out_of_range("Cannot erase end iterator");

  Node *current = pos.current;
  Node *prev = current->prev;
  Node *next = current->next;

  if (!prev)
    this->head = next;
  else
    prev->next = next;

  if (!next)
    this->tail = prev;
  else
    next->prev = prev;

  delete current;
  this->_size -= 1u;
}

template <class value_type>
inline auto list<value_type>::splice(const_iterator pos, list &other) -> void {
  if (pos == end()) throw std::out_of_range("Cannot splice at end iterator");
  if (other.empty()) return;
  for (iterator it = other.begin(); it != other.end(); ++it) insert(pos, *it);
  other.clear();
}

template <class value_type>
inline auto list<value_type>::splice(iterator pos, list &other) -> void {
  const_iterator it(pos);
  this->splice(it, other);
}

template <class value_type>
inline auto list<value_type>::unique() noexcept -> void {
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
typename list<T>::iterator list<T>::insert_many(const_iterator pos,
                                                Args &&...args) noexcept {
  iterator var_pos = iterator(const_cast<Node *>(pos.current));
  (this->insert(var_pos, std::forward<Args>(args)), ...);
  return var_pos;
}

template <class T>
template <typename... Args>
void list<T>::insert_many_back(Args &&...args) noexcept {
  (this->push_back(std::forward<Args>(args)), ...);
}

template <class T>
template <typename... Args>
void list<T>::insert_many_front(Args &&...args) noexcept {
  (this->push_front(std::forward<Args>(args)), ...);
}

template <class value_type>
inline list<value_type>::list() noexcept : deque<value_type>::deque() {}

template <class value_type>
inline list<value_type>::list(size_type n) noexcept
    : deque<value_type>::deque(n) {}

template <class value_type>
inline list<value_type>::~list() noexcept {
  deque<value_type>::clear();
}

template <class Key>
list<Key>::operator deque<Key>() const noexcept {
  return static_cast<deque<Key>>(*this);
}

}  // namespace s21
#endif  // __S21_LIST_CORE_HPP__