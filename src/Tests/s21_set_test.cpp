#include "s21_containers_test.hpp"

TEST(Set, Constructor_Default) {
  s21::set<int> s21_set;
  std::set<int> std_set;
  EXPECT_EQ(s21_set.empty(), std_set.empty());
}