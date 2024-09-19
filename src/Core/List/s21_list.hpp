#ifndef __S21_LIST_HXX__
#define __S21_LIST_HXX__

#include "../s21_containers.hpp"

namespace s21 {

template <class T>
class list final : public deque<T> {
 private:
  struct Iterator;
  struct ConstIterator;

 public:
  using Node = typename s21::deque<T>::Node;
  using size_type = size_t;
  using value_type = T;
  using reference = T &;
  using iterator = Iterator;
  using const_iterator = ConstIterator;
  using const_reference = const T &;

  list() noexcept;
  list(size_type n) noexcept;
  ~list() noexcept;
  list(const list &other) noexcept;
  list(list &&other) noexcept;
  list(std::initializer_list<value_type> const &items) noexcept;
  list<value_type> &operator=(list &&other) noexcept;
  list<value_type> &operator=(const list &other) noexcept;
  explicit operator s21::deque<value_type>() noexcept;

  // list
  reference operator[](const int index) const;
  void reverse();
  void sort();
  void swap(list &other) noexcept;
  void merge(list &other);

  iterator insert(iterator pos, const_reference value);
  iterator insert(iterator pos, std::initializer_list<value_type> const &items);
  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);
  template <typename... Args>
  void insert_many_back(Args &&...args);
  template <typename... Args>
  void insert_many_front(Args &&...args);

  void erase(iterator pos);
  void splice(const_iterator pos, list &other);
  void splice(iterator pos, list &other);
  void unique();
  Iterator begin() noexcept;
  Iterator end() noexcept;
  ConstIterator cbegin() const;
  ConstIterator cend() const;
};
}  // namespace s21

template <class T>
struct s21::list<T>::Iterator {
  Iterator() noexcept;
  Iterator(Node *node, s21::list<value_type> *lst = nullptr) noexcept;
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
  s21::list<value_type> *list;
  friend class s21::list<T>;
  friend class s21::list<T>::ConstIterator;
};

template <class T>
struct s21::list<T>::ConstIterator final : public s21::list<T>::Iterator {
  using s21::list<T>::Iterator::Iterator;
  ConstIterator(Node *node, const s21::list<T> *lst) noexcept;
  ConstIterator(iterator it) noexcept;
  const_reference operator*() const;
  Iterator &operator=(const Iterator &other) override;
};

#include "s21_list_core.hpp"
#include "s21_list_iterator.hpp"

#endif  // __S21_LIST_HXX__
