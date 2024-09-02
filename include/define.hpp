#ifndef DEFINE_H
#define DEFINE_H

/*constants*/
#define _DEBUG_MODE_
// #define _SIMD_MODE_             // open SIMD mode
// #define _AVX2_WILL_BE_USED_ON_  // open AVX2
/*end of constants*/

#define LIMIT

/*control block*/
#ifdef _SIMD_MODE_
#ifdef _AVX2_WILL_BE_USED_ON_
#define _SIMD_02_
#else
#define _SIMD_01_
#endif  // AVX_ON
#else
#undef _AVX2_WILL_BE_UESD_ON_
#endif  //_SIMD_MODE_
#ifndef __GNUC__
#define __attribute__(x)
#endif
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
#endif  // DEFINE_H
