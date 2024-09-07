#include "s21_list.hxx"

int main() {
  s21::List<int> list;
  list.value = 5;

  std::cout << list.value << std::endl;
  return 0;
}
