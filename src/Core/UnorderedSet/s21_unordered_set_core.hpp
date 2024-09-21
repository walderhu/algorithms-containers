#if !defined(__S21_UNORDERED_CORE_SET__)
#define __S21_UNORDERED_CORE_SET__

#include "s21_unordered_set.hpp"

namespace s21 {

template <class value_type>
inline unordered_set<value_type>::unordered_set() noexcept
    : capacity(0u), size_(0) {
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

template <class Key>
inline void unordered_set<Key>::insert(const key_type &key) noexcept {
  size_t index = hashFunction(key) % TABLE_SIZE;
  auto it = table.begin();

  for (auto &arr = *it; it != table.end(); ++it)
    if (auto &vec = arr->at(index); vec.empty()) {
      vec.push_back(key);
      size_++;
      break;
    } else if (vec.front() == key)
      break;

  if (it != table.end()) return;

  it = this->to_expand();
  auto &vec = (*it)->at(index);
  vec.push_back(key);
  size_++;
}

/* NOTES
все нормально, в функции insert я итерируюсь по узлам!
то есть, я захожу сначала в самый первый узел, и беру вектор который
соответсвует моему хэшу в этом узле (беру его по индексу),

если я пробежался по всем нодам структуры и так не смог найти ни одного узла,
который был бы свободен, значит мой указатель на It будет ссылаться на конец
списка, это я и проверяю в некст условии, если итератор указывает на конец,
значит мы не добавили элемент я добавляю новый узел, получаю итератор на него, и
присваиваю ему нужное мне значение

теперь если ведро пустое, добавляю, иначе проверяю че там лежит
если там лежит мой кей, то я выхожу из функции, иначе расширяю структуру
*/

template <class Key>
inline void unordered_set<Key>::clear() {
  for (auto it = table.begin(); it != table.end(); ++it) delete *it;
  table.clear();
}

template <class Key>
inline void unordered_set<Key>::debug() {
  auto it = table.begin();

  for (auto &arr = *it; it != table.end(); ++it)
    for (size_t i = 0u; i < TABLE_SIZE; i++)
      if (auto &vec = arr->at(i); !vec.empty())
        for (auto iter = vec.begin(); iter != vec.end(); ++iter)
          std::cout << *iter << " ";

  std::cout << std::endl;
}

template <class Key>
inline auto unordered_set<Key>::to_expand() -> IteratorType {
  auto *vec = new std::array<s21::vector<value_type>, TABLE_SIZE>();
  table.push_back(vec);
  capacity += TABLE_SIZE;
  return --(table.end());
}

template <class Key>
inline auto unordered_set<Key>::size() const noexcept -> size_type {
  return this->size_;
}

template <class Key>
inline auto unordered_set<Key>::empty() const noexcept -> size_type {
  return size() == 0u;
}
}  // namespace s21

#endif  // __S21_UNORDERED_CORE_SET__