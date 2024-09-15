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

 protected:
  void push_left(value_type value);
  void push_right(value_type value);
};

template <class Key>
struct s21::set<Key>::BinaryNode : public Node {
  value_type &value;
  BinaryNode *left;
  BinaryNode *right;
  BinaryNode(value_type value = value_type());
};

template <class Key>
struct s21::set<Key>::Iterator {
  Iterator() noexcept;
  Iterator(BinaryNode *node) noexcept;
  Iterator(BinaryNode *node, s21::set<value_type> *set = nullptr) noexcept;
  // Iterator(const Iterator &other) noexcept;
  //   bool operator==(const Iterator &other) const;
  //   bool operator!=(const Iterator &other) const;
  //   bool operator<(const Iterator &other) const;
  //   bool operator<=(const Iterator &other) const;
  //   bool operator>(const Iterator &other) const;
  //   bool operator>=(const Iterator &other) const;
  //   Iterator &operator++();
  //   Iterator &operator--();
  //   reference operator*() const;
  //   virtual Iterator &operator=(const Iterator &other);

 protected:
  BinaryNode *current;
  s21::set<value_type> *set;
  friend class s21::set<value_type>;
  friend class s21::set<value_type>::ConstIterator;
};

template <class Key>
struct s21::set<Key>::ConstIterator final : public s21::set<Key>::Iterator {
  ConstIterator() {}
};

}  // namespace s21
#include "s21_set.tpp"
#include "s21_set_iterator.tpp"
#endif  //  __S21_SET_HPP__