#include "s21_list.hxx"

int main() {
  s21::List<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  // std::cout << list << std::endl;
  list.print();
  return 0;
}