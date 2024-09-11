#include "s21_list.hpp"

template <typename value_type>
inline s21::list<value_type>::Node::Node(value_type value)
    : value(value), next(nullptr), prev(nullptr) {}

template <typename value_type>
inline s21::list<value_type>::Iterator::Iterator(
    Node* node, s21::list<value_type>* list) noexcept
    : current(node), list(list) {}

template <typename value_type>
inline s21::list<value_type>::Iterator::Iterator(Node* node) noexcept
    : current(node), list(nullptr) {}

template <typename value_type>
inline s21::list<value_type>::Iterator::Iterator() noexcept
    : current(nullptr) {}

template <typename value_type>
inline s21::list<value_type>::Iterator::Iterator(const Iterator& other) noexcept
    : current(other.current) {}

template <typename value_type>
inline auto s21::list<value_type>::Iterator::operator==(
    const Iterator& other) const -> bool {
  return current == other.current;
}

template <typename value_type>
inline auto s21::list<value_type>::Iterator::operator!=(
    const Iterator& other) const -> bool {
  return !(*this == other);
}

template <typename value_type>
inline auto s21::list<value_type>::Iterator::operator<(
    const Iterator& other) const -> bool {
  for (auto it = list->begin(); it != list->end(); ++it) {
    if (it == current) return true;
    if (it == other) return false;
  }
  throw std::out_of_range("Итератора не существует");
}

template <typename value_type>
inline auto s21::list<value_type>::Iterator::operator<=(
    const Iterator& other) const -> bool {
  return this->operator==(other) || this->operator<(other);
}

template <typename value_type>
inline auto s21::list<value_type>::Iterator::operator>(
    const Iterator& other) const -> bool {
  return !this->operator<(other);
}

template <typename value_type>
inline auto s21::list<value_type>::Iterator::operator>=(
    const Iterator& other) const -> bool {
  return this->operator==(other) || this->operator>(other);
}

template <typename value_type>
inline auto s21::list<value_type>::Iterator::operator*() const -> reference {
  return current->value;
}

template <typename value_type>
inline auto s21::list<value_type>::ConstIterator::operator*() const
    -> const_reference {
  return static_cast<const_reference>(Iterator::operator*());
}

template <typename value_type>
inline auto s21::list<value_type>::ConstIterator::operator=(
    const Iterator& other) -> Iterator& {
  (void)other;
  throw std::out_of_range("Cannot modify value through const_iterator");
  return *this;
}

template <typename value_type>
auto s21::list<value_type>::Iterator::operator++() -> Iterator& {
  if (current) current = current->next;
  return *this;
}

template <typename value_type>
inline auto s21::list<value_type>::Iterator::operator--() -> Iterator& {
  current = current ? current->prev : list->tail;
  return *this;
}

template <typename value_type>
inline auto s21::list<value_type>::Iterator::operator=(const Iterator& other)
    -> Iterator& {
  current = other.current;
  list = other.list;
  return *this;
}

template <typename value_type>
inline s21::list<value_type>::list() noexcept
    : head(nullptr), tail(nullptr), _size(0) {}

template <typename value_type>
inline s21::list<value_type>::list(size_type n) noexcept
    : s21::list<value_type>() {
  for (size_t i = 0; i < n; i++) push_front(value_type());
}

template <typename value_type>
inline s21::list<value_type>::list(const list& other) noexcept
    : head(nullptr), tail(nullptr), _size(0) {
  if (this != &other) {
    Node* current = other.head;
    while (current) {
      push_back(current->value);
      current = current->next;
    }
  }
}

template <typename value_type>
inline s21::list<value_type>::list(list&& other) noexcept
    : head(other.head), tail(other.tail), _size(other._size) {
  other.head = nullptr;
  other.tail = nullptr;
  other._size = 0;
}

template <typename value_type>
inline auto s21::list<value_type>::operator=(list&& other) noexcept
    -> s21::list<value_type>& {
  this->clear();

  this->head = other.head;
  this->tail = other.tail;
  this->_size = other._size;

  other.head = nullptr;
  other.tail = nullptr;
  other._size = 0;
  return *this;
}

template <typename value_type>
inline auto s21::list<value_type>::operator=(const list& other) noexcept
    -> s21::list<value_type>& {
  s21::list<value_type> new_list(other);
  *this = std::move(new_list);
  return *this;
}

template <typename value_type>
inline s21::list<value_type>::list(
    std::initializer_list<value_type> const& items) noexcept
    : s21::list<value_type>() {
  for (auto it = items.begin(); it != items.end(); ++it) push_back(*it);
}

template <typename value_type>
inline s21::list<value_type>::~list() noexcept {
  clear();
}

template <typename value_type>
inline auto s21::list<value_type>::size() const -> size_type {
  return _size;
}

template <typename value_type>
inline auto s21::list<value_type>::operator[](const int index) const
    -> reference {
  if (index < 0 || index >= _size)
    throw std::out_of_range("Index out of range");
  Node* current = head;
  for (int i = 0; i < index; ++i) current = current->next;
  return current->value;
}

template <typename value_type>
inline auto s21::list<value_type>::push_back(value_type value) -> void {
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

template <typename value_type>
inline auto s21::list<value_type>::empty() -> bool {
  return size() == 0;
}

template <typename value_type>
inline auto s21::list<value_type>::clear() -> void {
  while (_size) pop_front();
  tail = nullptr;
}

template <typename value_type>
inline auto s21::list<value_type>::begin() -> Iterator {
  return Iterator(this->head, this);
}

template <typename value_type>
inline auto s21::list<value_type>::end() -> Iterator {
  return Iterator(nullptr, this);
}

template <typename value_type>
inline auto s21::list<value_type>::cbegin() const -> ConstIterator {
  return ConstIterator(this->head, this);
}

template <typename value_type>
inline auto s21::list<value_type>::cend() const -> ConstIterator {
  return ConstIterator(nullptr, this);
}

namespace s21 {
template <typename value_type>
std::ostream& operator<<(std::ostream& os, const list<value_type>& obj) {
  for (auto it = obj.cbegin(); it != obj.cend(); ++it) os << *it << " ";
  return os;
}
}  // namespace s21

template <typename value_type>
inline auto s21::list<value_type>::print() -> void {
  for (auto it = begin(); it != end(); ++it) std::cout << *it << " ";
  std::cout << "\n";
}

template <typename value_type>
inline auto s21::list<value_type>::pop_front() -> void {
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

template <typename value_type>
inline auto s21::list<value_type>::push_front(value_type value) -> void {
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

template <typename value_type>
inline auto s21::list<value_type>::pop_back() -> void {
  if (head) {
    Node* tmp = tail;

    if (tail == head) {
      head = nullptr;
      tail = nullptr;
    } else {
      tail = tail->prev;
      tail->next = nullptr;
    }

    delete tmp;
    _size--;
  }
}

template <typename value_type>
inline auto s21::list<value_type>::reverse() -> void {
  if (this->size() < 2) return;
  list<value_type> new_list;
  for (auto it = this->begin(); it != this->end(); ++it)
    new_list.push_front(*it);
  *this = std::move(new_list);
}

template <typename value_type>
inline auto s21::list<value_type>::front() -> const_reference {
  if (head == nullptr) throw std::out_of_range("List is empty");
  return head->value;
}

template <typename value_type>
inline auto s21::list<value_type>::back() -> const_reference {
  if (tail == nullptr) throw std::out_of_range("List is empty");
  return tail->value;
}

template <typename value_type>
inline auto s21::list<value_type>::max_size() -> size_type {
  return (std::numeric_limits<size_t>::max() / sizeof(value_type)) / 2;
}

template <typename value_type>
inline auto s21::list<value_type>::sort() -> void {
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

template <typename value_type>
inline auto s21::list<value_type>::swap(list& other) noexcept -> void {
  std::swap(head, other.head);
  std::swap(tail, other.tail);
  std::swap(size, other.size);
}

template <typename value_type>
inline auto s21::list<value_type>::merge(list& other) -> void {
  for (auto it = other.begin(); it != other.end(); ++it) this->push_back(*it);
}

template <typename value_type>
inline auto s21::list<value_type>::insert(iterator pos,
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

template <typename value_type>
inline auto s21::list<value_type>::insert(
    iterator pos, std::initializer_list<value_type> const& items) -> iterator {
  for (auto item = items.end(); item != items.begin();) {
    --item;
    pos = insert(pos, *item);
  }
  return pos;
}

template <typename value_type>
inline auto s21::list<value_type>::erase(iterator pos) -> void {
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

template <typename value_type>
inline auto s21::list<value_type>::splice(const_iterator pos,
                                          list& other) -> void {
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

template <typename value_type>
inline auto s21::list<value_type>::unique() -> void {
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