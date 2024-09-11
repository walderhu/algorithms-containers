#include <list>

#include "s21_list.hpp"

template <typename type>
void print(type value) {
  std::cout << value << std::endl;
}

int main() {
  s21::list<int> s21_list;
  std::list<int> std_list;
  s21::list<int>::iterator s21_it;
  std::list<int>::iterator std_it;
  s21_it = s21_list.begin();
  std_it = std_list.begin();
  s21_list.insert(s21_it, 5);
  std_list.insert(std_it, 5);
  print(s21_list);
  // EXPECT_EQ(s21_list.front(), std_list.front());
  // EXPECT_EQ(s21_list.back(), std_list.back());
  // s21_list.insert(s21_it, 7);
  // std_list.insert(std_it, 7);
  // s21_list.insert(s21_it, 9);
  // std_list.insert(std_it, 9);
  // EXPECT_EQ(s21_list.front(), std_list.front());
  // EXPECT_EQ(s21_list.back(), std_list.back());
}