#include "s21_list.hpp"

template <class value_type>
inline s21::list<value_type>::Iterator::Iterator(
    Node* node, s21::list<value_type>* list) noexcept
    : current(node), list(list) {}

template <class value_type>
inline s21::list<value_type>::Iterator::Iterator(Node* node) noexcept
    : current(node), list(nullptr) {}

template <class value_type>
inline s21::list<value_type>::Iterator::Iterator() noexcept
    : current(nullptr), list(nullptr) {}

template <class value_type>
inline s21::list<value_type>::Iterator::Iterator(const Iterator& other) noexcept
    : current(other.current), list(other.list) {}

template <class value_type>
inline auto s21::list<value_type>::Iterator::operator==(
    const Iterator& other) const -> bool {
  return current == other.current;
}

template <class value_type>
inline auto s21::list<value_type>::Iterator::operator!=(
    const Iterator& other) const -> bool {
  return !(*this == other);
}

template <class value_type>
inline auto s21::list<value_type>::Iterator::operator<(
    const Iterator& other) const -> bool {
  for (auto it = list->begin(); it != list->end(); ++it) {
    if (it == current) return true;
    if (it == other) return false;
  }
  throw std::out_of_range("Disabled iterator. Not exist");
}

template <class value_type>
inline auto s21::list<value_type>::Iterator::operator<=(
    const Iterator& other) const -> bool {
  return this->operator==(other) || this->operator<(other);
}

template <class value_type>
inline auto s21::list<value_type>::Iterator::operator>(
    const Iterator& other) const -> bool {
  return !this->operator<(other);
}

template <class value_type>
inline auto s21::list<value_type>::Iterator::operator>=(
    const Iterator& other) const -> bool {
  return this->operator==(other) || this->operator>(other);
}

template <class value_type>
inline auto s21::list<value_type>::Iterator::operator*() const -> reference {
  return current->value;
}

template <class value_type>
inline auto s21::list<value_type>::ConstIterator::operator*() const
    -> const_reference {
  return static_cast<const_reference>(Iterator::operator*());
}

template <class value_type>
inline s21::list<value_type>::ConstIterator::ConstIterator(
    Node* node, const s21::list<value_type>* lst) noexcept
    : Iterator(node, const_cast<s21::list<value_type>*>(lst)) {}

template <class value_type>
inline s21::list<value_type>::ConstIterator::ConstIterator(
    iterator it) noexcept {
  Iterator::current = it.current;
  Iterator::list = it.list;
}

template <class value_type>
inline auto s21::list<value_type>::ConstIterator::operator=(
    const Iterator& other) -> Iterator& {
  (void)other;
  throw std::out_of_range("Cannot modify value through const_iterator");
  return *this;
}

template <class value_type>
auto s21::list<value_type>::Iterator::operator++() -> Iterator& {
  if (current) current = current->next;
  return *this;
}

template <class value_type>
inline auto s21::list<value_type>::Iterator::operator--() -> Iterator& {
  current = current ? current->prev : list->tail;
  return *this;
}

template <class value_type>
inline auto s21::list<value_type>::Iterator::operator=(const Iterator& other)
    -> Iterator& {
  current = other.current;
  list = other.list;
  return *this;
}

template <class value_type>
inline s21::list<value_type>::list(const list& other) noexcept {
  s21::deque<value_type>::head = nullptr;
  s21::deque<value_type>::tail = nullptr;

  deque<value_type>::_size = 0;
  if (this != &other) {
    Node* current = other.head;
    while (current) {
      s21::deque<value_type>::push_back(current->value);
      current = current->next;
    }
  }
}

template <class value_type>
inline s21::list<value_type>::list(list&& other) noexcept {
  s21::deque<value_type>::head = other.head;
  s21::deque<value_type>::tail = other.tail;

  deque<value_type>::_size = other._size;
  other.head = nullptr;
  other.tail = nullptr;
  other.deque<value_type>::_size = 0;
}

template <class value_type>
inline auto s21::list<value_type>::operator=(list&& other) noexcept
    -> s21::list<value_type>& {
  this->clear();

  s21::deque<value_type>::head = other.head;
  s21::deque<value_type>::tail = other.tail;
  this->deque<value_type>::_size = other.deque<value_type>::_size;

  other.head = nullptr;
  other.tail = nullptr;
  other.deque<value_type>::_size = 0;
  return *this;
}

template <class value_type>
inline auto s21::list<value_type>::operator=(const list& other) noexcept
    -> s21::list<value_type>& {
  s21::list<value_type> new_list(other);
  *this = std::move(new_list);
  return *this;
}

template <class value_type>
inline s21::list<value_type>::list(
    std::initializer_list<value_type> const& items) noexcept
    : s21::deque<value_type>() {
  for (auto it = items.begin(); it != items.end(); ++it)
    s21::deque<value_type>::push_back(*it);
}

template <class value_type>
inline auto s21::list<value_type>::operator[](const int index) const
    -> reference {
  if (index < 0 || index >= deque<value_type>::_size)
    throw std::out_of_range("Index out of range");
  Node* current = s21::deque<value_type>::head;
  for (int i = 0; i < index; ++i) current = current->next;
  return current->value;
}

template <class value_type>
inline auto s21::list<value_type>::begin() -> Iterator {
  return Iterator(s21::deque<value_type>::head, this);
}

template <class value_type>
inline auto s21::list<value_type>::end() -> Iterator {
  return Iterator(nullptr, this);
}

template <class value_type>
inline auto s21::list<value_type>::cbegin() const -> ConstIterator {
  return ConstIterator(s21::deque<value_type>::head, this);
}

template <class value_type>
inline auto s21::list<value_type>::cend() const -> ConstIterator {
  return ConstIterator(nullptr, this);
}

namespace s21 {
template <class value_type>
std::ostream& operator<<(std::ostream& os, const list<value_type>& obj) {
  for (auto it = obj.cbegin(); it != obj.cend(); ++it) os << *it << " ";
  return os;
}
}  // namespace s21

template <class value_type>
inline auto s21::list<value_type>::print() -> void {
  for (auto it = begin(); it != end(); ++it) std::cout << *it << " ";
  std::cout << "\n";
}

template <class value_type>
inline auto s21::list<value_type>::reverse() -> void {
  if (this->size() < 2) return;
  list<value_type> new_list;
  for (auto it = this->begin(); it != this->end(); ++it)
    new_list.push_front(*it);
  *this = std::move(new_list);
}

template <class value_type>
inline auto s21::list<value_type>::sort() -> void {
  Node* current = s21::deque<value_type>::head;
  bool swapped = true;

  while (swapped) {
    swapped = false;
    current = s21::deque<value_type>::head;

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

template <class value_type>
inline auto s21::list<value_type>::swap(list& other) noexcept -> void {
  std::swap(s21::deque<value_type>::head, other.head);
  std::swap(s21::deque<value_type>::tail, other.tail);
  std::swap(s21::deque<value_type>::_size, other._size);
}

template <class value_type>
inline auto s21::list<value_type>::merge(list& other) -> void {
  Node* current = other.head;
  this->push_back(current);
  s21::deque<value_type>::tail = other.tail;
  this->deque<value_type>::_size += other.deque<value_type>::_size - 1;

  other.head = nullptr;
  other.tail = nullptr;
  other.deque<value_type>::_size = 0;
}

template <class value_type>
inline auto s21::list<value_type>::insert(iterator pos, const_reference value)
    -> iterator {
  Node* new_node = new Node(value);

  if (pos == this->begin()) {
    this->push_front(new_node);
  } else if (pos == this->end()) {
    this->push_back(new_node);
  } else {
    Node* current = pos.current;
    Node* previous = current->prev;

    new_node->next = current;
    new_node->prev = previous;

    if (previous) previous->next = new_node;
    if (current) current->prev = new_node;

    this->deque<value_type>::_size++;
  }
  return new_node;
}

template <class value_type>
inline auto s21::list<value_type>::insert(
    iterator pos, std::initializer_list<value_type> const& items) -> iterator {
  for (auto item = items.end(); item != items.begin();) {
    --item;
    pos = insert(pos, *item);
  }
  return pos;
}

template <class value_type>
inline auto s21::list<value_type>::erase(iterator pos) -> void {
  if (pos == end()) throw std::out_of_range("Cannot erase end iterator");

  Node* current = pos.current;
  Node* prev = current->prev;
  Node* next = current->next;

  if (prev == nullptr)
    s21::deque<value_type>::head = next;
  else
    prev->next = next;

  if (next == nullptr)
    s21::deque<value_type>::tail = prev;
  else
    next->prev = prev;

  delete current;
  deque<value_type>::_size -= 1;
}

template <class value_type>
inline auto s21::list<value_type>::splice(const_iterator pos, list& other)
    -> void {
  if (pos == end()) throw std::out_of_range("Cannot splice at end iterator");
  if (other.empty()) return;
  auto other_begin = other.begin();
  auto other_end = other.end();

  for (auto it = other_begin; it != other_end; ++it) insert(pos, *it);
  other.clear();
}

template <class value_type>
inline auto s21::list<value_type>::splice(iterator pos, list& other) -> void {
  const_iterator it(pos);
  this->splice(it, other);
}

template <class value_type>
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

template <class T>
template <typename... Args>
typename s21::list<T>::iterator s21::list<T>::insert_many(const_iterator pos,
                                                          Args&&... args) {
  iterator var_pos = iterator(const_cast<Node*>(pos.current));
  (this->insert(var_pos, std::forward<Args>(args)), ...);
  return var_pos;
}

template <class T>
template <typename... Args>
void s21::list<T>::insert_many_back(Args&&... args) {
  (this->push_back(std::forward<Args>(args)), ...);
}

template <class T>
template <typename... Args>
void s21::list<T>::insert_many_front(Args&&... args) {
  (this->push_front(std::forward<Args>(args)), ...);
}
