#include "s21_containers_test.hpp"

TEST(unordered_multiset, ConstructorDefaultSet) {
  s21::unordered_multiset<int> s21_mst;
  std::unordered_multiset<int> std_mst;
  EXPECT_EQ(s21_mst.empty(), std_mst.empty());
}
