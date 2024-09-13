#ifndef __S21_MULTYSET_HPP__
#define __S21_MULTYSET_HPP__

#include "../Set/s21_set.hpp"
namespace s21 {

template <class T>
class multyset : public s21::set<T> {};

}  // namespace s21
#include "s21_multyset.tpp"
#endif  //  __S21_MULTYSET_HPP__
