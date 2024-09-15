#include <deque>
#include <list>
#include <set>

#include "s21_containers.hpp"

int main() {
  //   s21::set<int> s21_set = {4, 3, 2, 1, 1, 2, 3, 4, 5, 6, 7};
  //   s21::set<int> s21_set = {1, 2, 3, 4, 5};
  s21::set<int> s21_set = {4, 3, 2, 1};
  for (auto it = s21_set.begin(); it != s21_set.end(); ++it)
    std::cout << *it << std::endl;
  return 0;
}

// BinaryTree