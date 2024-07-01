#include <iostream>
#include <type_traits>
using namespace std;
template <typename T> T tho(const T &alpha) {
  if constexpr (is_same_v<T, int>) {
    cout << "int:";
  } else if constexpr (is_same_v<T, float>) {
    cout << "float:";
  } else {
    cout << "defult:";
  }
  return static_cast<T>(10.5);
}
signed main() {
  double a;
  cout << tho(a);
  return 0;
}
