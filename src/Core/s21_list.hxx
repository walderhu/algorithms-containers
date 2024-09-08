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
  ~List() noexcept { this->clear(); }

  size_t size() const { return this->_size; }

  friend std::ostream& operator<<(std::ostream& os, const List& obj) {
    Node* current = obj.head;
    while (current) {
      os << current->data << " ";
      current = current->next;
    }
    return os;
  }

  T& operator[](const int index) const;

  void push_back(T data);
  void clear();

 private:
  struct Node {
    T data;
    Node* next;
    Node* prev;
    Node(T data = T()) : data(data), next(nullptr), prev(nullptr) {}
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
  return current->data;
}

template <typename T>
void s21::List<T>::push_back(T data) {
  Node* new_node = new Node(data);

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
void s21::List<T>::clear() {
  while (head) {
    Node* temp = head;
    head = head->next;
    delete temp;
  }
  tail = nullptr;
}

#endif  // __S21_LIST_HXX__