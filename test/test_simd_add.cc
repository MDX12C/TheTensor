#include <iostream>

#include "simd_add.hpp"

int main() {
  const int size = 16;
  float a[size], b[size], result[size];

  for (int i = 0; i < size; ++i) {
    a[i] = i;
    b[i] = size - i;
  }

  simd_add(a, b, result, size);

  std::cout << "Result: ";
  for (int i = 0; i < size; ++i) {
    std::cout << result[i] << " ";
  }
  std::cout << std::endl;

  return 0;
}