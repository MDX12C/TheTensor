#include "log_divide.hpp"

signed main() {
  log_file::LogSupport::logInit(true);
  LOG_INIT;
  LOG("C:hello world\n");
  int a = 1203;
  LOG("C:a= %d\n", a);
  log_file::LogSupport::logPack(true);
  return 0;
}