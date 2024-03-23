#include <iostream>
#include "../includes/math.hpp"
using namespace std;
namespace La = Linalg;
signed main()
{
    float a;
    La::MaShape ms;
    cin >> ms.row >> ms.lines >> a;
    La::Matrix<float> alpha(ms, a);
    La::show_Matrix(alpha);
    return 0;
}