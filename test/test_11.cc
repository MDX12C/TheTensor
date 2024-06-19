#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
using namespace std;
const int sart = 43;
const int zero = 48;
const int terminal_ = 50;
string s = "/home/logman/proj/cpp/file_020/NNN/log/log_00000000.txt";
signed main() {
  int a;
  fstream road;
  road.open(s, ios::in);
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
  for (int i = 50; i >= 43; i--) {
    s[i] = char(48 + (a % 10));
    a /= 10;
  }
  road.open(s, ios::out);
  if (road.fail()) {
    cout << "out fail\n";
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
