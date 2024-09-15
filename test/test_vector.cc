#include <iostream>
#include <memory>

#include "../include/interface.hpp"

void tester(std::string name, std::shared_ptr<linalg::Vector<int>> a) {
  std::cout << "Test: " << name << std::endl;
  std::cout << *a << std::endl;
}

int main() {
  INITIALIZE;
  auto p = new int[10]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  printf("make an array of 10 int elements\n");
  auto a = new linalg::Vector<int>(10, p);
  printf("create a vector from the array\n");

  auto b = new linalg::Vector<int>(10, p);
  delete[] p;
  auto c = ((*a) * (*b)).sum();

  std::cout << "Test: Dot product " << std::endl << c << std::endl;

  std::cout << "Test: sum() for vectors" << std::endl;
  std::cout << a->sum() << std::endl;

  std::cout << "Test: operator[] for vector" << std::endl;
  for (auto i = 0; i < a->size(); i++) std::cout << (*a)[i] << std::endl;

  std::cout << "Test: resize() for vector" << std::endl;
  a->resize(5);
  std::cout << *a << std::endl;

  std::cout << "Test: load() for vector" << std::endl;
  p = new int[3]{1, 2, 3};
  a->load(3, p);
  delete[] p;
  std::cout << *a << std::endl;
  std::cout << "Total block count: "
            << memory_maintainer::MemoryManager::getBlockCount() << std::endl;
  std::cout << "Total usage: "
            << memory_maintainer::MemoryManager::getTotalUsage() << std::endl;
  delete a;
  delete b;
  return 0;
}