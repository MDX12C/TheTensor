#include<iostream>
#include"../includes/matrix.hpp"
#include<cstdlib>
#include<ctime>
using namespace std;
#define show(x) { cout << #x << ':' << '\n' << x << '\n'; }

signed main() {
    srand(time(0));
    Linalg::MaShape alpha;
    cin >> alpha.rows >> alpha.lines;
    show(alpha);
    Linalg::Matrix<_Float32> A;
    show(A);
    Linalg::Vector<_Float32> B;
    B = Basic_Math::random(alpha.lines * alpha.rows, Basic_Math::Float_value * (-1), Basic_Math::Float_value);
    show(B);
    A.stand_(B, alpha);
    show(A);
    return 0;
}