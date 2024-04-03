#include "../includes/math.hpp"
#include <iostream>
#include<cstdlib>
#include<ctime>
#define sv(x){    \
    std::cout<<#x<<":\n";\
    Linalg::show_Matrix(x);\
}
#define ss(x){  \
    std::cout<<#x<<":\n";\
    Linalg::show_Mashape(x);\
}
const int Max_hight = 10;
const int Max_wide = 10;
const int Int_Val = 30;
const float Float_Val = 30.0;
int random(int const&);
float random(float const&);
Linalg::Matrix<float> initer(const Linalg::MaShape&, bool);
signed main() {
    std::srand(std::time(0));
    float value = 0;
    Linalg::MaShape zeta, omega;
    Linalg::Matrix<float> alpha, beta;
    /*below is init block*/
    zeta.lines = random(Max_wide);
    zeta.rows = random(Max_hight);
    alpha = initer(zeta, true);
    beta = initer(zeta, true);
    /*below is testing block*/
    ss(zeta); sv(alpha); sv(beta);
    alpha += beta;
    sv(alpha);
    /*above is testing block*/
    alpha.~Matrix(); beta.~Matrix();
    return 0;
}

int random(int const& alpha) {
    return std::rand() % (alpha + 1);
}
float random(float const& alpha) {
    return ((float) std::rand() / RAND_MAX) * alpha;
}
Linalg::Matrix<float> initer(const Linalg::MaShape& alpha, bool) {
    Linalg::Matrix<float> temp(alpha);
    Linalg::MaShape beta;
    for (beta.rows = 0; beta.rows < alpha.rows; beta.rows++) {
        for (beta.lines = 0; beta.lines < alpha.lines; beta.lines++) {
            temp.endow_(beta, random(Float_Val));
        }
    }
    return temp;
}