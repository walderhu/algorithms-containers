#ifndef __S21_CONTAINER_HXX__
#define __S21_CONTAINER_HXX__

#include <cstddef>
#include <initializer_list>
#include <limits>
#include <stdexcept>
#include <utility>
#include <vector>

namespace s21 {

template <typename T>
class deque;

template <typename T>
class list;

template <typename T>
class set;

template <typename T>
class multiset;

}  // namespace s21

#include "Deque/s21_deque.hpp"
#include "List/s21_list.hpp"
#include "Multiset/s21_multiset.hpp"
#include "Set/s21_set.hpp"

#endif  // __S21_CONTAINER_HXX__