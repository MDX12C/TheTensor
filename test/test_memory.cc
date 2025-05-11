#include "interface.hpp"

auto Say = [](const char* const& __str) {
  system_message::Status::announce(__str);
};
auto Print = [] { memory_manage::MemorySupport::displayUsage(); };
signed main() {
  CONSTRUCT;
  system_message::Status::refresh("initial Status");
  Say("Story<int32>[30]");
  storage::Story<int32_t> test_1(30);
  Say("Vector<float>[9]");
  lina_lg::Vector<float_t> test_2(9);
  Say("Matrix<bool>[3,4]");
  lina_lg::Matrix<bool> test_3({3, 4});
  Print();
  DESTRUCT;
}