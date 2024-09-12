#ifndef __S21_DEQUE_HXX__
#define __S21_DEQUE_HXX__

#include <cstddef>
#include <initializer_list>
#include <limits>

namespace s21 {
template <class T>
class deque {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  deque() noexcept;
  deque(size_type n) noexcept;
  ~deque() noexcept;
  deque(const deque& other) noexcept;
  deque(deque&& other) noexcept;
  deque(std::initializer_list<value_type> const& items) noexcept;
  void clear();
  void push_front(value_type value);

  bool empty();
  void pop_front();
  void pop_back();

 protected:
  struct Node;
  Node* head;
  Node* tail;
  size_type _size;

 protected:
  void push_front(Node* new_node);
};
}  // namespace s21

template <class T>
struct s21::deque<T>::Node final {
  value_type value;
  Node* next;
  Node* prev;
  Node(value_type value = value_type());
};

#include "s21_deque.tpp"

#endif  // __S21_DEQUE_HXX__