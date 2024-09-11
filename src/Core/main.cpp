#include "s21_list.hpp"

int main() {
  // s21::list<int> lst = {2, 3, 1};
  // lst.push_back(2);
  // lst.push_back(3);
  // lst.push_back(1);
  // s21::list<int> list2 = lst;

  // lst.print();
  // lst.sort();
  // std::cout << lst << std::endl;
  // lst.reverse();
  // std::cout << lst << std::endl;
  // auto it = lst.begin();
  // ++it;
  // ++it;
  // lst.insert(it, {5, 2, 3});
  // std::cout << lst << std::endl;

  s21::list<int> s21_list = {1, 2, 3};
  s21::list<int>::iterator s21_it;
  s21_it = s21_list.end();
  --s21_it;
  std::cout << *s21_it << std::endl;
  return 0;
}