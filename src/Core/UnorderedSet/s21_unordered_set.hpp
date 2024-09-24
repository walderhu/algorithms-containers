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

  Iterator begin() const noexcept;
  Iterator end() const noexcept;
  const_iterator cbegin() const noexcept;
  const_iterator cend() const noexcept;
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
  template <class... Args>
  iterator emplace_hint(const_iterator position, Args &&...args);
  // new
  void rehash(size_type n);
  void reserve(size_type n);
  // key_equal key_eq() const;
  // get_allocator();
  // ust.max_bucket_count
  // ust.max_load_factor
  // ust.merge
  // ust.swap
  // ust.emplace
  // ust.bucket
  // ust.equal_range
  // ust.extract
  // new

#ifdef _GLIBCXX_OSTREAM
  template <typename U>
  friend std::ostream &operator<<(std::ostream &os,
                                  const unordered_set<U> &obj);
#endif  // _GLIBCXX_OSTREAM

 protected:
  static constexpr size_type DEFAULT_SIZE = 100;
  // unordered_set(size_type n = DEFAULT_SIZE) noexcept
  // : TABLE_SIZE(n),
  // table(s21::list<std::array<std::vector<value_type>, n> *>) {}
  size_type get_index(const key_type &key) const noexcept;
  virtual void add(std::vector<value_type> &vec, const key_type &key) noexcept;
  size_type size_;
  size_type capacity;
  mutable s21::list<std::array<std::vector<value_type>, DEFAULT_SIZE> *> table;
  // size_type TABLE_SIZE;
  static constexpr size_type TABLE_SIZE = 100;

  using IteratorType = typename s21::list<
      std::array<std::vector<value_type>, TABLE_SIZE> *>::iterator;
  IteratorType to_expand() noexcept;
  virtual void debug();  // TODO убрать
};

}  // namespace s21
#include "s21_unordered_set_core.hpp"
#include "s21_unordered_set_iterator.hpp"

#endif  // __S21_UNORDERED_SET__