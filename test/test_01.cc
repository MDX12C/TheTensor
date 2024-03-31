#include "../includes/math.hpp"
#include <iostream>
#define show(x){    \
    std::cout<<#x<<':'<<'\n';\
    Linalg::show_Matrix(x);\
}
//Linalg::Matrix<float> memory(Linalg::MaShape const&);
Linalg::Matrix<float> identity(Linalg::MaShape const&);
signed main() {
    float a;
    Linalg::MaShape ms, ma;
    std::cout << "shape:\n";
    std::cin >> ms.row >> ms.lines;
    Linalg::Matrix<float> alpha(ms, a);
    for (ma.row = 0; ma.row < alpha.size().row; ma.row++) {
        for (ma.lines = 0; ma.lines < alpha.size().lines; ma.lines++) {
            std::cout << "a[" << ma.row << "][" << ma.lines << "]: ";
            std::cin >> a;
            alpha.endow_(ma, a);
        }
    }
    show(alpha);
    std::cout << "times: ";
    std::cin >> a;
    for (int i = 0; i < a; i++) {
        alpha = alpha + identity(ms);
        show(alpha);
    }
    printf("main function ended\n");
    return 0;
}
Linalg::Matrix<float> identity(Linalg::MaShape const& alpha) {
    Linalg::Matrix<float> temp(alpha, float(1));
    return temp;
}