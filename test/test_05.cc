#include<x86intrin.h>
#include<immintrin.h>
#include"../includes/basic.hpp"
#define _Float32 float
namespace bsm = Basic_Math;
using namespace std;
#define _SIMD_MODE_
#define _SIMD2_MODE_
#define _TEST_MODE_
#ifdef _TEST_MODE_
constexpr int TEST_TIMES = 50;
#endif
#ifdef _SIMD2_MODE_
#undef _SIMD_MODE_
#endif
clock_t t1, t2;
#define flag(){ t2 = clock();cout<<"t:"<<1000*(double(t2-t1)/CLOCKS_PER_SEC)<<'\n';t1 = clock() ; }
constexpr int len = 1e8;
constexpr _Float32 mx = static_cast<_Float32>(10);
constexpr _Float32 mn = static_cast<_Float32>(-10);
void show(_Float32*);
signed main() {
    if (len % 8 != 0) { cout << "error\n"; return 1; }
    _Float32* A, * B, * C;
#if defined(_SIMD_MODE_)
    __m128 vecA, vecB, vecC;
#elif defined(_SIMD2_MODE_)
    __m256 vecA, vecB, vecC;
#endif
#if defined(_SIMD_MODE_) || defined(_SIMD2_MODE_)
    A = (_Float32*) _mm_malloc(len * sizeof(_Float32), 32);
    B = (_Float32*) _mm_malloc(len * sizeof(_Float32), 32);
    C = (_Float32*) _mm_malloc(len * sizeof(_Float32), 32);
#else
    A = new _Float32[len];
    B = new _Float32[len];
    C = new _Float32[len];
#endif
    for (int i = 0; i < len; i++) {
        A[i] = bsm::random(mn, mx);
        B[i] = bsm::random(mn, mx);
    }
    //show(A);
    //show(B);
    flag();
#if defined(_SIMD_MODE_)
    cout << "SIMD\n";
#ifdef _TEST_MODE_
    for (int times = 0; times < TEST_TIMES; times++) {
        printf("times:%d\n", times + 1);
#endif
        for (int i = 0; i < len; i += 4) {
            vecA = _mm_load_ps(&A[i]);
            vecB = _mm_load_ps(&B[i]);
            vecC = _mm_add_ps(vecA, vecB);
            _mm_store_ps(&C[i], vecC);
        }
#ifdef _TEST_MODE_
    }
#endif
#elif defined(_SIMD2_MODE_) 
    cout << "SIMD2\n";
#ifdef _TEST_MODE_
    for (int times = 0; times < TEST_TIMES; times++) {
        printf("times:%d\n", times + 1);
#endif
        for (int i = 0; i < len; i += 8) {
            vecA = _mm256_load_ps(&A[i]);
            vecB = _mm256_load_ps(&B[i]);
            vecC = _mm256_add_ps(vecA, vecB);
            _mm256_store_ps(&C[i], vecC);
        }
#ifdef _TEST_MODE_
    }
#endif
#else
#ifdef _TEST_MODE_
    for (int times = 0; times < TEST_TIMES; times++) {
        printf("times:%d\n", times + 1);
#endif
        for (int i = 0; i < len; i++) {
            C[i] = A[i] + B[i];
        }
#ifdef _TEST_MODE_
    }
#endif
#endif
    flag();
    //show(C);
#if defined(_SIMD_MODE_) || defined(_SIMD2_MODE_)
    _mm_free(A);
    _mm_free(B);
    _mm_free(C);
#else
    delete[] A;
    delete[] B;
    delete[] C;
#endif
    return 0;
}
void show(_Float32* alpha) {
    for (int i = 0; i < len; i++) {
        cout << alpha[i];
        if (i != len - 1)cout << ' ';
    }
    cout << '\n';
    return;
}