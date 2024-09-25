#pragma once
#include <iterator>
#include <vector>

#include "s21_unordered_set.hpp"
namespace s21 {
/*
template <class Key, size_type Capacity>
struct unordered_set<Key, Capacity>::Iterator {
using BucketType = typename std::vector<Key>;
using TableType = typename std::vector<BucketType>;

Iterator(IteratorType lst_iter, size_t bucket_index,
       s21::unordered_set<value_type> *ust = nullptr,
       BucketIterator bucket_iterator = BucketIterator());
friend int ::main();  // TODO убрать

Iterator(const Iterator &other) {
lst_iter = other.lst_iter;
bucket_index = other.bucket_index;
ust = other.ust;
bucket_iterator = other.bucket_iterator;
}

bool operator==(const Iterator &other) const;
bool operator!=(const Iterator &other) const;

Iterator &operator++();
Iterator &operator--();
Iterator operator++(int);
Iterator operator--(int);
reference operator*();
virtual Iterator &operator=(const Iterator &other);

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
struct unordered_set<Key>::ConstIterator : public unordered_set<Key>::Iterator {
using unordered_set<Key>::Iterator::Iterator;
};

template <class Key>
struct unordered_set<Key>::ReverseIterator
: public unordered_set<Key>::Iterator {
using unordered_set<Key>::Iterator::Iterator;
};*/
template <typename Key>
struct Iterator {
 public:
  using OuterIterator = typename std::vector<std::vector<Key>>::iterator;
  using InnerIterator = typename std::vector<Key>::iterator;

  Iterator(OuterIterator outer, InnerIterator inner)
      : outer_iter(outer), inner_iter(inner) {}

  // Dereference operator
  Key &operator*() { return *inner_iter; }

  // Pre-increment operator
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

  // Comparison operator
  bool operator!=(const Iterator &other) const {
    return outer_iter != other.outer_iter || inner_iter != other.inner_iter;
  }

  // Set the end iterator
  void setOuterEnd(OuterIterator end) { outer_end = end; }

 private:
  OuterIterator outer_iter;
  InnerIterator inner_iter;
  OuterIterator outer_end;  // To track the end of the outer vector
};
}  // namespace s21

#include "s21_unordered_set_iterator_core.hpp"
