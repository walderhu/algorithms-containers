#include "s21_containers_test.hpp"

TEST(set, ConstructorDefaultSet) {
  s21::set<int> s21_empty_set;
  std::set<int> std_empty_set;
  EXPECT_EQ(s21_empty_set.empty(), std_empty_set.empty());
}

TEST(set, InsertTest) {
  s21::set<int> s21_set;
  std::set<int> std_set;

  s21_set.insert(2);
  s21_set.insert(2);
  s21_set.insert(2);
  s21_set.insert(3);
  s21_set.insert(4);

  std_set.insert(2);
  std_set.insert(2);
  std_set.insert(2);
  std_set.insert(3);
  std_set.insert(4);

  EXPECT_EQ(s21_set.size(), std_set.size());
}

TEST(set, InsertManyTest) {
  s21::set<int> s21_set;
  std::set<int> std_set;
  s21_set.insert_many(2, 3, 2, 4, 5, 6, 7);

  std_set.insert(2);
  std_set.insert(3);
  std_set.insert(2);
  std_set.insert(4);
  std_set.insert(5);
  std_set.insert(6);
  std_set.insert(7);
  EXPECT_EQ(s21_set.size(), std_set.size());
}

// TEST(set, ConstructorInitializerSet) {
//   s21::set<char> s21_set = {'x', 'b', 'z', 'y'};
//   std::set<char> std_set = {'x', 'b', 'z', 'y'};
//   EXPECT_EQ(s21_set.size(), std_set.size());
//   auto s21_it = s21_set.begin();
//   auto std_it = std_set.begin();
//   for (; s21_it != s21_set.end(); ++s21_it, ++std_it) {
//     EXPECT_TRUE(*std_it == *s21_it);
//   }
// }

// TEST(set, ConstructorInitializer2Set) {
//   s21::set<char> s21_set = {};
//   std::set<char> std_set = {};
//   EXPECT_EQ(s21_set.size(), std_set.size());
//   auto s21_it = s21_set.begin();
//   auto std_it = std_set.begin();
//   for (; s21_it != s21_set.end(); ++s21_it, ++std_it) {
//     EXPECT_TRUE(*std_it == *s21_it);
//   }
// }

// TEST(set, ConstructorCopySet) {
//   s21::set<int> s21_set = {1, 2, 3, 4, 5};
//   std::set<int> std_set = {1, 2, 3, 4, 5};
//   s21::set<int> s21_set_copy = s21_set;
//   std::set<int> std_set_copy = std_set;
//   EXPECT_EQ(s21_set_copy.size(), std_set_copy.size());
//   auto s21_it = s21_set_copy.begin();
//   auto std_it = std_set_copy.begin();
//   for (; s21_it != s21_set_copy.end(); ++s21_it, ++std_it) {
//     EXPECT_TRUE(*std_it == *s21_it);
//   }
// }

// TEST(set, ConstructorMoveSet) {
//   s21::set<int> s21_set = {1, 2, 3, 4, 5};
//   std::set<int> std_set = {1, 2, 3, 4, 5};
//   s21::set<int> s21_set_copy = std::move(s21_set);
//   std::set<int> std_set_copy = std::move(std_set);
//   EXPECT_EQ(s21_set.size(), std_set.size());
//   EXPECT_EQ(s21_set_copy.size(), std_set_copy.size());
//   auto s21_it = s21_set_copy.begin();
//   auto std_it = std_set_copy.begin();
//   for (; s21_it != s21_set_copy.end(); ++s21_it, ++std_it) {
//     EXPECT_TRUE(*std_it == *s21_it);
//   }
// }

// TEST(set, SetIteratorsSet) {
//   s21::set<std::string> s21_set = {"This", "is", "s21", "set"};
//   std::set<std::string> std_set = {"This", "is", "s21", "set"};
//   auto s21_it = s21_set.begin();
//   auto std_it = std_set.begin();
//   EXPECT_TRUE(*std_it == *s21_it);
//   s21_it = s21_set.end();
//   std_it = std_set.end();
//   --s21_it;
//   --std_it;
//   EXPECT_TRUE(*std_it == *s21_it);
// }

TEST(set, CapacitySet) {
  s21::set<char> s21_empty_set;
  std::set<char> std_empty_set;
  EXPECT_EQ(s21_empty_set.empty(), std_empty_set.empty());
  EXPECT_EQ(s21_empty_set.size(), std_empty_set.size());
  s21_empty_set.insert('b');
  std_empty_set.insert('c');
  EXPECT_EQ(s21_empty_set.empty(), std_empty_set.empty());
  EXPECT_EQ(s21_empty_set.size(), std_empty_set.size());
}

// TEST(set, ClearSet) {
//   s21::set<char> s21_empty_set;
//   std::set<char> std_empty_set;
//   s21_empty_set.clear();
//   std_empty_set.clear();
//   EXPECT_EQ(s21_empty_set.empty(), std_empty_set.empty());
//   EXPECT_EQ(s21_empty_set.size(), std_empty_set.size());
//   s21_empty_set.insert('a');
//   std_empty_set.insert('b');
//   EXPECT_EQ(s21_empty_set.empty(), std_empty_set.empty());
//   EXPECT_EQ(s21_empty_set.size(), std_empty_set.size());
//   s21_empty_set.clear();
//   std_empty_set.clear();
//   EXPECT_EQ(s21_empty_set.empty(), std_empty_set.empty());
//   EXPECT_EQ(s21_empty_set.size(), std_empty_set.size());
// }

// TEST(set, InsertSet) {
//   s21::set<std::string> s21_set = {"This", "is", "s21", "set"};
//   std::set<std::string> std_set = {"This", "is", "s21", "set"};
//   auto s21_pr = s21_set.insert("best");
//   auto std_pr = std_set.insert("best");
//   EXPECT_TRUE(s21_pr.second == std_pr.second);
//   EXPECT_TRUE(*s21_pr.first == *std_pr.first);
//   s21_pr = s21_set.insert("is");
//   std_pr = std_set.insert("is");
//   EXPECT_TRUE(s21_pr.second == std_pr.second);
//   EXPECT_TRUE(*s21_pr.first == *std_pr.first);
// }

// TEST(set, EraseSet) {
//   s21::set<int> s21_set = {5, 4, 3, 2, 7, 8, 9};
//   std::set<int> std_set = {5, 4, 3, 2, 7, 8, 9};
//   auto size = s21_set.size();
//   s21_set.erase(s21_set.end());
//   auto new_size = s21_set.size();
//   EXPECT_EQ(size, new_size);
//   s21_set.erase(s21_set.begin());
//   std_set.erase(std_set.begin());
//   auto s21_it = s21_set.begin();
//   auto std_it = std_set.begin();
//   for (; s21_it != s21_set.end(); ++s21_it, ++std_it) {
//     EXPECT_TRUE(*std_it == *s21_it);
//   }
// }

// TEST(set, SwapSet) {
//   s21::set<int> s21_set = {1};
//   s21::set<int> s21_swap_set = {3, 4, 5};

//   s21_set.swap(s21_swap_set);
//   EXPECT_EQ(s21_set.size(), 3);
//   EXPECT_EQ(s21_swap_set.size(), 1);
//   EXPECT_EQ(*s21_set.begin(), 3);
//   EXPECT_EQ(*s21_swap_set.begin(), 1);
// }

// TEST(set, MergeSet) {
//   s21::set<int> s21_set = {1};
//   s21::set<int> s21_merge_set = {3, 4, 5};
//   s21_set.merge(s21_merge_set);

//   std::set<int> std_set = {1};
//   std::set<int> std_merge_set = {3, 4, 5};
//   std_set.merge(std_merge_set);
//   auto s21_it = s21_set.begin();
//   auto std_it = std_set.begin();
//   for (; s21_it != s21_set.end(); ++s21_it, ++std_it) {
//     EXPECT_TRUE(*std_it == *s21_it);
//   }
//   EXPECT_EQ(std_set.size(), s21_set.size());
//   EXPECT_EQ(s21_merge_set.size(), std_merge_set.size());
// }

// TEST(set, FindSet) {
//   s21::set<double> s21_set = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
//   s21::set<double> std_set = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
//   auto s21_it = s21_set.find(2.4);
//   auto std_it = std_set.find(2.4);
//   EXPECT_TRUE(*std_it == *s21_it);
// }

// TEST(set, ContainsSet) {
//   s21::set<double> s21_set = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
//   s21::set<double> std_set = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
//   EXPECT_EQ(s21_set.contains(2), std_set.contains(2));
//   EXPECT_EQ(s21_set.contains(2.1), std_set.contains(2.1));
// }