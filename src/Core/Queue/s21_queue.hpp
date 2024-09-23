#ifndef QUEUE_H
#define QUEUE_H
// #include "../List/s21_list.hpp"
#include <list>

#include "../s21_containers.hpp"

namespace s21 {

template <typename T, class Container>
class queue {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

  queue() : items() {}
  queue(std::initializer_list<value_type> const &items) : items(items) {}
  queue(const queue &q) : items(q.items) {}
  queue(queue &&q) noexcept : items(std::move(q.items)) {}
  queue &operator=(queue &&q) noexcept {
    this->items = std::move(q.items);
    return *this;
  }
  ~queue() {}

  const_reference front() const { return items.front(); }

  const_reference back() const { return items.back(); }

  bool empty() const { return items.empty(); }

  size_type size() const { return items.size(); }

  void push(const_reference value) { items.push_back(value); }

  void pop() { items.pop_front(); }

  void swap(queue &other) { items.swap(other.items); }

  void emplace_back(const_reference value) { items.emplace_back(value); }

  template <class... Args>
  void emplace(Args &&...args) {
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