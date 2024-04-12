#include<iostream>
#include"../includes/matrix.hpp"
#include<cstdlib>
#include<ctime>
using namespace std;
#define show(x) { cout << #x << ':' << '\n' << x << '\n'; }
namespace obj {
    const _Float32 Float_value = static_cast<_Float32>(100);
    _Float32 random(_Float32 const&);
    Linalg::Matrix<_Float32> initer(Linalg::MaShape const&, bool);
};
signed main() {
    srand(time(0));
    Linalg::MaShape alpha;
    std::cin >> alpha.rows >> alpha.lines;
    show(alpha);
    Linalg::Matrix<_Float32> beta = obj::initer(alpha, false);
    show(beta);
    return 0;
}
_Float32 obj::random(_Float32 const& alpha) {
    _Float32 beta = rand() % 2 ? static_cast<_Float32>(1) : static_cast<_Float32>(-1);
    return (static_cast<_Float32>(std::rand()) / RAND_MAX) * alpha * beta;
}
Linalg::Matrix<_Float32> obj::initer(Linalg::MaShape const& alpha, bool) {
    Linalg::Matrix<_Float32> temp(alpha);
    Linalg::MaShape beta;
    for (beta.rows = 0; beta.rows < alpha.rows; beta.rows++) {
        for (beta.lines = 0; beta.lines < alpha.lines; beta.lines++) {
            temp.endow_(beta, obj::random(Float_value));
        }
    }
    return temp;
}