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

  size_type hashFunction(key_type key) const noexcept;
  void clear() noexcept;
  virtual void insert(const key_type &key) noexcept;
  virtual void debug();  // TODO убрать

  size_type size() const noexcept;
  virtual size_type bucket_count() const noexcept;
  bool empty() const noexcept;
  void erase(const key_type &key) noexcept;
  size_type count(const key_type &key) const noexcept;
  bool contains(const key_type &key) const noexcept;
  size_type bucket_size(const key_type &key) const noexcept;
  virtual float load_factor() const noexcept;

  /*
  Метод load_factor в классе std::unordered_set используется для получения
  текущего коэффициента загрузки контейнера. Коэффициент загрузки — это
  отношение количества элементов в контейнере к количеству ведер (buckets),
  используемых для хранения этих элементов. Он позволяет оценить, насколько
  эффективно распределены элементы по ведрам и может помочь в управлении
  производительностью хэш-таблицы.

  я сначала создаю 100 пустых ведер, но они пустые
  считать их полноценно их ведрами можно только после того как там есть хотя бы
  1 элемент в случае сток сета использую size потому что он полностью
  семанимичен, в мультисете отдельный метод
  */

  /*
    template <class... Args>
    iterator emplace_hint(const_iterator position, Args &&...args);
  итератор это подсказка, мы можем игнорировать его полностью, но не стоит
  */

  /*
  void reserve(size_type n);
  нужно для перераспределения памяти на более емкую чтоли???
  просто переопределить более корректную table_max для такущей структуры
  и переопределить ее
  */

  /*
  Метод rehash в классе std::unordered_set используется для изменения количества
  ведер (buckets) в контейнере. Он позволяет установить новое количество ведер,
  что может быть полезно для оптимизации производительности при добавлении
  элементов.
  void rehash(size_type n);
  в моем случае начальное значение этих ведер это table_max
  */

 protected:
  size_type get_index(const key_type &key) const noexcept;
  virtual void add(s21::vector<value_type> &vec, const key_type &key) noexcept;
  size_type size_;
  size_type capacity;
  static constexpr size_type TABLE_SIZE = 100;
  mutable s21::list<std::array<s21::vector<value_type>, TABLE_SIZE> *> table;

  using IteratorType = typename s21::list<
      std::array<s21::vector<value_type>, TABLE_SIZE> *>::iterator;

  IteratorType to_expand() noexcept;
};
}  // namespace s21
#include "s21_unordered_set_core.hpp"

#endif  // __S21_UNORDERED_SET__
