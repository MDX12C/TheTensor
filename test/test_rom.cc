#include <H5Cpp.h>
#include "interface.hpp"

std::string fileName;

#define SHOW(X) std::cout << #X << '=' << X << std::endl;

signed main() {
  CONSTRUCT;
  fileName = __FILE__;
  for (auto i = fileName.size() - 1; i >= 0; i--) {
    if (fileName[i] == '/') {
      fileName = fileName.substr(i + 1);
      break;
    }
  }
  fileName.pop_back();
  fileName.pop_back();
  fileName += "hdf5";
  fileName = "/../datas/" + fileName;
  fileName = std::filesystem::current_path().string() + fileName;
  SHOW(fileName);
  auto alpha = basic_math::random<float>(30, -5.0F, 5.0F);
  SHOW(alpha);
  DESTRUCT;
  return 0;
}