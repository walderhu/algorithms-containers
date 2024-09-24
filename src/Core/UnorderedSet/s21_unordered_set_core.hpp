#if !defined(__S21_UNORDERED_CORE_SET__)
#define __S21_UNORDERED_CORE_SET__

#include "s21_unordered_set.hpp"

namespace s21 {

template <class value_type>
inline unordered_set<value_type>::unordered_set() noexcept
    : capacity(0u), size_(0) {
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
inline auto unordered_set<value_type>::hashFunction(key_type key) const noexcept
    -> size_type {
  return std::hash<key_type>()(key);
}

template <class Key>
inline auto unordered_set<Key>::insert(const key_type &key) noexcept
    -> std::pair<iterator, bool> {
  size_t bucket_index = get_index(key);  // всегда 0
  auto it = table.begin();
  auto &bucket = *it;
  for (; it != table.end(); ++it) {
    if (auto &vec = bucket->at(bucket_index); vec.empty()) {
      add(vec, key);
      auto iter = Iterator(it, bucket_index, this);
      return std::make_pair(iter, true);
    } else if (vec.front() == key) {
      auto iter = Iterator(it, bucket_index, this);
      return std::make_pair(iter, false);
    }
  }
  if (it == table.end()) {
    it = this->to_expand();
    auto &vec = (*it)->at(bucket_index);
    add(vec, key);
  }
  auto iter = Iterator(it, bucket_index, this);
  return std::make_pair(iter, true);
}

template <class Key>
inline void unordered_set<Key>::clear() noexcept {
  for (auto it = table.begin(); it != table.end(); ++it) delete *it;
  table.clear();
}

template <class Key>
inline void unordered_set<Key>::debug() {
  for (auto it = begin(); it != end(); ++it) std::cout << *it << " ";
  std::cout << std::endl;
}

template <class Key>
inline auto unordered_set<Key>::to_expand() noexcept -> IteratorType {
  auto *new_bucketay = new std::array<std::vector<value_type>, TABLE_SIZE>();
  table.push_back(new_bucketay);
  capacity += TABLE_SIZE;
  return --table.end();
}

template <class Key>
inline auto unordered_set<Key>::size() const noexcept -> size_type {
  return this->size_;
}

template <class Key>
inline auto unordered_set<Key>::add(std::vector<value_type> &vec,
                                    const key_type &key) noexcept -> void {
  vec.push_back(key);
  size_++;
}

template <class Key>
inline auto unordered_set<Key>::bucket_count() const noexcept -> size_type {
  return this->size_;
}

template <class Key>
inline auto unordered_set<Key>::empty() const noexcept -> bool {
  return size() == 0u;
}

template <class Key>
inline auto unordered_set<Key>::get_index(const key_type &key) const noexcept
    -> size_type {
  return hashFunction(key) % TABLE_SIZE;
}

template <class Key>
inline auto unordered_set<Key>::erase(const key_type &key) noexcept -> void {
  size_t bucket_index = get_index(key);
  auto it = table.begin();

  for (auto &bucket = *it; it != table.end(); ++it)
    if (auto &vec = bucket->at(bucket_index);
        !vec.empty() && vec.front() == key) {
      vec.pop_back();
      size_--;
      return;
    }
}

template <class Key>
inline auto unordered_set<Key>::bucket_size(const key_type &key) const noexcept
    -> size_type {
  return this->count(key);
}

template <class Key>
inline auto unordered_set<Key>::count(const key_type &key) const noexcept
    -> size_type {
  size_t bucket_index = get_index(key);
  auto it = table.begin();

  for (auto &bucket = *it; it != table.end(); ++it)
    if (auto &vec = bucket->at(bucket_index);
        !vec.empty() && vec.front() == key)
      return vec.size();
  return 0;
}

template <class Key>
inline auto unordered_set<Key>::contains(const key_type &key) const noexcept
    -> bool {
  return static_cast<bool>(this->count(key));
}

template <class Key>
inline auto unordered_set<Key>::load_factor() const noexcept -> float {
  return static_cast<float>(capacity) / static_cast<float>(size_);
}

template <class value_type>
template <typename... Args>
inline auto unordered_set<value_type>::insert_many(Args &&...args)
    -> std::vector<std::pair<iterator, bool>> {
  std::vector<std::pair<iterator, bool>> results;
  (results.emplace_back(this->insert(std::forward<Args>(args))), ...);
  return results;
}

template <class value_type>
template <typename... Args>
inline auto unordered_set<value_type>::emplace_back(Args &&...args)
    -> std::vector<std::pair<iterator, bool>> {
  return insert_many(std::forward<Args>(args)...);
}

template <class value_type>
template <typename... Args>
inline auto unordered_set<value_type>::emplace_hint(
    const_iterator position, Args &&...args) -> iterator {
  std::vector<std::pair<iterator, bool>> results;
  (results.emplace_back(this->insert(std::forward<Args>(args))), ...);
  if (!results.empty()) return results.back().first;
  return this->end();
}

#ifdef _GLIBCXX_OSTREAM
template <typename U>
std::ostream &operator<<(std::ostream &os, const unordered_set<U> &obj) {
  auto it = obj.cbegin();
  auto cend = obj.cend();
  while (it != cend) os << *it << (++it != cend ? " " : "");
  return os;
}
#endif  // _GLIBCXX_OSTREAM

}  // namespace s21

#endif  // __S21_UNORDERED_CORE_SET__