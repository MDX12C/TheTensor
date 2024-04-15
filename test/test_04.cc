#include<iostream>
#include"../includes/matrix.hpp"
#include<cstdlib>
#include<ctime>
using namespace std;
#define show(x) { cout << '\n' << #x << ':' << '\n' << x << '\n'; }
namespace bsm = Basic_Math;
signed main() {
    srand(time(0));
    Linalg::MaShape alpha;
    cin >> alpha.rows >> alpha.lines;
    show(alpha);
    Linalg::Matrix<_Float32> A = bsm::random(alpha, bsm::Float_value * (-1), bsm::Float_value);
    Linalg::Matrix<_Float32> B = bsm::random(alpha, bsm::Float_value * (-1), bsm::Float_value);
    show(A);
    show(B);
    show(A*B);
    return 0;
}