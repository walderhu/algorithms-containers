#ifndef __S21_LIST_HXX__
#define __S21_LIST_HXX__

// #include <initializer_list>
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
  // using iterator = T*;
  // using const_iterator = const T*;
  using size_type = size_t;

  List() noexcept;
  ~List() noexcept;

  size_t size() const;
  T& operator[](const int index) const;
  void push_back(T value);
  bool empty();
  void clear();
  void pop_front();
  void push_front(T value);
  void pop_back();
  void reverse();
  const T& front();
  const T& back();
  size_t max_size();
  void sort();

  struct iterator {
    Node* current;
    iterator(Node* n);
    bool operator==(const iterator& other);
    bool operator!=(const iterator& other);
    T& operator*();
    iterator& operator++() {
      current = current->next;
      return *this;
    }
  };
  iterator begin() { return iterator(head); }
  iterator end() { return iterator(nullptr); }

  void print() {
    for (auto it = begin(); it != end(); ++it) std::cout << *it << " ";
    std::cout << std::endl;
  }

  friend std::ostream& operator<<(std::ostream& os, const List& obj) {
    Node* current = obj.head;
    while (current) {
      os << current->value << " ";
      current = current->next;
    }
    return os;
  }
};

#endif  // __S21_LIST_HXX__