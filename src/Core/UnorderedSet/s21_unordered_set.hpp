#pragma once
#include <array>
#include <vector>

#include "../s21_containers.hpp"
using size_type = std::size_t;
extern int main();  // TODO убрать

namespace s21 {
template <class Key>
class unordered_set {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;

 protected:
  struct Iterator;
  struct ConstIterator;
  struct ReverseIterator;
  friend int ::main();  // TODO убрать
  friend struct Iterator;
  friend struct ConstIterator;
  friend struct ReverseIterator;
  static constexpr size_type DEFAULT_CAPACITY = 100u;
  // using TableType =
  // typename std::vector<std::array<std::vector<value_type>, DEFAULT_SIZE> *>;
  // TableType table;
  // using IteratorType = typename TableType::iterator;

  // size_type get_index(const key_type &key) const noexcept;
  // virtual void add(std::vector<value_type> &vec, const key_type &key)
  // noexcept;
  size_type size_;
  size_type capacity;
  // IteratorType to_expand()
  // noexcept; virtual void debug();  // TODO убрать

 public:
  using iterator = Iterator;
  using const_iterator = ConstIterator;
  using reverse_iterator = ReverseIterator;

  template <size_type Capacity = DEFAULT_CAPACITY>
  unordered_set() noexcept;

  //   unordered_set(std::initializer_list<Key> const &items) noexcept;
  //   ~unordered_set() noexcept;

  //   size_type hashFunction(key_type key) const noexcept;
  //   void clear() noexcept;
  //   virtual std::pair<Iterator, bool> insert(const key_type &key) noexcept;

  //   Iterator begin() const noexcept;
  //   Iterator end() const noexcept;
  //   const_iterator cbegin() const noexcept;
  //   const_iterator cend() const noexcept;
  //   ReverseIterator rbegin();
  //   ReverseIterator rend();

  //   size_type size() const noexcept;
  //   virtual size_type bucket_count() const noexcept;
  //   bool empty() const noexcept;
  //   void erase(const key_type &key) noexcept;
  //   size_type count(const key_type &key) const noexcept;
  //   bool contains(const key_type &key) const noexcept;
  //   size_type bucket_size(const key_type &key) const noexcept;
  //   virtual float load_factor() const noexcept;
  //   template <typename... Args>
  //   std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);
  //   template <typename... Args>
  //   std::vector<std::pair<iterator, bool>> emplace_back(Args &&...args);
  //   template <class... Args>
  //   iterator emplace_hint(const_iterator position, Args &&...args);
  //   void rehash(size_type n);
  //   void reserve(size_type n);

  // #ifdef _GLIBCXX_OSTREAM
  //   template <typename U>
  //   friend std::ostream &operator<<(std::ostream &os,
  //                                   const unordered_set<U> &obj);
  // #endif  // _GLIBCXX_OSTREAM
};

}  // namespace s21
#include "s21_unordered_set_core.hpp"
#include "s21_unordered_set_iterator.hpp"