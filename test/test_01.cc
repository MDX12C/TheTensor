#include "../includes/math.hpp"
#include <iostream>
using namespace std;
signed main() {
  float a;
  Linalg::MaShape ms;
  cin >> ms.row >> ms.lines >> a;
  Linalg::Matrix<float> alpha(ms, a);
  Linalg::show_Matrix(alpha);
  cin >> ms.row >> ms.lines >> a;
  alpha.endow_(ms, a);
  Linalg::show_Matrix(alpha);
  return 0;
}
