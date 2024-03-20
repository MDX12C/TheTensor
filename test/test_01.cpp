#include<iostream>
#include"../includes/math.hpp"
using namespace std;
namespace La=Linalg;
signed main(){
    int a;
    La::MaShape ms;
    cin>>ms.row>>ms.lines>>a;
    La::Matrix<int> alpha(ms,a);
    La::show_Matrix(alpha);
    return 0;
}