#if !defined(__S21_UNORDERED_SET_ITERATOR_HPP__)
#define __S21_UNORDERED_SET_ITERATOR_HPP__
#include "s21_unordered_set.hpp"

namespace s21 {

template <class Key>
inline unordered_set<Key>::Iterator::Iterator(
    IteratorType lst_iter, size_t bucket_index,
    s21::unordered_set<value_type> *ust)
    : lst_iter(lst_iter), bucket_index(bucket_index), ust(ust) {
  if (lst_iter == ust->table.end()) return;
  if (bucket_index >= TABLE_SIZE)
    throw std::runtime_error("Размер таблицы превышает заданный");

  auto &vec = (*lst_iter)->at(bucket_index);
  bucket_iterator = vec.begin();
}

template <class Key>
inline auto unordered_set<Key>::Iterator::get_value() const -> Key & {
  // auto &arr = *lst_iter;
  // auto &vec = arr->at(bucket_index);
  // if (auto iter = vec.begin(); iter != vec.end()) return *iter;
  // throw std::runtime_error("Ошибка: Элемент не найден.");

  return *bucket_iterator;
}

template <class Key>
inline auto unordered_set<Key>::Iterator::operator==(
    const Iterator &other) const -> bool {
  return lst_iter == other.lst_iter && bucket_index == other.bucket_index;
}

template <class Key>
inline auto unordered_set<Key>::Iterator::operator!=(
    const Iterator &other) const -> bool {
  return !this->operator==(other);
}

template <class Key>
inline auto unordered_set<Key>::Iterator::operator++() -> Iterator & {
  if (lst_iter == ust->table.end()) throw std::runtime_error("Нет таблицы.");

  if (bucket_index >= TABLE_SIZE)
    if (auto table = *(++lst_iter); lst_iter != ust->table.end()) {
      bucket_index = 0u;
      bucket_iterator = (table->at(bucket_index)).begin();
      return this->operator++();
    }

  auto table = *lst_iter;
  std::vector<Key> bucket = table->at(bucket_index);
  if (bucket.empty()) {
    move_next(table, bucket);
  } else {
    if (++bucket_iterator; bucket_iterator == bucket.end()) {
      // ++bucket_iterator;
      move_next(table, bucket);
    }
  }
  return *this;
}

template <class Key>
inline auto unordered_set<Key>::Iterator::move_next(
    ArrayType &table, std::vector<Key> &bucket) -> void {
  while (++bucket_index < TABLE_SIZE)
    if (bucket = table->at(bucket_index); !bucket.empty()) {
      bucket_iterator = bucket.begin();
      break;
    }
  if (bucket_index == TABLE_SIZE) this->operator++();
}

template <class Key>
inline auto unordered_set<Key>::Iterator::operator*() const -> reference {
  return get_value();
}

template <class Key>
inline auto unordered_set<Key>::Iterator::operator=(const Iterator &other)
    -> Iterator & {
  if (this != &other) {
    this->lst_iter = other.lst_iter;
    this->bucket_index = other.bucket_index;
    this->bucket_iterator = other.bucket_iterator;
    this->ust = other.ust;
  }
  return *this;
}

template <class Key>
inline auto unordered_set<Key>::begin() noexcept -> Iterator {
  auto it = table.begin();
  if (it == table.end()) return Iterator(it, TABLE_SIZE, this);

  size_t bucket_index = 0;
  for (auto &table = *it; it != this->table.end(); ++it)
    for (size_t i = 0; bucket_index < TABLE_SIZE; ++bucket_index)
      if (auto bucket = table->at(bucket_index); !bucket.empty())
        return Iterator(it, bucket_index, this);

  return Iterator(table.end(), TABLE_SIZE, this);
}

template <class Key>
inline auto unordered_set<Key>::end() noexcept -> Iterator {
  return Iterator(table.end(), TABLE_SIZE, this);
}

}  // namespace s21

#endif  // __S21_UNORDERED_SET_ITERATOR_HPP__
