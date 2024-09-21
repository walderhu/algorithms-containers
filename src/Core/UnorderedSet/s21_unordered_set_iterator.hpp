#if !defined(__S21_UNORDERED_SET_ITERATOR_HPP__)
#define __S21_UNORDERED_SET_ITERATOR_HPP__
#include "s21_unordered_set.hpp"

namespace s21 {

template <class Key>
inline unordered_set<Key>::Iterator::Iterator(
    IteratorType iter, size_t index, s21::unordered_set<value_type> *ust)
    : iter(iter), index(index), ust(ust) {}

template <class Key>
inline auto unordered_set<Key>::Iterator::get_value() const -> Key & {
  if (iter == ust->table.end())
    throw std::runtime_error("Ошибка: Итератор достиг конца контейнера.");

  auto &arr = *iter;
  if (index >= unordered_set<Key>::TABLE_SIZE)
    throw std::runtime_error("Ошибка: Индекс вне диапазона.");

  auto &vec = (*iter)->at(index);
  if (vec.empty()) throw std::runtime_error("Ошибка: Вектор пуст.");

  return static_cast<Key &>(vec.front());
}

// template <class Key>
// inline auto unordered_set<Key>::Iterator::get_value() const -> Key & {
//   if (auto &arr = *iter; iter != ust->table.end())
//     if (size_t i = this->index; i < unordered_set<Key>::TABLE_SIZE)
//       if (auto &vec = (*iter)->at(i); !vec.empty())
//         if (auto iter__ = vec.begin(); iter__ != vec.end()) return *iter__;
//   throw std::runtime_error("Ошибка: Элемент не найден.");
// }

// template <class Key>
// inline auto unordered_set<Key>::Iterator::get_value() const  -> Key &
// {
//   auto it = this->iter;
//   for (auto &arr = *it; it != ust->table.end(); ++it)
//     for (size_t i = this->index; i < unordered_set<Key>::TABLE_SIZE; i++)
//       if (auto &vec = (*it)->at(i); !vec.empty())
//         for (auto iter__ = (bucket_iterator != nullptr) ? bucket_iterator
//                                                         : vec.begin();
//              iter__ != vec.end(); ++iter__)
//           return *iter__;
//   return *bucket_iterator;
//   // DEBUG("hello");
// }

template <class Key>
inline auto unordered_set<Key>::Iterator::operator==(
    const Iterator &other) const -> bool {
  return this->iter == other.iter;
}

template <class Key>
inline auto unordered_set<Key>::Iterator::operator!=(
    const Iterator &other) const -> bool {
  return this->iter != other.iter;
}

template <class Key>
inline auto unordered_set<Key>::Iterator::operator*() const -> reference {
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
inline auto unordered_set<Key>::Iterator::operator++() -> Iterator & {
  // if (auto &vec = (*iter)->at(index); bucket_iterator != vec.end()) {
  // ++bucket_iterator;
  // } else

  if (index < unordered_set<Key>::TABLE_SIZE) {
    // bucket_iterator = nullptr;
    // this->bucket_iterator = *((*ust->table->begin())->at(0).begin());
    ++index;
  } else if (iter != ust->table.end()) {
    // bucket_iterator = nullptr;
    // this->bucket_iterator = *((*ust->table->begin())->at(0).begin());

    index = 0u;
    ++iter;
  } else {
    index = unordered_set<Key>::TABLE_SIZE;
    iter = ust->table.end();
  }
  return *this;
}

// begin end
// template <class Key>
// inline auto unordered_set<Key>::begin() noexcept -> Iterator {
//   return Iterator(table.begin(), 0u, this);
// }

// template <class Key>
// inline auto unordered_set<Key>::begin() noexcept -> Iterator {
//   auto it = table.begin();
//   DEBUG("hey");
//   if (it == table.end()) return Iterator(it, TABLE_SIZE, this);
//   for (auto &arr = *it; it != table.end(); ++it)
//     for (size_t i = 0; i < TABLE_SIZE; ++i)
//       if (!arr[i].empty()) return Iterator(it, i, this);

//   DEBUG("hey");
//   return Iterator(table.end(), TABLE_SIZE, this);
// }

template <class Key>
inline auto unordered_set<Key>::begin() noexcept -> Iterator {
  auto it = table.begin();
  DEBUG("Begin called");

  if (it == table.end()) {
    DEBUG("Table is empty");
    return Iterator(it, TABLE_SIZE, this);
  }

  for (auto &arr = *it; it != table.end(); ++it)
    for (size_t i = 0; i < TABLE_SIZE; ++i)
      if (!arr[i].empty()) {
        DEBUG("BEGIN is OK");
        return Iterator(it, i, this);
      }

  DEBUG("No non-empty buckets found");
  return Iterator(table.end(), TABLE_SIZE, this);
}

/*
 передаю итератор на начало листа, итератор на индекс баккета,
 и ссылку на текущий класс я не передаю индексы на положение
 внутри бакета, только сам бакет
 */

template <class Key>
inline auto unordered_set<Key>::end() noexcept -> Iterator {
  return Iterator(table.end(), TABLE_SIZE, this);
}

// template <class Key>
// inline void unordered_set<Key>::cbegin()  -> Iterator {
//   return ConstIterator(table.begin(), 0u, this);
// }

// template <class Key>
// inline void unordered_set<Key>::cend()  -> Iterator {
//   return ConstIterator(table.end(), TABLE_SIZE, this);
// }

}  // namespace s21

#endif  // __S21_UNORDERED_SET_ITERATOR_HPP__
