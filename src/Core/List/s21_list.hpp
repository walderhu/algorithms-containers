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
  ~list() noexcept override;
  list(const list &other) noexcept;
  list(list &&other) noexcept;
  list(std::initializer_list<value_type> const &items) noexcept;
  list<value_type> &operator=(list &&other) noexcept;
  list<value_type> &operator=(const list &other) noexcept;
  explicit operator s21::deque<value_type>() const noexcept;

  // list
  reference operator[](const unsigned index) const;
  void reverse() noexcept;
  void sort() noexcept;
  void swap(list &other) noexcept;
  void merge(list &other) noexcept;

  iterator insert(iterator pos, const_reference value) noexcept;
  iterator insert(iterator pos,
                  std::initializer_list<value_type> const &items) noexcept;
  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args) noexcept;
  template <typename... Args>
  void insert_many_back(Args &&...args) noexcept;
  template <typename... Args>
  void insert_many_front(Args &&...args) noexcept;

  void erase(iterator pos);
  void splice(const_iterator pos, list &other);
  void splice(iterator pos, list &other);
  void unique() noexcept;
  Iterator begin() noexcept;
  Iterator end() noexcept;
  ConstIterator cbegin() const noexcept;
  ConstIterator cend() const noexcept;
};

template <class T>
struct list<T>::Iterator {
  Iterator() noexcept;
  Iterator(Node *node, list<value_type> *lst = nullptr) noexcept;
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
  friend class list<T>;
};

template <class T>
struct list<T>::ConstIterator final : public list<T>::Iterator {
  using list<T>::Iterator::Iterator;
  ConstIterator(Node *node, const list<T> *lst) noexcept;
  ConstIterator(iterator it) noexcept;
  const_reference operator*() const;
  Iterator &operator=(const Iterator &other) override;
};
}  // namespace s21

#include "s21_list_core.hpp"
#include "s21_list_iterator.hpp"

#endif  // __S21_LIST_HXX__
