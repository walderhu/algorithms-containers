#include <deque>
#include <list>
#include <set>

#include "s21_containers.hpp"

int main() {
  s21::set<int> s21_set = {1, 2, 3, 4};
  for (auto it = s21_set.begin(); it != s21_set.end(); ++it)
    std::cout << *it << std::endl;
  return 0;
}

// BinaryTree