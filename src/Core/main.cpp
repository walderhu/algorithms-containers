#include <cassert>
#include <iostream>
#include <memory>

#include "s21_containers.hpp"

void test1() {
  s21::unordered_set<int, 200> ust;
  //  = {5, 5, 5, 5, 3, 2, 1, 0, -3, 11};
  // assert(!ust.empty());
  // DEBUG(ust);
}

int main() {
  test1();
  return 0;
}