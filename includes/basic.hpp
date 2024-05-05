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
#include<type_traits>
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
#elif defined(_THREAD_MODE_)
    constexpr int vec_len = 3;
#else
    constexpr int vec_len = 1;
#endif //_SIMD_00_
#ifdef _SIMD_MODE_
    constexpr bool SIMD_ON = true;
    constexpr bool THREAD_ON = true;
#else
    constexpr bool SIMD_ON = false;
#ifdef _TREAD_MODE_
    constexpr bool THREAD_ON = true;
#else
    constexpr bool THREAD_ON = false;
#endif //_TREAD_MODE_
#endif //_SIMD_MODE_
#ifdef _THREAD_MODE_
    constexpr int align_size = 16;
#endif //_THREAD_MODE_
    constexpr float float_value_max = static_cast<float>(200);
    constexpr float float_value_min = (-1) * float_value_max;
    constexpr int int_value_max = static_cast<int>(200);
    constexpr int int_value_min = (-1) * int_value_max;
    extern std::atomic<bool> set_seed;
    extern std::atomic<unsigned long long> memory_heap;
    template <typename Data>
    int Int_Digits(Data const&);
    template <typename Data>
    Data random(Data const&, Data const&);
    inline void status() {
        std::cout << '\n';
        for (int i = 0; i < terminal_width; i++) std::cout << "-";
        std::cout << '\n';
        if (set_seed.load()) {
            std::cout << "have set seed\n";
        }
        else {
            std::cout << "no set seed\n";
        }
#ifdef _THREAD_MODE_
        std::cout << "_TREAD_MODE_\nalign_size: " << std::noshowpos << align_size << '\n';
#endif
        if (SIMD_ON) {
            std::cout << "_SIMD_MODE_";
#ifdef _SIMD_01_
            std::cout << "01_\n";
#else 
            std::cout << "02_\n";
#endif
        }
        std::cout << "memory heap: " << std::noshowpos << memory_heap.load() << '\n';
        for (int i = 0; i < terminal_width; i++) std::cout << "-";
        std::cout << "\n\n";
        return;
    }
#ifdef _THREAD_MODE_
    template <typename Data>
    inline void tuple_add(Data* const& alpha, Data* const& beta, Data* const& gamma) {
        if constexpr ((std::is_same_v<Data, float>) && (SIMD_ON)) {
#if defined(_SIMD_01_)
            _mm_store_ps(gamma, _mm_add_ps(_mm_load_ps(alpha), _mm_load_ps(beta)));
#elif defined(_SIMD_02_)
            _mm256_store_ps(gamma, _mm256_add_ps(_mm256_load_ps(alpha), _mm256_load_ps(beta)));
#endif
        }
        else if constexpr (std::is_same_v<Data, bool>) {
            for (int i = 0; i < vec_len; i++) {
                gamma[i] = alpha[i] || beta[i];
            }
        }
        else {
            for (int i = 0; i < vec_len; i++) {
                gamma[i] = alpha[i] + beta[i];
            }
        }
        return;
    }
    template <typename Data>
    inline void tuple_add_s_(Data* const& alpha, Data const& beta, Data* const& gamma) {
        if constexpr ((std::is_same_v<Data, float>) && (SIMD_ON)) {
#if defined(_SIMD_01_)
            _mm_store_ps(gamma, _mm_add_ps(_mm_load_ps(alpha), _mm_set1_ps(beta)));
#elif defined(_SIMD_02_)
            _mm256_store_ps(gamma, _mm256_add_ps(_mm256_load_ps(alpha), _mm256_set1_ps(beta)));
#endif
        }
        else if constexpr (std::is_same_v<Data, bool>) {
            for (int i = 0; i < vec_len; i++) {
                gamma[i] = alpha[i] || beta;
            }
        }
        else {
            for (int i = 0; i < vec_len; i++) {
                gamma[i] = alpha[i] + beta;
            }
        }
        return;
    }
    template <typename Data>
    inline void tuple_sub(Data* const& alpha, Data* const& beta, Data* const& gamma) {
        if constexpr ((std::is_same_v<Data, float>) && (SIMD_ON)) {
#if defined(_SIMD_01_)
            _mm_store_ps(gamma, _mm_sub_ps(_mm_load_ps(alpha), _mm_load_ps(beta)));
#elif defined(_SIMD_02_)
            _mm256_store_ps(gamma, _mm256_sub_ps(_mm256_load_ps(alpha), _mm256_load_ps(beta)));
#endif
        }
        else if constexpr (std::is_same_v<Data, bool>) {
            for (int i = 0; i < vec_len; i++) {
                gamma[i] = alpha[i] || (!beta[i]);
            }
        }
        else {
            for (int i = 0; i < vec_len; i++) {
                gamma[i] = alpha[i] - beta[i];
            }
        }
        return;
    }
    template <typename Data>
    inline void tuple_sub_sb_(Data* const& alpha, Data const& beta, Data* const& gamma) {
        if constexpr ((std::is_same_v<Data, float>) && (SIMD_ON)) {
#if defined(_SIMD_01_)
            _mm_store_ps(gamma, _mm_sub_ps(_mm_load_ps(alpha), _mm_set1_ps(beta)));
#elif defined(_SIMD_02_)
            _mm256_store_ps(gamma, _mm256_sub_ps(_mm256_load_ps(alpha), _mm256_set1_ps(beta)));
#endif
        }
        else if constexpr (std::is_same_v<Data, bool>) {
            for (int i = 0; i < vec_len; i++) {
                gamma[i] = alpha[i] || (!beta);
            }
        }
        else {
            for (int i = 0; i < vec_len; i++) {
                gamma[i] = alpha[i] - beta;
            }
        }
        return;
    }
    template <typename Data>
    inline void tuple_sub_sf_(Data const& alpha, Data* const& beta, Data* const& gamma) {
        if constexpr ((std::is_same_v<Data, float>) && (SIMD_ON)) {
#if defined(_SIMD_01_)
            _mm_store_ps(gamma, _mm_sub_ps(_mm_set1_ps(alpha), _mm_load_ps(beta)));
#elif defined(_SIMD_02_)
            _mm256_store_ps(gamma, _mm256_sub_ps(_mm256_set1_ps(alpha), _mm256_load_ps(beta)));
#endif
        }
        else if constexpr (std::is_same_v<Data, bool>) {
            for (int i = 0; i < vec_len; i++) {
                gamma[i] = alpha || (!beta[i]);
            }
        }
        else {
            for (int i = 0; i < vec_len; i++) {
                gamma[i] = alpha - beta[i];
            }
        }
        return;
    }
    template <typename Data>
    inline void tuple_mul(Data* const& alpha, Data* const& beta, Data* const& gamma) {
        if constexpr ((std::is_same_v<Data, float>) && (SIMD_ON)) {
#if defined(_SIMD_01_)
            _mm_store_ps(gamma, _mm_mul_ps(_mm_load_ps(alpha), _mm_load_ps(beta)));
#elif defined(_SIMD_02_)
            _mm256_store_ps(gamma, _mm256_mul_ps(_mm256_load_ps(alpha), _mm256_load_ps(beta)));
#endif
        }
        else if constexpr (std::is_same_v<Data, bool>) {
            for (int i = 0; i < vec_len; i++) {
                gamma[i] = alpha[i] && beta[i];
            }
        }
        else {
            for (int i = 0; i < vec_len; i++) {
                gamma[i] = alpha[i] * beta[i];
            }
        }
        return;
    }
    template <typename Data>
    inline void tuple_mul_s_(Data* const& alpha, Data const& beta, Data* const& gamma) {
        if constexpr ((std::is_same_v<Data, float>) && (SIMD_ON)) {
#if defined(_SIMD_01_)
            _mm_store_ps(gamma, _mm_mul_ps(_mm_load_ps(alpha), _mm_set1_ps(beta)));
#elif defined(_SIMD_02_)
            _mm256_store_ps(gamma, _mm256_mul_ps(_mm256_load_ps(alpha), _mm256_set1_ps(beta)));
#endif
        }
        else if constexpr (std::is_same_v<Data, bool>) {
            for (int i = 0; i < vec_len; i++) {
                gamma[i] = alpha[i] && beta;
            }
        }
        else {
            for (int i = 0; i < vec_len; i++) {
                gamma[i] = alpha[i] * beta;
            }
        }
        return;
    }
    template <typename Data>
    inline void tuple_div(Data* const& alpha, Data* const& beta, Data* const& gamma) {
        if constexpr ((std::is_same_v<Data, float>) && (SIMD_ON)) {
#if defined(_SIMD_01_)
            _mm_store_ps(gamma, _mm_div_ps(_mm_load_ps(alpha), _mm_load_ps(beta)));
#elif defined(_SIMD_02_)
            _mm256_store_ps(gamma, _mm256_div_ps(_mm256_load_ps(alpha), _mm256_load_ps(beta)));
#endif
        }
        else if constexpr (std::is_same_v<Data, bool>) {
            for (int i = 0; i < vec_len; i++) {
                gamma[i] = (alpha[i] || beta[i]) && (!(alpha[i] && beta[i]));
            }
        }
        else {
            for (int i = 0; i < vec_len; i++) {
                gamma[i] = alpha[i] / beta[i];
            }
        }
        return;
    }
    template <typename Data>
    inline void tuple_div_sb_(Data* const& alpha, Data const& beta, Data* const& gamma) {
        if constexpr ((std::is_same_v<Data, float>) && (SIMD_ON)) {
#if defined(_SIMD_01_)
            _mm_store_ps(gamma, _mm_div_ps(_mm_load_ps(alpha), _mm_set1_ps(beta)));
#elif defined(_SIMD_02_)
            _mm256_store_ps(gamma, _mm256_div_ps(_mm256_load_ps(alpha), _mm256_set1_ps(beta)));
#endif
        }
        else if constexpr (std::is_same_v<Data, bool>) {
            for (int i = 0; i < vec_len; i++) {
                gamma[i] = (alpha[i] || beta) && (!(alpha[i] && beta));
            }
        }
        else {
            for (int i = 0; i < vec_len; i++) {
                gamma[i] = alpha[i] / beta;
            }
        }
        return;
    }
    template <typename Data>
    inline void tuple_div_sf_(Data const& alpha, Data* const& beta, Data* const& gamma) {
        if constexpr ((std::is_same_v<Data, float>) && (SIMD_ON)) {
#if defined(_SIMD_01_)
            _mm_store_ps(gamma, _mm_div_ps(_mm_set1_ps(alpha), _mm_load_ps(beta)));
#elif defined(_SIMD_02_)
            _mm256_store_ps(gamma, _mm256_div_ps(_mm256_set1_ps(alpha), _mm256_load_ps(beta)));
#endif
        }
        else if constexpr (std::is_same_v<Data, bool>) {
            for (int i = 0; i < vec_len; i++) {
                gamma[i] = (alpha || beta[i]) && (!(alpha && beta[i]));
            }
        }
        else {
            for (int i = 0; i < vec_len; i++) {
                gamma[i] = alpha / beta[i];
            }
        }
        return;
    }
    template <typename Data>
    inline void tuple_eq_v(Data* const& alpha, Data* const& beta, bool* const& gamma) {
        for (int i = 0; i < vec_len; i++) {
            gamma[i] = alpha[i] == beta[i];
        }
        return;
    }
    template <typename Data>
    inline void tuple_eq_s(Data* const& alpha, Data const& beta, bool* const& gamma) {
        for(int i = 0; i < vec_len; i++) {
            gamma[i] = alpha[i] == beta;
        }
        return;
    }
    template <typename Data>
    inline void tuple_ne_v(Data* const& alpha, Data* const& beta, bool* const& gamma) {
        for (int i = 0; i < vec_len; i++) {
            gamma[i] = alpha[i] != beta[i];
        }
        return;
    }
    template <typename Data>
    inline void tuple_ne_s(Data* const& alpha, Data const& beta, bool* const& gamma) {
        for(int i = 0; i < vec_len; i++) {
            gamma[i] = alpha[i] != beta;
        }
        return;
    }
    template <typename Data>
    inline void tuple_bg_v(Data* const& alpha, Data* const& beta, bool* const& gamma) {
        for(int i = 0; i < vec_len; i++) {
            gamma[i] = alpha[i] > beta[i];
        }
        return;
    }
    template <typename Data>
    inline void tuple_bg_sb(Data* const& alpha, Data const& beta, bool* const& gamma) {
        for(int i = 0; i < vec_len; i++) {
            gamma[i] = alpha[i] > beta;
        }
        return;
    }
    template <typename Data>
    inline void tuple_bg_sf(Data const& alpha, Data* const& beta, bool* const& gamma) {
        for(int i = 0; i < vec_len; i++) {
            gamma[i] = alpha > beta[i];
        }
        return;
    }
    template <typename Data>
    inline void tuple_bq_v(Data* const& alpha, Data* const& beta, bool* const& gamma) {
        for(int i = 0; i < vec_len; i++) {
            gamma[i] = alpha[i] >= beta[i];
        }
        return;
    }
    template <typename Data>
    inline void tuple_bq_sb(Data* const& alpha, Data const& beta, bool* const& gamma) {
        for(int i = 0; i < vec_len; i++) {
            gamma[i] = alpha[i] >= beta;
        }
        return;
    }
    template <typename Data>
    inline void tuple_bq_sf(Data const& alpha, Data* const& beta, bool* const& gamma) {
        for(int i = 0; i < vec_len; i++) {
            gamma[i] = alpha >= beta[i];
        }
        return;
    }
    template <typename Data>
    inline void tuple_sm_v(Data* const& alpha, Data* const& beta, bool* const& gamma) {
        for(int i = 0; i < vec_len; i++) {
            gamma[i] = alpha[i] < beta[i];
        }
        return;
    }
    template <typename Data>
    inline void tuple_sm_sb(Data* const& alpha, Data const& beta, bool* const& gamma) {
        for(int i = 0; i < vec_len; i++) {
            gamma[i] = alpha[i] < beta;
        }
        return;
    }
    template <typename Data>
    inline void tuple_sm_sf(Data const& alpha, Data* const& beta, bool* const& gamma) {
        for(int i = 0; i < vec_len; i++) {
            gamma[i] = alpha < beta[i];
        }
        return;
    }
    template <typename Data>
    inline void tuple_sq_v(Data* const& alpha, Data* const& beta, bool* const& gamma) {
        for(int i = 0; i < vec_len; i++) {
            gamma[i] = alpha[i] <= beta[i];
        }
        return;
    }
    template <typename Data>
    inline void tuple_sq_sb(Data* const& alpha, Data const& beta, bool* const& gamma) {
        for(int i = 0; i < vec_len; i++) {
            gamma[i] = alpha[i] <= beta;
        }
        return;
    }
    template <typename Data>
    inline void tuple_sq_sf(Data const& alpha, Data* const& beta, bool* const& gamma) {
        for(int i = 0; i < vec_len; i++) {
            gamma[i] = alpha <= beta[i];
        }
        return;
    }
#endif
}
namespace Linalg {
    typedef struct
    {
        int rows = 1;
        int lines = 1;
    } MaShape;
    bool operator==(MaShape const&, MaShape const&);
    bool operator<(MaShape const&, MaShape const&);
    bool operator<=(MaShape const&, MaShape const&);
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