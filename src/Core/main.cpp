#include "s21_list.hpp"

int main() {
  s21::List<int> list = {2, 3, 1};
  list.push_back(2);
  list.push_back(3);
  list.push_back(1);
  // s21::List<int> list2(list);  // BUG
  s21::List<int> list2 = list;

  list.print();
  list.sort();
  std::cout << list << std::endl;
  list.reverse();
  std::cout << list << std::endl;
  auto it = list.begin();
  ++it;
  ++it;
  list.insert(it, {5, 2, 3});
  std::cout << list << std::endl;
  // list.clear();
  // list.print();

  return 0;
}