#if !defined(__S21_UNORDERED_SET_ITERATOR_HPP__)
#define __S21_UNORDERED_SET_ITERATOR_HPP__
#include "s21_unordered_set.hpp"

namespace s21 {

template <class Key>
inline unordered_set<Key>::Iterator::Iterator(
    IteratorType lst_iter, size_t bucket_index,
    s21::unordered_set<value_type> *ust)
    : lst_iter(lst_iter), bucket_index(bucket_index), ust(ust) {
  if (lst_iter == ust->table.end()) {
    bucket_iterator = BucketIterator();
    return;
  } else if (bucket_index < TABLE_SIZE) {
    ArrayType &table = *lst_iter;
    BucketType &bucket = table->at(bucket_index);
    bucket_iterator = bucket.begin();
  } else {
    throw std::runtime_error("Размер таблицы превышает заданный");
  }
}

template <class Key>
inline auto unordered_set<Key>::Iterator::get_value() const -> Key & {
  return *bucket_iterator;
}

template <class Key>
inline auto unordered_set<Key>::Iterator::operator==(
    const Iterator &other) const -> bool {
  return lst_iter == other.lst_iter && bucket_index == other.bucket_index &&
         bucket_iterator == other.bucket_iterator;
}

template <class Key>
inline auto unordered_set<Key>::Iterator::operator!=(
    const Iterator &other) const -> bool {
  return !this->operator==(other);
}

template <class Key>
inline auto unordered_set<Key>::Iterator::operator++() -> Iterator & {
  if (lst_iter == ust->table.end()) throw std::runtime_error("No table.");

  if (bucket_index >= TABLE_SIZE) {
    if (IteratorType it = ++lst_iter; it != ust->table.end()) {
      ArrayType table = *it;
      bucket_index = 0u;
      BucketType &bucket = table->at(bucket_index);
      bucket_iterator = bucket.begin();
      return this->operator++();
    } else if (lst_iter == ust->table.end()) {
      bucket_iterator = BucketIterator();
      return *this;
    }
  }

  ArrayType &table = *lst_iter;
  BucketType &bucket = table->at(bucket_index);
  if (bucket.empty()) {
    move_next(table, bucket);
  } else {
    ++bucket_iterator;
    move_next(table, bucket);
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
inline auto unordered_set<Key>::Iterator::operator*() -> reference {
  this->if_end();
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
inline auto unordered_set<Key>::Iterator::if_end() -> void {
  if (lst_iter == ust->table.end() && bucket_index == TABLE_SIZE &&
      bucket_iterator == BucketIterator()) {
    bucket_index = TABLE_SIZE - 1;
    --lst_iter;
    ArrayType &table = *lst_iter;
    BucketType &bucket = table->at(bucket_index);
    move_prev(table, bucket, true);
  }
}

template <class Key>
inline auto unordered_set<Key>::Iterator::move_prev(ArrayType &table,
                                                    std::vector<Key> &bucket,
                                                    bool current) -> void {
  if (bucket = table->at(bucket_index); current && !bucket.empty()) {
    bucket_iterator = --bucket.end();
  } else if (--bucket_index < TABLE_SIZE)
    move_prev(table, bucket, true);
}

template <class Key>
inline auto unordered_set<Key>::Iterator::operator--() -> Iterator & {
  this->if_end();

  if (bucket_index == 0 || bucket_index >= TABLE_SIZE) {
    PRINT("Декремент от начала сета");
    IteratorType it = --lst_iter;
    bucket_index = TABLE_SIZE - 1;
    ArrayType table = *it;
    BucketType &bucket = table->at(bucket_index);
    move_prev(table, bucket, true);
    return *this;
  }

  ArrayType &table = *lst_iter;
  BucketType &bucket = table->at(bucket_index);
  move_prev(table, bucket, bucket.empty());

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
