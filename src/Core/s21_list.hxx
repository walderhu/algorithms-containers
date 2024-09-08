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

template <typename T>
inline List<T>::Node::Node(T value)
    : value(value), next(nullptr), prev(nullptr) {}

template <typename T>
inline List<T>::iterator::iterator(Node* n) : current(n) {}

template <typename T>
inline bool List<T>::iterator::operator==(const iterator& other) {
  return current == other.current;
}

template <typename T>
inline bool List<T>::iterator::operator!=(const iterator& other) {
  return !(*this == other);
}

template <typename T>
inline T& List<T>::iterator::operator*() {
  return current->value;
}

}  // namespace s21

template <typename T>
inline s21::List<T>::List() noexcept : head(nullptr), tail(nullptr), _size(0) {}

template <typename T>
inline s21::List<T>::~List() noexcept {
  clear();
}

template <typename T>
inline size_t s21::List<T>::size() const {
  return _size;
}

template <typename T>
inline T& s21::List<T>::operator[](const int index) const {
  if (index < 0 || index >= _size)
    throw std::out_of_range("Index out of range");
  Node* current = head;
  for (int i = 0; i < index; ++i) current = current->next;
  return current->value;
}

template <typename T>
void s21::List<T>::push_back(T value) {
  Node* new_node = new Node(value);
  if (!head) {
    head = new_node;
    tail = new_node;
  } else {
    new_node->prev = tail;
    tail->next = new_node;
    tail = new_node;
  }
  _size++;
}

template <typename T>
inline bool s21::List<T>::empty() {
  return size() == 0;
}

// template <typename T>
// void s21::List<T>::clear() {
//   while (head) {
//     Node* temp = head;
//     head = head->next;
//     delete temp;
//   }
//   tail = nullptr;
// }

// TODO потестировать update
template <typename T>
void s21::List<T>::clear() {
  while (_size) pop_front();
  tail = nullptr;
}

template <typename T>
inline void s21::List<T>::pop_front() {
  if (head) {
    Node* tmp = head;
    head = head->next;
    delete tmp;
    if (head)
      head->prev = nullptr;
    else
      tail = nullptr;

    _size -= 1;
  }
}

template <typename T>
inline void s21::List<T>::push_front(T value) {
  Node* new_node = new Node(value);
  if (!head) {
    head = new_node;
    tail = new_node;
  } else {
    new_node->next = head;
    head->prev = new_node;
    head = new_node;
  }
  _size++;
}

template <typename T>
inline void s21::List<T>::pop_back() {
  if (head) {
    Node* tmp = tail;
    tail = tail->prev;
    delete tail;
    _size--;

    if (head)
      tail->next = nullptr;
    else
      tail = nullptr;
  }
}

// TODO надо тестить, странно работает
template <typename T>
inline void s21::List<T>::reverse() {
  if (size() > 1) {
    Node* current = head;
    while (current != tail) {
      std::swap(current->next, current->prev);
      current = current->prev;
    }
    std::swap(head, tail);
  }
}

template <typename T>
inline const T& s21::List<T>::front() {
  return head->value;
}

template <typename T>
inline const T& s21::List<T>::back() {
  return tail->value;
}

template <typename T>
inline size_t s21::List<T>::max_size() {
  return (std::numeric_limits<size_t>::max() / sizeof(T)) / 2;
}

template <typename T>
inline void s21::List<T>::sort() {
  Node* current = head;
  bool swapped = true;

  while (swapped) {
    swapped = false;
    current = head;

    while (current && current->next) {
      Node* next_node = current->next;
      if (current->value > next_node->value) {
        std::swap(current->value, next_node->value);
        swapped = true;
      }
      current = current->next;
    }
  }
}

#endif  // __S21_LIST_HXX__