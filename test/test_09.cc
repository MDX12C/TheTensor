#include <cstdarg>
#include <iostream>
using namespace std;
bool ptf(unsigned int, ...);
signed main() {
  int a = 3;
  int *arr = new int[a];
  arr[0] = 1;
  arr[1] = 2;
  arr[2] = 3;
  ptf(a, arr, arr + 1, arr + 2);
  delete[] arr;
  return 0;
}
bool ptf(unsigned int alpha, ...) {
  if (alpha <= 0)
    return false;
  va_list argument;
  va_start(argument, alpha);
  for (auto i = 0; i < alpha; i++) {
    auto ptr = va_arg(argument, void *);
    cout << i + 1 << ": " << ptr << " value= " << *(int *)ptr << endl;
  }
  va_end(argument);
  return true;
}
