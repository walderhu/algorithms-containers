#pragma once
#include "s21_unordered_set.hpp"

namespace s21 {

template <class Key, size_type Capacity>
unordered_set<Key, Capacity>::unordered_set() noexcept
    : capacity_(Capacity), size_(0), table(Capacity){};

template <class Key, size_type Capacity>
inline unordered_set<Key, Capacity>::unordered_set(
    std::initializer_list<Key> const &items) noexcept {
  for (auto it = items.begin(); it != items.end(); ++it) this->insert(*it);
}

template <class Key, size_type Capacity>
inline unordered_set<Key, Capacity>::~unordered_set() noexcept {
  clear();
}

template <class Key, size_type Capacity>
inline auto unordered_set<Key, Capacity>::hashFunction(Key key) const noexcept
    -> size_type {
  return std::hash<Key>()(key);
}

template <class Key, size_type Capacity>
inline auto unordered_set<Key, Capacity>::reserve(size_type n) -> void {
  table.reserve(n);
}

template <class Key, size_type Capacity>
inline auto unordered_set<Key, Capacity>::insert(const Key &key) noexcept
    -> void {
  size_t bucket_index = std::hash<Key>()(key) % table.size();
  if (table[bucket_index].empty()) table[bucket_index].resize(1);
  table[bucket_index].push_back(key);
}

template <class Key, size_type Capacity>
inline auto unordered_set<Key, Capacity>::add(std::vector<Key> &vec,
                                              const Key &key) noexcept -> void {
  vec.push_back(key);
  size_++;
}

template <class Key, size_type Capacity>
inline void unordered_set<Key, Capacity>::clear() noexcept {
  table.clear();
}

// template <class Key>
// inline void unordered_set<Key>::rehash(size_type n) {}

template <class Key, size_type Capacity>
inline auto unordered_set<Key, Capacity>::size() const noexcept -> size_type {
  return this->size_;
}

template <class Key, size_type Capacity>
inline auto unordered_set<Key, Capacity>::bucket_count() const noexcept
    -> size_type {
  return this->size_;
}

template <class Key, size_type Capacity>
inline auto unordered_set<Key, Capacity>::empty() const noexcept -> bool {
  return size() == 0u;
}

template <class Key, size_type Capacity>
inline auto unordered_set<Key, Capacity>::get_index(
    const Key &key) const noexcept -> size_type {
  return hashFunction(key) % capacity_;
}

// template <class Key>
// inline auto unordered_set<Key>::erase(const key_type &key) noexcept -> void
// {
//   size_t bucket_index = get_index(key);
//   auto it = table.begin();

//   for (auto &bucket = *it; it != table.end(); ++it)
//     if (auto &vec = bucket->at(bucket_index);
//         !vec.empty() && vec.front() == key) {
//       vec.pop_back();
//       size_--;
//       return;
//     }
// }

// template <class Key>
// inline auto unordered_set<Key>::bucket_size(const key_type &key) const
// noexcept
//     -> size_type {
//   return this->count(key);
// }

// template <class Key>
// inline auto unordered_set<Key>::count(const key_type &key) const noexcept
//     -> size_type {
//   size_t bucket_index = get_index(key);
//   auto it = table.begin();

//   for (auto &bucket = *it; it != table.end(); ++it)
//     if (auto &vec = bucket->at(bucket_index);
//         !vec.empty() && vec.front() == key)
//       return vec.size();
//   return 0;
// }

// template <class Key, size_type Capacity>
// inline auto unordered_set<Key, Capacity>::contains(
//     const key_type &key) const noexcept -> bool {
//   return static_cast<bool>(this->count(key));
// }

// template <class Key>
// inline auto unordered_set<Key>::load_factor() const noexcept -> float {
//   return static_cast<float>(capacity) / static_cast<float>(size_);
// }

// template <class value_type>
// template <typename... Args>
// inline auto unordered_set<value_type>::insert_many(Args &&...args)
//     -> std::vector<std::pair<iterator, bool>> {
//   std::vector<std::pair<iterator, bool>> results;
//   (results.emplace_back(this->insert(std::forward<Args>(args))), ...);
//   return results;
// }

// template <class value_type>
// template <typename... Args>
// inline auto unordered_set<value_type>::emplace_back(Args &&...args)
//     -> std::vector<std::pair<iterator, bool>> {
//   return insert_many(std::forward<Args>(args)...);
// }

// template <class value_type>
// template <typename... Args>
// inline auto unordered_set<value_type>::emplace_hint(
//     const_iterator position, Args &&...args) -> iterator {
//   std::vector<std::pair<iterator, bool>> results;
//   (results.emplace_back(this->insert(std::forward<Args>(args))), ...);
//   if (!results.empty()) return results.back().first;
//   return this->end();
// }

// #ifdef _GLIBCXX_OSTREAM
// template <typename U>
// std::ostream &operator<<(std::ostream &os, const unordered_set<U> &obj) {
//   auto it = obj.cbegin();
//   auto cend = obj.cend();
//   while (it != cend) os << *it << (++it != cend ? " " : "");
//   return os;
// }
// #endif  // _GLIBCXX_OSTREAM

}  // namespace s21