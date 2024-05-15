#ifndef BASIC_H
#define BASIC_H
/*constants*/
#define _DEBUG_MODE_
#define _THREAD_MODE_ //open thread mode
#define _SIMD_MODE_ //open SIMD mode
#define _AVX2_WILL_BE_USED_ON_
//---------------------------------------
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
#include<xmmintrin.h>
#endif //_THREAD_MODE_
#ifdef _SIMD_MODE_
#include<immintrin.h>
#include<x86intrin.h>
#ifdef _AVX2_WILL_BE_USED_ON_
#include<avx2intrin.h>
#include<avxintrin.h>
#include<avxvnniintrin.h>
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
	constexpr int wait_time = 100;
#if defined(_SIMD_01_)
	constexpr int align_size = 16;
#elif defined(_SIMD_02_)
	constexpr int align_size = 16;
#else 
	constexpr int align_size = 16;
#endif
#endif //_THREAD_MODE_
	constexpr float float_value_max = static_cast<float>(200);
	constexpr float float_value_min = (-1) * float_value_max;
	constexpr int int_value_max = static_cast<int>(200);
	constexpr int int_value_min = (-1) * int_value_max;
	extern std::atomic<bool> set_seed;
	extern std::atomic<unsigned long long> memory_heap;
	template <typename Data>
	inline int Int_Digits(Data const& alpha) {
		if constexpr (std::is_same_v<Data, bool>) {
			return 1;
		}
		else {
			if (alpha < static_cast<Data>(0)) {
				return (std::floor(std::log10(-alpha)) + 1);
			}
			else {
				return (std::floor(std::log10(alpha)) + 1);
			}
		}
	}
	template <typename Data>
	inline Data random(Data const& alpha, Data const& beta) {
		if (!static_cast<bool>(set_seed.load())) {
			std::srand(int(std::time(0)));
			set_seed.store(true);
		}
		if constexpr (std::is_same_v<Data, int>) {
#ifdef _DEBUG_MODE_
			printf("int random\n");
#endif
			long long range = static_cast<long long>(beta) - static_cast<long long>(alpha) + 1;
			long long ans = static_cast<long long>(std::rand()) * 2;
			if (range < 0) {
				range *= -1;
				ans %= range;
				return static_cast<int>(beta + ans);
			}
			else {
				ans %= range;
				return static_cast<int>(alpha + ans);
			}
		}
		else if constexpr (std::is_same_v<Data, float>) {
#ifdef _DEBUG_MODE_
			printf("float random\n");
#endif
			long double range = static_cast<long double>(beta) - static_cast<long double>(alpha) + 1;
			long double floating = static_cast<long double>(std::rand()) / RAND_MAX;
			if (range < 0) {
				range *= -1;
				floating *= range;
				return static_cast<float>(beta + floating);
			}
			else {
				floating *= range;
				return static_cast<float>(alpha + floating);
			}
		}
		else if constexpr (std::is_same_v<Data, bool>) {
#ifdef _DEBUG_MODE_
			printf("bool random\n");
#endif
			return static_cast<bool>(std::rand() % 2);
		}
		else {
			Data range = beta - alpha + 1;
			return alpha + (std::rand() % range);
		}
	}
	inline void status() {
		printf("\n");
		for (int i = 0; i < terminal_width; i++) printf("-");
		printf("\n");
		if (set_seed.load()) {
			printf("have set seed\n");
		}
		else {
			printf("no set seed\n");
		}
#ifdef _THREAD_MODE_
		printf("_THREAD_MODE_\nalign_size: %d\n", align_size);
#else
		printf("_THREAD_OFF_\n");
#endif
#if defined(_SIMD_01_)
		printf("_SIMD_MODE_01_\n");
#elif defined(_SIMD_02_) 
		printf("_SIMD_MODE_02_\n");
#else
		printf("_SIMD_OFF_\n");
#endif
		printf("memory heap: %llu\n", memory_heap.load());
		for (int i = 0; i < terminal_width; i++) printf("-");
		printf("\n\n");
		return;
	}
#ifdef _THREAD_MODE_
	inline int size_check(int const& alpha) {
		int gamma = alpha / vec_len; gamma += (alpha % vec_len) ? 1 : 0; gamma *= vec_len; return gamma;
	}
	template <typename Data>
	inline void tuple_add(Data* const& alpha, Data* const& beta, Data* const& gamma) {
		if constexpr ((std::is_same_v<Data, float>) && (SIMD_ON)) {
#if defined(_SIMD_01_)
			_mm_storeu_ps(gamma, _mm_add_ps(_mm_load_ps(alpha), _mm_load_ps(beta)));
#elif defined(_SIMD_02_)
			_mm256_storeu_ps(gamma, _mm256_add_ps(_mm256_load_ps(alpha), _mm256_load_ps(beta)));
#endif
		}
		else if constexpr (std::is_same_v<Data, bool>) {
#if defined(_SIMD_01_)
			gamma[0] = alpha[0] || beta[0]; gamma[1] = alpha[1] || beta[1]; gamma[2] = alpha[2] || beta[2]; gamma[3] = alpha[3] || beta[3];
#elif defined(_SIMD_02_)
			gamma[0] = alpha[0] || beta[0]; gamma[1] = alpha[1] || beta[1]; gamma[2] = alpha[2] || beta[2]; gamma[3] = alpha[3] || beta[3];
			gamma[4] = alpha[4] || beta[4]; gamma[5] = alpha[5] || beta[5]; gamma[6] = alpha[6] || beta[6]; gamma[7] = alpha[7] || beta[7];
#else
			gamma[0] = alpha[0] || beta[0]; gamma[1] = alpha[1] || beta[1]; gamma[2] = alpha[2] || beta[2];
#endif
		}
		else {
#if defined(_SIMD_01_)
			gamma[0] = alpha[0] + beta[0]; gamma[1] = alpha[1] + beta[1]; gamma[2] = alpha[2] + beta[2]; gamma[3] = alpha[3] + beta[3];
#elif defined(_SIMD_02_)
			gamma[0] = alpha[0] + beta[0]; gamma[1] = alpha[1] + beta[1]; gamma[2] = alpha[2] + beta[2]; gamma[3] = alpha[3] + beta[3];
			gamma[4] = alpha[4] + beta[4]; gamma[5] = alpha[5] + beta[5]; gamma[6] = alpha[6] + beta[6]; gamma[7] = alpha[7] + beta[7];
#else
			gamma[0] = alpha[0] + beta[0]; gamma[1] = alpha[1] + beta[1]; gamma[2] = alpha[2] + beta[2];
#endif
		}
		return;
	}
	template <typename Data>
	inline void tuple_add_s_(Data* const& alpha, Data const& beta, Data* const& gamma) {
		if constexpr ((std::is_same_v<Data, float>) && (SIMD_ON)) {
#if defined(_SIMD_01_)
			_mm_storeu_ps(gamma, _mm_add_ps(_mm_load_ps(alpha), _mm_set1_ps(beta)));
#elif defined(_SIMD_02_)
			_mm256_storeu_ps(gamma, _mm256_add_ps(_mm256_load_ps(alpha), _mm256_set1_ps(beta)));
#endif
		}
		else if constexpr (std::is_same_v<Data, bool>) {
#if defined(_SIMD_01_)
			gamma[0] = alpha[0] || beta; gamma[1] = alpha[1] || beta; gamma[2] = alpha[2] || beta; gamma[3] = alpha[3] || beta;
#elif defined(_SIMD_02_)
			gamma[0] = alpha[0] || beta; gamma[1] = alpha[1] || beta; gamma[2] = alpha[2] || beta; gamma[3] = alpha[3] || beta;
			gamma[4] = alpha[4] || beta; gamma[5] = alpha[5] || beta; gamma[6] = alpha[6] || beta; gamma[7] = alpha[7] || beta;
#else
			gamma[0] = alpha[0] || beta; gamma[1] = alpha[1] || beta; gamma[2] = alpha[2] || beta;
#endif
		}
		else {
#if defined(_SIMD_01_)
			gamma[0] = alpha[0] + beta; gamma[1] = alpha[1] + beta; gamma[2] = alpha[2] + beta; gamma[3] = alpha[3] + beta;
#elif defined(_SIMD_02_)
			gamma[0] = alpha[0] + beta; gamma[1] = alpha[1] + beta; gamma[2] = alpha[2] + beta; gamma[3] = alpha[3] + beta;
			gamma[4] = alpha[4] + beta; gamma[5] = alpha[5] + beta; gamma[6] = alpha[6] + beta; gamma[7] = alpha[7] + beta;
#else
			gamma[0] = alpha[0] + beta; gamma[1] = alpha[1] + beta; gamma[2] = alpha[2] + beta;
#endif
		}
		return;
	}
	template <typename Data>
	inline void tuple_sub(Data* const& alpha, Data* const& beta, Data* const& gamma) {
		if constexpr ((std::is_same_v<Data, float>) && (SIMD_ON)) {
#if defined(_SIMD_01_)
			_mm_storeu_ps(gamma, _mm_sub_ps(_mm_load_ps(alpha), _mm_load_ps(beta)));
#elif defined(_SIMD_02_)
			_mm256_storeu_ps(gamma, _mm256_sub_ps(_mm256_load_ps(alpha), _mm256_load_ps(beta)));
#endif
		}
		else if constexpr (std::is_same_v<Data, bool>) {
#if defined(_SIMD_01_)
			gamma[0] = alpha[0] || (!beta[0]); gamma[1] = alpha[1] || (!beta[1]); gamma[2] = alpha[2] || (!beta[2]); gamma[3] = alpha[3] || (!beta[3]);
#elif defined(_SIMD_02_)
			gamma[0] = alpha[0] || (!beta[0]); gamma[1] = alpha[1] || (!beta[1]); gamma[2] = alpha[2] || (!beta[2]); gamma[3] = alpha[3] || (!beta[3]);
			gamma[4] = alpha[4] || (!beta[4]); gamma[5] = alpha[5] || (!beta[5]); gamma[6] = alpha[6] || (!beta[6]); gamma[7] = alpha[7] || (!beta[7]);
#else
			gamma[0] = alpha[0] || (!beta[0]); gamma[1] = alpha[1] || (!beta[1]); gamma[2] = alpha[2] || (!beta[2]);
#endif
		}
		else {
#if defined(_SIMD_01_)
			gamma[0] = alpha[0] - beta[0]; gamma[1] = alpha[1] - beta[1]; gamma[2] = alpha[2] - beta[2]; gamma[3] = alpha[3] - beta[3];
#elif defined(_SIMD_02_)
			gamma[0] = alpha[0] - beta[0]; gamma[1] = alpha[1] - beta[1]; gamma[2] = alpha[2] - beta[2]; gamma[3] = alpha[3] - beta[3];
			gamma[4] = alpha[4] - beta[4]; gamma[5] = alpha[5] - beta[5]; gamma[6] = alpha[6] - beta[6]; gamma[7] = alpha[7] - beta[7];
#else
			gamma[0] = alpha[0] - beta[0]; gamma[1] = alpha[1] - beta[1]; gamma[2] = alpha[2] - beta[2];
#endif
		}
		return;
	}
	template <typename Data>
	inline void tuple_sub_sb_(Data* const& alpha, Data const& beta, Data* const& gamma) {
		if constexpr ((std::is_same_v<Data, float>) && (SIMD_ON)) {
#if defined(_SIMD_01_)
			_mm_storeu_ps(gamma, _mm_sub_ps(_mm_load_ps(alpha), _mm_set1_ps(beta)));
#elif defined(_SIMD_02_)
			_mm256_storeu_ps(gamma, _mm256_sub_ps(_mm256_load_ps(alpha), _mm256_set1_ps(beta)));
#endif
		}
		else if constexpr (std::is_same_v<Data, bool>) {
#if defined(_SIMD_01_)
			gamma[0] = alpha[0] || (!beta); gamma[1] = alpha[1] || (!beta); gamma[2] = alpha[2] || (!beta); gamma[3] = alpha[3] || (!beta);
#elif defined(_SIMD_02_)
			gamma[0] = alpha[0] || (!beta); gamma[1] = alpha[1] || (!beta); gamma[2] = alpha[2] || (!beta); gamma[3] = alpha[3] || (!beta);
			gamma[4] = alpha[4] || (!beta); gamma[5] = alpha[5] || (!beta); gamma[6] = alpha[6] || (!beta); gamma[7] = alpha[7] || (!beta);
#else
			gamma[0] = alpha[0] || (!beta); gamma[1] = alpha[1] || (!beta); gamma[2] = alpha[2] || (!beta);
#endif
		}
		else {
#if defined(_SIMD_01_)
			gamma[0] = alpha[0] - beta; gamma[1] = alpha[1] - beta; gamma[2] = alpha[2] - beta; gamma[3] = alpha[3] - beta;
#elif defined(_SIMD_02_)
			gamma[0] = alpha[0] - beta; gamma[1] = alpha[1] - beta; gamma[2] = alpha[2] - beta; gamma[3] = alpha[3] - beta;
			gamma[4] = alpha[4] - beta; gamma[5] = alpha[5] - beta; gamma[6] = alpha[6] - beta; gamma[7] = alpha[7] - beta;
#else
			gamma[0] = alpha[0] - beta; gamma[1] = alpha[1] - beta; gamma[2] = alpha[2] - beta;
#endif
		}
		return;
	}
	template <typename Data>
	inline void tuple_sub_sf_(Data const& alpha, Data* const& beta, Data* const& gamma) {
		if constexpr ((std::is_same_v<Data, float>) && (SIMD_ON)) {
#if defined(_SIMD_01_)
			_mm_storeu_ps(gamma, _mm_sub_ps(_mm_set1_ps(alpha), _mm_load_ps(beta)));
#elif defined(_SIMD_02_)
			_mm256_storeu_ps(gamma, _mm256_sub_ps(_mm256_set1_ps(alpha), _mm256_load_ps(beta)));
#endif
		}
		else if constexpr (std::is_same_v<Data, bool>) {
#if defined(_SIMD_01_)
			gamma[0] = alpha || (!beta[0]); gamma[1] = alpha || (!beta[1]); gamma[2] = alpha || (!beta[2]); gamma[3] = alpha || (!beta[3]);
#elif defined(_SIMD_02_)
			gamma[0] = alpha || (!beta[0]); gamma[1] = alpha || (!beta[1]); gamma[2] = alpha || (!beta[2]); gamma[3] = alpha || (!beta[3]);
			gamma[4] = alpha || (!beta[4]); gamma[5] = alpha || (!beta[5]); gamma[6] = alpha || (!beta[6]); gamma[7] = alpha || (!beta[7]);
#else
			gamma[0] = alpha || (!beta[0]); gamma[1] = alpha || (!beta[1]); gamma[2] = alpha || (!beta[2]);
#endif
		}
		else {
#if defined(_SIMD_01_)
			gamma[0] = alpha - beta[0]; gamma[1] = alpha - beta[1]; gamma[2] = alpha - beta[2]; gamma[3] = alpha - beta[3];
#elif defined(_SIMD_02_)
			gamma[0] = alpha - beta[0]; gamma[1] = alpha - beta[1]; gamma[2] = alpha - beta[2]; gamma[3] = alpha - beta[3];
			gamma[4] = alpha - beta[4]; gamma[5] = alpha - beta[5]; gamma[6] = alpha - beta[6]; gamma[7] = alpha - beta[7];
#else
			gamma[0] = alpha - beta[0]; gamma[1] = alpha - beta[1]; gamma[2] = alpha - beta[2];
#endif
		}
		return;
	}
	template <typename Data>
	inline void tuple_mul(Data* const& alpha, Data* const& beta, Data* const& gamma) {
		if constexpr ((std::is_same_v<Data, float>) && (SIMD_ON)) {
#if defined(_SIMD_01_)
			_mm_storeu_ps(gamma, _mm_mul_ps(_mm_load_ps(alpha), _mm_load_ps(beta)));
#elif defined(_SIMD_02_)
			_mm256_storeu_ps(gamma, _mm256_mul_ps(_mm256_load_ps(alpha), _mm256_load_ps(beta)));
#endif
		}
		else if constexpr (std::is_same_v<Data, bool>) {
#if defined(_SIMD_01_)
			gamma[0] = alpha[0] && beta[0]; gamma[1] = alpha[1] && beta[1]; gamma[2] = alpha[2] && beta[2]; gamma[3] = alpha[3] && beta[3];
#elif defined(_SIMD_02_)
			gamma[0] = alpha[0] && beta[0]; gamma[1] = alpha[1] && beta[1]; gamma[2] = alpha[2] && beta[2]; gamma[3] = alpha[3] && beta[3];
			gamma[4] = alpha[4] && beta[4]; gamma[5] = alpha[5] && beta[5]; gamma[6] = alpha[6] && beta[6]; gamma[7] = alpha[7] && beta[7];
#else
			gamma[0] = alpha[0] && beta[0]; gamma[1] = alpha[1] && beta[1]; gamma[2] = alpha[2] && beta[2];
#endif
		}
		else {
#if defined(_SIMD_01_)
			gamma[0] = alpha[0] * beta[0]; gamma[1] = alpha[1] * beta[1]; gamma[2] = alpha[2] * beta[2]; gamma[3] = alpha[3] * beta[3];
#elif defined(_SIMD_02_)
			gamma[0] = alpha[0] * beta[0]; gamma[1] = alpha[1] * beta[1]; gamma[2] = alpha[2] * beta[2]; gamma[3] = alpha[3] * beta[3];
			gamma[4] = alpha[4] * beta[4]; gamma[5] = alpha[5] * beta[5]; gamma[6] = alpha[6] * beta[6]; gamma[7] = alpha[7] * beta[7];
#else
			gamma[0] = alpha[0] * beta[0]; gamma[1] = alpha[1] * beta[1]; gamma[2] = alpha[2] * beta[2];
#endif
		}
		return;
	}
	template <typename Data>
	inline void tuple_mul_s_(Data* const& alpha, Data const& beta, Data* const& gamma) {
		if constexpr ((std::is_same_v<Data, float>) && (SIMD_ON)) {
#if defined(_SIMD_01_)
			_mm_storeu_ps(gamma, _mm_mul_ps(_mm_load_ps(alpha), _mm_set1_ps(beta)));
#elif defined(_SIMD_02_)
			_mm256_storeu_ps(gamma, _mm256_mul_ps(_mm256_load_ps(alpha), _mm256_set1_ps(beta)));
#endif
		}
		else if constexpr (std::is_same_v<Data, bool>) {
#if defined(_SIMD_01_)
			gamma[0] = alpha[0] && beta; gamma[1] = alpha[1] && beta; gamma[2] = alpha[2] && beta; gamma[3] = alpha[3] && beta;
#elif defined(_SIMD_02_)
			gamma[0] = alpha[0] && beta; gamma[1] = alpha[1] && beta; gamma[2] = alpha[2] && beta; gamma[3] = alpha[3] && beta;
			gamma[4] = alpha[4] && beta; gamma[5] = alpha[5] && beta; gamma[6] = alpha[6] && beta; gamma[7] = alpha[7] && beta;
#else
			gamma[0] = alpha[0] && beta; gamma[1] = alpha[1] && beta; gamma[2] = alpha[2] && beta;
#endif
		}
		else {
#if defined(_SIMD_01_)
			gamma[0] = alpha[0] * beta; gamma[1] = alpha[1] * beta; gamma[2] = alpha[2] * beta; gamma[3] = alpha[3] * beta;
#elif defined(_SIMD_02_)
			gamma[0] = alpha[0] * beta; gamma[1] = alpha[1] * beta; gamma[2] = alpha[2] * beta; gamma[3] = alpha[3] * beta;
			gamma[4] = alpha[4] * beta; gamma[5] = alpha[5] * beta; gamma[6] = alpha[6] * beta; gamma[7] = alpha[7] * beta;
#else
			gamma[0] = alpha[0] * beta; gamma[1] = alpha[1] * beta; gamma[2] = alpha[2] * beta;
#endif
		}
		return;
	}
	template <typename Data>
	inline void tuple_div(Data* const& alpha, Data* const& beta, Data* const& gamma) {
		if constexpr ((std::is_same_v<Data, float>) && (SIMD_ON)) {
#if defined(_SIMD_01_)
			_mm_storeu_ps(gamma, _mm_div_ps(_mm_load_ps(alpha), _mm_load_ps(beta)));
#elif defined(_SIMD_02_)
			_mm256_storeu_ps(gamma, _mm256_div_ps(_mm256_load_ps(alpha), _mm256_load_ps(beta)));
#endif
		}
		else if constexpr (std::is_same_v<Data, bool>) {
#if defined(_SIMD_01_)
			gamma[0] = (alpha[0] || beta[0]) && (!(alpha[0] && beta[0])); gamma[1] = (alpha[1] || beta[1]) && (!(alpha[1] && beta[1]));
			gamma[2] = (alpha[2] || beta[2]) && (!(alpha[2] && beta[2])); gamma[3] = (alpha[3] || beta[3]) && (!(alpha[3] && beta[3]));
#elif defined(_SIMD_02_)
			gamma[0] = (alpha[0] || beta[0]) && (!(alpha[0] && beta[0])); gamma[1] = (alpha[1] || beta[1]) && (!(alpha[1] && beta[1]));
			gamma[2] = (alpha[2] || beta[2]) && (!(alpha[2] && beta[2])); gamma[3] = (alpha[3] || beta[3]) && (!(alpha[3] && beta[3]));
			gamma[4] = (alpha[4] || beta[4]) && (!(alpha[4] && beta[4])); gamma[5] = (alpha[5] || beta[5]) && (!(alpha[5] && beta[5]));
			gamma[6] = (alpha[6] || beta[6]) && (!(alpha[6] && beta[6])); gamma[7] = (alpha[7] || beta[7]) && (!(alpha[7] && beta[7]));
#else
			gamma[0] = (alpha[0] || beta[0]) && (!(alpha[0] && beta[0])); gamma[1] = (alpha[1] || beta[1]) && (!(alpha[1] && beta[1]));
			gamma[2] = (alpha[2] || beta[2]) && (!(alpha[2] && beta[2]));
#endif
		}
		else {
#if defined(_SIMD_01_)
			gamma[0] = alpha[0] / beta[0]; gamma[1] = alpha[1] / beta[1]; gamma[2] = alpha[2] / beta[2]; gamma[3] = alpha[3] / beta[3];
#elif defined(_SIMD_02_)
			gamma[0] = alpha[0] / beta[0]; gamma[1] = alpha[1] / beta[1]; gamma[2] = alpha[2] / beta[2]; gamma[3] = alpha[3] / beta[3];
			gamma[4] = alpha[4] / beta[4]; gamma[5] = alpha[5] / beta[5]; gamma[6] = alpha[6] / beta[6]; gamma[7] = alpha[7] / beta[7];
#else
			gamma[0] = alpha[0] / beta[0]; gamma[1] = alpha[1] / beta[1]; gamma[2] = alpha[2] / beta[2];
#endif
		}
		return;
	}
	template <typename Data>
	inline void tuple_div_sb_(Data* const& alpha, Data const& beta, Data* const& gamma) {
		if constexpr ((std::is_same_v<Data, float>) && (SIMD_ON)) {
#if defined(_SIMD_01_)
			_mm_storeu_ps(gamma, _mm_div_ps(_mm_load_ps(alpha), _mm_set1_ps(beta)));
#elif defined(_SIMD_02_)
			_mm256_storeu_ps(gamma, _mm256_div_ps(_mm256_load_ps(alpha), _mm256_set1_ps(beta)));
#endif
		}
		else if constexpr (std::is_same_v<Data, bool>) {
#if defined(_SIMD_01_)
			gamma[0] = (alpha[0] || beta) && (!(alpha[0] && beta)); gamma[1] = (alpha[1] || beta) && (!(alpha[1] && beta));
			gamma[2] = (alpha[2] || beta) && (!(alpha[2] && beta)); gamma[3] = (alpha[3] || beta) && (!(alpha[3] && beta));
#elif defined(_SIMD_02_)
			gamma[0] = (alpha[0] || beta) && (!(alpha[0] && beta)); gamma[1] = (alpha[1] || beta) && (!(alpha[1] && beta));
			gamma[2] = (alpha[2] || beta) && (!(alpha[2] && beta)); gamma[3] = (alpha[3] || beta) && (!(alpha[3] && beta));
			gamma[4] = (alpha[4] || beta) && (!(alpha[4] && beta)); gamma[5] = (alpha[5] || beta) && (!(alpha[5] && beta));
			gamma[6] = (alpha[6] || beta) && (!(alpha[6] && beta)); gamma[7] = (alpha[7] || beta) && (!(alpha[7] && beta));
#else
			gamma[0] = (alpha[0] || beta) && (!(alpha[0] && beta)); gamma[1] = (alpha[1] || beta) && (!(alpha[1] && beta));
			gamma[2] = (alpha[2] || beta) && (!(alpha[2] && beta));
#endif
		}
		else {
#if defined(_SIMD_01_)
			gamma[0] = alpha[0] / beta; gamma[1] = alpha[1] / beta; gamma[2] = alpha[2] / beta; gamma[3] = alpha[3] / beta;
#elif defined(_SIMD_02_)
			gamma[0] = alpha[0] / beta; gamma[1] = alpha[1] / beta; gamma[2] = alpha[2] / beta; gamma[3] = alpha[3] / beta;
			gamma[4] = alpha[4] / beta; gamma[5] = alpha[5] / beta; gamma[6] = alpha[6] / beta; gamma[7] = alpha[7] / beta;
#else
			gamma[0] = alpha[0] / beta; gamma[1] = alpha[1] / beta; gamma[2] = alpha[2] / beta;
#endif
		}
		return;
	}
	template <typename Data>
	inline void tuple_div_sf_(Data const& alpha, Data* const& beta, Data* const& gamma) {
		if constexpr ((std::is_same_v<Data, float>) && (SIMD_ON)) {
#if defined(_SIMD_01_)
			_mm_storeu_ps(gamma, _mm_div_ps(_mm_set1_ps(alpha), _mm_load_ps(beta)));
#elif defined(_SIMD_02_)
			_mm256_storeu_ps(gamma, _mm256_div_ps(_mm256_set1_ps(alpha), _mm256_load_ps(beta)));
#endif
		}
		else if constexpr (std::is_same_v<Data, bool>) {
#if defined(_SIMD_01_)
			gamma[0] = (alpha || beta[0]) && (!(alpha && beta[0])); gamma[1] = (alpha || beta[1]) && (!(alpha && beta[1]));
			gamma[2] = (alpha || beta[2]) && (!(alpha && beta[2])); gamma[3] = (alpha || beta[3]) && (!(alpha && beta[3]));
#elif defined(_SIMD_02_)
			gamma[0] = (alpha || beta[0]) && (!(alpha && beta[0])); gamma[1] = (alpha || beta[1]) && (!(alpha && beta[1]));
			gamma[2] = (alpha || beta[2]) && (!(alpha && beta[2])); gamma[3] = (alpha || beta[3]) && (!(alpha && beta[3]));
			gamma[4] = (alpha || beta[4]) && (!(alpha && beta[4])); gamma[5] = (alpha || beta[5]) && (!(alpha && beta[5]));
			gamma[6] = (alpha || beta[6]) && (!(alpha && beta[6])); gamma[7] = (alpha || beta[7]) && (!(alpha && beta[7]));
#else
			gamma[0] = (alpha || beta[0]) && (!(alpha && beta[0])); gamma[1] = (alpha || beta[1]) && (!(alpha && beta[1]));
			gamma[2] = (alpha || beta[2]) && (!(alpha && beta[2]));
#endif
		}
		else {
#if defined(_SIMD_01_)
			gamma[0] = alpha / beta[0]; gamma[1] = alpha / beta[1]; gamma[2] = alpha / beta[2]; gamma[3] = alpha / beta[3];
#elif defined(_SIMD_02_)
			gamma[0] = alpha / beta[0]; gamma[1] = alpha / beta[1]; gamma[2] = alpha / beta[2]; gamma[3] = alpha / beta[3];
			gamma[4] = alpha / beta[4]; gamma[5] = alpha / beta[5]; gamma[6] = alpha / beta[6]; gamma[7] = alpha / beta[7];
#else
			gamma[0] = alpha / beta[0]; gamma[1] = alpha / beta[1]; gamma[2] = alpha / beta[2];
#endif
		}
		return;
	}
	template <typename Data>
	inline void tuple_eq_v(Data* const& alpha, Data* const& beta, bool* const& gamma) {
#if defined(_SIMD_01_)
		gamma[0] = alpha[0] == beta[0]; gamma[1] = alpha[1] == beta[1]; gamma[2] = alpha[2] == beta[2]; gamma[3] = alpha[3] == beta[3];
#elif defined(_SIMD_02_)
		gamma[0] = alpha[0] == beta[0]; gamma[1] = alpha[1] == beta[1]; gamma[2] = alpha[2] == beta[2]; gamma[3] = alpha[3] == beta[3];
		gamma[4] = alpha[4] == beta[4]; gamma[5] = alpha[5] == beta[5]; gamma[6] = alpha[6] == beta[6]; gamma[7] = alpha[7] == beta[7];
#else
		gamma[0] = alpha[0] == beta[0]; gamma[1] = alpha[1] == beta[1]; gamma[2] = alpha[2] == beta[2];
#endif
		return;
	}
	template <typename Data>
	inline void tuple_eq_s(Data* const& alpha, Data const& beta, bool* const& gamma) {
#if defined(_SIMD_01_)
		gamma[0] = alpha[0] == beta; gamma[1] = alpha[1] == beta; gamma[2] = alpha[2] == beta; gamma[3] = alpha[3] == beta;
#elif defined(_SIMD_02_)
		gamma[0] = alpha[0] == beta; gamma[1] = alpha[1] == beta; gamma[2] = alpha[2] == beta; gamma[3] = alpha[3] == beta;
		gamma[4] = alpha[4] == beta; gamma[5] = alpha[5] == beta; gamma[6] = alpha[6] == beta; gamma[7] = alpha[7] == beta;
#else
		gamma[0] = alpha[0] == beta; gamma[1] = alpha[1] == beta; gamma[2] = alpha[2] == beta;
#endif
		return;
	}
	template <typename Data>
	inline void tuple_ne_v(Data* const& alpha, Data* const& beta, bool* const& gamma) {
#if defined(_SIMD_01_)
		gamma[0] = alpha[0] != beta[0]; gamma[1] = alpha[1] != beta[1]; gamma[2] = alpha[2] != beta[2]; gamma[3] = alpha[3] != beta[3];
#elif defined(_SIMD_02_)
		gamma[0] = alpha[0] != beta[0]; gamma[1] = alpha[1] != beta[1]; gamma[2] = alpha[2] != beta[2]; gamma[3] = alpha[3] != beta[3];
		gamma[4] = alpha[4] != beta[4]; gamma[5] = alpha[5] != beta[5]; gamma[6] = alpha[6] != beta[6]; gamma[7] = alpha[7] != beta[7];
#else
		gamma[0] = alpha[0] != beta[0]; gamma[1] = alpha[1] != beta[1]; gamma[2] = alpha[2] != beta[2];
#endif
		return;
	}
	template <typename Data>
	inline void tuple_ne_s(Data* const& alpha, Data const& beta, bool* const& gamma) {
#if defined(_SIMD_01_)
		gamma[0] = alpha[0] != beta; gamma[1] = alpha[1] != beta; gamma[2] = alpha[2] != beta; gamma[3] = alpha[3] != beta;
#elif defined(_SIMD_02_)
		gamma[0] = alpha[0] != beta; gamma[1] = alpha[1] != beta; gamma[2] = alpha[2] != beta; gamma[3] = alpha[3] != beta;
		gamma[4] = alpha[4] != beta; gamma[5] = alpha[5] != beta; gamma[6] = alpha[6] != beta; gamma[7] = alpha[7] != beta;
#else
		gamma[0] = alpha[0] != beta; gamma[1] = alpha[1] != beta; gamma[2] = alpha[2] != beta;
#endif
		return;
	}
	template <typename Data>
	inline void tuple_bg_v(Data* const& alpha, Data* const& beta, bool* const& gamma) {
#if defined(_SIMD_01_)
		gamma[0] = alpha[0] > beta[0]; gamma[1] = alpha[1] > beta[1]; gamma[2] = alpha[2] > beta[2]; gamma[3] = alpha[3] > beta[3];
#elif defined(_SIMD_02_)
		gamma[0] = alpha[0] > beta[0]; gamma[1] = alpha[1] > beta[1]; gamma[2] = alpha[2] > beta[2]; gamma[3] = alpha[3] > beta[3];
		gamma[4] = alpha[4] > beta[4]; gamma[5] = alpha[5] > beta[5]; gamma[6] = alpha[6] > beta[6]; gamma[7] = alpha[7] > beta[7];
#else
		gamma[0] = alpha[0] > beta[0]; gamma[1] = alpha[1] > beta[1]; gamma[2] = alpha[2] > beta[2];
#endif
		return;
	}
	template <typename Data>
	inline void tuple_bg_sb(Data* const& alpha, Data const& beta, bool* const& gamma) {
#if defined(_SIMD_01_)
		gamma[0] = alpha[0] > beta; gamma[1] = alpha[1] > beta; gamma[2] = alpha[2] > beta; gamma[3] = alpha[3] > beta;
#elif defined(_SIMD_02_)
		gamma[0] = alpha[0] > beta; gamma[1] = alpha[1] > beta; gamma[2] = alpha[2] > beta; gamma[3] = alpha[3] > beta;
		gamma[4] = alpha[4] > beta; gamma[5] = alpha[5] > beta; gamma[6] = alpha[6] > beta; gamma[7] = alpha[7] > beta;
#else
		gamma[0] = alpha[0] > beta; gamma[1] = alpha[1] > beta; gamma[2] = alpha[2] > beta;
#endif
		return;
	}
	template <typename Data>
	inline void tuple_bg_sf(Data const& alpha, Data* const& beta, bool* const& gamma) {
#if defined(_SIMD_01_)
		gamma[0] = alpha > beta[0]; gamma[1] = alpha > beta[1]; gamma[2] = alpha > beta[2]; gamma[3] = alpha > beta[3];
#elif defined(_SIMD_02_)
		gamma[0] = alpha > beta[0]; gamma[1] = alpha > beta[1]; gamma[2] = alpha > beta[2]; gamma[3] = alpha > beta[3];
		gamma[4] = alpha > beta[4]; gamma[5] = alpha > beta[5]; gamma[6] = alpha > beta[6]; gamma[7] = alpha > beta[7];
#else
		gamma[0] = alpha > beta[0]; gamma[1] = alpha > beta[1]; gamma[2] = alpha > beta[2];
#endif
		return;
	}
	template <typename Data>
	inline void tuple_bq_v(Data* const& alpha, Data* const& beta, bool* const& gamma) {
#if defined(_SIMD_01_)
		gamma[0] = alpha[0] >= beta[0]; gamma[1] = alpha[1] >= beta[1]; gamma[2] = alpha[2] >= beta[2]; gamma[3] = alpha[3] >= beta[3];
#elif defined(_SIMD_02_)
		gamma[0] = alpha[0] >= beta[0]; gamma[1] = alpha[1] >= beta[1]; gamma[2] = alpha[2] >= beta[2]; gamma[3] = alpha[3] >= beta[3];
		gamma[4] = alpha[4] >= beta[4]; gamma[5] = alpha[5] >= beta[5]; gamma[6] = alpha[6] >= beta[6]; gamma[7] = alpha[7] >= beta[7];
#else
		gamma[0] = alpha[0] >= beta[0]; gamma[1] = alpha[1] >= beta[1]; gamma[2] = alpha[2] >= beta[2];
#endif
		return;
	}
	template <typename Data>
	inline void tuple_bq_sb(Data* const& alpha, Data const& beta, bool* const& gamma) {
#if defined(_SIMD_01_)
		gamma[0] = alpha[0] >= beta; gamma[1] = alpha[1] >= beta; gamma[2] = alpha[2] >= beta; gamma[3] = alpha[3] >= beta;
#elif defined(_SIMD_02_)
		gamma[0] = alpha[0] >= beta; gamma[1] = alpha[1] >= beta; gamma[2] = alpha[2] >= beta; gamma[3] = alpha[3] >= beta;
		gamma[4] = alpha[4] >= beta; gamma[5] = alpha[5] >= beta; gamma[6] = alpha[6] >= beta; gamma[7] = alpha[7] >= beta;
#else
		gamma[0] = alpha[0] >= beta; gamma[1] = alpha[1] >= beta; gamma[2] = alpha[2] >= beta;
#endif
		return;
	}
	template <typename Data>
	inline void tuple_bq_sf(Data const& alpha, Data* const& beta, bool* const& gamma) {
#if defined(_SIMD_01_)
		gamma[0] = alpha >= beta[0]; gamma[1] = alpha >= beta[1]; gamma[2] = alpha >= beta[2]; gamma[3] = alpha >= beta[3];
#elif defined(_SIMD_02_)
		gamma[0] = alpha >= beta[0]; gamma[1] = alpha >= beta[1]; gamma[2] = alpha >= beta[2]; gamma[3] = alpha >= beta[3];
		gamma[4] = alpha >= beta[4]; gamma[5] = alpha >= beta[5]; gamma[6] = alpha >= beta[6]; gamma[7] = alpha >= beta[7];
#else
		gamma[0] = alpha >= beta[0]; gamma[1] = alpha >= beta[1]; gamma[2] = alpha >= beta[2];
#endif
		return;
	}
	template <typename Data>
	inline void tuple_sm_v(Data* const& alpha, Data* const& beta, bool* const& gamma) {
#if defined(_SIMD_01_)
		gamma[0] = alpha[0] < beta[0]; gamma[1] = alpha[1] < beta[1]; gamma[2] = alpha[2] < beta[2]; gamma[3] = alpha[3] < beta[3];
#elif defined(_SIMD_02_)
		gamma[0] = alpha[0] < beta[0]; gamma[1] = alpha[1] < beta[1]; gamma[2] = alpha[2] < beta[2]; gamma[3] = alpha[3] < beta[3];
		gamma[4] = alpha[4] < beta[4]; gamma[5] = alpha[5] < beta[5]; gamma[6] = alpha[6] < beta[6]; gamma[7] = alpha[7] < beta[7];
#else
		gamma[0] = alpha[0] < beta[0]; gamma[1] = alpha[1] < beta[1]; gamma[2] = alpha[2] < beta[2];
#endif
		return;
	}
	template <typename Data>
	inline void tuple_sm_sb(Data* const& alpha, Data const& beta, bool* const& gamma) {
#if defined(_SIMD_01_)
		gamma[0] = alpha[0] < beta; gamma[1] = alpha[1] < beta; gamma[2] = alpha[2] < beta; gamma[3] = alpha[3] < beta;
#elif defined(_SIMD_02_)
		gamma[0] = alpha[0] < beta; gamma[1] = alpha[1] < beta; gamma[2] = alpha[2] < beta; gamma[3] = alpha[3] < beta;
		gamma[4] = alpha[4] < beta; gamma[5] = alpha[5] < beta; gamma[6] = alpha[6] < beta; gamma[7] = alpha[7] < beta;
#else
		gamma[0] = alpha[0] < beta; gamma[1] = alpha[1] < beta; gamma[2] = alpha[2] < beta;
#endif
		return;
	}
	template <typename Data>
	inline void tuple_sm_sf(Data const& alpha, Data* const& beta, bool* const& gamma) {
#if defined(_SIMD_01_)
		gamma[0] = alpha < beta[0]; gamma[1] = alpha < beta[1]; gamma[2] = alpha < beta[2]; gamma[3] = alpha < beta[3];
#elif defined(_SIMD_02_)
		gamma[0] = alpha < beta[0]; gamma[1] = alpha < beta[1]; gamma[2] = alpha < beta[2]; gamma[3] = alpha < beta[3];
		gamma[4] = alpha < beta[4]; gamma[5] = alpha < beta[5]; gamma[6] = alpha < beta[6]; gamma[7] = alpha < beta[7];
#else
		gamma[0] = alpha < beta[0]; gamma[1] = alpha < beta[1]; gamma[2] = alpha < beta[2];
#endif
		return;
	}
	template <typename Data>
	inline void tuple_sq_v(Data* const& alpha, Data* const& beta, bool* const& gamma) {
#if defined(_SIMD_01_)
		gamma[0] = alpha[0] <= beta[0]; gamma[1] = alpha[1] <= beta[1]; gamma[2] = alpha[2] <= beta[2]; gamma[3] = alpha[3] <= beta[3];
#elif defined(_SIMD_02_)
		gamma[0] = alpha[0] <= beta[0]; gamma[1] = alpha[1] <= beta[1]; gamma[2] = alpha[2] <= beta[2]; gamma[3] = alpha[3] <= beta[3];
		gamma[4] = alpha[4] <= beta[4]; gamma[5] = alpha[5] <= beta[5]; gamma[6] = alpha[6] <= beta[6]; gamma[7] = alpha[7] <= beta[7];
#else
		gamma[0] = alpha[0] <= beta[0]; gamma[1] = alpha[1] <= beta[1]; gamma[2] = alpha[2] <= beta[2];
#endif
		return;
	}
	template <typename Data>
	inline void tuple_sq_sb(Data* const& alpha, Data const& beta, bool* const& gamma) {
#if defined(_SIMD_01_)
		gamma[0] = alpha[0] <= beta; gamma[1] = alpha[1] <= beta; gamma[2] = alpha[2] <= beta; gamma[3] = alpha[3] <= beta;
#elif defined(_SIMD_02_)
		gamma[0] = alpha[0] <= beta; gamma[1] = alpha[1] <= beta; gamma[2] = alpha[2] <= beta; gamma[3] = alpha[3] <= beta;
		gamma[4] = alpha[4] <= beta; gamma[5] = alpha[5] <= beta; gamma[6] = alpha[6] <= beta; gamma[7] = alpha[7] <= beta;
#else
		gamma[0] = alpha[0] <= beta; gamma[1] = alpha[1] <= beta; gamma[2] = alpha[2] <= beta;
#endif
		return;
	}
	template <typename Data>
	inline void tuple_sq_sf(Data const& alpha, Data* const& beta, bool* const& gamma) {
#if defined(_SIMD_01_)
		gamma[0] = alpha <= beta[0]; gamma[1] = alpha <= beta[1]; gamma[2] = alpha <= beta[2]; gamma[3] = alpha <= beta[3];
#elif defined(_SIMD_02_)
		gamma[0] = alpha <= beta[0]; gamma[1] = alpha <= beta[1]; gamma[2] = alpha <= beta[2]; gamma[3] = alpha <= beta[3];
		gamma[4] = alpha <= beta[4]; gamma[5] = alpha <= beta[5]; gamma[6] = alpha <= beta[6]; gamma[7] = alpha <= beta[7];
#else
		gamma[0] = alpha <= beta[0]; gamma[1] = alpha <= beta[1]; gamma[2] = alpha <= beta[2];
#endif
		return;
	}
	template <typename Data>
	inline void tuple_abs(Data* const& alpha, Data* const& gamma) {
#ifdef _DEBUG_MODE_
		printf("~tuple abs at %p~\n", alpha);
#endif
		if constexpr (std::is_same_v<Data, float>) {
#if defined(_SIMD_01_)
			gamma[0] = std::fabs(alpha[0]); gamma[1] = std::fabs(alpha[1]); gamma[2] = std::fabs(alpha[2]); gamma[3] = std::fabs(alpha[3]);
#elif defined(_SIMD_02_)
			gamma[0] = std::fabs(alpha[0]); gamma[1] = std::fabs(alpha[1]); gamma[2] = std::fabs(alpha[2]); gamma[3] = std::fabs(alpha[3]);
			gamma[4] = std::fabs(alpha[4]); gamma[5] = std::fabs(alpha[5]); gamma[6] = std::fabs(alpha[6]); gamma[7] = std::fabs(alpha[7]);
#else
			gamma[0] = std::fabs(alpha[0]); gamma[1] = std::fabs(alpha[1]); gamma[2] = std::fabs(alpha[2]);
#endif
		}
		else if constexpr (std::is_same_v<Data, int>) {
#if defined(_SIMD_01_)
			gamma[0] = std::abs(alpha[0]); gamma[1] = std::abs(alpha[1]); gamma[2] = std::abs(alpha[2]); gamma[3] = std::abs(alpha[3]);
#elif defined(_SIMD_02_)
			gamma[0] = std::abs(alpha[0]); gamma[1] = std::abs(alpha[1]); gamma[2] = std::abs(alpha[2]); gamma[3] = std::abs(alpha[3]);
			gamma[4] = std::abs(alpha[4]); gamma[5] = std::abs(alpha[5]); gamma[6] = std::abs(alpha[6]); gamma[7] = std::abs(alpha[7]);
#else
			gamma[0] = std::abs(alpha[0]); gamma[1] = std::abs(alpha[1]); gamma[2] = std::abs(alpha[2]);
#endif
		}
		else {
#if defined(_SIMD_01_)
			gamma[0] = alpha[0]; gamma[1] = alpha[1]; gamma[2] = alpha[2]; gamma[3] = alpha[3];
#elif defined(_SIMD_02_)
			gamma[0] = alpha[0]; gamma[1] = alpha[1]; gamma[2] = alpha[2]; gamma[3] = alpha[3];
			gamma[4] = alpha[4]; gamma[5] = alpha[5]; gamma[6] = alpha[6]; gamma[7] = alpha[7];
#else
			gamma[0] = alpha[0]; gamma[1] = alpha[1]; gamma[2] = alpha[2];
#endif
		}
#ifdef _DEBUG_MODE_
		printf("~tuple abs end~\n");
#endif
		return;
	}
	template <typename Data>
	inline void tuple_rand(Data* const& gamma, Data const& alpha, Data const& beta) {
#if defined(_SIMD_01_)
		gamma[0] = Basic_Math::random(alpha, beta); gamma[1] = Basic_Math::random(alpha, beta);
		gamma[2] = Basic_Math::random(alpha, beta); gamma[3] = Basic_Math::random(alpha, beta);
#elif defined(_SIMD_02_)
		gamma[0] = Basic_Math::random(alpha, beta); gamma[1] = Basic_Math::random(alpha, beta);
		gamma[2] = Basic_Math::random(alpha, beta); gamma[3] = Basic_Math::random(alpha, beta);
		gamma[4] = Basic_Math::random(alpha, beta); gamma[5] = Basic_Math::random(alpha, beta);
		gamma[6] = Basic_Math::random(alpha, beta); gamma[7] = Basic_Math::random(alpha, beta);
#else
		gamma[0] = Basic_Math::random(alpha, beta); gamma[1] = Basic_Math::random(alpha, beta);
		gamma[2] = Basic_Math::random(alpha, beta);
#endif
		return;
	}
	template <typename Data>
	inline void tuple_set(Data* const& gamma, Data const& alpha) {
#ifdef _DEBUG_MODE_
		printf("~tuple set at %p~\n", gamma);
#endif
#if defined(_SIMD_01_)
		if constexpr (std::is_same_v<Data, float>) {
			_mm_storeu_ps(gamma, _mm_set1_ps(alpha));
		}
		else {
			gamma[0] = alpha; gamma[1] = alpha; gamma[2] = alpha; gamma[3] = alpha;
		}
#elif defined(_SIMD_02_)
		if constexpr (std::is_same_v<Data, float>) {
			_mm256_storeu_ps(gamma, _mm256_set1_ps(alpha));
		}
		else {
			gamma[0] = alpha; gamma[1] = alpha; gamma[2] = alpha; gamma[3] = alpha;
			gamma[4] = alpha; gamma[5] = alpha; gamma[6] = alpha; gamma[7] = alpha;
		}
#else
		gamma[0] = alpha; gamma[1] = alpha; gamma[2] = alpha;
#endif
#ifdef _DEBUG_MODE_
		printf("~tuple set finish~\n");
#endif
		return;
	}
	template <typename Data>
	inline void tuple_load(Data* const& alpha, Data* const& gamma) {
#ifdef _DEBUG_MODE_
		printf("~tuple load from %p to %p~\n", alpha, gamma);
#endif
#if defined(_SIMD_01_)
		if constexpr (std::is_same_v<Data, float>) {
			_mm_storeu_ps(gamma, _mm_loadu_ps(alpha));
		}
		else {
			gamma[0] = alpha[0]; gamma[1] = alpha[1]; gamma[2] = alpha[2]; gamma[3] = alpha[3];
		}
#elif defined(_SIMD_02_)
		if constexpr (std::is_same_v<Data, float>) {
			_mm256_storeu_ps(gamma, _mm256_loadu_ps(alpha));
		}
		else {
			gamma[0] = alpha[0]; gamma[1] = alpha[1]; gamma[2] = alpha[2]; gamma[3] = alpha[3];
			gamma[4] = alpha[4]; gamma[5] = alpha[5]; gamma[6] = alpha[6]; gamma[7] = alpha[7];
		}
#else
		gamma[0] = alpha[0]; gamma[1] = alpha[1]; gamma[2] = alpha[2];
#endif
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