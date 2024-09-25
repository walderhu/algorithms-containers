#ifndef __S21_DEQUE_CORE_HXX__
#define __S21_DEQUE_CORE_HXX__

#include "s21_deque.hpp"
namespace s21 {

template <typename value_type>
inline deque<value_type>::Node::Node(value_type val) noexcept
    : value(val), next(nullptr), prev(nullptr) {}

template <class value_type>
inline auto deque<value_type>::empty() const noexcept -> bool {
  return this->_size == 0u;
}

template <class value_type>
inline auto deque<value_type>::pop_front() noexcept -> void {
  if (head) {
    Node* tmp = head;
    head = head->next;
    delete tmp;
    if (head)
      head->prev = nullptr;
    else
      tail = nullptr;

    _size -= 1u;
  }
}

template <class value_type>
inline auto deque<value_type>::pop_back() noexcept -> void {
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
    _size--;
  }
}

template <class value_type>
inline deque<value_type>::deque() noexcept
    : head(nullptr), tail(nullptr), _size(0u) {}

template <class value_type>
inline deque<value_type>::deque(size_type n) noexcept : deque<value_type>() {
  for (size_t i = 0u; i < n; i++) push_front(value_type());
}

template <class value_type>
inline deque<value_type>::~deque() noexcept {
  clear();
}

template <class value_type>
inline auto deque<value_type>::clear() noexcept -> void {
  while (_size) deque<value_type>::pop_front();
  tail = nullptr;
}

template <class value_type>
inline deque<value_type>::deque(const deque& other) noexcept {
  head = nullptr;
  tail = nullptr;

  _size = 0u;
  if (this != &other) {
    Node* current = other.head;
    while (current) {
      push_back(current->value);
      current = current->next;
    }
  }
}

template <class value_type>
inline deque<value_type>::deque(deque&& other) noexcept {
  head = other.head;
  tail = other.tail;

  _size = other._size;
  other.head = nullptr;
  other.tail = nullptr;
  other._size = 0u;
}

template <class value_type>
inline auto deque<value_type>::push_front(value_type value) -> void {
  Node* new_node = new Node(value);
  this->push_front(new_node);
}

template <class value_type>
inline auto deque<value_type>::push_front(Node* new_node) noexcept -> void {
  if (!head) {
    head = new_node;
    tail = new_node;
  } else {
    new_node->next = head;
    head->prev = new_node;
    head = new_node;
  }
  _size++;
}

template <class value_type>
inline auto deque<value_type>::push_back(value_type value) -> void {
  Node* new_node = new Node(value);
  this->push_back(new_node);
}

template <class value_type>
inline auto deque<value_type>::push_back(Node* new_node) noexcept -> void {
  if (!head) {
    head = new_node;
    tail = new_node;
  } else {
    new_node->prev = tail;
    tail->next = new_node;
    tail = new_node;
  }
  _size++;
}

template <class value_type>
inline auto deque<value_type>::size() const -> size_type {
  return _size;
}

template <class value_type>
inline auto deque<value_type>::front() const -> const_reference {
  if (head == nullptr) throw std::out_of_range("deque is empty");
  return head->value;
}

template <class value_type>
inline auto deque<value_type>::back() const -> const_reference {
  if (tail == nullptr) throw std::out_of_range("deque is empty");
  return tail->value;
}

template <class value_type>
inline auto deque<value_type>::max_size() const noexcept -> size_type {
  return (std::numeric_limits<size_t>::max() / sizeof(value_type)) / 2;
}

template <class value_type>
inline deque<value_type>::deque(
    std::initializer_list<value_type> const& items) noexcept
    : deque<value_type>() {
  for (auto it = items.begin(); it != items.end(); ++it) this->push_back(*it);
}

template <class value_type>
inline auto deque<value_type>::operator=(deque&& other) noexcept
    -> deque<value_type>& {
  this->clear();

  head = other.head;
  tail = other.tail;
  this->_size = other._size;

  other.head = nullptr;
  other.tail = nullptr;
  other._size = 0u;
  return *this;
}

template <class value_type>
inline auto deque<value_type>::operator=(const deque& other) noexcept
    -> deque<value_type>& {
  deque<value_type> new_deque(other);
  *this = std::move(new_deque);
  return *this;
}

template <class value_type>
deque<value_type>::operator multiset<value_type>() const noexcept {
  set<value_type> mst;
  for (Node* i = this->head; i != nullptr; i = i->next) mst.insert(i->value);
  return mst;
}

template <class value_type>
deque<value_type>::operator set<value_type>() const noexcept {
  set<value_type> st;
  for (Node* i = this->head; i != nullptr; i = i->next) st.insert(i->value);
  return st;
}

template <class value_type>
deque<value_type>::operator list<value_type>() const noexcept {
  list<value_type> lst;
  for (Node* i = this->head; i != nullptr; i = i->next) lst.push_back(i->value);
  return lst;
}
}  // namespace s21
#endif  // __S21_DEQUE_CORE_HXX__