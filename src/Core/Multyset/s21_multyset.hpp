#ifndef __S21_MULTYSET_HPP__
#define __S21_MULTYSET_HPP__

#include "../Set/s21_set.hpp"
namespace s21 {

template <class T>
class multyset : public s21::set<T> {
  //   set() noexcept;
  //   set(std::initializer_list<value_type> const &items) noexcept;
  //   set(const set &s);
  //   set(set &&s);
  //   ~set() noexcept;
  //   set<value_type> &operator=(set &&s) noexcept;
  //   set<value_type> &operator=(const set &s) noexcept;

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
  //   void swap(set &other);
  //   void erase(iterator pos);
  //   void merge(set &other);
  //   size_type size() const;

  //   template <typename... Args>
  //   std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);

  //  protected:
  //   size_type _size;
  //   std::pair<iterator, bool> insert(value_type value, Node *&current,
  //                                    Node *parent);
  //   void clear(Node *&current);
  //   Node *deleteNode(Node *current, value_type key);
  //   Node *minValueNode(Node *node);
};

}  // namespace s21
#include "s21_multyset_core.hpp"
#endif  //  __S21_MULTYSET_HPP__
