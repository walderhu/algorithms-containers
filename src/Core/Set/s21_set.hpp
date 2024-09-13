#ifndef __S21_SET_HPP__
#define __S21_SET_HPP__

#include "../BinaryTree/s21_BinaryTree.hpp"
namespace s21 {

template <class T> class set : public s21::deque<T> {
public:
  using Node = typename s21::deque<T>::Node;

  struct Iterator;
  struct ConstIterator;
  using size_type = size_t;
  using value_type = T;
  using reference = T &;
  using iterator = Iterator;
  using const_iterator = ConstIterator;
  using const_reference = const T &;

  set();
  set(std::initializer_list<value_type> const &items) {}
  set(const set &s) : s21::deque<T>(s) {}
  set(set &&s) : s21::deque<T>(std::move(s)) {}
  ~set() = default;

protected:
  Node *root;
};

} // namespace s21
#include "s21_set.tpp"
#include "s21_set_iterator.tpp"
#endif //  __S21_SET_HPP__