
#include "interface.hpp"

#define SHOW(X) std::cout << #X << '=' << X << std::endl;

signed main() {
  CONSTRUCT;
  std::string name;
  linalg::Matrix<float> alpha;
  name = "alpha";
  rom_io::RomSupport::read(name, alpha.begin());
  SHOW(alpha);
  alpha.random(-1.0F, 1.0F);
  SHOW(alpha);
  rom_io::RomSupport::write(name, alpha.begin(), alpha.size());
  DESTRUCT;
  return 0;
}