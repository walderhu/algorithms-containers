#if !defined(__S21_UNORDERED_MULTISET__)
#define __S21_UNORDERED_MULTISET__

#include "../s21_containers.hpp"
namespace s21 {
template <class Key>
class unordered_multiset : public unordered_set<Key> {
 public:
  friend int main();  // TODO убрать
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

  using unordered_set<Key>::table;
  using unordered_set<Key>::TABLE_SIZE;
  using unordered_set<Key>::size_;

  unordered_multiset() noexcept;
  unordered_multiset(std::initializer_list<Key> const &items) noexcept;
  ~unordered_multiset() noexcept;

  void insert(const key_type &key) noexcept override;
  void debug() override;  // TODO убрать
};
}  // namespace s21
#include "s21_unordered_multiset_core.hpp"

#endif  // __S21_UNORDERED_MULTISET__
