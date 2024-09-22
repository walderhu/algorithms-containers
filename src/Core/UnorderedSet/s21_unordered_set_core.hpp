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
inline auto unordered_set<value_type>::hashFunction(key_type key) const noexcept
    -> size_type {
  return std::hash<key_type>()(key);
}

// template <class Key>
// inline void unordered_set<Key>::insert(const key_type &key) noexcept {
//   size_t bucket_index = get_index(key);
//   auto it = table.begin();

//   for (auto &arr = *it; it != table.end(); ++it)
//     if (auto &vec = arr->at(bucket_index); vec.empty()) {
//       add(vec, key);
//       break;
//     } else if (vec.front() == key)
//       break;

//   if (it != table.end()) return;

//   it = this->to_expand();
//   auto &vec = (*it)->at(bucket_index);
//   add(vec, key);
// }

template <class Key>
inline void unordered_set<Key>::insert(const key_type &key) noexcept {
  size_t bucket_index = get_index(key);
  auto it = table.begin();

  for (auto &arr = *it; it != table.end(); ++it) {
    if (auto &vec = arr->at(bucket_index); vec.empty()) {
      add(vec, key);
      break;
    } else if (vec.front() == key) {
      break;
    }
  }

  if (it != table.end()) return;
  it = this->to_expand();
  auto &vec = (*it)->at(bucket_index);
  add(vec, key);
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
inline void unordered_set<Key>::clear() noexcept {
  for (auto it = table.begin(); it != table.end(); ++it) delete *it;
  table.clear();
}

template <class Key>
inline void unordered_set<Key>::debug() {
  auto lst_it = table.begin();
  for (auto &arr = *lst_it; lst_it != table.end(); ++lst_it)
    for (size_t i = 0u; i < TABLE_SIZE; i++)
      if (auto &vec = arr->at(i); !vec.empty())
        for (auto iter = vec.begin(); iter != vec.end(); ++iter)
          std::cout << *iter << " ";

  std::cout << std::endl;
}
/*
Итератору надо по чему то итерироваться но епть у меня тут дважды вложенный цикл
мне нужна какая от отправная точка, например итератор листа условно
в begin конструктор итератора я могу передавать изначальные значения
auto it = table.begin(); и size_t i = 0u;
тем самым уменьшая количество итераций цикла

и можно будет сделать его статичным, *переменную, и увеличивать ее в зависимости
от значения то есть я передаю begin -> return Iterator(table.begin(), 0u);
в самом итераторе он сохранит все значения и вернет

*/

template <class Key>
inline auto unordered_set<Key>::to_expand() noexcept -> IteratorType {
  auto *new_array = new std::array<std::vector<value_type>, TABLE_SIZE>();
  table.push_back(new_array);
  capacity += TABLE_SIZE;
  return --table.end();
}

template <class Key>
inline auto unordered_set<Key>::size() const noexcept -> size_type {
  return this->size_;
}

template <class Key>
inline auto unordered_set<Key>::add(std::vector<value_type> &vec,
                                    const key_type &key) noexcept -> void {
  vec.push_back(key);
  size_++;
}

template <class Key>
inline auto unordered_set<Key>::bucket_count() const noexcept -> size_type {
  return this->size_;
}

template <class Key>
inline auto unordered_set<Key>::empty() const noexcept -> bool {
  return size() == 0u;
}

template <class Key>
inline auto unordered_set<Key>::get_index(const key_type &key) const noexcept
    -> size_type {
  return hashFunction(key) % TABLE_SIZE;
}

template <class Key>
inline auto unordered_set<Key>::erase(const key_type &key) noexcept -> void {
  size_t bucket_index = get_index(key);
  auto it = table.begin();

  for (auto &arr = *it; it != table.end(); ++it)
    if (auto &vec = arr->at(bucket_index); !vec.empty() && vec.front() == key) {
      vec.pop_back();
      size_--;
      return;
    }
}

template <class Key>
inline auto unordered_set<Key>::bucket_size(const key_type &key) const noexcept
    -> size_type {
  return this->count(key);
}

template <class Key>
inline auto unordered_set<Key>::count(const key_type &key) const noexcept
    -> size_type {
  size_t bucket_index = get_index(key);
  auto it = table.begin();

  for (auto &arr = *it; it != table.end(); ++it)
    if (auto &vec = arr->at(bucket_index); !vec.empty() && vec.front() == key)
      return vec.size();
  return 0;
}

template <class Key>
inline auto unordered_set<Key>::contains(const key_type &key) const noexcept
    -> bool {
  return static_cast<bool>(this->count(key));
}

template <class Key>
inline auto unordered_set<Key>::load_factor() const noexcept -> float {
  return static_cast<float>(capacity) / static_cast<float>(size_);
}

// template <class value_type>
// template <typename... Args>
// inline auto unordered_set<value_type>::insert_many(Args &&...args)
//     -> std::vector<std::pair<iterator, bool>> {
//   std::vector<std::pair<iterator, bool>> results;
//   (results.insert_many_back(this->insert(std::forward<Args>(args))), ...);
//   return results;
// }

}  // namespace s21

#endif  // __S21_UNORDERED_CORE_SET__