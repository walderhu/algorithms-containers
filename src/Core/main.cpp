#include "s21_list.hpp"

int main() {
  s21::List<int> list;
  list.push_back(2);
  list.push_back(3);
  list.push_back(1);

  list.print();
  list.sort();
  list.print();
  // list.reverse();
  // list.clear();
  // list.print();

  return 0;
}