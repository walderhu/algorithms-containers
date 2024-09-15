#ifndef __S21_BINARY_TREE_HPP__
#define __S21_BINARY_TREE_HPP__

#include "../Deque/s21_deque.hpp"
namespace s21 {

template <class T>
class BinaryTree : public s21::deque<T> {};
}  // namespace s21
#include "s21_BinaryTree.hpp"
#endif  //  __S21_BINARY_TREE_HPP__