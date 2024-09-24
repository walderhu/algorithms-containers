#include <iostream>
#include <list>
#include <unordered_set>
using namespace std;
#include "s21_containers.hpp"
int main() {
  s21::unordered_set<int> ust = {5, 5, 5, 5, 3, 2, 1, 0, -3, 11};
  // auto it = ust.cbegin();
  // ust.emplace_hint(it, 99, 98, 312);
  // ust.debug();
  cout << ust << endl;

  return 0;
}
