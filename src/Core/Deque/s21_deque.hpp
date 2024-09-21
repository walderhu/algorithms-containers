#ifndef __S21_DEQUE_HXX__
#define __S21_DEQUE_HXX__

#include "../s21_containers.hpp"

namespace s21 {
template <class T>
class deque {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  // using deque<T>::head;
  // using deque<T>::tail;
  // using deque<T>::_size;

  deque() noexcept;
  deque(size_type n) noexcept;
  virtual ~deque() noexcept;
  deque(const deque& other) noexcept;
  deque(deque&& other) noexcept;
  deque(std::initializer_list<value_type> const& items) noexcept;

  void clear() noexcept;
  void push_front(value_type value);
  void push_back(value_type value);
  size_type size() const;
  deque<value_type>& operator=(deque&& other) noexcept;
  deque<value_type>& operator=(const deque& other) noexcept;
  explicit operator s21::set<value_type>() const noexcept;
  explicit operator s21::multiset<value_type>() const noexcept;
  explicit operator s21::list<value_type>() const noexcept;

  bool empty() const noexcept;
  void pop_front() noexcept;
  void pop_back() noexcept;
  const_reference front() const;
  const_reference back() const;
  size_type max_size() const noexcept;

 protected:
  struct Node;
  Node* head;
  Node* tail;
  size_type _size;
  void push_front(Node* new_node) noexcept;
  void push_back(Node* new_node) noexcept;
};

template <class T>
struct deque<T>::Node {
  value_type value;
  Node* next;
  Node* prev;
  Node(value_type val = value_type()) noexcept;
};

}  // namespace s21
#include "s21_deque_core.hpp"

#endif  // __S21_DEQUE_HXX__