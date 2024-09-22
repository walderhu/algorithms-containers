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
  friend int ::main();  // TODO убрать
  friend struct Iterator;
  friend struct ConstIterator;
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

  Iterator begin() noexcept;
  Iterator end() noexcept;
  ConstIterator cbegin() const;
  ConstIterator cend() const;

  size_type size() const noexcept;
  virtual size_type bucket_count() const noexcept;
  bool empty() const noexcept;
  void erase(const key_type &key) noexcept;
  size_type count(const key_type &key) const noexcept;
  bool contains(const key_type &key) const noexcept;
  size_type bucket_size(const key_type &key) const noexcept;
  virtual float load_factor() const noexcept;
  /*
    template <typename... Args>
    std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);
  */
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
  /*
  Метод key_eq в классе std::unordered_set возвращает функцию, которая
  используется для сравнения ключей на равенство. Это позволяет пользователю
  проверить, равны ли два ключа, используя определенный предикат сравнения,
  который может быть задан при создании unordered_set.
  key_equal key_eq() const;
      auto cmpfn = mySet.key_eq();

  Проверяем равенство двух символов
    std::cout << "cmpfn('a', 'a') == " << std::boolalpha << cmpfn('a', 'a') <<
  std::endl; // true std::cout << "cmpfn('a', 'b') == " << std::boolalpha <<
  cmpfn('a', 'b') << std::endl; // false

  */
  /*
  Метод get_allocator в классе std::unordered_set возвращает объект
  распределителя (allocator), который используется для управления памятью в
  контейнере. Это позволяет пользователям получить доступ к распределителю,
  который был использован для выделения памяти для элементов в unordered_set.
  allocator_type get_allocator() const noexcept;
    std::unordered_set<int> mySet;

    // Получаем распределитель
    auto alloc = mySet.get_allocator();

    // Выводим адреса выделенной памяти
    int* p = alloc.allocate(1); // Выделяем память для одного элемента
    *p = 42; // Присваиваем значение

    std::cout << "Allocated memory for value: " << *p << std::endl;

    alloc.deallocate(p, 1); // Освобождаем память
  */

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
};

template <class Key>
struct unordered_set<Key>::Iterator {
  using BucketIterator = typename std::vector<value_type>::iterator;

  using BucketType = typename std::vector<value_type>;
  using ArrayType = typename std::array<BucketType, TABLE_SIZE> *;
  using IteratorType = typename s21::list<ArrayType>::iterator;

  Iterator(IteratorType lst_iter, size_t bucket_index,
           s21::unordered_set<value_type> *ust = nullptr);
  Iterator(const Iterator &other);
  friend int ::main();  // TODO убрать

  bool operator==(const Iterator &other) const;
  bool operator!=(const Iterator &other) const;

  Iterator &operator++();
  Iterator &operator--();
  reference operator*() const;
  virtual Iterator &operator=(const Iterator &other);

 protected:
  Key &get_value() const;
  IteratorType lst_iter;

  void move_next(ArrayType &table, std::vector<Key> &bucket);
  void move_prev(ArrayType &table, std::vector<Key> &bucket);
  size_t bucket_index;
  BucketIterator bucket_iterator;
  s21::unordered_set<Key> *ust;
  friend class unordered_set<Key>;
};

template <class Key>
struct unordered_set<Key>::ConstIterator : public unordered_set<Key>::Iterator {
};

}  // namespace s21
#include "s21_unordered_set_core.hpp"
#include "s21_unordered_set_iterator.hpp"

#endif  // __S21_UNORDERED_SET__