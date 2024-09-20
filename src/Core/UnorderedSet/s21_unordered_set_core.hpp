#if !defined(__S21_UNORDERED_CORE_SET__)
#define __S21_UNORDERED_CORE_SET__

#include "s21_unordered_set.hpp"

namespace s21 {

template <class value_type>
inline unordered_set<value_type>::unordered_set() noexcept {};

template <class value_type>
inline unordered_set<value_type>::unordered_set(
    std::initializer_list<value_type> const &items) noexcept {
  for (auto it = items.begin(); it != items.end(); ++it) this->insert(*it);
}

template <class value_type>
inline unordered_set<value_type>::unordered_set(
    const unordered_set &s) noexcept {}

template <class value_type>
inline unordered_set<value_type>::unordered_set(unordered_set &&s) noexcept {}

template <class value_type>
inline unordered_set<value_type>::~unordered_set() noexcept {
  this->clear();
}

template <class value_type>
inline auto unordered_set<value_type>::operator=(unordered_set &&s) noexcept
    -> unordered_set<value_type> & {
  return *this;
}

template <class value_type>
inline auto unordered_set<value_type>::operator=(
    const unordered_set &s) noexcept -> unordered_set<value_type> & {
  return *this;
}

// here

template <class value_type>
inline auto unordered_set<value_type>::hashFunction(key_type key) -> size_type {
  return std::hash<key_type>()(key);
}

template <class Key>
inline void unordered_set<Key>::insert(const key_type &key) noexcept {
  size_type index = this->hashFunction(key) % TABLE_SIZE;
  this->table[index].push_back(key);
}

template <class Key>
inline void unordered_set<Key>::clear() {}

template <class Key>
inline bool unordered_set<Key>::contains(const key_type &key) const noexcept {
  size_type index = this->hashFunction(key) % TABLE_SIZE;
  for (auto &&element : table[index])
    if (element == key) return true;
  return false;
}

template <class Key>
inline void unordered_set<Key>::remove(key_type key) {
  size_t index = hashFunction(key) % TABLE_SIZE;
  auto &vec = table[index];
  vec.erase(std::remove(vec.begin(), vec.end(), key), vec.end());
}

}  // namespace s21

#endif  // __S21_UNORDERED_CORE_SET__
