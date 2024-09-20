#if !defined(__S21_UNORDERED_SET__)
#define __S21_UNORDERED_SET__
#include <array>
#include <typeinfo>  // TODO убрать
                     // DEBUG(typeid(vec).name());

#include "../s21_containers.hpp"
namespace s21 {
template <class Key>
class unordered_set {
 public:
  friend int main();  // TODO убрать
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

  unordered_set() noexcept;
  unordered_set(std::initializer_list<Key> const &items) noexcept;
  ~unordered_set() noexcept;

  size_type hashFunction(key_type key);
  void clear();
  void insert(const key_type &key) noexcept;
  void debug();  // TODO убрать

 protected:
  size_type capacity;
  static constexpr size_type TABLE_SIZE = 100;
  mutable s21::list<std::array<s21::vector<value_type>, TABLE_SIZE> *> table;

  using IteratorType = typename s21::list<
      std::array<s21::vector<value_type>, TABLE_SIZE> *>::iterator;

  IteratorType to_expand();
};
}  // namespace s21
#include "s21_unordered_set_core.hpp"

#endif  // __S21_UNORDERED_SET__
