#pragma once
#include <algorithm>
#include <array>
#include <stdexcept>
#include <vector>

#include "../s21_containers.hpp"
using size_type = std::size_t;
extern int main();  // TODO убрать

namespace s21 {
template <class Key, size_type Capacity = 100u>
class unordered_set {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;

 protected:
  struct Iterator {
   public:
    using OuterIterator = typename std::vector<std::vector<Key>>::iterator;
    using InnerIterator = typename std::vector<Key>::iterator;

    Iterator(OuterIterator outer, InnerIterator inner)
        : outer_iter(outer), inner_iter(inner) {}

    Key &operator*() { return *inner_iter; }

    Iterator &operator++() {
      ++inner_iter;
      if (inner_iter == outer_iter->end()) {
        ++outer_iter;
        if (outer_iter != outer_end) {
          inner_iter = outer_iter->begin();
        }
      }
      return *this;
    }

    bool operator!=(const Iterator &other) const {
      return outer_iter != other.outer_iter || inner_iter != other.inner_iter;
    }

    void setOuterEnd(OuterIterator end) { outer_end = end; }

   private:
    OuterIterator outer_iter;
    InnerIterator inner_iter;
    OuterIterator outer_end;
  };
  // struct ReverseIterator;
  friend int ::main();  // TODO убрать
  friend struct Iterator;
  // friend struct ConstIterator;
  // friend struct ReverseIterator;
  using BucketType = typename std::vector<Key>;
  using TableType = typename std::vector<BucketType>;
  TableType table;

  size_type get_index(const key_type &key) const noexcept;
  size_type capacity_;
  size_type size_;

 public:
  using iterator = Iterator;
  // using const_iterator = ConstIterator;
  // using reverse_iterator = ReverseIterator;

  unordered_set() noexcept;
  unordered_set(std::initializer_list<Key> const &items) noexcept;
  ~unordered_set() noexcept;
  size_type hashFunction(key_type key) const noexcept;
  void clear() noexcept;
  void insert(const key_type &key) noexcept;

  // Iterator begin() const noexcept;
  // Iterator end() const noexcept;
  // const_iterator cbegin() const noexcept;
  // const_iterator cend() const noexcept;
  //   ReverseIterator rbegin();
  //   ReverseIterator rend();

  auto begin() {
    auto outer_begin = table.begin();
    auto inner_begin = (outer_begin != table.end()) ? outer_begin->begin()
                                                    : BucketType().end();
    Iterator it(outer_begin, inner_begin);
    it.setOuterEnd(table.end());
    return it;
  }

  auto end() { return Iterator(table.end(), BucketType().end()); }

  size_type size() const noexcept;
  virtual size_type bucket_count() const noexcept;
  bool empty() const noexcept;
  void erase(const key_type &key) noexcept;
  size_type count(const key_type &key) const noexcept;
  bool contains(const key_type &key) const noexcept;
  size_type bucket_size(const key_type &key) const noexcept;
  virtual float load_factor() const;
  //   template <typename... Args>
  //   std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);
  //   template <typename... Args>
  //   std::vector<std::pair<iterator, bool>> emplace_back(Args &&...args);
  //   template <class... Args>
  //   iterator emplace_hint(const_iterator position, Args &&...args);
  //   void rehash(size_type n);
  void reserve(size_type n);

#ifdef _GLIBCXX_OSTREAM
  template <typename U>
  friend std::ostream &operator<<(std::ostream &os,
                                  const unordered_set<U> &obj);
#endif  // _GLIBCXX_OSTREAM
};

}  // namespace s21
#include "s21_unordered_set_core.hpp"