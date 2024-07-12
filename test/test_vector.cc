#include <iostream>
#include <memory>

#include "basic.hpp"
#include "vector.hpp"

void tester(std::string name, std::shared_ptr<linalg::Vector<int>> a) {
  std::cout << "Test: " << name << std::endl;
  std::cout << *a << std::endl;
}

int main() {
  auto a = linalg::Vector<int>::create(
      10, new int[10]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
  tester("Create and std output", a);

  auto b = linalg::Vector<int>::create(
      10, new int[10]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
  auto c = linalg::dot<int>(*a, *b);

  std::cout << "Dot product: " << c << std::endl;
  return 0;
}