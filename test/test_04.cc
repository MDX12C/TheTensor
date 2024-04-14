#include<iostream>
#include"../includes/matrix.hpp"
#include<cstdlib>
#include<ctime>
using namespace std;
#define show(x) { cout << #x << ':' << '\n' << x << '\n'; }
namespace obj {
    const int Max_hight = 15;
    const _Float32 Float_value = static_cast<_Float32>(100);
    _Float32 random(_Float32 const&);
    int random(int const&);
    Linalg::Matrix<_Float32> initer(Linalg::MaShape const&, bool);
    Linalg::Vector<_Float32> initer(int const&, bool);
};
signed main() {
    srand(time(0));
    Linalg::MaShape alpha;
    cin >> alpha.rows >> alpha.lines;
    show(alpha);
    Linalg::Matrix<_Float32> A;
    show(A);
    Linalg::Vector<_Float32> B = obj::initer(alpha.rows * alpha.lines, false);
    show(B);
    A.stand_(B, alpha);
    show(A);
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
int obj::random(int const& alpha) {
    return (std::rand() % alpha) + 1;
}
Linalg::Vector<_Float32> obj::initer(int const& alpha, bool) {
    Linalg::Vector<_Float32> temp(alpha);
    for (int i = 0; i < alpha; i++) {
        temp.endow_(i, obj::random(Float_value));
    }
    return temp;
}