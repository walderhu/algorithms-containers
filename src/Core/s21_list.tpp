#include "s21_list.hpp"

template <typename T>
inline s21::List<T>::Node::Node(T value)
    : value(value), next(nullptr), prev(nullptr) {}

template <typename T>
inline s21::List<T>::Iterator::Iterator(Node* n) : current(n) {}

template <typename T>
inline bool s21::List<T>::Iterator::operator==(const Iterator& other) {
  return current == other.current;
}

template <typename T>
inline bool s21::List<T>::Iterator::operator!=(const Iterator& other) {
  return !(*this == other);
}

template <typename T>
inline typename s21::List<T>::reference s21::List<T>::Iterator::operator*() {
  return current->value;
}

template <typename T>
typename s21::List<T>::Iterator& s21::List<T>::Iterator::operator++() {
  current = current->next;
  return *this;
}

template <typename T>
typename s21::List<T>::Iterator& s21::List<T>::Iterator::operator--() {
  current = current->prev;
  return *this;
}

template <typename T>
inline s21::List<T>::ConstIterator::ConstIterator(Node* n) : current(n) {}

template <typename T>
inline bool s21::List<T>::ConstIterator::operator==(
    const ConstIterator& other) const {
  return current == other.current;
}

template <typename T>
inline bool s21::List<T>::ConstIterator::operator!=(
    const ConstIterator& other) const {
  return !(*this == other);
}

template <typename T>
inline typename s21::List<T>::const_reference
s21::List<T>::ConstIterator::operator*() const {
  return current->value;
}

template <typename T>
typename s21::List<T>::ConstIterator&
s21::List<T>::ConstIterator::operator++() {
  current = current->next;
  return *this;
}

template <typename T>
typename s21::List<T>::ConstIterator&
s21::List<T>::ConstIterator::operator--() {
  current = current->prev;
  return *this;
}

template <typename T>
inline s21::List<T>::List() noexcept : head(nullptr), tail(nullptr), _size(0) {}

template <typename T>
inline s21::List<T>::List(size_type n) noexcept : s21::List<T>() {
  this->_size = n;
  for (size_t i = 0; i < size(); i++) push_front(T());
}

// TODO проверить на наличие утечек памяти, если вызывать clear() то
// munmap_chunk(): invalid pointer
template <typename T>
inline s21::List<T>::List(const List& other) noexcept
    : head(nullptr), tail(nullptr), _size(0) {
  if (this != &other) {
    Node* current = other.head;
    while (current) {
      push_back(current->value);
      current = current->next;
    }
  }
}

// Конструктор перемещения
template <typename T>
inline s21::List<T>::List(List&& other) noexcept {
  this->clear();

  this->head = other.head;
  this->tail = other.tail;
  this->_size = other._size;

  other.head = nullptr;
  other.tail = nullptr;
  other._size = 0;
}

template <typename T>
inline s21::List<T>& s21::List<T>::operator=(List&& other) noexcept {
  this->clear();

  this->head = other.head;
  this->tail = other.tail;
  this->_size = other._size;

  other.head = nullptr;
  other.tail = nullptr;
  other._size = 0;
  return *this;
}

template <typename T>
inline s21::List<T>::List(
    std::initializer_list<value_type> const& items) noexcept
    : s21::List<T>() {
  for (auto it = items.begin(); it != items.end(); ++it) push_back(*it);
}

template <typename T>
inline s21::List<T>::~List() noexcept {
  clear();
}

template <typename T>
inline typename s21::List<T>::size_type s21::List<T>::size() const {
  return _size;
}

template <typename T>
inline typename s21::List<T>::reference s21::List<T>::operator[](
    const int index) const {
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

template <typename T>
void s21::List<T>::clear() {
  while (_size) pop_front();
  tail = nullptr;
}

template <typename T>
typename s21::List<T>::Iterator s21::List<T>::begin() {
  return Iterator(this->head);
}

template <typename T>
typename s21::List<T>::Iterator s21::List<T>::end() {
  return Iterator(nullptr);
}

template <typename T>
typename s21::List<T>::ConstIterator s21::List<T>::cbegin() const {
  return ConstIterator(this->head);
}

template <typename T>
typename s21::List<T>::ConstIterator s21::List<T>::cend() const {
  return ConstIterator(nullptr);
}
//

namespace s21 {

template <typename T>
std::ostream& operator<<(std::ostream& os, const List<T>& obj) {
  typename List<T>::Node* current = obj.head;
  while (current) {
    os << current->value << " ";
    current = current->next;
  }
  return os;
}

}  // namespace s21

template <typename T>
void s21::List<T>::print() {
  for (auto it = begin(); it != end(); ++it) std::cout << *it << " ";
  std::cout << "\n";
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
  if (this->size() < 2) return;
  List<T> new_list;
  for (auto it = this->begin(); it != this->end(); ++it)
    new_list.push_front(*it);
  *this = std::move(new_list);
}

template <typename T>
inline typename s21::List<T>::const_reference s21::List<T>::front() {
  return head->value;
}

// template <typename T>
// inline auto s21::List<T>::front() -> const_reference {
// return head->value;
// }

template <typename T>
inline typename s21::List<T>::const_reference s21::List<T>::back() {
  return tail->value;
}

template <typename T>
inline typename s21::List<T>::size_type s21::List<T>::max_size() {
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

template <typename T>
inline auto s21::List<T>::swap(List& other) noexcept -> void {
  std::swap(head, other.head);
  std::swap(tail, other.tail);
  std::swap(size, other.size);
}

template <typename T>
inline auto s21::List<T>::merge(List& other) -> void {
  for (auto it = other.begin(); it != other.end(); ++it) this->push_back(*it);
}

template <typename T>
inline auto s21::List<T>::insert(iterator pos,
                                 const_reference value) -> iterator {
  Node* new_node = new Node(value);

  if (pos == begin()) {
    new_node->next = head;
    if (head) head->prev = new_node;
    head = new_node;
  } else {
    Node* current = pos.current;
    Node* previous = current->prev;

    new_node->next = current;
    new_node->prev = previous;

    if (previous) previous->next = new_node;
    current->prev = new_node;
  }

  if (pos == end()) tail = new_node;
  this->_size++;
  return new_node;
}

template <typename T>
inline auto s21::List<T>::insert(
    iterator pos, std::initializer_list<value_type> const& items) -> iterator {
  for (auto item = items.end(); item != items.begin();) {
    --item;
    pos = insert(pos, *item);
  }
  return pos;
}

template <typename T>
inline auto s21::List<T>::erase(iterator pos) -> void {
  if (pos == end()) throw std::out_of_range("Cannot erase end iterator");

  Node* current = pos.current;
  Node* prev = current->prev;
  Node* next = current->next;

  if (prev == nullptr)
    head = next;
  else
    prev->next = next;

  if (next == nullptr)
    tail = prev;
  else
    next->prev = prev;

  delete current;
  _size -= 1;
}

template <typename T>
inline auto s21::List<T>::splice(const_iterator pos, List& other) -> void {
  if (pos == end()) throw std::out_of_range("Cannot splice at end iterator");
  if (other.empty()) return;
  auto other_begin = other.begin();
  auto other_end = other.end();

  for (auto it = other_end; it != other_begin;) {
    --it;
    insert(pos, *it);
  }
  other.clear();
}

template <typename T>
inline auto s21::List<T>::unique() -> void {
  if (this->empty()) return;

  for (iterator it = this->begin(); it != this->end();) {
    Node* current = it.current;

    if (current->next && current->value == current->next->value) {
      Node* next = current->next;
      this->erase(it);
      it = iterator(next);
    } else {
      ++it;
    }
  }
}