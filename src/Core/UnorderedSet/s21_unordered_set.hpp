#if !defined(__S21_UNORDERED_SET__)
#define __S21_UNORDERED_SET__
#include <array>
#include <vector>

#include "../s21_containers.hpp"
extern int main();

namespace s21 {
template <class Key>
class unordered_set {
 public:
  struct Iterator;
  struct ConstIterator;
  struct ReverseIterator;
  friend int ::main();  // TODO убрать
  friend struct Iterator;
  friend struct ConstIterator;
  friend struct ReverseIterator;
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;
  using iterator = Iterator;
  using const_iterator = ConstIterator;
  unordered_set() noexcept;
  unordered_set(std::initializer_list<Key> const &items) noexcept;
  ~unordered_set() noexcept;

  size_type hashFunction(key_type key) const noexcept;
  void clear() noexcept;
  virtual std::pair<Iterator, bool> insert(const key_type &key) noexcept;

  Iterator begin() noexcept;
  Iterator end() noexcept;
  ConstIterator cbegin() const;
  ConstIterator cend() const;
  ReverseIterator rbegin();
  ReverseIterator rend();

  size_type size() const noexcept;
  virtual size_type bucket_count() const noexcept;
  bool empty() const noexcept;
  void erase(const key_type &key) noexcept;
  size_type count(const key_type &key) const noexcept;
  bool contains(const key_type &key) const noexcept;
  size_type bucket_size(const key_type &key) const noexcept;
  virtual float load_factor() const noexcept;
  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);
  template <typename... Args>
  std::vector<std::pair<iterator, bool>> emplace_back(Args &&...args);

 protected:
  size_type get_index(const key_type &key) const noexcept;
  virtual void add(std::vector<value_type> &vec, const key_type &key) noexcept;
  size_type size_;
  size_type capacity;
  static constexpr size_type TABLE_SIZE = 100;
  mutable s21::list<std::array<std::vector<value_type>, TABLE_SIZE> *> table;
  using IteratorType = typename s21::list<
      std::array<std::vector<value_type>, TABLE_SIZE> *>::iterator;
  IteratorType to_expand() noexcept;
  virtual void debug();  // TODO убрать
};

}  // namespace s21
#include "s21_unordered_set_core.hpp"
#include "s21_unordered_set_iterator.hpp"

#endif  // __S21_UNORDERED_SET__