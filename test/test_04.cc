#include<iostream>
#include"../includes/matrix.hpp"
#include<cstdlib>
#include<ctime>
using namespace std;
clock_t t1, t2;
#define show(x) { cout << '\n' << #x << ':' << '\n' << x << '\n'; }
#define flag(){ t2 = clock();cout<<"t:"<<1000*double(t2-t1)/CLOCKS_PER_SEC<<'\n';t1 = clock() ; }
namespace bsm = Basic_Math;
signed main() {
    t1 = t2 = clock();
    int alpha;
    //cin >> alpha;
    //
    alpha = 100000;
    //
    Linalg::Vector<_Float32> A = bsm::random(alpha, bsm::Float_value * (-1), bsm::Float_value);
    Linalg::Vector<_Float32> B;
    flag();
    B = A;
    flag();
    return 0;
}