﻿
#ifndef BASIC_H
#define BASIC_H
#pragma loop_opt(on)
#define DEBUG_MODE
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
    #ifdef DEBUG_MODE
    constexpr _Float32 Float_value = static_cast<_Float32>(100);
    #endif
    static bool set_seed = false;
    template <typename Data>
    int Int_Digits(Data const&);
    int32_t random(int32_t const&, int32_t const&);
    _Float32 random(_Float32 const&, _Float32 const&);
}
namespace Linalg {
    typedef struct
    {
        int rows = 1;
        int lines = 1;
    } MaShape;
    bool operator==(MaShape const&, MaShape const&);
    bool belongs(MaShape const&, MaShape const&);
    std::ostream& operator<<(std::ostream&, MaShape const&);
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