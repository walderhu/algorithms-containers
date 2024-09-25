#include <cassert>
#include <iostream>
#include <memory>

#include "s21_containers.hpp"

void test1() {
  s21::unordered_set<int> ust = {5, 5, 5, 5, 3, 2, 1, 0, -3, 11};
  assert(!ust.empty());
  DEBUG(ust);
}

void test2() {
  s21::unordered_set<std::shared_ptr<int>> ust;
  ust.insert(std::make_shared<int>(5));
  auto it = ust.begin();
  DEBUG(**it);
}

void foo(int x) {
  if (x > 10) throw std::bad_alloc();
}

void bar(int x) {
  try {
    foo(x);
  } catch (const std::bad_alloc &e) {
    std::cerr << e.what() << '\n';
  }
}

int main() {
  bar(11);
  // test1();
  return 0;
}

/*
а че я вообще копаюсь тут((
самый изи способ сделать все это вместо моего листа сделать vector
и будет
vector<array<vector, 100>> и так уже манипулировать моей хэш таблицей
пофигу вообще на все, это будет выглядеть мега легко и понятно
самое главное понятно и оптимизировано
я везде абсолютно буду делегировать все вычисления на уже существующие методы
и ну нафиг тот лист, все равно можно установить начальное значение
и эта типо динамическая расширяемость с хз каким временем итерации отпадет

крч если и переделывать то на такой парадигме
*/