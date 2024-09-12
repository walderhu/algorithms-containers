#include "s21_deque.hpp"

template <typename value_type>
inline s21::deque<value_type>::Node::Node(value_type value)
    : value(value), next(nullptr), prev(nullptr) {}