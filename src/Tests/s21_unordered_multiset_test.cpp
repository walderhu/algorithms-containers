// #include "s21_containers_test.hpp"

// TEST(unordered_multiset, ConstructorDefaultSet) {
//   s21::unordered_multiset<int> s21_mst;
//   std::unordered_multiset<int> std_mst;
//   EXPECT_EQ(s21_mst.empty(), std_mst.empty());
// }

// TEST(unordered_multiset, InsertTest) {
//   s21::unordered_multiset<int> s21_mst;
//   std::unordered_multiset<int> std_mst;

//   s21_mst.insert(2);
//   s21_mst.insert(2);
//   s21_mst.insert(2);
//   s21_mst.insert(3);
//   s21_mst.insert(4);

//   std_mst.insert(2);
//   std_mst.insert(2);
//   std_mst.insert(2);
//   std_mst.insert(3);
//   std_mst.insert(4);

//   EXPECT_EQ(s21_mst.size(), std_mst.size());
// }