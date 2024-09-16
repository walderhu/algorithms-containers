#ifndef __S21_multiset_HPP__
#define __S21_multiset_HPP__

#include "../Set/s21_set.hpp"
namespace s21 {
/*
получается если я сделаю инсерт виртуальным методом и сделаю перегрузку
то вся остальная логика у меня заработает как надо, поскольку
при заполнении и оставшееся ** у меня будет делегирование
идти уже на переопределенную функцию
*/
template <class Key>
class multiset : public s21::set<Key> {
 public:
  using Node = typename s21::set<Key>::Node;

  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename s21::set<Key>::Iterator;
  using const_iterator = typename s21::set<Key>::ConstIterator;
  using size_type = size_t;

  multiset() noexcept : set<Key>::set() {};
  multiset(std::initializer_list<Key> const &items) noexcept
      : set<Key>::set(items) {}
  multiset(const multiset &s) : set<Key>::set(s) {}
  multiset(multiset &&s) : set<Key>::set(std::move(s)) {}
  ~multiset() noexcept { set<Key>::clear(); }
  multiset<Key> &operator=(multiset &&s) noexcept {
    return set<Key>::operator=(std::move(s));
  }
  multiset<Key> &operator=(const multiset &s) noexcept {
    return set<Key>::operator=(s);
  }

  //   iterator find(const Key &key);
  //   bool contains(const Key &key);

  //   bool empty() const;
  //   void clear();

  //   std::pair<iterator, bool> insert(value_type value);
  //   size_type max_size();

  //   iterator begin();
  //   iterator end();
  //   ConstIterator cbegin() const;
  //   ConstIterator cend() const;
  //   void swap(multiset &other);
  //   void erase(iterator pos);
  //   void merge(multiset &other);
  //   size_type size() const;

  //   template <typename... Args>
  //   std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);

  //  protected:
  //   size_type _size;
  std::pair<iterator, bool> insert(value_type value, Node *&current,
                                   Node *parent);
  //   void clear(Node *&current);
  //   Node *deleteNode(Node *current, value_type key);
  //   Node *minValueNode(Node *node);
};

}  // namespace s21
#include "s21_multiset_core.hpp"
#endif  //  __S21_multiset_HPP__
