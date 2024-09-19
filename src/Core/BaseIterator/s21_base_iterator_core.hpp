// #ifndef __S21_BASE_ITERATOR_CORE_HPP__
// #define __S21_BASE_ITERATOR_CORE_HPP__

// #include "s21_base_iterator.hpp"

// template <typename value_type>
// inline s21::BaseNode<value_type>::BaseNode(value_type val)
//     : value(val), next(nullptr), prev(nullptr) {}

// template <class value_type>
// inline auto s21::BaseIterator<value_type>::operator==(
//     const BaseIterator& other) const -> bool {
//   return current == other.current;
// }

// template <class value_type>
// inline auto s21::BaseIterator<value_type>::operator!=(
//     const BaseIterator& other) const -> bool {
//   return current != other.current;
// }

// template <class value_type>
// inline auto s21::BaseIterator<value_type>::operator<(
//     const BaseIterator& other) const -> bool {
//   for (auto it = list->begin(); it != list->end(); ++it) {
//     if (it == current) return true;
//     if (it == other) return false;
//   }
//   throw std::out_of_range("Disabled BaseIterator. Not exist");
// }

// template <class value_type>
// inline auto s21::BaseIterator<value_type>::operator<=(
//     const BaseIterator& other) const -> bool {
//   return this->operator==(other) || this->operator<(other);
// }

// template <class value_type>
// inline auto s21::BaseIterator<value_type>::operator>(
//     const BaseIterator& other) const -> bool {
//   return !this->operator<(other);
// }

// template <class value_type>
// inline auto s21::BaseIterator<value_type>::operator>=(
//     const BaseIterator& other) const -> bool {
//   return this->operator==(other) || this->operator>(other);
// }

// template <class value_type>
// inline auto s21::BaseIterator<value_type>::operator*() const -> value_type& {
//   return current->value;
// }

// #endif  // __S21_BASE_ITERATOR_CORE_HPP__