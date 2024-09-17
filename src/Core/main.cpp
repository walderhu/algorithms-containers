#include <deque>
#include <iostream>
#include <list>
#include <set>

#include "s21_containers.hpp"
using namespace std;
int main() {
  s21::multiset<std::string> s21_multiset({"this", "world", "is mine"});
  std::multiset<std::string> std_multiset({"this", "world", "is mine"});
  std::cout << *(--(s21_multiset.end())) << std::endl;
  std::cout << *(--(std_multiset.end())) << std::endl;

  return 0;
}

// BinaryTree