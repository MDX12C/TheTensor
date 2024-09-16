#include "log_divide.hpp"

signed main() {
  LOG_INIT;
  LOG("C:hello world\n");
  int a = 1203;
  LOG("C:a= %d\n", a);
  return 0;
}