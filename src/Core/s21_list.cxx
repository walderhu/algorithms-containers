#include "s21_list.hxx"

/*
TODO ~HEAD TASK

*/

template <typename type>
void s21::List<type>::push_back(type value) {
  Node* new_node = new Node(value);
  if (tail) {
    this->tail->next = new_node;
    new_node->prev = this->tail;
    this->tail = new_node;
  } else {
    this->tail = this->head = new_node;
  }
}

template <typename type>
void s21::List<type>::clear() {
  Node* current = head;
  while (current) {
    Node* new_node = current->next;
    delete current;
    current = new_node;
  }
  this->head = this->tail = nullptr;
}