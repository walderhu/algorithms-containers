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
  List(const List& other) noexcept;
  List(List&& other) noexcept;

  // operator=(list && l);
  // operator= [size_t index];

  // iterator insert(iterator pos, const_reference value);
  // void erase(iterator pos);
  // void swap(list& other);
  // void merge(list& other);
  // void splice(const_iterator pos, list& other);
  // void unique();
  //

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

// TODO
// using Array = std::initializer_list<double>;

// S21Matrix::S21Matrix(const Array& array) : S21Matrix(array.size(), 1) {
//   FillingMatrix(array);
// }

// void S21Matrix::FillingMatrix(const Matrix& matrix) {
//   int row = 0, col = 0;
//   for (const auto& rows : matrix) {
//     col = 0;
//     for (const auto& elem : rows) {
//       this->matrix_[row][col] = elem;
//       col++;
//     }
//     row++;
//   }
// }

// template <typename T>
// inline s21::List<T>::List(
//     std::initializer_list<value_type> const& items) noexcept
//     : _size(items.size()) {
//   for (const value_type& item : items) push_back(item);
// }
