#include "s21_list.hxx"

int main() {
  s21::List<int> list;
  list.push_back(2);
  list.push_back(3);
  list.push_back(1);

  std::cout << list << std::endl;
  list.sort();
  std::cout << list << std::endl;

  return 0;
}