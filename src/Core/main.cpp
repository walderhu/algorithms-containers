#include <deque>
#include <iostream>
#include <list>
#include <set>

#include "s21_containers.hpp"
using namespace std;
int main() {
  s21::multiset<int> _multiset({5, 4, 1, 0, 2, 1, 4, 3, 3, 2});
  auto i = _multiset.end();
  --i;
  i--;
  return 0;
}

// BinaryTree