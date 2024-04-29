#ifndef BASIC_H
#define BASIC_H
#define _DEBUG_MODE_
#define _THREAD_MODE_
#define _SIMD_MODE_
#include<iostream>
#include<iomanip>
#include<cfloat>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<climits>
#include<utility>
#ifdef _THREAD_MODE_
#include<chrono>
#include<thread>
#include<atomic>
#include<mutex>
#include<functional>
#endif //_THREAD_MODE_
//#define _AVX02_WILL_BE_USED_ON_
#ifdef _SIMD_MODE_
#include<type_traits>
#include<immintrin.h>
#include<x86intrin.h>
#ifdef _AVX02_WILL_BE_USED_ON_
#define _SIMD_02_
#else //_AVX02_WILL_BE_USED_ON_
#define _SIMD_01_
#endif //_AVX02_WILL_BE_USED_ON_
#else //_SIMD_MODE_
#undef _AVX02_WILL_BE_USED_ON_
#endif //_SIMD_MODE_
namespace Basic_Math {
    constexpr int Float16_Accuracy = 3;
    constexpr int Float32_Accuracy = 7;
    constexpr int Float64_Accuracy = 15;
    constexpr int terminal_width = 144;
    constexpr int terminal_height = 40;
#if defined(_SIMD_01_)
    constexpr int vec_len = 4;
#elif defined(_SIMD_02_)
    constexpr int vec_len = 8;
#endif
    constexpr float Float_value = static_cast<float>(100);
    constexpr int Int_value = static_cast<int>(100);
    static bool set_seed = false;
    template <typename Data>
    int Int_Digits(Data const&);
    template <typename Data>
    Data random(Data const&,Data const&);
    int random(int const&, int const&);
    float random(float const&, float const&);
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