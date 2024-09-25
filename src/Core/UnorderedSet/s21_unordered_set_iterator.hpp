// #pragma once
// #include "s21_unordered_set.hpp"

// namespace s21 {
// template <class Key>
// struct unordered_set<Key>::Iterator {
//   using BucketIterator = typename std::vector<value_type>::iterator;

//   using BucketType = typename std::vector<value_type>;
//   using ArrayType = typename std::array<BucketType, DEFAULT_SIZE> *;
//   using IteratorType = typename std::vector<ArrayType>::iterator;

//   Iterator(IteratorType lst_iter, size_t bucket_index,
//            s21::unordered_set<value_type> *ust = nullptr,
//            BucketIterator bucket_iterator = BucketIterator());
//   friend int ::main();  // TODO убрать

//   Iterator(const Iterator &other) {
//     lst_iter = other.lst_iter;
//     bucket_index = other.bucket_index;
//     ust = other.ust;
//     bucket_iterator = other.bucket_iterator;
//   }

//   bool operator==(const Iterator &other) const;
//   bool operator!=(const Iterator &other) const;

//   Iterator &operator++();
//   Iterator &operator--();
//   Iterator operator++(int);
//   Iterator operator--(int);
//   reference operator*();
//   virtual Iterator &operator=(const Iterator &other);

//  protected:
//   Key &get_value() const;
//   IteratorType lst_iter;

//   void move_next(ArrayType &table, std::vector<Key> &bucket);
//   void move_prev(ArrayType &table, std::vector<Key> &bucket,
//                  bool current = false);
//   void if_end();
//   size_t bucket_index;
//   BucketIterator bucket_iterator;
//   s21::unordered_set<Key> *ust;
//   friend class unordered_set<Key>;
// };

// template <class Key>
// struct unordered_set<Key>::ConstIterator : public
// unordered_set<Key>::Iterator {
//   using unordered_set<Key>::Iterator::Iterator;
// };

// template <class Key>
// struct unordered_set<Key>::ReverseIterator
//     : public unordered_set<Key>::Iterator {
//   using unordered_set<Key>::Iterator::Iterator;
// };
// }  // namespace s21

// #include "s21_unordered_set_iterator_core.hpp"