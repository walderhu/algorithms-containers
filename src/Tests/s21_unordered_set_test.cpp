#include "s21_containers_test.hpp"

TEST(unordered_set, ConstructorDefaultSet) {
  s21::unordered_set<int> s21_ust;
  std::unordered_set<int> std_ust;
  EXPECT_EQ(s21_ust.empty(), std_ust.empty());
}

TEST(unordered_set, InsertTest) {
  s21::unordered_set<int> s21_ust;
  std::unordered_set<int> std_ust;

  s21_ust.insert(2);
  s21_ust.insert(2);
  s21_ust.insert(2);
  s21_ust.insert(3);
  s21_ust.insert(4);

  std_ust.insert(2);
  std_ust.insert(2);
  std_ust.insert(2);
  std_ust.insert(3);
  std_ust.insert(4);

  EXPECT_EQ(s21_ust.size(), std_ust.size());
}

// TEST(unordered_set, InsertManyTest) {
//   s21::unordered_set<int> s21_set;
//   std::unordered_set<int> std_set;
//   s21_set.insert_many(2, 3, 2, 4, 5, 6, 7);

//   std_set.insert(2);
//   std_set.insert(3);
//   std_set.insert(2);
//   std_set.insert(4);
//   std_set.insert(5);
//   std_set.insert(6);
//   std_set.insert(7);
//   EXPECT_EQ(s21_set.size(), std_set.size());
// }

// TEST(unordered_set, ConstructorInitializerSet) {
//   s21::unordered_set<char> s21_set = {'x', 'b', 'z', 'y'};
//   std::unordered_set<char> std_set = {'x', 'b', 'z', 'y'};
//   EXPECT_EQ(s21_set.size(), std_set.size());
//   auto s21_it = s21_set.begin();
//   auto std_it = std_set.begin();
//   for (; s21_it != s21_set.end(); ++s21_it, ++std_it) {
//     EXPECT_TRUE(*std_it == *s21_it);
//   }
// }

// TEST(unordered_set, ConstructorInitializer2Set) {
//   s21::unordered_set<char> s21_set = {};
//   std::unordered_set<char> std_set = {};
//   EXPECT_EQ(s21_set.size(), std_set.size());
//   auto s21_it = s21_set.begin();
//   auto std_it = std_set.begin();
//   for (; s21_it != s21_set.end(); ++s21_it, ++std_it) {
//     EXPECT_TRUE(*std_it == *s21_it);
//   }
// }

// TEST(unordered_set, ConstructorCopySet) {
//   s21::unordered_set<int> s21_set = {1, 2, 3, 4, 5};
//   std::unordered_set<int> std_set = {1, 2, 3, 4, 5};
//   s21::unordered_set<int> s21_set_copy = s21_set;
//   std::unordered_set<int> std_set_copy = std_set;
//   EXPECT_EQ(s21_set_copy.size(), std_set_copy.size());
//   auto s21_it = s21_set_copy.begin();
//   auto std_it = std_set_copy.begin();
//   for (; s21_it != s21_set_copy.end(); ++s21_it, ++std_it)
//     EXPECT_TRUE(*std_it == *s21_it);
// }

// TEST(unordered_set, ConstructorMoveSet) {
//   s21::unordered_set<int> s21_set = {1, 2, 3, 4, 5};
//   std::unordered_set<int> std_set = {1, 2, 3, 4, 5};
//   s21::unordered_set<int> s21_set_copy = std::move(s21_set);
//   std::unordered_set<int> std_set_copy = std::move(std_set);
//   EXPECT_EQ(s21_set.size(), std_set.size());
//   EXPECT_EQ(s21_set_copy.size(), std_set_copy.size());
//   auto s21_it = s21_set_copy.begin();
//   auto std_it = std_set_copy.begin();
//   for (; s21_it != s21_set_copy.end(); ++s21_it, ++std_it) {
//     EXPECT_TRUE(*std_it == *s21_it);
//   }
// }

// TEST(unordered_set, SetIteratorsSet) {
//   s21::unordered_set<std::string> s21_set = {"This", "is", "s21",
//   "unordered_set"}; std::unordered_set<std::string> std_set = {"This", "is",
//   "s21", "unordered_set"}; auto s21_it = s21_set.begin(); auto std_it =
//   std_set.begin(); EXPECT_TRUE(*std_it == *s21_it); s21_it = s21_set.end();
//   std_it = std_set.end();
//   --s21_it;
//   --std_it;
//   EXPECT_TRUE(*std_it == *s21_it);
// }

// TEST(unordered_set, CapacitySet) {
//   s21::unordered_set<char> s21_empty_set;
//   std::unordered_set<char> std_empty_set;
//   EXPECT_EQ(s21_empty_set.empty(), std_empty_set.empty());
//   EXPECT_EQ(s21_empty_set.size(), std_empty_set.size());
//   s21_empty_set.insert('b');
//   std_empty_set.insert('c');
//   EXPECT_EQ(s21_empty_set.empty(), std_empty_set.empty());
//   EXPECT_EQ(s21_empty_set.size(), std_empty_set.size());
// }

// TEST(unordered_set, ClearSet) {
//   s21::unordered_set<char> s21_empty_set;
//   std::unordered_set<char> std_empty_set;
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

// TEST(unordered_set, InsertSet) {
//   s21::unordered_set<std::string> s21_set = {"This", "is", "s21",
//   "unordered_set"}; std::unordered_set<std::string> std_set = {"This", "is",
//   "s21", "unordered_set"}; auto s21_pr = s21_set.insert("best"); auto std_pr
//   = std_set.insert("best"); EXPECT_TRUE(s21_pr.second == std_pr.second);
//   EXPECT_TRUE(*s21_pr.first == *std_pr.first);
//   s21_pr = s21_set.insert("is");
//   std_pr = std_set.insert("is");
//   EXPECT_TRUE(s21_pr.second == std_pr.second);
//   EXPECT_TRUE(*s21_pr.first == *std_pr.first);
// }

// TEST(unordered_set, EraseSet) {
//   s21::unordered_set<int> s21_set = {5, 4, 3, 2, 7, 8, 9};
//   std::unordered_set<int> std_set = {5, 4, 3, 2, 7, 8, 9};
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

// TEST(unordered_set, SwapSet) {
//   s21::unordered_set<int> s21_set = {1};
//   s21::unordered_set<int> s21_swap_set = {3, 4, 5};

//   s21_set.swap(s21_swap_set);
//   EXPECT_EQ(s21_set.size(), 3);
//   EXPECT_EQ(s21_swap_set.size(), 1);
//   EXPECT_EQ(*s21_set.begin(), 3);
//   EXPECT_EQ(*s21_swap_set.begin(), 1);
// }

// TEST(unordered_set, MergeSet) {
//   s21::unordered_set<int> s21_set = {1};
//   s21::unordered_set<int> s21_merge_set = {3, 4, 5};
//   s21_set.merge(s21_merge_set);

//   std::unordered_set<int> std_set = {1};
//   std::unordered_set<int> std_merge_set = {3, 4, 5};
//   std_set.merge(std_merge_set);
//   auto s21_it = s21_set.begin();
//   auto std_it = std_set.begin();
//   for (; s21_it != s21_set.end(); ++s21_it, ++std_it) {
//     EXPECT_TRUE(*std_it == *s21_it);
//   }
//   EXPECT_EQ(std_set.size(), s21_set.size());
//   EXPECT_EQ(s21_merge_set.size(), std_merge_set.size());
// }

// TEST(unordered_set, FindSet) {
//   s21::unordered_set<double> s21_set = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
//   s21::unordered_set<double> std_set = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
//   auto s21_it = s21_set.find(2.4);
//   auto std_it = std_set.find(2.4);
//   EXPECT_TRUE(*std_it == *s21_it);
// }

// TEST(unordered_set, ContainsSet) {
//   s21::unordered_set<double> s21_set = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
//   s21::unordered_set<double> std_set = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
//   EXPECT_EQ(s21_set.contains(2), std_set.contains(2));
//   EXPECT_EQ(s21_set.contains(2.1), std_set.contains(2.1));
// }