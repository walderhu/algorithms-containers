#if !defined(__S21_UNORDERED_SET_ITERATOR_HPP__)
#define __S21_UNORDERED_SET_ITERATOR_HPP__
#include "s21_unordered_set.hpp"

namespace s21 {
template <class Key>
struct unordered_set<Key>::ConstIterator {
  using BucketIterator = typename std::vector<value_type>::iterator;

  using BucketType = typename std::vector<value_type>;
  using ArrayType = typename std::array<BucketType, TABLE_SIZE> *;
  using IteratorType = typename s21::list<ArrayType>::iterator;

  ConstIterator(IteratorType lst_iter, size_t bucket_index,
                s21::unordered_set<value_type> *ust = nullptr,
                BucketIterator bucket_iterator = BucketIterator());
  friend int ::main();  // TODO убрать

  ConstIterator(const ConstIterator &other) {
    lst_iter = other.lst_iter;
    bucket_index = other.bucket_index;
    ust = other.ust;
    bucket_iterator = other.bucket_iterator;
  }

  bool operator==(const ConstIterator &other) const;
  bool operator!=(const ConstIterator &other) const;

  ConstIterator &operator++();
  ConstIterator &operator--();
  ConstIterator operator++(int);
  ConstIterator operator--(int);
  reference operator*();
  virtual ConstIterator &operator=(const ConstIterator &other);

 protected:
  Key &get_value() const;
  IteratorType lst_iter;

  void move_next(ArrayType &table, std::vector<Key> &bucket);
  void move_prev(ArrayType &table, std::vector<Key> &bucket,
                 bool current = false);
  void if_end();
  size_t bucket_index;
  BucketIterator bucket_iterator;
  s21::unordered_set<Key> *ust;
  friend class unordered_set<Key>;
};

template <class Key>
struct unordered_set<Key>::Iterator : public unordered_set<Key>::ConstIterator {
  using unordered_set<Key>::ConstIterator::ConstIterator;
};

template <class Key>
struct unordered_set<Key>::ReverseIterator
    : public unordered_set<Key>::Iterator {
  using unordered_set<Key>::ConstIterator::ConstIterator;
};
}  // namespace s21

#include "s21_unordered_set_iterator_core.hpp"
#endif  // __S21_UNORDERED_SET_ITERATOR_HPP__
