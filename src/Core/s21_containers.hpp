#ifndef __S21_CONTAINER_HXX__
#define __S21_CONTAINER_HXX__

#include <cstddef>
#include <initializer_list>
#include <limits>
#include <stdexcept>
#include <utility>
#include <vector>  //
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
class vector;

template <typename Key, typename T>
class AVLTree;

template <typename T, size_t Size>
class array;

template <typename Key, typename T>
class map;

template <typename T, class Container = s21::list<T>>
class queue;

template <typename T, class Container = std::vector<T>>
class stack;
}  // namespace s21

#include "AVLTree/s21_binary_tree.hpp"
#include "Array/s21_array.hpp"
#include "Deque/s21_deque.hpp"
#include "List/s21_list.hpp"
#include "Map/s21_map.hpp"
#include "Multiset/s21_multiset.hpp"
#include "Queue/s21_queue.hpp"
#include "Set/s21_set.hpp"
#include "Stack/s21_stack.hpp"
#include "Vector/s21_vector.hpp"

#endif  // __S21_CONTAINER_HXX__