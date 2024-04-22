
#ifndef BASIC_H
#define BASIC_H
#pragma loop_opt(on)
#define _DEBUG_MODE_
#include<iostream>
#include<iomanip>
#include<cfloat>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<climits>
#include<type_traits>
#define _SIMD_MODE_
#define _SIMD2_MODE_
namespace Basic_Math {
    constexpr int Float16_Accuracy = 3;
    constexpr int Float32_Accuracy = 7;
    constexpr int Float64_Accuracy = 15;
    constexpr int terminal_width = 144;
    constexpr _Float32 Float_value = static_cast<_Float32>(100);
    constexpr int32_t Int_value = static_cast<int32_t>(100);
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
#endif