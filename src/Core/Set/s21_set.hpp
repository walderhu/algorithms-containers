#ifndef __S21_SET_HPP__
#define __S21_SET_HPP__

#include <cstddef>
#include <initializer_list>
#include <limits>
#include <stdexcept>
#include <utility>
#include <vector>

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
  set(std::initializer_list<value_type> const &items) noexcept;
  set(const set &s);
  set(set &&s);
  ~set() noexcept;
  set<value_type> &operator=(set &&s) noexcept;
  set<value_type> &operator=(const set &s) noexcept;

  iterator find(const Key &key);
  bool contains(const Key &key);

  bool empty() const;
  void clear();

  std::pair<iterator, bool> insert(value_type value);

  iterator begin();
  iterator end();
  ConstIterator cbegin() const;
  ConstIterator cend() const;
  void swap(set &other);
  size_type size() const;

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);

 protected:
  size_type _size;
  std::pair<iterator, bool> insert(value_type value, Node *&current,
                                   Node *parent);
  void clear(Node *&current);
  void push_left(value_type value);
  void push_right(value_type value);
};

template <class Key>
struct s21::set<Key>::Node {
  value_type value;
  Node *left;
  Node *right;
  Node *parent;
  Node(value_type value = value_type());
};

template <class Key>
struct s21::set<Key>::Iterator {
  Iterator() noexcept;
  Iterator(Node *node, s21::set<value_type> *set = nullptr) noexcept;
  Iterator(const Iterator &other) noexcept;
  bool operator==(const Iterator &other) const;
  bool operator!=(const Iterator &other) const;
  bool operator<(const Iterator &other) const;
  bool operator<=(const Iterator &other) const;
  bool operator>(const Iterator &other) const;
  bool operator>=(const Iterator &other) const;
  Iterator &operator++();
  Iterator &operator--();
  reference operator*() const;
  virtual Iterator &operator=(const Iterator &other);

 protected:
  Node *current;
  s21::set<value_type> *set;
  friend class s21::set<value_type>;
  friend class s21::set<value_type>::ConstIterator;
};

template <class Key>
struct s21::set<Key>::ConstIterator final : public s21::set<Key>::Iterator {
  using s21::set<Key>::Iterator::Iterator;
  ConstIterator(Node *node, const s21::set<Key> *set_) noexcept;
  ConstIterator(iterator it) noexcept;
  const_reference operator*() const;
  Iterator &operator=(const Iterator &other) override;
};

}  // namespace s21

#include "s21_set_core.hpp"
#include "s21_set_iterator.hpp"

#endif  //  __S21_SET_HPP__