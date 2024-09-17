#ifndef __S21_multiset_HPP__
#define __S21_multiset_HPP__

#include "../Set/s21_set.hpp"
namespace s21 {

template <class Key>
class multiset final : public s21::set<Key> {
 public:
  using Node = typename s21::set<Key>::Node;

  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename s21::set<Key>::Iterator;
  using const_iterator = typename s21::set<Key>::ConstIterator;
  using size_type = size_t;

  multiset() noexcept;
  multiset(std::initializer_list<Key> const &items) noexcept;
  multiset(const multiset &s);
  multiset(multiset &&s);
  ~multiset() noexcept;
  multiset<Key> &operator=(multiset &&s) noexcept;
  multiset<Key> &operator=(const multiset &s) noexcept;

  iterator lower_bound(const Key &key) noexcept;
  iterator upper_bound(const Key &key) noexcept;
  std::pair<iterator, iterator> equal_range(const Key &key) noexcept;

  std::pair<iterator, bool> insert(const value_type &value);
  size_type count(const Key &key) const;

 protected:
  std::pair<iterator, bool> insert(value_type value, Node *&current,
                                   Node *parent) override;
};

}  // namespace s21
#include "s21_multiset_core.hpp"
#endif  //  __S21_multiset_HPP__
