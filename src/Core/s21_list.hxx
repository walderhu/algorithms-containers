#ifndef __S21_LIST_HXX__
#define __S21_LIST_HXX__

#include <iostream>
namespace s21 {

template <typename type>
class List final {
 public:
  List() noexcept : size(0), head(nullptr), tail(nullptr) {}
  ~List() noexcept { this->clear(); }
  size_t size;

  friend std::ostream& operator<<(std::ostream& os, const List& obj) {
    os << "Size: " << obj.size;
    return os;
  }

  type& operator[](const int index) const;

  void push_back(type data);
  void clear();
  void print() const;

 private:
  struct Node {
    type data;
    Node* next;
    Node* prev;
    Node(type data = type()) : data(data), next(nullptr), prev(nullptr) {}
  };
  Node* head;
  Node* tail;
};

}  // namespace s21

template <typename type>
inline type& s21::List<type>::operator[](const int index) const {
  if (index < 0 || index >= size) throw std::out_of_range("Index out of range");
  Node* current = head;
  for (int i = 0; i < index; ++i) current = current->next;
  return current->data;
}

template <typename type>
void s21::List<type>::push_back(type data) {
  Node* new_node = new Node(data);

  if (!head) {
    head = new_node;
    tail = new_node;
  } else {
    new_node->prev = tail;
    tail->next = new_node;
    tail = new_node;
  }
  size++;
}

template <typename type>
void s21::List<type>::clear() {
  while (head) {
    Node* temp = head;
    head = head->next;
    delete temp;
  }
  tail = nullptr;
}

template <typename type>
inline void s21::List<type>::print() const {
  Node* current = head;
  while (current) {
    std::cout << current->data << " ";  // Выводим данные узла
    current = current->next;  // Переходим к следующему узлу
  }
  std::cout
      << std::endl;  // Переход на новую строку после вывода всех элементов
}

#endif  // __S21_LIST_HXX__