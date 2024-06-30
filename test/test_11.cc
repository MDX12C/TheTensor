#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>
using namespace std;
constexpr int start = 8;
constexpr int with = 8;
constexpr int terminal_ = 50;
string s = "log/log_00000000.txt";
signed main() {
  filesystem::path now = filesystem::current_path();
  filesystem::path auto_path = now / s;
  unsigned long long a, b;
  fstream road;
  road.open(auto_path, ios::in);
  if (!road.is_open()) {
    cout << "in fail\n";
    exit(1);
  }
  road >> a;
  cout << a;
  road.close();
  road.open(s, ios::out);
  if (road.fail()) {
    cout << "out fail\n";
    exit(1);
  }
  road << a + 1;
  road.close();
  for (int i = start + with - 1; i >= start; i--) {
    b = a % 36;
    if (b >= 10) {
      b -= 10;
      s[i] = char(int('A') + b);
    } else {
      s[i] = char(int('0') + b);
    }
    a /= 36;
  }
  auto_path = now / s;
  road.open(s, ios::out);
  if (road.fail()) {
    cout << "create fail\n";
    exit(1);
  }
  for (int i = 0; i < terminal_; i++) {
    road << '-';
  }
  road << '\n';
  time_t temp = time(NULL);
  road << "com at: " << __TIMESTAMP__ << "\nrun at: " << ctime(&temp);
  for (int i = 0; i < terminal_; i++) {
    road << '-';
  }
  road << "\nfor test";
  road.close();
  return 0;
}
