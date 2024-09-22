#include <list>
#include <unordered_set>

#include "s21_containers.hpp"

int main() {
  // std::unordered_set<int> ust = {5, 5, 5, 5, 3, 2, 1, 0, -3, 11};
  s21::unordered_set<int> ust = {5, 5, 5, 5, 3, 2, 1, 0, -3, 11};

  // for (; it != ust.end(); ++it) DEBUG(*it);
  // for (auto it = ust.begin(); it != ust.end(); ++it) DEBUG(*it);

  auto it = ust.end();
  --it;
  // --it;
  // --it;
  // --it;
  DEBUG(*it);
  // if (auto it = ust.end(); it != ust.begin()) {
  // --it;
  // for (; it != ust.end(); --it) std::cout << *it << " ";
  // }

  return 0;
}

/*
неупорядоченное множество не поддерживает дубликаты, прямо как обычный сет

наследовать его от односвязного списка как изначально планировалось
является глупой идеей, поскольку тогда алгоритмы добавления будут занимать
O(n) времени, где n это количество элементво в структуре

по идее доступ к элементу занимает O(1) и структура реализована на хэш функции

порядок положения элементов задается тоже хэш функцией, он рандомный (своего
рода хэштаблица)
 если заполняем 0,1,2,3,4,5 может храниться 5,4,0,1,2,3

 мультисет делается очень легко после этого, просто у нас есть бакеты в которых
 хранятся значения
 и в мультисете они просто пихаются туда, в обычно сете тоже самое, с учетом
того что в ковше всегда 1 элемент

ТЕХНИЧЕСКАЯ ЗАДАЧА

ust.emplace
  ust.bucket
ust.equal_range
ust.extract

ust.find
ust.get_allocator
  ust.key_eq

  ust.max_bucket_count
  ust.max_load_factor

  ust.merge
  ust.swap

  ust.rehash
  ust.reserve
ust.emplace_hint
cbegin cend begin end
*/