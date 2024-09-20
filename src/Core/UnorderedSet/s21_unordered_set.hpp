#if !defined(__S21_UNORDERED_SET__)
#define __S21_UNORDERED_SET__

#include "../s21_containers.hpp"
namespace s21 {
template <class Key>
class unordered_set {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

  unordered_set() noexcept;
  unordered_set(std::initializer_list<Key> const &items) noexcept;
  unordered_set(const unordered_set &s) noexcept;
  unordered_set(unordered_set &&s) noexcept;
  ~unordered_set() noexcept;
  unordered_set<Key> &operator=(unordered_set &&s) noexcept;
  unordered_set<Key> &operator=(const unordered_set &s) noexcept;

  size_type hashFunction(key_type key);
  void clear();
  void remove(key_type key);
  void insert(const key_type &key) noexcept;
  bool contains(const key_type &key) const noexcept;

 protected:
  static constexpr size_type TABLE_SIZE = 100;
  mutable s21::vector<value_type> table[TABLE_SIZE];
};
}  // namespace s21
#include "s21_unordered_set_core.hpp"

#endif  // __S21_UNORDERED_SET__
