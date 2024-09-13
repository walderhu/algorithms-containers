#ifndef __S21_SET_HPP__
#define __S21_SET_HPP__

#include "../BinaryTree/s21_BinaryTree.hpp"
namespace s21 {

template <class T> class set : public s21::deque<T> {
public:
  struct Iterator;
  struct ConstIterator;
  using typename s21::deque<T>::Node;
  using size_type = size_t;
  using value_type = T;
  using reference = T &;
  using iterator = Iterator;
  using const_iterator = ConstIterator;
  using const_reference = const T &;
};

} // namespace s21
#include "s21_set.tpp"
#include "s21_set_iterator.tpp"
#endif //  __S21_SET_HPP__