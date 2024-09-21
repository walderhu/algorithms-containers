#if !defined(__S21_UNORDERED_SET_ITERATOR_HPP__)
#define __S21_UNORDERED_SET_ITERATOR_HPP__
#include "s21_unordered_set.hpp"

namespace s21 {

template <class Key>
inline unordered_set<Key>::Iterator::Iterator(
    IteratorType iter, size_t index, s21::unordered_set<value_type> *ust,
    BucketIterator bucket_iterator) noexcept
    : iter(iter), index(index), bucket_iterator(bucket_iterator), ust(ust) {}

template <class Key>
inline auto unordered_set<Key>::Iterator::get_value() const noexcept -> Key & {
  auto it = this->iter;
  for (auto &arr = *it; it != ust->table.end(); ++it)
    for (size_t i = this->index; i < unordered_set<Key>::TABLE_SIZE; i++)
      if (auto &vec = (*it)->at(i); !vec.empty())
        for (auto iter__ = (bucket_iterator != nullptr) ? bucket_iterator
                                                        : vec.begin();
             iter__ != vec.end(); ++iter__)
          return *iter__;
  return *bucket_iterator;
}

template <class Key>
inline auto unordered_set<Key>::Iterator::operator==(
    const Iterator &other) const noexcept -> bool {
  return this->get_value() == other.get_value();
}

template <class Key>
inline auto unordered_set<Key>::Iterator::operator!=(
    const Iterator &other) const noexcept -> bool {
  return this->get_value() != other.get_value();
}

template <class Key>
inline auto unordered_set<Key>::Iterator::operator*() const noexcept
    -> reference {
  return this->get_value();
}

template <class Key>
inline auto unordered_set<Key>::Iterator::operator=(const Iterator &other)
    -> Iterator & {
  if (this != &other) {
    this->iter = other.iter;
    this->index = other.index;
    this->bucket_iterator = other.bucket_iterator;
    this->ust = other.ust;
  }
  return *this;
}

template <class Key>
inline auto unordered_set<Key>::Iterator::operator++() noexcept -> Iterator & {
  if (auto &vec = (*iter)->at(index); bucket_iterator != vec.end()) {
    ++bucket_iterator;
  } else if (index < unordered_set<Key>::TABLE_SIZE) {
    bucket_iterator = nullptr;
    ++index;
  } else if (iter != ust->table.end()) {
    bucket_iterator = nullptr;
    index = 0u;
    ++iter;
  } else {
    index = unordered_set<Key>::TABLE_SIZE;
    iter = ust->table.end();
  }
  return *this;
}

// begin end
template <class Key>
inline auto unordered_set<Key>::begin() noexcept -> Iterator {
  return Iterator(table.begin(), 0u, this);
}

template <class Key>
inline auto unordered_set<Key>::end() noexcept -> Iterator {
  return Iterator(table.end(), TABLE_SIZE, this);
}

// template <class Key>
// inline void unordered_set<Key>::cbegin() noexcept -> Iterator {
//   return ConstIterator(table.begin(), 0u, this);
// }

// template <class Key>
// inline void unordered_set<Key>::cend() noexcept -> Iterator {
//   return ConstIterator(table.end(), TABLE_SIZE, this);
// }

}  // namespace s21

#endif  // __S21_UNORDERED_SET_ITERATOR_HPP__
