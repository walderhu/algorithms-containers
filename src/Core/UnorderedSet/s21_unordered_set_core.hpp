#if !defined(__S21_UNORDERED_CORE_SET__)
#define __S21_UNORDERED_CORE_SET__

#include "s21_unordered_set.hpp"

namespace s21 {

template <class value_type>
inline unordered_set<value_type>::unordered_set() noexcept : capacity(0u) {
  this->to_expand();
};

template <class value_type>
inline unordered_set<value_type>::unordered_set(
    std::initializer_list<value_type> const &items) noexcept {
  for (auto it = items.begin(); it != items.end(); ++it) this->insert(*it);
}

template <class value_type>
inline unordered_set<value_type>::~unordered_set() noexcept {
  this->clear();
}

template <class value_type>
inline auto unordered_set<value_type>::hashFunction(key_type key) -> size_type {
  return std::hash<key_type>()(key);
}

#include <typeinfo>  // TODO убрать
                     // DEBUG(typeid(vec).name());
template <class Key>
inline void unordered_set<Key>::insert(const key_type &key) noexcept {
  size_t index = hashFunction(key) % TABLE_SIZE;
  auto it = table.begin();

  for (auto &arr = *it; it != table.end(); ++it) {
    auto &vec = arr->at(index);
    if (vec.empty()) vec.push_back(key);
  }
}

template <class Key>
inline void unordered_set<Key>::clear() {
  for (auto it = table.begin(); it != table.end(); ++it) delete *it;
  table.clear();
}

template <class Key>
inline void unordered_set<Key>::to_expand() {
  auto *vec = new std::array<s21::vector<value_type>, TABLE_SIZE>();
  table.push_back(vec);
  capacity += TABLE_SIZE;
}

}  // namespace s21

#endif  // __S21_UNORDERED_CORE_SET__
