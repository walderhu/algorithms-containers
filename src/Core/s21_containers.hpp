#ifndef __S21_CONTAINER_HXX__
#define __S21_CONTAINER_HXX__

#include <cstddef>
#include <initializer_list>
#include <limits>
#include <stdexcept>
#include <utility>
#include <vector>

namespace s21 {

template <class T>
class deque;

template <class T>
class list;

template <class T>
class set;

template <class T>
class multiset;

template <class T>
class BaseIterator;

}  // namespace s21

#include "BaseIterator/s21_base_iterator.hpp"
#include "Deque/s21_deque.hpp"
#include "List/s21_list.hpp"
#include "Multiset/s21_multiset.hpp"
#include "Set/s21_set.hpp"

#endif  // __S21_CONTAINER_HXX__