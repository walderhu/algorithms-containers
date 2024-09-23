#ifndef STACK_H
#define STACK_H
// #include "../Vector/s21_vector.h"
#include <vector>

#include "../s21_containers.hpp"

namespace s21 {

template <typename T, class Container>
class stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

  stack() : items() {}
  stack(std::initializer_list<value_type> const &items) : items(items) {}
  stack(const stack &s) : items(s.items) {}
  stack(stack &&s) noexcept : items(std::move(s.items)) {}
  stack &operator=(stack &&s) noexcept {
    this->items = std::move(s.items);
    return *this;
  }
  ~stack() {}

  const_reference top() const { return items.back(); }

  bool empty() const { return items.empty(); }

  size_type size() const { return items.size(); }

  void push(const_reference value) { items.push_back(value); }

  void pop() { items.pop_back(); }

  void swap(stack &other) { items.swap(other.items); }

  template <class... Args>
  void emplace(const Args &...args) {
    items.emplace_back(args...);
  }

  void emplace_back(const_reference value) { items.push_back(value); }

  template <typename... Args>
  void emplace_front(Args &&...args) {
    for (const auto &arg : {args...}) {
      items.emplace_back(arg);
    }
  }

  template <class... Args>
  void insert_many_back(Args &&...args) {
    for (const auto &arg : {args...}) {
      items.push_back(arg);
    }
  }

 private:
  Container items;
};

}  // namespace s21

#endif