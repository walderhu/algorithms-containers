#ifndef __S21_SET_HPP__
#define __S21_SET_HPP__

#include "../BinaryTree/s21_BinaryTree.hpp"
namespace s21 {

template <class T>
class set : public s21::BinaryTree<T> {};

}  // namespace s21
#include "s21_set.tpp"
#endif  //  __S21_SET_HPP__