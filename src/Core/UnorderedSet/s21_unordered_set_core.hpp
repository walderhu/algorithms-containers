#pragma once
#include "s21_unordered_set.hpp"

namespace s21 {

template <class Key, size_type Capacity>
unordered_set<Key, Capacity>::unordered_set() noexcept
    : table(Capacity), capacity_(Capacity), size_(0){};

template <class Key, size_type Capacity>
inline unordered_set<Key, Capacity>::unordered_set(
    std::initializer_list<Key> const &items) noexcept
    : s21::unordered_set<Key, Capacity>() {
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
  size_t bucket_index = get_index(key);
  if (table[bucket_index].empty()) table[bucket_index].resize(1);
  table[bucket_index].push_back(key);
}

template <class Key, size_type Capacity>
inline void unordered_set<Key, Capacity>::clear() noexcept {
  table.clear();
}

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
  return hashFunction(key) % table.size();
}

template <class Key, size_type Capacity>
inline auto unordered_set<Key, Capacity>::erase(const key_type &key) noexcept
    -> void {
  size_t bucket_index = get_index(key);
  BucketType &bucket = table[bucket_index];
  auto it = std::remove(bucket.begin(), bucket.end(), key);
  if (it != bucket.end()) bucket.erase(it, bucket.end());
}
template <class Key, size_type Capacity>
inline auto unordered_set<Key, Capacity>::bucket_size(
    const Key &key) const noexcept -> size_type {
  return count(key);
}

template <class Key, size_type Capacity>
inline auto unordered_set<Key, Capacity>::count(
    const key_type &key) const noexcept -> size_type {
  BucketType vec = table[get_index(key)];
  return std::count(vec.begin(), vec.end(), key);
}

template <class Key, size_type Capacity>
inline auto unordered_set<Key, Capacity>::contains(
    const Key &key) const noexcept -> bool {
  return static_cast<bool>(count(key));
}

template <class Key, size_type Capacity>
inline auto unordered_set<Key, Capacity>::load_factor() const -> float {
  if (size_ == 0) throw std::runtime_error("Пустое множество");
  return static_cast<float>(capacity_) / static_cast<float>(size_);
}

// template <class Key, size_type Capacity>
// template <typename... Args>
// inline auto unordered_set<Key>::insert_many(Args &&...args)
//     -> std::vector<std::pair<iterator, bool>> {
//   std::vector<std::pair<iterator, bool>> results;
//   (results.emplace_back(this->insert(std::forward<Args>(args))), ...);
//   return results;
// }

// template <class Key, size_type Capacity>
// template <typename... Args>
// inline auto unordered_set<value_type>::emplace_back(Args &&...args)
//     -> std::vector<std::pair<iterator, bool>> {
//   return insert_many(std::forward<Args>(args)...);
// }

// template <class Key, size_type Capacity>
// template <typename... Args>
// inline auto unordered_set<value_type>::emplace_hint(
//     const_iterator position, Args &&...args) -> iterator {
//   std::vector<std::pair<iterator, bool>> results;
//   (results.emplace_back(this->insert(std::forward<Args>(args))), ...);
//   if (!results.empty()) return results.back().first;
//   return this->end();
// }

#ifdef _GLIBCXX_OSTREAM
template <typename U>
std::ostream &operator<<(std::ostream &os, const unordered_set<U> &obj) {
  auto it = obj.begin();
  auto cend = obj.end();
  while (it != cend) os << *it << (++it != cend ? " " : "");
  return os;
}
#endif  // _GLIBCXX_OSTREAM

}  // namespace s21