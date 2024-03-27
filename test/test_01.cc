#include "../includes/math.hpp"
#include <iostream>
signed main() {
    float a;
    Linalg::MaShape ms;
    std::cin >> ms.row >> ms.lines >> a;
    Linalg::Matrix<float> alpha(ms, a);
    Linalg::show_Matrix(alpha);
    std::cin >> ms.row >> ms.lines >> a;
    alpha.endow_(ms, a);
    Linalg::show_Matrix(alpha);
    return 0;
}
