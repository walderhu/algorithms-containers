#include "s21_set.hpp"

template <class value_type>
inline s21::set<value_type>::set() : s21::deque<value_type>::deque() {
  this->root = nullptr;
}

template <class value_type>
inline s21::set<value_type>::BinaryNode::BinaryNode(value_type value)
    : Node::Node() {
  this->left = Node::prev;
  this->right = Node::next;
  this->value = Node::value;
}

template <class value_type>
inline auto s21::set<value_type>::push_left(value_type value) -> void {
  iterator it;
}

template <class value_type>
inline auto s21::set<value_type>::push_right(value_type value) -> void {}