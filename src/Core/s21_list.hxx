#ifndef __S21_LIST_HXX__
#define __S21_LIST_HXX__

#include <iostream>

namespace s21 {

template <typename type>
class List final {
 public:
  struct Node {
    type value;
    type* next;
    type* prev;
    Node(type value) : value(value), prev(nullptr), next(nullptr) {}
  };

  List() : head(nullptr), tail(nullptr) {}
  ~List() { this->clear(); }
  void push_back(type value);
  void clear();

 private:
  Node* head;
  Node* tail;

 protected:
  //   void push_front(type value);
  //   void pop_back();
  //   void pop_front();
};
}  // namespace s21

#endif  // __S21_LIST_HXX__