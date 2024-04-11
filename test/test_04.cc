#include<iostream>
#include"../includes/vector.hpp"
#include<cstdlib>
#include<ctime>
using namespace std;
namespace obj {
    const _Float32 Float_value = static_cast<_Float32>(100);
    _Float32 random(_Float32 const&);
    Linalg::Vector<_Float32> initer(int const&);
};
signed main() {
    srand(time(0));
    int a = 8;
    Linalg::Vector<_Float32> alpha = obj::initer(a);
    cout << alpha;
    return 0;
}
_Float32 obj::random(_Float32 const& alpha) {
    _Float32 beta = rand() % 2 ? static_cast<_Float32>(1) : static_cast<_Float32>(-1);
    return (static_cast<_Float32>(std::rand()) / RAND_MAX) * alpha * beta;
}
Linalg::Vector<_Float32> obj::initer(int const& alpha) {
    Linalg::Vector<_Float32> temp(alpha);
    for (int i = 0; i < temp.size(); i++) {
        temp.endow_(i, obj::random(obj::Float_value));
    }
    return temp;
}
