// #ifndef __S21_BASE_ITERATOR_HPP__
// #define __S21_BASE_ITERATOR_HPP__

// #include "../s21_containers.hpp"

// namespace s21 {

// template <class value_type>
// struct s21::deque<value_type>::BaseNode {
//   value_type value;
//   BaseNode(value_type val = value_type());
// };

// template <class value_type>
// class BaseIterator {
//   BaseIterator() noexcept = 0;
//   BaseIterator(const BaseIterator &other) noexcept = 0;
//   bool operator==(const BaseIterator &other) const;
//   bool operator!=(const BaseIterator &other) const;
//   bool operator<(const BaseIterator &other) const;
//   bool operator<=(const BaseIterator &other) const;
//   bool operator>(const BaseIterator &other) const;
//   bool operator>=(const BaseIterator &other) const;
//   BaseIterator &operator++() = 0;
//   BaseIterator &operator--() = 0;
//   BaseIterator operator++(int) = 0;
//   BaseIterator operator--(int) = 0;
//   value_type &operator*() const;
//   virtual BaseIterator &operator=(const BaseIterator &other) = 0;

//  protected:
//   s21::BaseNode<value_type> *current;
// };
// }  // namespace s21

// #endif  // __S21_BASE_ITERATOR_HPP__