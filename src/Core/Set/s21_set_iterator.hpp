#ifndef __S21_SET_ITERATOR__
#define __S21_SET_ITERATOR__
#include "s21_set.hpp"

template <class value_type>
inline s21::set<value_type>::Iterator::Iterator() noexcept
    : current(nullptr), set(nullptr) {}

template <class value_type>
inline s21::set<value_type>::Iterator::Iterator(
    BinaryNode* node, s21::set<value_type>* set) noexcept
    : current(node), set(set) {}

#endif // __S21_SET_ITERATOR__