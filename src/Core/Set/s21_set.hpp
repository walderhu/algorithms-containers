#ifndef __S21_SET_HPP__
#define __S21_SET_HPP__

#include "../BinaryTree/s21_BinaryTree.hpp"
namespace s21 {

template <class Key>
class set : public s21::deque<Key> {
 protected:
  using Node = typename s21::deque<Key>::Node;
  struct BinaryNode;
  struct Iterator;
  struct ConstIterator;
  BinaryNode *root;

 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = Iterator;
  using const_iterator = ConstIterator;
  using size_type = size_t;

  set();
  set(std::initializer_list<value_type> const &items) {}
  set(const set &s) : s21::deque<Key>(s) {}
  set(set &&s) : s21::deque<Key>(std::move(s)) {}
  ~set() = default;
};

template <class Key>
struct s21::set<Key>::BinaryNode : public Node {
  value_type *value;
  BinaryNode *left;
  BinaryNode *right;
  BinaryNode(value_type value = value_type()) : Node::Node() {
    this->left = Node::prev;
    this->right = Node::next;
    this->value = &(Node::value);
  }
};

template <class Key>
struct s21::set<Key>::Iterator {
  Iterator() {}
};

template <class Key>
struct s21::set<Key>::ConstIterator final : public s21::set<Key>::Iterator {
  ConstIterator() {}
};

}  // namespace s21
#include "s21_set.tpp"
#include "s21_set_iterator.tpp"
#endif  //  __S21_SET_HPP__