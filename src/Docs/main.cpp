#include <initializer_list>
#include <iostream>

void sum(std::initializer_list<int> list) {
  int result = 0;
  for (int i : list) {
    result += i;
  }
  std::cout << "Sum: " << result << std::endl;
}

template <typename... Args>
void sum_variadic(Args... args) {
  sum({args...});
}

int main() {
  sum_variadic(1, 2, 3, 4);
  return 0;
}