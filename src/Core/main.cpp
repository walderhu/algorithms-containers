#include <deque>
#include <iostream>
#include <list>
#include <set>

#include "s21_containers.hpp"
using namespace std;
int main() {
  s21::multiset<int> s21_multiset = {1, 1, 2, 3, 3, 4, 4, 5};
  // s21::multiset<int> s21_multiset;
  // s21_multiset.insert(1);
  // s21_multiset.insert(1);
  // s21_multiset.insert(2);
  // s21_multiset.insert(3);
  // s21_multiset.insert(3);
  // s21_multiset.insert(4);
  // s21_multiset.insert(4);
  // s21_multiset.insert(5);

  for (auto it = s21_multiset.begin(); it != s21_multiset.end(); ++it)
    cout << *it << endl;

  return 0;
}

// BinaryTree