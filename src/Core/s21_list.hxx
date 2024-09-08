#ifndef __S21_LIST_HXX__
#define __S21_LIST_HXX__

namespace s21 {

template <typename type>
class List final {
 public:
  List() : head(nullptr), tail(nullptr) {}
  ~List() { this->clear(); }

  void push_back(type data);
  void clear();

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

#endif  // __S21_LIST_HXX__