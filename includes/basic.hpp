#include<iostream>
#include<iomanip>
#include<cfloat>
#include<cmath>

#ifndef BASIC_H
#define BASIC_H
namespace Basic_Math {
    constexpr int Float16_Accuracy = 3;
    constexpr int Float32_Accuracy = 7;
    constexpr int Float64_Accuracy = 15;
    constexpr int terminal_width = 144;
    template <typename Data>
    int Int_Digits(Data const&);
}
namespace Linalg {
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
#endif