#include "s21_containers_test.hpp"

void run_tests() {
  ::testing::InitGoogleTest();
  int result = RUN_ALL_TESTS();
  std::cout << "\e[32mSuccess: " << (result == 0 ? 1 : 0) << "\e[0m\n";
  std::cout << "\e[31mFailures: " << (result != 0 ? 1 : 0) << "\e[0m\n";
}

int main(int argc, char **argv) {
  run_tests();
  return 0;
}