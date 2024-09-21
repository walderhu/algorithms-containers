#include <deque>
#include <iostream>
#include <list>
#include <set>
#include <string>  // TODO убрать
#include <unordered_set>

#include "s21_containers.hpp"
int main() {
  // s21::unordered_set<int> ust;
  s21::unordered_multiset<int> ust;
  // auto x = ust.hashFunction(5);
  ust.insert(5);
  ust.insert(5);
  ust.insert(5);
  ust.insert(5);
  ust.insert(3);
  ust.insert(2);
  ust.insert(1);
  ust.insert(0);
  ust.insert(-3);
  ust.insert(11);
  // ust.debug();

  for (auto it = ust.begin(); it != ust.end(); ++it) DEBUG(*it);
  DEBUG(ust.count(5));
  DEBUG(ust.bucket_count());
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



по сути у меня мапа ключом которой является хэш числа??
*/
// ТЕХНИЧЕСКАЯ ЗАДАЧА

// ust.emplace
//   ust.bucket
// ust.equal_range
// ust.extract

// ust.find
// ust.get_allocator
//   ust.key_eq

//   ust.max_bucket_count
//   ust.max_load_factor

//   ust.merge
//   ust.swap

//   ust.rehash
//   ust.reserve
// ust.emplace_hint
// cbegin cend begin end
