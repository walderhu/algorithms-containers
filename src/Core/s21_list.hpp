#ifndef __S21_LIST_HXX__
#define __S21_LIST_HXX__

#include <initializer_list>
#include <iostream>
#include <limits>

namespace s21 {

template <typename T>
class List final {
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
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = T*;
  using const_iterator = const T*;
  using size_type = size_t;

  List() noexcept;
  ~List() noexcept;

  size_type size() const;
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

  // TODO
  List(size_type n) noexcept;
  List(std::initializer_list<value_type> const& items) noexcept;
  List(const List& other) noexcept;           // BUG
  List(List&& other) noexcept;                // BUG
  List<T>& operator=(List&& other) noexcept;  // BUG

  // iterator insert(iterator pos, const_reference value);
  // void erase(iterator pos);
  // void swap(list& other);
  // void merge(list& other);
  // void splice(const_iterator pos, list& other);
  // void unique();

  struct Iterator {
    Node* current;
    Iterator(Node* n);
    bool operator==(const Iterator& other);
    bool operator!=(const Iterator& other);
    reference operator*();
    Iterator& operator++();
  };
  Iterator begin();
  Iterator end();

  template <typename U>
  friend std::ostream& operator<<(std::ostream& os, const List<U>& obj);
};
}  // namespace s21

#include "s21_list.tpp"

#endif  // __S21_LIST_HXX__
