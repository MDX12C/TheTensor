#include<iostream>
#include"../includes/matrix.hpp"
#include<cstdlib>
#include<ctime>
using namespace std;
#define show(x) { cout << '\n' << #x << ':' << '\n' << x << '\n'; }
namespace bsm = Basic_Math;
signed main() {
    srand(time(0));
    Linalg::MaShape alpha, beta;
    cin >> alpha.rows >> beta.lines;
    alpha.lines = beta.rows = Basic_Math::random(1, 15);
    show(alpha);
    show(beta);
    Linalg::Matrix<_Float32> A = bsm::random(alpha, bsm::Float_value * (-1), bsm::Float_value);
    Linalg::Matrix<_Float32> B = bsm::random(beta, bsm::Float_value * (-1), bsm::Float_value);
    show(A);
    show(B);
    show(Linalg::dot(A, B));
    return 0;
}