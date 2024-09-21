#if !defined(__S21_UNORDERED_CORE_MULTISET__)
#define __S21_UNORDERED_CORE_MULTISET__

#include "s21_unordered_multiset.hpp"

namespace s21 {

template <class value_type>
inline unordered_multiset<value_type>::unordered_multiset() noexcept
    : unordered_set<value_type>::unordered_set(), bucket_count_(0u) {}

template <class value_type>
inline unordered_multiset<value_type>::unordered_multiset(
    std::initializer_list<value_type> const &items) noexcept
    : unordered_set<value_type>::unordered_set(items) {}

template <class value_type>
inline unordered_multiset<value_type>::~unordered_multiset() noexcept {
  unordered_set<value_type>::clear();
}

template <class Key>
inline void unordered_multiset<Key>::insert(const key_type &key) noexcept {
  size_t index = unordered_set<Key>::get_index(key);
  auto it = table.begin();

  for (auto &arr = *it; it != table.end(); ++it)
    if (auto &vec = arr->at(index); vec.empty() || vec.front() == key) {
      add(vec, key);
      return;
    }

  if (it == table.end()) {
    it = this->to_expand();
    auto &vec = (*it)->at(index);
    add(vec, key);
  }
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

если я пробежался по всем нодам структуры и так не смог найти ни одного узла,
который был бы свободен, значит мой указатель на It будет ссылаться на конец
списка, это я и проверяю в некст условии, если итератор указывает на конец,
значит мы не добавили элемент я добавляю новый узел, получаю итератор на него, и
присваиваю ему нужное мне значение
*/

template <class Key>
inline void unordered_multiset<Key>::debug() {
  auto it = table.begin();

  for (auto &arr = *it; it != table.end(); ++it)
    for (size_t i = 0u; i < TABLE_SIZE; i++)
      if (auto &vec = arr->at(i); !vec.empty())
        for (auto iter = vec.begin(); iter != vec.end(); ++iter)
          std::cout << *iter << " ";

  std::cout << std::endl;
}

template <class Key>
inline auto unordered_multiset<Key>::bucket_count() const noexcept
    -> size_type {
  return this->bucket_count_;
}

template <class Key>
inline auto unordered_multiset<Key>::add(s21::vector<value_type> &vec,
                                         const key_type &key) noexcept -> void {
  if (vec.empty()) bucket_count_++;
  vec.push_back(key);
  size_++;
}

template <class Key>
inline auto unordered_multiset<Key>::load_factor() const noexcept -> float {
  return static_cast<float>(capacity) / static_cast<float>(bucket_count_);
}
}  // namespace s21

#endif  // __S21_UNORDERED_CORE_MULTISET__
