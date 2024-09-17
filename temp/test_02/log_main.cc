#include <iostream>

#include "log_divide.hpp"

signed main() {
  log_file::logInit();
  LOG_INIT;
  LOG("C:hello world\n");
  int a = 1203;
  LOG("C:a= %d\n", a);
  log_file::logPack();
  return 0;
}