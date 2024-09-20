#if !defined(__S21_UNORDERED_CORE_SET__)
#define __S21_UNORDERED_CORE_SET__

#include "s21_unordered_set.hpp"

namespace s21 {

template <class value_type>
inline unordered_set<value_type>::unordered_set() noexcept
    : set<value_type>::set(){};

template <class value_type>
inline unordered_set<value_type>::unordered_set(
    std::initializer_list<value_type> const &items) noexcept {
  for (auto it = items.begin(); it != items.end(); ++it)
    set<value_type>::insert(*it);
}

template <class value_type>
inline unordered_set<value_type>::unordered_set(const unordered_set &s) noexcept
    : set<value_type>::set(s) {}

template <class value_type>
inline unordered_set<value_type>::unordered_set(unordered_set &&s) noexcept
    : set<value_type>::set(std::move(s)) {}

template <class value_type>
inline unordered_set<value_type>::~unordered_set() noexcept {
  set<value_type>::clear();
}

template <class value_type>
inline auto unordered_set<value_type>::operator=(unordered_set &&s) noexcept
    -> unordered_set<value_type> & {
  if (this != &s) {
    unordered_set<value_type>::clear();
    this->root = std::move(s.root);
    this->_size = std::move(s._size);
    s.root = nullptr;
    s._size = 0u;
  }
  return *this;
}

template <class value_type>
inline auto unordered_set<value_type>::operator=(
    const unordered_set &s) noexcept -> unordered_set<value_type> & {
  return set<value_type>::operator=(s);
}

}  // namespace s21

#endif  // __S21_UNORDERED_CORE_SET__
