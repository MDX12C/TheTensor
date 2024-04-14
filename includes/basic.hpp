
#ifndef BASIC_H
#define BASIC_H
#include<iostream>
#include<iomanip>
#include<cfloat>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<climits>
namespace Basic_Math {
    constexpr int Float16_Accuracy = 3;
    constexpr int Float32_Accuracy = 7;
    constexpr int Float64_Accuracy = 15;
    constexpr int terminal_width = 144;
    bool set_seed = false;
    template <typename Data>
    int Int_Digits(Data const&);
    int32_t random(int32_t const&, int32_t const&);
    _Float32 random(_Float32 const&, _Float32 const&);
    inline bool random() {
        if (!set_seed) {
            std::srand(int(std::time(0)));
            set_seed = true;
        }
        return (std::rand() % 2 == 1);
    }
}
namespace Linalg {
    typedef struct MaShape;
    template <typename Data>
    class Vector;
    template <typename Data>
    class Matrix;
    template <typename Data>
    class Tensor;
    template <typename Data>
    void AddLine_(Matrix<Data>&, Vector<Data> const&);
    template <typename Data>
    void AddRow_(Matrix<Data>&, Vector<Data> const&);
}
namespace Basic_Math {
    template <typename Data>
    Linalg::Vector<Data> random(int const&, Data const&, Data const&);
    template <typename Data>
    Linalg::Matrix<Data> random(Linalg::MaShape const&, Data const&, Data const&);
}
#endif