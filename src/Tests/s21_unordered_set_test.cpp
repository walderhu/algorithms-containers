#include "s21_containers_test.hpp"

TEST(unordered_set, ConstructorDefaultSet) {
  s21::unordered_set<int> s21_ust;
  std::unordered_set<int> std_ust;
  EXPECT_EQ(s21_ust.empty(), std_ust.empty());
}
