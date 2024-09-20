#ifndef __S21_SET_HPP__
#define __S21_SET_HPP__

#include "../s21_containers.hpp"

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
  set(const set &s) noexcept;
  set(set &&s) noexcept;
  virtual ~set() noexcept;
  set<value_type> &operator=(set &&s) noexcept;
  set<value_type> &operator=(const set &s) noexcept;

  explicit operator s21::deque<Key>() const noexcept;
  explicit operator s21::list<Key>() const noexcept;
  explicit operator s21::multiset<Key>() const noexcept;

  iterator find(const Key &key) noexcept;
  bool contains(const Key &key) noexcept;
  bool empty() const noexcept;
  void clear() noexcept;
  void swap(set &other) noexcept;
  void erase(iterator pos) noexcept;
  void merge(set &other) noexcept;
  virtual std::pair<iterator, bool> insert(const value_type value) noexcept;

  iterator begin() noexcept;
  iterator end() noexcept;
  ConstIterator cbegin() const noexcept;
  ConstIterator cend() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args &&...args);

 protected:
  size_type _size;
  void clear(Node *&current);

 private:
  Node *deleteNode(Node *current, value_type key);
  virtual std::pair<iterator, bool> insert_in(value_type value, Node *&current,
                                              Node *parent) noexcept;
};

template <class Key>
struct s21::set<Key>::Node {
  Node *left;
  Node *right;
  Node *parent;
  value_type value;
  Node(value_type val = value_type()) noexcept;
};

template <class Key>
struct s21::set<Key>::Iterator {
  Iterator() noexcept;
  Iterator(Node *node, s21::set<value_type> *st = nullptr) noexcept;
  Iterator(const Iterator &other) noexcept;
  bool operator==(const Iterator &other) const noexcept;
  bool operator!=(const Iterator &other) const noexcept;
  bool operator<(const Iterator &other) const noexcept;
  bool operator<=(const Iterator &other) const noexcept;
  bool operator>(const Iterator &other) const noexcept;
  bool operator>=(const Iterator &other) const noexcept;
  Iterator &operator++();
  Iterator &operator--();
  Iterator operator++(int);
  Iterator operator--(int);
  reference operator*() const;
  virtual Iterator &operator=(const Iterator &other);
  Key get_value() const;

 protected:
  Node *current;
  Iterator last();
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