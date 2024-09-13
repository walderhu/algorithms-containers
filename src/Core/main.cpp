#include <list>

#include "s21_containers.hpp"

int main() {
  s21::list<int> s21_list_first = {1};
  s21::list<int> s21_list_second = {2, 3, 4, 5};
  std::list<int> std_list_first = {1};
  std::list<int> std_list_second = {2, 3, 4, 5};
  s21::list<int>::iterator s21_it = s21_list_first.begin();
  std::list<int>::iterator std_it = std_list_first.begin();
  s21_list_first.splice(s21_it, s21_list_second);
  std_list_first.splice(std_it, std_list_second);
  s21_list_first.print();
  return 0;
}

// BinaryTree