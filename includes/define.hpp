#ifndef DEFINE_H
#define DEFINE_H
/*constants*/
#define _DEBUG_MODE_
#define _THREAD_MODE_          // open thread mode
#define _SIMD_MODE_            // open SIMD mode
#define _AVX2_WILL_BE_USED_ON_ // open AVX2
/*end of constants*/

#define LIMIT

/*control block*/
#ifdef _SIMD_MODE_
#define _THREAD_MODE_
#ifdef _AVX2_WILL_BE_USED_ON_
#define _SIMD_02_
#else
#define _SIMD_01_
#endif // AVX_ON
#else
#undef _AVX2_WILL_BE_UESD_ON_
#endif //_SIMD_MODE_
#ifndef __GNUC__
#define __attribute__(x)
#endif
#include <cfloat>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <set>
#include <type_traits>
#include <utility>
#ifdef _THREAD_MODE_
#include <atomic>
#include <chrono>
#include <functional>
#include <mutex>
#include <thread>
#include <xmmintrin.h>
#endif //_THREAD_MODE_
#ifdef _SIMD_MODE_
#include <immintrin.h>
#include <x86intrin.h>
#endif //_SIMD_MODE_
#ifdef _AVX2_WILL_BE_USED_ON_
#include <avx2intrin.h>
#include <avxintrin.h>
#include <avxvnniintrin.h>
#endif // AVX2_ON
#endif // DEFINE_H
