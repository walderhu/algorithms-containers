#include "s21_list_test.hxx"

TEST(S21ListTest, ListTest1) { EXPECT_EQ(1, 1); }

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