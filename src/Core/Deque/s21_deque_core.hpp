#ifndef __S21_DEQUE_CORE_HXX__
#define __S21_DEQUE_CORE_HXX__

#include "s21_deque.hpp"

template <typename value_type>
inline s21::deque<value_type>::Node::Node(value_type value)
    : value(value), next(nullptr), prev(nullptr) {}

template <class value_type>
inline auto s21::deque<value_type>::empty() -> bool {
  return this->_size == 0;
}

template <class value_type>
inline auto s21::deque<value_type>::pop_front() -> void {
  if (head) {
    Node* tmp = head;
    head = head->next;
    delete tmp;
    if (head)
      head->prev = nullptr;
    else
      tail = nullptr;

    deque<value_type>::_size -= 1;
  }
}

template <class value_type>
inline auto s21::deque<value_type>::pop_back() -> void {
  if (head) {
    Node* tmp = tail;

    if (tail == head) {
      head = nullptr;
      tail = nullptr;
    } else {
      tail = tail->prev;
      tail->next = nullptr;
    }

    delete tmp;
    deque<value_type>::_size--;
  }
}

template <class value_type>
inline s21::deque<value_type>::deque() noexcept
    : head(nullptr), tail(nullptr), _size(0) {}

template <class value_type>
inline s21::deque<value_type>::deque(size_type n) noexcept
    : s21::deque<value_type>() {
  for (size_t i = 0; i < n; i++) push_front(value_type());
}

template <class value_type>
inline s21::deque<value_type>::~deque() noexcept {
  clear();
}

template <class value_type>
inline auto s21::deque<value_type>::clear() -> void {
  while (deque<value_type>::_size) s21::deque<value_type>::pop_front();
  s21::deque<value_type>::tail = nullptr;
}

template <class value_type>
inline s21::deque<value_type>::deque(const deque& other) noexcept {
  s21::deque<value_type>::head = nullptr;
  s21::deque<value_type>::tail = nullptr;

  deque<value_type>::_size = 0;
  if (this != &other) {
    Node* current = other.head;
    while (current) {
      push_back(current->value);
      current = current->next;
    }
  }
}

template <class value_type>
inline s21::deque<value_type>::deque(deque&& other) noexcept {
  s21::deque<value_type>::head = other.head;
  s21::deque<value_type>::tail = other.tail;

  deque<value_type>::_size = other._size;
  other.head = nullptr;
  other.tail = nullptr;
  other.deque<value_type>::_size = 0;
}

template <class value_type>
inline auto s21::deque<value_type>::push_front(value_type value) -> void {
  Node* new_node = new Node(value);
  this->push_front(new_node);
}

template <class value_type>
inline auto s21::deque<value_type>::push_front(Node* new_node) -> void {
  if (!s21::deque<value_type>::head) {
    s21::deque<value_type>::head = new_node;
    s21::deque<value_type>::tail = new_node;
  } else {
    new_node->next = s21::deque<value_type>::head;
    s21::deque<value_type>::head->prev = new_node;
    s21::deque<value_type>::head = new_node;
  }
  deque<value_type>::_size++;
}

template <class value_type>
inline auto s21::deque<value_type>::push_back(value_type value) -> void {
  Node* new_node = new Node(value);
  this->push_back(new_node);
}

template <class value_type>
inline auto s21::deque<value_type>::push_back(Node* new_node) -> void {
  if (!s21::deque<value_type>::head) {
    s21::deque<value_type>::head = new_node;
    s21::deque<value_type>::tail = new_node;
  } else {
    new_node->prev = s21::deque<value_type>::tail;
    s21::deque<value_type>::tail->next = new_node;
    s21::deque<value_type>::tail = new_node;
  }
  deque<value_type>::_size++;
}

template <class value_type>
inline auto s21::deque<value_type>::size() const -> size_type {
  return deque<value_type>::_size;
}

template <class value_type>
inline auto s21::deque<value_type>::front() -> const_reference {
  if (s21::deque<value_type>::head == nullptr)
    throw std::out_of_range("deque is empty");
  return s21::deque<value_type>::head->value;
}

template <class value_type>
inline auto s21::deque<value_type>::back() -> const_reference {
  if (s21::deque<value_type>::tail == nullptr)
    throw std::out_of_range("deque is empty");
  return s21::deque<value_type>::tail->value;
}

template <class value_type>
inline auto s21::deque<value_type>::max_size() -> size_type {
  return (std::numeric_limits<size_t>::max() / sizeof(value_type)) / 2;
}

template <class value_type>
inline s21::deque<value_type>::deque(
    std::initializer_list<value_type> const& items) noexcept
    : s21::deque<value_type>() {
  for (auto it = items.begin(); it != items.end(); ++it) this->push_back(*it);
}

template <class value_type>
inline auto s21::deque<value_type>::operator=(deque&& other) noexcept
    -> s21::deque<value_type>& {
  this->clear();

  s21::deque<value_type>::head = other.head;
  s21::deque<value_type>::tail = other.tail;
  this->deque<value_type>::_size = other.deque<value_type>::_size;

  other.head = nullptr;
  other.tail = nullptr;
  other.deque<value_type>::_size = 0;
  return *this;
}

template <class value_type>
inline auto s21::deque<value_type>::operator=(const deque& other) noexcept
    -> s21::deque<value_type>& {
  s21::deque<value_type> new_deque(other);
  *this = std::move(new_deque);
  return *this;
}

#endif  // __S21_DEQUE_CORE_HXX__