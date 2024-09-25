#ifndef __S21_CONTAINER_HXX__
#define __S21_CONTAINER_HXX__

#include <cstddef>
#include <initializer_list>
#include <limits>
#include <stdexcept>
#include <utility>

#define DEBUG(x)                                                    \
  std::cout << "DEBUG: " << #x << " = " << x << " (in " << __FILE__ \
            << ", line " << __LINE__ << ")" << std::endl;

#define RED_TEXT "\033[31m"
#define RESET_TEXT "\033[0m"

#define PRINT(x)                                                               \
  std::cout << RED_TEXT << x << RESET_TEXT << " (in " << __FILE__ << ", line " \
            << __LINE__ << ")" << std::endl;

#define PING() PRINT("ping")
namespace s21 {

template <class T>
class deque;

template <class T>
class list;

template <class T>
class set;

template <class T>
class multiset;

// template <class T = int>
// class unordered_set;

// template <class T>
// class unordered_multiset;

template <class T>
class vector;

}  // namespace s21

#include "Deque/s21_deque.hpp"
#include "List/s21_list.hpp"
#include "Multiset/s21_multiset.hpp"
#include "Set/s21_set.hpp"
#include "UnorderedMultiset/s21_unordered_multiset.hpp"
#include "UnorderedSet/s21_unordered_set.hpp"
#include "Vector/s21_vector.hpp"

#endif  // __S21_CONTAINER_HXX__