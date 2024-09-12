#ifndef __S21_DEQUE_HXX__
#define __S21_DEQUE_HXX__

#include <cstddef>
#include <limits>

namespace s21 {
template <class T>
class deque {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

 protected:
  struct Node;
  Node* head;
  Node* tail;
  size_type _size;
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