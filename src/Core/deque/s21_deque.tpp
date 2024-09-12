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
