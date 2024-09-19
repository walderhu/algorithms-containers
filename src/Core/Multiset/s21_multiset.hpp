#ifndef __S21_MUITISET_HPP__
#define __S21_MUITISET_HPP__

#include <deque>
#include <list>
// #include <set>

#include "../Set/s21_set.hpp"

namespace s21 {
template <class Key>
class multiset final : public s21::set<Key> {
 public:
  using Node = typename set<Key>::Node;

  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename set<Key>::Iterator;
  using const_iterator = typename set<Key>::ConstIterator;
  using size_type = size_t;

  multiset() noexcept;
  multiset(std::initializer_list<Key> const &items) noexcept;
  multiset(const multiset &s);
  multiset(multiset &&s);
  ~multiset() noexcept;
  multiset<Key> &operator=(multiset &&s) noexcept;
  multiset<Key> &operator=(const multiset &s) noexcept;

  explicit operator std::deque<Key>() noexcept {
    std::deque<Key> lst;
    for (auto it = this->begin(); it != this->end(); ++it) lst.push_back(*it);
    return lst;
  }

  explicit operator std::list<Key>() noexcept {
    return this->operator std::deque<Key, std::allocator<Key>>();
  }

  explicit operator s21::set<Key>() noexcept {
    s21::set<Key> st;
    for (auto it = this->begin(); it != this->end(); ++it) st.insert(*it);
    return st;
  }

  iterator lower_bound(const Key &key) noexcept;
  iterator upper_bound(const Key &key) noexcept;
  std::pair<iterator, iterator> equal_range(const Key &key) noexcept;
  size_type count(const Key &key) const;

 private:
  std::pair<iterator, bool> insert_in(value_type value, Node *&current,
                                      Node *parent) override;
};

}  // namespace s21
#include "s21_multiset_core.hpp"

#endif  //  __S21_MUITISET_HPP__
