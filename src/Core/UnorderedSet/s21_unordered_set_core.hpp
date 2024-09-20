#if !defined(__S21_UNORDERED_CORE_SET__)
#define __S21_UNORDERED_CORE_SET__

#include "s21_unordered_set.hpp"

namespace s21 {

template <class value_type>
inline unordered_set<value_type>::unordered_set() noexcept : capacity(0u) {
  this->to_expand();
};

template <class value_type>
inline unordered_set<value_type>::unordered_set(
    std::initializer_list<value_type> const &items) noexcept {
  for (auto it = items.begin(); it != items.end(); ++it) this->insert(*it);
}

template <class value_type>
inline unordered_set<value_type>::~unordered_set() noexcept {
  this->clear();
}

template <class value_type>
inline auto unordered_set<value_type>::hashFunction(key_type key) -> size_type {
  return std::hash<key_type>()(key);
}

#include <typeinfo>  // TODO убрать
                     // DEBUG(typeid(vec).name());
template <class Key>
inline void unordered_set<Key>::insert(const key_type &key) noexcept {
  size_t index = hashFunction(key) % TABLE_SIZE;
  auto it = table.begin();

  for (auto &arr = *it; it != table.end(); ++it)
    if (auto &vec = arr->at(index); vec.empty() || vec.front() == key)
      vec.push_back(key);
    else
      this->to_expand();
}
/* NOTES

все нормально стой, на 36 строчке я итерируюсь по узлам!
то есть, я захожу сначала в самый первый узел, и беру вектор который
соответсвует моему хэшу в этом узле (беру его по индексу), смотрю пустой он или
нет, если не пустой, он должен содержать значения равные моему (я проверяю
только первое) если одно из этих условий удовлетворяет, значит это нужное ведро,
и мы добавляем туда наше значение, иначе мы должны расширить нашу структуру
поскольку у нас начинают появляться коллизии (шаг расширения у меня в дефолте
100, я не сильно раскидываюсь в памяти) да и шанс что чел вкинет числа с хэшем в
разницу моего шага очень мала

*/

template <class Key>
inline void unordered_set<Key>::clear() {
  for (auto it = table.begin(); it != table.end(); ++it) delete *it;
  table.clear();
}

template <class Key>
inline auto unordered_set<Key>::to_expand() -> IteratorType {
  auto *vec = new std::array<s21::vector<value_type>, TABLE_SIZE>();
  table.push_back(vec);
  capacity += TABLE_SIZE;

  return --(table.end());
}

}  // namespace s21

#endif  // __S21_UNORDERED_CORE_SET__
