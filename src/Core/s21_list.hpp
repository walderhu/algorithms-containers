#ifndef __S21_LIST_HXX__
#define __S21_LIST_HXX__

#include <initializer_list>
#include <iostream>
#include <limits>

namespace s21 {

template <typename T>
class list final {
 private:
  struct Node {
    T value;
    Node* next;
    Node* prev;
    Node(T value = T());
  };
  Node* head;
  Node* tail;
  size_t _size;

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
  list<T>& operator=(list&& other) noexcept;
  list<T>& operator=(const list& other) noexcept;
  reference operator[](const int index) const;
  void push_back(T value);
  bool empty();
  void clear();
  void pop_front();
  void push_front(T value);
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
  void unique();

  struct Iterator {
    Node* current;
    s21::list<T>* list;
    Iterator() noexcept;
    Iterator(Node* node) noexcept;
    Iterator(Node* node, s21::list<T>* list) noexcept;
    Iterator(const Iterator& other) noexcept;
    virtual bool operator==(const Iterator& other);
    virtual bool operator!=(const Iterator& other);
    bool operator<(const Iterator& other);
    bool operator<=(const Iterator& other);
    bool operator>(const Iterator& other);
    bool operator>=(const Iterator& other);
    virtual reference operator*();
    Iterator& operator++();
    Iterator& operator--();
    Iterator& operator=(const Iterator& other);
  };
  Iterator begin();
  Iterator end();

  struct ConstIterator final : public Iterator {
    bool operator==(const ConstIterator& other) const override;
    bool operator!=(const ConstIterator& other) const override;
    const_reference operator*() const override;
  };
  ConstIterator cbegin() const;
  ConstIterator cend() const;

  template <typename U>
  friend std::ostream& operator<<(std::ostream& os, const list<U>& obj);
};
}  // namespace s21

#include "s21_list.tpp"

#endif  // __S21_LIST_HXX__
