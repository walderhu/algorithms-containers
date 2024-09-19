#ifndef __S21_BASE_ITERATOR_HPP__
#define __S21_BASE_ITERATOR_HPP__

#include "../s21_containers.hpp"

namespace s21 {
template <class value_type>
struct BaseNode {
  value_type value;
  BaseNode(value_type val = value_type());
};

template <class value_type, class object_type>
class BaseIterator {
  BaseIterator() noexcept = default;
  BaseIterator(const BaseIterator &other) noexcept = default;

  bool operator==(const BaseIterator &other) const;
  bool operator!=(const BaseIterator &other) const;
  bool operator<(const BaseIterator &other) const = 0;
  bool operator<=(const BaseIterator &other) const;
  bool operator>(const BaseIterator &other) const;
  bool operator>=(const BaseIterator &other) const;
  value_type &operator*() const;
  BaseIterator &operator++() = 0;
  BaseIterator &operator--() = 0;
  BaseIterator operator++(int);
  BaseIterator operator--(int);
  virtual BaseIterator &operator=(const BaseIterator &other) = 0;

 protected:
  BaseNode<value_type> *current;
  object_type object;
};
}  // namespace s21

#endif  // __S21_BASE_ITERATOR_HPP__