#ifndef BASIC_H
#define BASIC_H
//#define _DEBUG_MODE_
#define _THREAD_MODE_ //open thread mode
#define _SIMD_MODE_ //open SIMD mode
//#define _AVX02_WILL_BE_USED_ON_
#include<iostream>
#include<iomanip>
#include<cfloat>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<climits>
#include<utility>
#ifdef _SIMD_MODE_
#define _THREAD_MODE_
#endif //_SIMD_MODE_
#ifdef _THREAD_MODE_
#include<chrono>
#include<thread>
#include<atomic>
#include<mutex>
#include<functional>
#endif //_THREAD_MODE_
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
#endif //_SIMD_00_
#ifdef _SIMD_MODE_
    constexpr bool SIMD_ON = true;
#else
    constexpr bool SIMD_ON = false;
#endif //_SIMD_MODE_
    constexpr float float_value_max = static_cast<float>(100);
    constexpr float float_value_min = (-1) * float_value_max;
    constexpr int int_value_max = static_cast<int>(100);
    constexpr int int_value_min = (-1) * int_value_max;
    static bool set_seed = false;
    template <typename Data>
    int Int_Digits(Data const&);
    template <typename Data>
    Data random(Data const&, Data const&);
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
#endif //BASIC_H