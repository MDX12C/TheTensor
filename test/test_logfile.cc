#include <stdio.h>

#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
// #define INPUT
using namespace std;
signed main() {
  string s = "dist/out.txt";
#ifdef INPUT
  int input;
  vector<char> v;
#endif
  filesystem::path run_p = filesystem::current_path() / s;
  fstream stream;
#ifdef INPUT
  stream.open(run_p, ios::out | ios::binary);
#else
  stream.open(run_p, ios::in | ios::binary);
#endif
  if (!stream.is_open()) {
    printf("open fail\n");
    exit(1);
  } else {
    printf("open success\n");
  }
#ifdef INPUT
  v.clear();
ONEMORE:
  cout << "enter number:\n";
  cin >> input;
  if (input <= 0) {
    goto ONEMORE;
  }
  while (input) {
    v.push_back(char((input % 10) + 48));
    input /= 10;
  }
  cout << "reverse = ";
  for (auto i : v) {
    cout << i;
  }
  printf("\nin\n");
  for (int i = v.size() - 1; i >= 0; i--) {
    stream.put(v[i]);
  }
#else
  while (!stream.eof()) {
    cout << char(stream.get());
  }
#endif
  stream.close();
  return 0;
}
