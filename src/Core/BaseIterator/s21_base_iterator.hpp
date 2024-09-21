#if !defined(__S21_BASE_ITERATOR_HPP__)
#define __S21_BASE_ITERATOR_HPP__

namespace s21 {

template <class T>
struct BaseNode {
  BaseNode(T val = T());
  T value;
};

template <class T>
struct BaseIterator {
  BaseIterator();
};

}  // namespace s21

#endif  // __S21_BASE_ITERATOR_HPP__
