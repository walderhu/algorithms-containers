#if !defined(__S21_UNORDERED_SET_ITERATOR_HPP__)
#define __S21_UNORDERED_SET_ITERATOR_HPP__
#include "s21_unordered_set.hpp"

namespace s21 {

template <class Key>
inline unordered_set<Key>::Iterator::Iterator(
    IteratorType lst_iter, size_t arr_index,
    s21::unordered_set<value_type> *ust)
    : lst_iter(lst_iter), arr_index(arr_index), ust(ust) {
  auto &vec = (*lst_iter)->at(arr_index);
  bucket_iterator = vec.begin();
}

// template <class Key>
// inline auto unordered_set<Key>::Iterator::get_value() const -> Key & {
//   if (auto &arr = *lst_iter; lst_iter != ust->table.end())
//     if (size_t i = this->arr_index; i < unordered_set<Key>::TABLE_SIZE)
//       if (auto &vec = (*lst_iter)->at(i); !vec.empty())
//         if (auto iter__ = vec.begin(); iter__ != vec.end()) return *iter__;
//   throw std::runtime_error("Ошибка: Элемент не найден.");
// }

template <class Key>
inline auto unordered_set<Key>::Iterator::get_value() const -> Key & {
  if (auto &arr = *lst_iter; lst_iter != ust->table.end())
    if (arr_index < TABLE_SIZE)
      if (auto &vec = arr->at(arr_index); !vec.empty())
        if (auto iter = vec.begin(); iter != vec.end()) return *iter;
  throw std::runtime_error("Ошибка: Элемент не найден.");
}

/*
По сути эти лишние условия вообще не нужны тут, мне кажется
после норм написания инкремента, все эти условаия можно будет убрать
оставивив что нибудь похожее на код ниже
*/

// template <class Key>
// inline auto unordered_set<Key>::Iterator::get_value() const -> Key & {
//   if (bucket_iterator == (*lst_iter)->at(arr_index).end()) {
//     throw std::runtime_error(
//         "Ошибка: Итератор находится в недопустимом состоянии.");
//   }

//   return *bucket_iterator;
// }

template <class Key>
inline auto unordered_set<Key>::Iterator::operator==(
    const Iterator &other) const -> bool {
  return lst_iter == other.lst_iter && arr_index == other.arr_index &&
         bucket_iterator == other.bucket_iterator;
}

/*
  auto lst_it = table.begin();
  for (auto &arr = *lst_it; lst_it != table.end(); ++lst_it)
    for (size_t i = 0u; i < TABLE_SIZE; i++)
      if (auto &vec = arr->at(i); !vec.empty())
        for (auto iter = vec.begin(); iter != vec.end(); ++iter)
          std::cout << *iter << " ";

  std::cout << std::endl;
*/

template <class Key>
inline auto unordered_set<Key>::Iterator::operator++() -> Iterator & {
  auto &arr = *lst_iter;
  auto &vec = arr->at(arr_index);
  bucket_iterator;
  // here
  //  if (++bucket_iterator == vec.end())
  //  ;
  //
  /*
    if (auto &arr = *lst_iter; lst_iter != ust->table.end())
    if (arr_index < TABLE_SIZE)
      if (auto &vec = arr->at(arr_index); !vec.empty())
        if (auto iter = vec.begin(); iter != vec.end()) return *iter;
  throw std::runtime_error("Ошибка: Элемент не найден.");
  */
  // if (auto &arr = *lst_iter; lst_iter != ust->table.end())
  // if (size_t i = arr_index; i < TABLE_SIZE)
  // if (auto &vec = arr->at(i); !vec.empty())
  // if (auto iter = vec.begin(); iter != vec.end()) return *iter;
  // throw std::runtime_error("Ошибка: Элемент не найден.");
  return *this;
}
// auto lst_it = lst_iter;
// if (auto &arr = *lst_it; lst_it != ust->table.end())
//   if (size_t i = arr_index; i < TABLE_SIZE)
//     if (auto &vec = arr->at(i); !vec.empty())
//       if (auto iter = vec.begin(); iter != vec.end()) return *iter;
// throw std::runtime_error("Ошибка: Элемент не найден.");

// template <class Key>
// inline auto unordered_set<Key>::Iterator::operator++() -> Iterator & {
//   if (bucket_iterator != (*lst_iter)->at(arr_index).end()) {
//     ++bucket_iterator;
//   } else if (arr_index < unordered_set<Key>::TABLE_SIZE) {
//     bucket_iterator = (*lst_iter)->at(++arr_index).begin();
//   } else if (lst_iter != ust->table.end()) {
//     bucket_iterator = (*ust->table.begin())->at(0).end();
//     arr_index = 0u;
//     ++lst_iter;
//   } else {
//     arr_index = unordered_set<Key>::TABLE_SIZE;
//     lst_iter = ust->table.end();
//   }
//   return *this;
// }

template <class Key>
inline auto unordered_set<Key>::Iterator::operator!=(
    const Iterator &other) const -> bool {
  return !this->operator==(other);
}

template <class Key>
inline auto unordered_set<Key>::Iterator::operator*() const -> reference {
  return this->get_value();
}

template <class Key>
inline auto unordered_set<Key>::Iterator::operator=(const Iterator &other)
    -> Iterator & {
  if (this != &other) {
    this->lst_iter = other.lst_iter;
    this->arr_index = other.arr_index;
    this->bucket_iterator = other.bucket_iterator;
    this->ust = other.ust;
  }
  return *this;
}

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
