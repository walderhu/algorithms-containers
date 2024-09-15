#ifndef __S21_SET_HPP__
#define __S21_SET_HPP__

#include "../Deque/s21_deque.hpp"

namespace s21 {

template <class Key>
class set {
 protected:
  struct Node;
  struct Iterator;
  struct ConstIterator;
  Node *root;

 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = Iterator;
  using const_iterator = ConstIterator;
  using size_type = size_t;

  set() noexcept;

  set(std::initializer_list<value_type> const &items) {}
  set(const set &s) : s21::deque<Key>(s) {}
  set(set &&s) : s21::deque<Key>(std::move(s)) {}
  ~set() = default;
  bool empty() const;

  Iterator insert(value_type value);

  Iterator begin();
  Iterator end();
  size_type size() const;

 protected:
  size_type _size;
  Iterator insert(value_type value, Node *&current);
  void push_left(value_type value);
  void push_right(value_type value);
};

template <class Key>
struct s21::set<Key>::Node {
  value_type value;
  Node *left;
  Node *right;
  Node(value_type value = value_type());
};

template <class Key>
struct s21::set<Key>::Iterator {
  Iterator() noexcept;
  Iterator(Node *node, s21::set<value_type> *set = nullptr) noexcept;
  // Iterator(const Iterator &other) noexcept;
  //   bool operator==(const Iterator &other) const;
  //   bool operator!=(const Iterator &other) const;
  //   bool operator<(const Iterator &other) const;
  //   bool operator<=(const Iterator &other) const;
  //   bool operator>(const Iterator &other) const;
  //   bool operator>=(const Iterator &other) const;
  Iterator &operator++();
  Iterator &operator--();
  reference operator*() const { return current->value; };
  Iterator &operator=(const Iterator &other) {
    current = other.current;
    return *this;
  }

 protected:
  Node *current;
  s21::set<value_type> *set;
  friend class s21::set<value_type>;
  friend class s21::set<value_type>::ConstIterator;
};

template <class Key>
struct s21::set<Key>::ConstIterator final : public s21::set<Key>::Iterator {
  ConstIterator() {}
};

}  // namespace s21

#include "s21_set_core.hpp"
#include "s21_set_iterator.hpp"

#endif  //  __S21_SET_HPP__