#ifndef DEFINE_H
#define DEFINE_H 1

/*constants*/
// #define _DEBUG_MODE_ 1
//   #define _SIMD_MODE_    1         // open SIMD mode
//   #define _AVX2_WILL_BE_USED_ON_   1// open AVX2
//  #define _SPEED_MODE_ 1
// #define LIMIT 1
/*end of constants*/

#ifdef LIMIT
#define ROM_H 0
#endif

/*control block*/
#ifdef _SIMD_MODE_
#ifdef _AVX2_WILL_BE_USED_ON_
#define _SIMD_02_
#else
#define _SIMD_01_
#endif  // AVX_ON
#else
#define _SIMD_MODE_ 0
#undef _AVX2_WILL_BE_UESD_ON_
#endif  //_SIMD_MODE_
#ifndef __GNUC__
#define __attribute__(x)
#endif
#ifndef _DEBUG_MODE_
#define _DEBUG_MODE_ 0
#endif
#ifndef _SPEED_MODE_
#define _SPEED_MODE_ 0
#endif
#include <H5Cpp.h>
#include <xmmintrin.h>

#include <atomic>
#include <cfloat>
#include <chrono>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <random>
#include <set>
#include <thread>
#include <type_traits>
#include <utility>
#ifdef _SIMD_MODE_
#include <immintrin.h>
#include <x86intrin.h>
#endif  //_SIMD_MODE_
#ifdef _AVX2_WILL_BE_USED_ON_
#include <avx2intrin.h>
#include <avxintrin.h>
#include <avxvnniintrin.h>
#endif  // AVX2_ON

extern inline void endOfMainFunction();
#endif  // DEFINE_H