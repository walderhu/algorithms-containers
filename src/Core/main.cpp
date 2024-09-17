#include <deque>
#include <iostream>
#include <list>
#include <set>

#include "s21_containers.hpp"
using namespace std;
int main() {
  s21::multiset<int> _multiset({5, 4, 1, 0, 2, 1, 4, 3, 3, 2});
  auto i = _multiset.find(5);

  // for (auto it = _multiset.begin(); it != _multiset.end(); ++it)
  // cout << *it << " ";
  // cout << endl;

  _multiset.erase(i);

  for (auto it = _multiset.begin(); it != _multiset.end(); ++it)
    cout << *it << " ";
  cout << endl;
  cout << _multiset.contains(5) << endl;

  return 0;
}

// BinaryTree