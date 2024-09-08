#ifndef __S21_LIST_HXX__
#define __S21_LIST_HXX__

#include <iostream>
namespace s21 {

template <typename T>
class List final {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = T*;
  using const_iterator = const T*;
  using size_type = size_t;

  List() noexcept : head(nullptr), tail(nullptr), _size(0) {}
  ~List() noexcept { clear(); }

  size_t size() const { return _size; }
  T& operator[](const int index) const;
  void push_back(T value);
  bool empty();
  void clear();
  void pop_front();
  void push_front(T value);
  void pop_back();
  void reverse();
  const T& front() { return head->value; }
  const T& back() { return tail->value; }

  friend std::ostream& operator<<(std::ostream& os, const List& obj) {
    Node* current = obj.head;
    while (current) {
      os << current->value << " ";
      current = current->next;
    }
    return os;
  }

 private:
  struct Node {
    T value;
    Node* next;
    Node* prev;
    Node(T value = T()) : value(value), next(nullptr), prev(nullptr) {}
  };
  Node* head;
  Node* tail;
  size_t _size;
};

}  // namespace s21

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
  return bool(head);
}

template <typename T>
void s21::List<T>::clear() {
  while (head) {
    Node* temp = head;
    head = head->next;
    delete temp;
  }
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

template <typename T>
inline void s21::List<T>::reverse() {
  if (size > 1) {
    Node* current = head;
    while (current != tail) {
      std::swap(current->next, current->prev);
      current = current->prev;
    }
    std::swap(head, tail);
  }
}

#endif  // __S21_LIST_HXX__