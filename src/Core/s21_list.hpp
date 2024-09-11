#ifndef __S21_LIST_HXX__
#define __S21_LIST_HXX__

#include <iostream>
#include <limits>

namespace s21 {

template <typename T>
class list final {
 private:
  struct Node;
  Node* head;
  Node* tail;
  size_t _size;
  void push_front(Node* new_node);
  void push_back(Node* new_node);

 public:
  struct Iterator;
  struct ConstIterator;
  using value_type = T;
  using reference = T&;
  using iterator = Iterator;
  using const_iterator = ConstIterator;
  using const_reference = const T&;
  using size_type = size_t;

  list() noexcept;
  ~list() noexcept;
  list(size_type n) noexcept;
  list(std::initializer_list<value_type> const& items) noexcept;
  list(const list& other) noexcept;
  list(list&& other) noexcept;

  size_type size() const;
  list<value_type>& operator=(list&& other) noexcept;
  list<value_type>& operator=(const list& other) noexcept;
  reference operator[](const int index) const;
  void push_back(value_type value);
  bool empty();
  void clear();
  void pop_front();
  void push_front(value_type value);
  void pop_back();
  void reverse();
  const_reference front();
  const_reference back();
  size_type max_size();
  void sort();
  void print();
  void swap(list& other) noexcept;
  void merge(list& other);
  iterator insert(iterator pos, const_reference value);
  iterator insert(iterator pos, std::initializer_list<value_type> const& items);
  void erase(iterator pos);
  void splice(const_iterator pos, list& other);
  void splice(iterator pos, list& other);
  void unique();

  struct Iterator;
  struct ConstIterator;
  Iterator begin();
  Iterator end();
  ConstIterator cbegin() const;
  ConstIterator cend() const;

  template <typename U>
  friend std::ostream& operator<<(std::ostream& os, const list<U>& obj);
};
}  // namespace s21

template <typename T>
struct s21::list<T>::Node final {
  value_type value;
  Node* next;
  Node* prev;
  Node(value_type value = value_type());
};

template <typename T>
struct s21::list<T>::Iterator {
  Iterator() noexcept;
  Iterator(Node* node) noexcept;
  Iterator(Node* node, s21::list<value_type>* list) noexcept;
  Iterator(const Iterator& other) noexcept;
  bool operator==(const Iterator& other) const;
  bool operator!=(const Iterator& other) const;
  bool operator<(const Iterator& other) const;
  bool operator<=(const Iterator& other) const;
  bool operator>(const Iterator& other) const;
  bool operator>=(const Iterator& other) const;
  Iterator& operator++();
  Iterator& operator--();
  reference operator*() const;
  virtual Iterator& operator=(const Iterator& other);

 protected:
  Node* current;
  s21::list<value_type>* list;
  friend class s21::list<T>;
  friend class s21::list<T>::ConstIterator;
};

template <typename T>
struct s21::list<T>::ConstIterator final : public s21::list<T>::Iterator {
  using s21::list<T>::Iterator::Iterator;
  ConstIterator(Node* node, const s21::list<T>* lst) noexcept;
  ConstIterator(iterator it) noexcept;
  const_reference operator*() const;
  Iterator& operator=(const Iterator& other) override;
};

#include "s21_list.tpp"

#endif  // __S21_LIST_HXX__
