#include <iostream>

#include "s21_containers.hpp"

using namespace std;

void test1() {
  s21::unordered_set<int> ust;  //= {5, 5, 5, 5, 3, 2, 1, 0, -3, 11};
  ust.insert(5);
  ust.insert(5);
  ust.insert(5);
  ust.insert(3);
  ust.insert(2);
  ust.insert(1);
  cout << ust << endl;
}

void test2() { cout << 5 % 1 << endl; }

int main() {
  test1();
  return 0;
}
