#ifndef BASIC_H
#define BASIC_H
#include"./define.hpp"
namespace Basic_Math {
	/*base for 'check_simd'*/
	template <class T>
	struct is_simd_on {
#ifdef _SIMD_MODE_
		constexpr static bool value = is_same_v<T, float>;
#else 
		constexpr static bool value = false;
#endif
	};
	/*check if the type is support for SIMD*/
	template <class T>
	constexpr bool check_simd = is_simd_on<T>::value;
	// the value do as you think
	constexpr int Float16_Accuracy = 3;
	// the value do as you think
	constexpr int Float32_Accuracy = 7;
	// the value do as you think
	constexpr int Float64_Accuracy = 15;
	// the value do as you think
	constexpr int terminal_width = 144;
	// the value do as you think
	constexpr int terminal_height = 40;
	//vec_len: in order to pack tuple
#if defined(_SIMD_01_)
	constexpr int vec_len = 4;
#elif defined(_SIMD_02_)
	constexpr int vec_len = 8;
#elif defined(_THREAD_MODE_)
	constexpr int vec_len = 4;
#else
	constexpr int vec_len = 1;
#endif //_SIMD_00_
#ifdef _SIMD_MODE_
	constexpr bool SIMD_ON = true;
	constexpr bool THREAD_ON = true;
#else
	constexpr bool SIMD_ON = false;
#ifdef _THREAD_MODE_
	constexpr bool THREAD_ON = true;
#else
	constexpr bool THREAD_ON = false;
#endif //_THREAD_MODE_
#endif //_SIMD_MODE_
#ifdef _THREAD_MODE_
	//the base delay that threads use
	constexpr int wait_time = 100;
	//addition to set value
	constexpr int set_delay = 32;
	//addition to do operate
	constexpr int operate_delay = 128;
	//addition to call funcion
	constexpr int function_delay = 1024;
	//the aligned size that support x86
#if defined(_SIMD_01_)
	constexpr int align_size = 16;
#elif defined(_SIMD_02_)
	constexpr int align_size = 32;
#else 
	constexpr int align_size = 8;
#endif
#endif //_THREAD_MODE_
	extern std::atomic<bool> set_seed;
	//space when memory is leak
	extern float float_leak;
	//space when memory is leak
	extern bool bool_leak;
	//space when memory is leak
	extern int int_leak;
	/*int digits
	Enter: 1.value
	count how many digits the value has before the decimal point
	return the answer*/
	template <typename Data>
	static inline __attribute__((__always_inline__)) int Int_Digits(Data const& alpha) {
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
	/*random
	Enter: 1.min value 2.max value
	random a value between min and max
	return the answer*/
	template <typename Data>
	static inline __attribute__((__always_inline__)) Data random(Data const& alpha, Data const& beta) {
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
			long double range = static_cast<long double>(beta) - static_cast<long double>(alpha);
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
#ifdef _THREAD_MODE_
	/*below are the functions you don't need to use*/
	static inline __attribute__((__always_inline__)) int size_check(int const& alpha) {
		if (alpha <= 0)return vec_len;
		int gamma = alpha / vec_len; gamma += (alpha % vec_len) ? 1 : 0; gamma *= vec_len; return gamma;
	}
	/*below are the functions you don't need to use*/
	template <typename Data>
	static inline __attribute__((__always_inline__)) void tuple_add(Data* const& alpha, Data* const& beta, Data* const& gamma) {
		if constexpr ((std::is_same_v<Data, float>) && (SIMD_ON)) {
#if defined(_SIMD_01_)
			_mm_store_ps(gamma, _mm_add_ps(_mm_load_ps(alpha), _mm_load_ps(beta)));
#elif defined(_SIMD_02_)
			_mm256_store_ps(gamma, _mm256_add_ps(_mm256_load_ps(alpha), _mm256_load_ps(beta)));
#endif
		}
		else if constexpr (std::is_same_v<Data, bool>) {
#if defined(_SIMD_01_)
			gamma[0] = alpha[0] || beta[0]; gamma[1] = alpha[1] || beta[1]; gamma[2] = alpha[2] || beta[2]; gamma[3] = alpha[3] || beta[3];
#elif defined(_SIMD_02_)
			gamma[0] = alpha[0] || beta[0]; gamma[1] = alpha[1] || beta[1]; gamma[2] = alpha[2] || beta[2]; gamma[3] = alpha[3] || beta[3];
			gamma[4] = alpha[4] || beta[4]; gamma[5] = alpha[5] || beta[5]; gamma[6] = alpha[6] || beta[6]; gamma[7] = alpha[7] || beta[7];
#else
			gamma[0] = alpha[0] || beta[0]; gamma[1] = alpha[1] || beta[1]; gamma[2] = alpha[2] || beta[2]; gamma[3] = alpha[3] || beta[3];
#endif
		}
		else {
#if defined(_SIMD_01_)
			gamma[0] = alpha[0] + beta[0]; gamma[1] = alpha[1] + beta[1]; gamma[2] = alpha[2] + beta[2]; gamma[3] = alpha[3] + beta[3];
#elif defined(_SIMD_02_)
			gamma[0] = alpha[0] + beta[0]; gamma[1] = alpha[1] + beta[1]; gamma[2] = alpha[2] + beta[2]; gamma[3] = alpha[3] + beta[3];
			gamma[4] = alpha[4] + beta[4]; gamma[5] = alpha[5] + beta[5]; gamma[6] = alpha[6] + beta[6]; gamma[7] = alpha[7] + beta[7];
#else
			gamma[0] = alpha[0] + beta[0]; gamma[1] = alpha[1] + beta[1]; gamma[2] = alpha[2] + beta[2]; gamma[3] = alpha[3] + beta[3];
#endif
		}
		return;
	}
	/*below are the functions you don't need to use*/
	template <typename Data>
	static inline __attribute__((__always_inline__)) void tuple_add_s_(Data* const& alpha, Data const& beta, Data* const& gamma) {
		if constexpr ((std::is_same_v<Data, float>) && (SIMD_ON)) {
#if defined(_SIMD_01_)
			_mm_store_ps(gamma, _mm_add_ps(_mm_load_ps(alpha), _mm_set1_ps(beta)));
#elif defined(_SIMD_02_)
			_mm256_store_ps(gamma, _mm256_add_ps(_mm256_load_ps(alpha), _mm256_set1_ps(beta)));
#endif
		}
		else if constexpr (std::is_same_v<Data, bool>) {
#if defined(_SIMD_01_)
			gamma[0] = alpha[0] || beta; gamma[1] = alpha[1] || beta; gamma[2] = alpha[2] || beta; gamma[3] = alpha[3] || beta;
#elif defined(_SIMD_02_)
			gamma[0] = alpha[0] || beta; gamma[1] = alpha[1] || beta; gamma[2] = alpha[2] || beta; gamma[3] = alpha[3] || beta;
			gamma[4] = alpha[4] || beta; gamma[5] = alpha[5] || beta; gamma[6] = alpha[6] || beta; gamma[7] = alpha[7] || beta;
#else
			gamma[0] = alpha[0] || beta; gamma[1] = alpha[1] || beta; gamma[2] = alpha[2] || beta; gamma[3] = alpha[3] || beta;
#endif
		}
		else {
#if defined(_SIMD_01_)
			gamma[0] = alpha[0] + beta; gamma[1] = alpha[1] + beta; gamma[2] = alpha[2] + beta; gamma[3] = alpha[3] + beta;
#elif defined(_SIMD_02_)
			gamma[0] = alpha[0] + beta; gamma[1] = alpha[1] + beta; gamma[2] = alpha[2] + beta; gamma[3] = alpha[3] + beta;
			gamma[4] = alpha[4] + beta; gamma[5] = alpha[5] + beta; gamma[6] = alpha[6] + beta; gamma[7] = alpha[7] + beta;
#else
			gamma[0] = alpha[0] + beta; gamma[1] = alpha[1] + beta; gamma[2] = alpha[2] + beta; gamma[3] = alpha[3] + beta;
#endif
		}
		return;
	}
	/*below are the functions you don't need to use*/
	template <typename Data>
	static inline __attribute__((__always_inline__)) void tuple_sub(Data* const& alpha, Data* const& beta, Data* const& gamma) {
		if constexpr ((std::is_same_v<Data, float>) && (SIMD_ON)) {
#if defined(_SIMD_01_)
			_mm_store_ps(gamma, _mm_sub_ps(_mm_load_ps(alpha), _mm_load_ps(beta)));
#elif defined(_SIMD_02_)
			_mm256_store_ps(gamma, _mm256_sub_ps(_mm256_load_ps(alpha), _mm256_load_ps(beta)));
#endif
		}
		else if constexpr (std::is_same_v<Data, bool>) {
#if defined(_SIMD_01_)
			gamma[0] = alpha[0] || (!beta[0]); gamma[1] = alpha[1] || (!beta[1]); gamma[2] = alpha[2] || (!beta[2]); gamma[3] = alpha[3] || (!beta[3]);
#elif defined(_SIMD_02_)
			gamma[0] = alpha[0] || (!beta[0]); gamma[1] = alpha[1] || (!beta[1]); gamma[2] = alpha[2] || (!beta[2]); gamma[3] = alpha[3] || (!beta[3]);
			gamma[4] = alpha[4] || (!beta[4]); gamma[5] = alpha[5] || (!beta[5]); gamma[6] = alpha[6] || (!beta[6]); gamma[7] = alpha[7] || (!beta[7]);
#else
			gamma[0] = alpha[0] || (!beta[0]); gamma[1] = alpha[1] || (!beta[1]); gamma[2] = alpha[2] || (!beta[2]); gamma[3] = alpha[3] || (!beta[3]);
#endif
		}
		else {
#if defined(_SIMD_01_)
			gamma[0] = alpha[0] - beta[0]; gamma[1] = alpha[1] - beta[1]; gamma[2] = alpha[2] - beta[2]; gamma[3] = alpha[3] - beta[3];
#elif defined(_SIMD_02_)
			gamma[0] = alpha[0] - beta[0]; gamma[1] = alpha[1] - beta[1]; gamma[2] = alpha[2] - beta[2]; gamma[3] = alpha[3] - beta[3];
			gamma[4] = alpha[4] - beta[4]; gamma[5] = alpha[5] - beta[5]; gamma[6] = alpha[6] - beta[6]; gamma[7] = alpha[7] - beta[7];
#else
			gamma[0] = alpha[0] - beta[0]; gamma[1] = alpha[1] - beta[1]; gamma[2] = alpha[2] - beta[2]; gamma[3] = alpha[3] - beta[3];
#endif
		}
		return;
	}
	/*below are the functions you don't need to use*/
	template <typename Data>
	static inline __attribute__((__always_inline__)) void tuple_sub_sb_(Data* const& alpha, Data const& beta, Data* const& gamma) {
		if constexpr ((std::is_same_v<Data, float>) && (SIMD_ON)) {
#if defined(_SIMD_01_)
			_mm_store_ps(gamma, _mm_sub_ps(_mm_load_ps(alpha), _mm_set1_ps(beta)));
#elif defined(_SIMD_02_)
			_mm256_store_ps(gamma, _mm256_sub_ps(_mm256_load_ps(alpha), _mm256_set1_ps(beta)));
#endif
		}
		else if constexpr (std::is_same_v<Data, bool>) {
#if defined(_SIMD_01_)
			gamma[0] = alpha[0] || (!beta); gamma[1] = alpha[1] || (!beta); gamma[2] = alpha[2] || (!beta); gamma[3] = alpha[3] || (!beta);
#elif defined(_SIMD_02_)
			gamma[0] = alpha[0] || (!beta); gamma[1] = alpha[1] || (!beta); gamma[2] = alpha[2] || (!beta); gamma[3] = alpha[3] || (!beta);
			gamma[4] = alpha[4] || (!beta); gamma[5] = alpha[5] || (!beta); gamma[6] = alpha[6] || (!beta); gamma[7] = alpha[7] || (!beta);
#else
			gamma[0] = alpha[0] || (!beta); gamma[1] = alpha[1] || (!beta); gamma[2] = alpha[2] || (!beta); gamma[3] = alpha[3] || (!beta);
#endif
		}
		else {
#if defined(_SIMD_01_)
			gamma[0] = alpha[0] - beta; gamma[1] = alpha[1] - beta; gamma[2] = alpha[2] - beta; gamma[3] = alpha[3] - beta;
#elif defined(_SIMD_02_)
			gamma[0] = alpha[0] - beta; gamma[1] = alpha[1] - beta; gamma[2] = alpha[2] - beta; gamma[3] = alpha[3] - beta;
			gamma[4] = alpha[4] - beta; gamma[5] = alpha[5] - beta; gamma[6] = alpha[6] - beta; gamma[7] = alpha[7] - beta;
#else
			gamma[0] = alpha[0] - beta; gamma[1] = alpha[1] - beta; gamma[2] = alpha[2] - beta; gamma[3] = alpha[3] - beta;
#endif
		}
		return;
	}
	/*below are the functions you don't need to use*/
	template <typename Data>
	static inline __attribute__((__always_inline__)) void tuple_sub_sf_(Data const& alpha, Data* const& beta, Data* const& gamma) {
		if constexpr ((std::is_same_v<Data, float>) && (SIMD_ON)) {
#if defined(_SIMD_01_)
			_mm_store_ps(gamma, _mm_sub_ps(_mm_set1_ps(alpha), _mm_load_ps(beta)));
#elif defined(_SIMD_02_)
			_mm256_store_ps(gamma, _mm256_sub_ps(_mm256_set1_ps(alpha), _mm256_load_ps(beta)));
#endif
		}
		else if constexpr (std::is_same_v<Data, bool>) {
#if defined(_SIMD_01_)
			gamma[0] = alpha || (!beta[0]); gamma[1] = alpha || (!beta[1]); gamma[2] = alpha || (!beta[2]); gamma[3] = alpha || (!beta[3]);
#elif defined(_SIMD_02_)
			gamma[0] = alpha || (!beta[0]); gamma[1] = alpha || (!beta[1]); gamma[2] = alpha || (!beta[2]); gamma[3] = alpha || (!beta[3]);
			gamma[4] = alpha || (!beta[4]); gamma[5] = alpha || (!beta[5]); gamma[6] = alpha || (!beta[6]); gamma[7] = alpha || (!beta[7]);
#else
			gamma[0] = alpha || (!beta[0]); gamma[1] = alpha || (!beta[1]); gamma[2] = alpha || (!beta[2]); gamma[3] = alpha || (!beta[3]);
#endif
		}
		else {
#if defined(_SIMD_01_)
			gamma[0] = alpha - beta[0]; gamma[1] = alpha - beta[1]; gamma[2] = alpha - beta[2]; gamma[3] = alpha - beta[3];
#elif defined(_SIMD_02_)
			gamma[0] = alpha - beta[0]; gamma[1] = alpha - beta[1]; gamma[2] = alpha - beta[2]; gamma[3] = alpha - beta[3];
			gamma[4] = alpha - beta[4]; gamma[5] = alpha - beta[5]; gamma[6] = alpha - beta[6]; gamma[7] = alpha - beta[7];
#else
			gamma[0] = alpha - beta[0]; gamma[1] = alpha - beta[1]; gamma[2] = alpha - beta[2]; gamma[3] = alpha - beta[3];
#endif
		}
		return;
	}
	/*below are the functions you don't need to use*/
	template <typename Data>
	static inline __attribute__((__always_inline__)) void tuple_mul(Data* const& alpha, Data* const& beta, Data* const& gamma) {
		if constexpr ((std::is_same_v<Data, float>) && (SIMD_ON)) {
#if defined(_SIMD_01_)
			_mm_store_ps(gamma, _mm_mul_ps(_mm_load_ps(alpha), _mm_load_ps(beta)));
#elif defined(_SIMD_02_)
			_mm256_store_ps(gamma, _mm256_mul_ps(_mm256_load_ps(alpha), _mm256_load_ps(beta)));
#endif
		}
		else if constexpr (std::is_same_v<Data, bool>) {
#if defined(_SIMD_01_)
			gamma[0] = alpha[0] && beta[0]; gamma[1] = alpha[1] && beta[1]; gamma[2] = alpha[2] && beta[2]; gamma[3] = alpha[3] && beta[3];
#elif defined(_SIMD_02_)
			gamma[0] = alpha[0] && beta[0]; gamma[1] = alpha[1] && beta[1]; gamma[2] = alpha[2] && beta[2]; gamma[3] = alpha[3] && beta[3];
			gamma[4] = alpha[4] && beta[4]; gamma[5] = alpha[5] && beta[5]; gamma[6] = alpha[6] && beta[6]; gamma[7] = alpha[7] && beta[7];
#else
			gamma[0] = alpha[0] && beta[0]; gamma[1] = alpha[1] && beta[1]; gamma[2] = alpha[2] && beta[2]; gamma[3] = alpha[3] && beta[3];
#endif
		}
		else {
#if defined(_SIMD_01_)
			gamma[0] = alpha[0] * beta[0]; gamma[1] = alpha[1] * beta[1]; gamma[2] = alpha[2] * beta[2]; gamma[3] = alpha[3] * beta[3];
#elif defined(_SIMD_02_)
			gamma[0] = alpha[0] * beta[0]; gamma[1] = alpha[1] * beta[1]; gamma[2] = alpha[2] * beta[2]; gamma[3] = alpha[3] * beta[3];
			gamma[4] = alpha[4] * beta[4]; gamma[5] = alpha[5] * beta[5]; gamma[6] = alpha[6] * beta[6]; gamma[7] = alpha[7] * beta[7];
#else
			gamma[0] = alpha[0] * beta[0]; gamma[1] = alpha[1] * beta[1]; gamma[2] = alpha[2] * beta[2]; gamma[3] = alpha[3] * beta[3];
#endif
		}
		return;
	}
	/*below are the functions you don't need to use*/
	template <typename Data>
	static inline __attribute__((__always_inline__)) void tuple_mul_s_(Data* const& alpha, Data const& beta, Data* const& gamma) {
		if constexpr ((std::is_same_v<Data, float>) && (SIMD_ON)) {
#if defined(_SIMD_01_)
			_mm_store_ps(gamma, _mm_mul_ps(_mm_load_ps(alpha), _mm_set1_ps(beta)));
#elif defined(_SIMD_02_)
			_mm256_store_ps(gamma, _mm256_mul_ps(_mm256_load_ps(alpha), _mm256_set1_ps(beta)));
#endif
		}
		else if constexpr (std::is_same_v<Data, bool>) {
#if defined(_SIMD_01_)
			gamma[0] = alpha[0] && beta; gamma[1] = alpha[1] && beta; gamma[2] = alpha[2] && beta; gamma[3] = alpha[3] && beta;
#elif defined(_SIMD_02_)
			gamma[0] = alpha[0] && beta; gamma[1] = alpha[1] && beta; gamma[2] = alpha[2] && beta; gamma[3] = alpha[3] && beta;
			gamma[4] = alpha[4] && beta; gamma[5] = alpha[5] && beta; gamma[6] = alpha[6] && beta; gamma[7] = alpha[7] && beta;
#else
			gamma[0] = alpha[0] && beta; gamma[1] = alpha[1] && beta; gamma[2] = alpha[2] && beta; gamma[3] = alpha[3] && beta;
#endif
		}
		else {
#if defined(_SIMD_01_)
			gamma[0] = alpha[0] * beta; gamma[1] = alpha[1] * beta; gamma[2] = alpha[2] * beta; gamma[3] = alpha[3] * beta;
#elif defined(_SIMD_02_)
			gamma[0] = alpha[0] * beta; gamma[1] = alpha[1] * beta; gamma[2] = alpha[2] * beta; gamma[3] = alpha[3] * beta;
			gamma[4] = alpha[4] * beta; gamma[5] = alpha[5] * beta; gamma[6] = alpha[6] * beta; gamma[7] = alpha[7] * beta;
#else
			gamma[0] = alpha[0] * beta; gamma[1] = alpha[1] * beta; gamma[2] = alpha[2] * beta; gamma[3] = alpha[3] * beta;
#endif
		}
		return;
	}
	/*below are the functions you don't need to use*/
	template <typename Data>
	static inline __attribute__((__always_inline__)) void tuple_div(Data* const& alpha, Data* const& beta, Data* const& gamma) {
		if constexpr ((std::is_same_v<Data, float>) && (SIMD_ON)) {
#if defined(_SIMD_01_)
			_mm_store_ps(gamma, _mm_div_ps(_mm_load_ps(alpha), _mm_load_ps(beta)));
#elif defined(_SIMD_02_)
			_mm256_store_ps(gamma, _mm256_div_ps(_mm256_load_ps(alpha), _mm256_load_ps(beta)));
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
			gamma[2] = (alpha[2] || beta[2]) && (!(alpha[2] && beta[2])); gamma[3] = (alpha[3] || beta[3]) && (!(alpha[3] && beta[3]));
#endif
		}
		else {
#if defined(_SIMD_01_)
			gamma[0] = alpha[0] / beta[0]; gamma[1] = alpha[1] / beta[1]; gamma[2] = alpha[2] / beta[2]; gamma[3] = alpha[3] / beta[3];
#elif defined(_SIMD_02_)
			gamma[0] = alpha[0] / beta[0]; gamma[1] = alpha[1] / beta[1]; gamma[2] = alpha[2] / beta[2]; gamma[3] = alpha[3] / beta[3];
			gamma[4] = alpha[4] / beta[4]; gamma[5] = alpha[5] / beta[5]; gamma[6] = alpha[6] / beta[6]; gamma[7] = alpha[7] / beta[7];
#else
			gamma[0] = alpha[0] / beta[0]; gamma[1] = alpha[1] / beta[1]; gamma[2] = alpha[2] / beta[2]; gamma[3] = alpha[3] / beta[3];
#endif
		}
		return;
	}
	/*below are the functions you don't need to use*/
	template <typename Data>
	static inline __attribute__((__always_inline__)) void tuple_div_sb_(Data* const& alpha, Data const& beta, Data* const& gamma) {
		if constexpr ((std::is_same_v<Data, float>) && (SIMD_ON)) {
#if defined(_SIMD_01_)
			_mm_store_ps(gamma, _mm_div_ps(_mm_load_ps(alpha), _mm_set1_ps(beta)));
#elif defined(_SIMD_02_)
			_mm256_store_ps(gamma, _mm256_div_ps(_mm256_load_ps(alpha), _mm256_set1_ps(beta)));
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
			gamma[2] = (alpha[2] || beta) && (!(alpha[2] && beta)); gamma[3] = (alpha[3] || beta) && (!(alpha[3] && beta));
#endif
		}
		else {
#if defined(_SIMD_01_)
			gamma[0] = alpha[0] / beta; gamma[1] = alpha[1] / beta; gamma[2] = alpha[2] / beta; gamma[3] = alpha[3] / beta;
#elif defined(_SIMD_02_)
			gamma[0] = alpha[0] / beta; gamma[1] = alpha[1] / beta; gamma[2] = alpha[2] / beta; gamma[3] = alpha[3] / beta;
			gamma[4] = alpha[4] / beta; gamma[5] = alpha[5] / beta; gamma[6] = alpha[6] / beta; gamma[7] = alpha[7] / beta;
#else
			gamma[0] = alpha[0] / beta; gamma[1] = alpha[1] / beta; gamma[2] = alpha[2] / beta; gamma[3] = alpha[3] / beta;
#endif
		}
		return;
	}
	/*below are the functions you don't need to use*/
	template <typename Data>
	static inline __attribute__((__always_inline__)) void tuple_div_sf_(Data const& alpha, Data* const& beta, Data* const& gamma) {
		if constexpr ((std::is_same_v<Data, float>) && (SIMD_ON)) {
#if defined(_SIMD_01_)
			_mm_store_ps(gamma, _mm_div_ps(_mm_set1_ps(alpha), _mm_load_ps(beta)));
#elif defined(_SIMD_02_)
			_mm256_store_ps(gamma, _mm256_div_ps(_mm256_set1_ps(alpha), _mm256_load_ps(beta)));
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
			gamma[2] = (alpha || beta[2]) && (!(alpha && beta[2])); gamma[3] = (alpha || beta[3]) && (!(alpha && beta[3]));
#endif
		}
		else {
#if defined(_SIMD_01_)
			gamma[0] = alpha / beta[0]; gamma[1] = alpha / beta[1]; gamma[2] = alpha / beta[2]; gamma[3] = alpha / beta[3];
#elif defined(_SIMD_02_)
			gamma[0] = alpha / beta[0]; gamma[1] = alpha / beta[1]; gamma[2] = alpha / beta[2]; gamma[3] = alpha / beta[3];
			gamma[4] = alpha / beta[4]; gamma[5] = alpha / beta[5]; gamma[6] = alpha / beta[6]; gamma[7] = alpha / beta[7];
#else
			gamma[0] = alpha / beta[0]; gamma[1] = alpha / beta[1]; gamma[2] = alpha / beta[2]; gamma[3] = alpha / beta[3];
#endif
		}
		return;
	}
	/*below are the functions you don't need to use*/
	template <typename Data>
	static inline __attribute__((__always_inline__)) void tuple_eq_v(Data* const& alpha, Data* const& beta, bool* const& gamma) {
#if defined(_SIMD_01_)
		gamma[0] = alpha[0] == beta[0]; gamma[1] = alpha[1] == beta[1]; gamma[2] = alpha[2] == beta[2]; gamma[3] = alpha[3] == beta[3];
#elif defined(_SIMD_02_)
		gamma[0] = alpha[0] == beta[0]; gamma[1] = alpha[1] == beta[1]; gamma[2] = alpha[2] == beta[2]; gamma[3] = alpha[3] == beta[3];
		gamma[4] = alpha[4] == beta[4]; gamma[5] = alpha[5] == beta[5]; gamma[6] = alpha[6] == beta[6]; gamma[7] = alpha[7] == beta[7];
#else
		gamma[0] = alpha[0] == beta[0]; gamma[1] = alpha[1] == beta[1]; gamma[2] = alpha[2] == beta[2]; gamma[3] = alpha[3] == beta[3];
#endif
		return;
	}
	/*below are the functions you don't need to use*/
	template <typename Data>
	static inline __attribute__((__always_inline__)) void tuple_eq_s(Data* const& alpha, Data const& beta, bool* const& gamma) {
#if defined(_SIMD_01_)
		gamma[0] = alpha[0] == beta; gamma[1] = alpha[1] == beta; gamma[2] = alpha[2] == beta; gamma[3] = alpha[3] == beta;
#elif defined(_SIMD_02_)
		gamma[0] = alpha[0] == beta; gamma[1] = alpha[1] == beta; gamma[2] = alpha[2] == beta; gamma[3] = alpha[3] == beta;
		gamma[4] = alpha[4] == beta; gamma[5] = alpha[5] == beta; gamma[6] = alpha[6] == beta; gamma[7] = alpha[7] == beta;
#else
		gamma[0] = alpha[0] == beta; gamma[1] = alpha[1] == beta; gamma[2] = alpha[2] == beta; gamma[3] = alpha[3] == beta;
#endif
		return;
	}
	/*below are the functions you don't need to use*/
	template <typename Data>
	static inline __attribute__((__always_inline__)) void tuple_ne_v(Data* const& alpha, Data* const& beta, bool* const& gamma) {
#if defined(_SIMD_01_)
		gamma[0] = alpha[0] != beta[0]; gamma[1] = alpha[1] != beta[1]; gamma[2] = alpha[2] != beta[2]; gamma[3] = alpha[3] != beta[3];
#elif defined(_SIMD_02_)
		gamma[0] = alpha[0] != beta[0]; gamma[1] = alpha[1] != beta[1]; gamma[2] = alpha[2] != beta[2]; gamma[3] = alpha[3] != beta[3];
		gamma[4] = alpha[4] != beta[4]; gamma[5] = alpha[5] != beta[5]; gamma[6] = alpha[6] != beta[6]; gamma[7] = alpha[7] != beta[7];
#else
		gamma[0] = alpha[0] != beta[0]; gamma[1] = alpha[1] != beta[1]; gamma[2] = alpha[2] != beta[2]; gamma[3] = alpha[3] != beta[3];
#endif
		return;
	}
	/*below are the functions you don't need to use*/
	template <typename Data>
	static inline __attribute__((__always_inline__)) void tuple_ne_s(Data* const& alpha, Data const& beta, bool* const& gamma) {
#if defined(_SIMD_01_)
		gamma[0] = alpha[0] != beta; gamma[1] = alpha[1] != beta; gamma[2] = alpha[2] != beta; gamma[3] = alpha[3] != beta;
#elif defined(_SIMD_02_)
		gamma[0] = alpha[0] != beta; gamma[1] = alpha[1] != beta; gamma[2] = alpha[2] != beta; gamma[3] = alpha[3] != beta;
		gamma[4] = alpha[4] != beta; gamma[5] = alpha[5] != beta; gamma[6] = alpha[6] != beta; gamma[7] = alpha[7] != beta;
#else
		gamma[0] = alpha[0] != beta; gamma[1] = alpha[1] != beta; gamma[2] = alpha[2] != beta; gamma[3] = alpha[3] != beta;
#endif
		return;
	}
	/*below are the functions you don't need to use*/
	template <typename Data>
	static inline __attribute__((__always_inline__)) void tuple_bg_v(Data* const& alpha, Data* const& beta, bool* const& gamma) {
#if defined(_SIMD_01_)
		gamma[0] = alpha[0] > beta[0]; gamma[1] = alpha[1] > beta[1]; gamma[2] = alpha[2] > beta[2]; gamma[3] = alpha[3] > beta[3];
#elif defined(_SIMD_02_)
		gamma[0] = alpha[0] > beta[0]; gamma[1] = alpha[1] > beta[1]; gamma[2] = alpha[2] > beta[2]; gamma[3] = alpha[3] > beta[3];
		gamma[4] = alpha[4] > beta[4]; gamma[5] = alpha[5] > beta[5]; gamma[6] = alpha[6] > beta[6]; gamma[7] = alpha[7] > beta[7];
#else
		gamma[0] = alpha[0] > beta[0]; gamma[1] = alpha[1] > beta[1]; gamma[2] = alpha[2] > beta[2]; gamma[3] = alpha[3] > beta[3];
#endif
		return;
	}
	/*below are the functions you don't need to use*/
	template <typename Data>
	static inline __attribute__((__always_inline__)) void tuple_bg_sb(Data* const& alpha, Data const& beta, bool* const& gamma) {
#if defined(_SIMD_01_)
		gamma[0] = alpha[0] > beta; gamma[1] = alpha[1] > beta; gamma[2] = alpha[2] > beta; gamma[3] = alpha[3] > beta;
#elif defined(_SIMD_02_)
		gamma[0] = alpha[0] > beta; gamma[1] = alpha[1] > beta; gamma[2] = alpha[2] > beta; gamma[3] = alpha[3] > beta;
		gamma[4] = alpha[4] > beta; gamma[5] = alpha[5] > beta; gamma[6] = alpha[6] > beta; gamma[7] = alpha[7] > beta;
#else
		gamma[0] = alpha[0] > beta; gamma[1] = alpha[1] > beta; gamma[2] = alpha[2] > beta; gamma[3] = alpha[3] > beta;
#endif
		return;
	}
	/*below are the functions you don't need to use*/
	template <typename Data>
	static inline __attribute__((__always_inline__)) void tuple_bg_sf(Data const& alpha, Data* const& beta, bool* const& gamma) {
#if defined(_SIMD_01_)
		gamma[0] = alpha > beta[0]; gamma[1] = alpha > beta[1]; gamma[2] = alpha > beta[2]; gamma[3] = alpha > beta[3];
#elif defined(_SIMD_02_)
		gamma[0] = alpha > beta[0]; gamma[1] = alpha > beta[1]; gamma[2] = alpha > beta[2]; gamma[3] = alpha > beta[3];
		gamma[4] = alpha > beta[4]; gamma[5] = alpha > beta[5]; gamma[6] = alpha > beta[6]; gamma[7] = alpha > beta[7];
#else
		gamma[0] = alpha > beta[0]; gamma[1] = alpha > beta[1]; gamma[2] = alpha > beta[2]; gamma[3] = alpha > beta[3];
#endif
		return;
	}
	/*below are the functions you don't need to use*/
	template <typename Data>
	static inline __attribute__((__always_inline__)) void tuple_bq_v(Data* const& alpha, Data* const& beta, bool* const& gamma) {
#if defined(_SIMD_01_)
		gamma[0] = alpha[0] >= beta[0]; gamma[1] = alpha[1] >= beta[1]; gamma[2] = alpha[2] >= beta[2]; gamma[3] = alpha[3] >= beta[3];
#elif defined(_SIMD_02_)
		gamma[0] = alpha[0] >= beta[0]; gamma[1] = alpha[1] >= beta[1]; gamma[2] = alpha[2] >= beta[2]; gamma[3] = alpha[3] >= beta[3];
		gamma[4] = alpha[4] >= beta[4]; gamma[5] = alpha[5] >= beta[5]; gamma[6] = alpha[6] >= beta[6]; gamma[7] = alpha[7] >= beta[7];
#else
		gamma[0] = alpha[0] >= beta[0]; gamma[1] = alpha[1] >= beta[1]; gamma[2] = alpha[2] >= beta[2]; gamma[3] = alpha[3] >= beta[3];
#endif
		return;
	}
	/*below are the functions you don't need to use*/
	template <typename Data>
	static inline __attribute__((__always_inline__)) void tuple_bq_sb(Data* const& alpha, Data const& beta, bool* const& gamma) {
#if defined(_SIMD_01_)
		gamma[0] = alpha[0] >= beta; gamma[1] = alpha[1] >= beta; gamma[2] = alpha[2] >= beta; gamma[3] = alpha[3] >= beta;
#elif defined(_SIMD_02_)
		gamma[0] = alpha[0] >= beta; gamma[1] = alpha[1] >= beta; gamma[2] = alpha[2] >= beta; gamma[3] = alpha[3] >= beta;
		gamma[4] = alpha[4] >= beta; gamma[5] = alpha[5] >= beta; gamma[6] = alpha[6] >= beta; gamma[7] = alpha[7] >= beta;
#else
		gamma[0] = alpha[0] >= beta; gamma[1] = alpha[1] >= beta; gamma[2] = alpha[2] >= beta; gamma[3] = alpha[3] >= beta;
#endif
		return;
	}
	/*below are the functions you don't need to use*/
	template <typename Data>
	static inline __attribute__((__always_inline__)) void tuple_bq_sf(Data const& alpha, Data* const& beta, bool* const& gamma) {
#if defined(_SIMD_01_)
		gamma[0] = alpha >= beta[0]; gamma[1] = alpha >= beta[1]; gamma[2] = alpha >= beta[2]; gamma[3] = alpha >= beta[3];
#elif defined(_SIMD_02_)
		gamma[0] = alpha >= beta[0]; gamma[1] = alpha >= beta[1]; gamma[2] = alpha >= beta[2]; gamma[3] = alpha >= beta[3];
		gamma[4] = alpha >= beta[4]; gamma[5] = alpha >= beta[5]; gamma[6] = alpha >= beta[6]; gamma[7] = alpha >= beta[7];
#else
		gamma[0] = alpha >= beta[0]; gamma[1] = alpha >= beta[1]; gamma[2] = alpha >= beta[2]; gamma[3] = alpha >= beta[3];
#endif
		return;
	}
	/*below are the functions you don't need to use*/
	template <typename Data>
	static inline __attribute__((__always_inline__)) void tuple_sm_v(Data* const& alpha, Data* const& beta, bool* const& gamma) {
#if defined(_SIMD_01_)
		gamma[0] = alpha[0] < beta[0]; gamma[1] = alpha[1] < beta[1]; gamma[2] = alpha[2] < beta[2]; gamma[3] = alpha[3] < beta[3];
#elif defined(_SIMD_02_)
		gamma[0] = alpha[0] < beta[0]; gamma[1] = alpha[1] < beta[1]; gamma[2] = alpha[2] < beta[2]; gamma[3] = alpha[3] < beta[3];
		gamma[4] = alpha[4] < beta[4]; gamma[5] = alpha[5] < beta[5]; gamma[6] = alpha[6] < beta[6]; gamma[7] = alpha[7] < beta[7];
#else
		gamma[0] = alpha[0] < beta[0]; gamma[1] = alpha[1] < beta[1]; gamma[2] = alpha[2] < beta[2]; gamma[3] = alpha[3] < beta[3];
#endif
		return;
	}
	/*below are the functions you don't need to use*/
	template <typename Data>
	static inline __attribute__((__always_inline__)) void tuple_sm_sb(Data* const& alpha, Data const& beta, bool* const& gamma) {
#if defined(_SIMD_01_)
		gamma[0] = alpha[0] < beta; gamma[1] = alpha[1] < beta; gamma[2] = alpha[2] < beta; gamma[3] = alpha[3] < beta;
#elif defined(_SIMD_02_)
		gamma[0] = alpha[0] < beta; gamma[1] = alpha[1] < beta; gamma[2] = alpha[2] < beta; gamma[3] = alpha[3] < beta;
		gamma[4] = alpha[4] < beta; gamma[5] = alpha[5] < beta; gamma[6] = alpha[6] < beta; gamma[7] = alpha[7] < beta;
#else
		gamma[0] = alpha[0] < beta; gamma[1] = alpha[1] < beta; gamma[2] = alpha[2] < beta; gamma[3] = alpha[3] < beta;
#endif
		return;
	}
	/*below are the functions you don't need to use*/
	template <typename Data>
	static inline __attribute__((__always_inline__)) void tuple_sm_sf(Data const& alpha, Data* const& beta, bool* const& gamma) {
#if defined(_SIMD_01_)
		gamma[0] = alpha < beta[0]; gamma[1] = alpha < beta[1]; gamma[2] = alpha < beta[2]; gamma[3] = alpha < beta[3];
#elif defined(_SIMD_02_)
		gamma[0] = alpha < beta[0]; gamma[1] = alpha < beta[1]; gamma[2] = alpha < beta[2]; gamma[3] = alpha < beta[3];
		gamma[4] = alpha < beta[4]; gamma[5] = alpha < beta[5]; gamma[6] = alpha < beta[6]; gamma[7] = alpha < beta[7];
#else
		gamma[0] = alpha < beta[0]; gamma[1] = alpha < beta[1]; gamma[2] = alpha < beta[2]; gamma[3] = alpha < beta[3];
#endif
		return;
	}
	/*below are the functions you don't need to use*/
	template <typename Data>
	static inline __attribute__((__always_inline__)) void tuple_sq_v(Data* const& alpha, Data* const& beta, bool* const& gamma) {
#if defined(_SIMD_01_)
		gamma[0] = alpha[0] <= beta[0]; gamma[1] = alpha[1] <= beta[1]; gamma[2] = alpha[2] <= beta[2]; gamma[3] = alpha[3] <= beta[3];
#elif defined(_SIMD_02_)
		gamma[0] = alpha[0] <= beta[0]; gamma[1] = alpha[1] <= beta[1]; gamma[2] = alpha[2] <= beta[2]; gamma[3] = alpha[3] <= beta[3];
		gamma[4] = alpha[4] <= beta[4]; gamma[5] = alpha[5] <= beta[5]; gamma[6] = alpha[6] <= beta[6]; gamma[7] = alpha[7] <= beta[7];
#else
		gamma[0] = alpha[0] <= beta[0]; gamma[1] = alpha[1] <= beta[1]; gamma[2] = alpha[2] <= beta[2]; gamma[3] = alpha[3] <= beta[3];
#endif
		return;
	}
	/*below are the functions you don't need to use*/
	template <typename Data>
	static inline __attribute__((__always_inline__)) void tuple_sq_sb(Data* const& alpha, Data const& beta, bool* const& gamma) {
#if defined(_SIMD_01_)
		gamma[0] = alpha[0] <= beta; gamma[1] = alpha[1] <= beta; gamma[2] = alpha[2] <= beta; gamma[3] = alpha[3] <= beta;
#elif defined(_SIMD_02_)
		gamma[0] = alpha[0] <= beta; gamma[1] = alpha[1] <= beta; gamma[2] = alpha[2] <= beta; gamma[3] = alpha[3] <= beta;
		gamma[4] = alpha[4] <= beta; gamma[5] = alpha[5] <= beta; gamma[6] = alpha[6] <= beta; gamma[7] = alpha[7] <= beta;
#else
		gamma[0] = alpha[0] <= beta; gamma[1] = alpha[1] <= beta; gamma[2] = alpha[2] <= beta; gamma[3] = alpha[3] <= beta;
#endif
		return;
	}
	/*below are the functions you don't need to use*/
	template <typename Data>
	static inline __attribute__((__always_inline__)) void tuple_sq_sf(Data const& alpha, Data* const& beta, bool* const& gamma) {
#if defined(_SIMD_01_)
		gamma[0] = alpha <= beta[0]; gamma[1] = alpha <= beta[1]; gamma[2] = alpha <= beta[2]; gamma[3] = alpha <= beta[3];
#elif defined(_SIMD_02_)
		gamma[0] = alpha <= beta[0]; gamma[1] = alpha <= beta[1]; gamma[2] = alpha <= beta[2]; gamma[3] = alpha <= beta[3];
		gamma[4] = alpha <= beta[4]; gamma[5] = alpha <= beta[5]; gamma[6] = alpha <= beta[6]; gamma[7] = alpha <= beta[7];
#else
		gamma[0] = alpha <= beta[0]; gamma[1] = alpha <= beta[1]; gamma[2] = alpha <= beta[2]; gamma[3] = alpha <= beta[3];
#endif
		return;
	}
	/*below are the functions you don't need to use*/
	template <typename Data>
	static inline __attribute__((__always_inline__)) void tuple_abs(Data* const& alpha, Data* const& gamma) {
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
			gamma[0] = std::fabs(alpha[0]); gamma[1] = std::fabs(alpha[1]); gamma[2] = std::fabs(alpha[2]); gamma[3] = std::fabs(alpha[3]);
#endif
		}
		else if constexpr (std::is_same_v<Data, int>) {
#if defined(_SIMD_01_)
			gamma[0] = std::abs(alpha[0]); gamma[1] = std::abs(alpha[1]); gamma[2] = std::abs(alpha[2]); gamma[3] = std::abs(alpha[3]);
#elif defined(_SIMD_02_)
			gamma[0] = std::abs(alpha[0]); gamma[1] = std::abs(alpha[1]); gamma[2] = std::abs(alpha[2]); gamma[3] = std::abs(alpha[3]);
			gamma[4] = std::abs(alpha[4]); gamma[5] = std::abs(alpha[5]); gamma[6] = std::abs(alpha[6]); gamma[7] = std::abs(alpha[7]);
#else
			gamma[0] = std::abs(alpha[0]); gamma[1] = std::abs(alpha[1]); gamma[2] = std::abs(alpha[2]); gamma[3] = std::abs(alpha[3]);
#endif
		}
		else {
#if defined(_SIMD_01_)
			gamma[0] = alpha[0]; gamma[1] = alpha[1]; gamma[2] = alpha[2]; gamma[3] = alpha[3];
#elif defined(_SIMD_02_)
			gamma[0] = alpha[0]; gamma[1] = alpha[1]; gamma[2] = alpha[2]; gamma[3] = alpha[3];
			gamma[4] = alpha[4]; gamma[5] = alpha[5]; gamma[6] = alpha[6]; gamma[7] = alpha[7];
#else
			gamma[0] = alpha[0]; gamma[1] = alpha[1]; gamma[2] = alpha[2]; gamma[3] = alpha[3];
#endif
		}
#ifdef _DEBUG_MODE_
		printf("~tuple abs end~\n");
#endif
		return;
	}
	/*below are the functions you don't need to use*/
	template <typename Data>
	static inline __attribute__((__always_inline__)) void tuple_rand(Data* const& gamma, Data const& alpha, Data const& beta) {
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
		gamma[2] = Basic_Math::random(alpha, beta); gamma[3] = Basic_Math::random(alpha, beta);
#endif
		return;
	}
	/*below are the functions you don't need to use*/
	template <typename Data>
	static inline __attribute__((__always_inline__)) void tuple_set(Data* const& gamma, Data const& alpha) {
#ifdef _DEBUG_MODE_
		printf("~tuple set at %p~\n", gamma);
#endif
#if defined(_SIMD_01_)
		if constexpr (std::is_same_v<Data, float>) {
			_mm_store_ps(gamma, _mm_set1_ps(alpha));
		}
		else {
			gamma[0] = alpha; gamma[1] = alpha; gamma[2] = alpha; gamma[3] = alpha;
		}
#elif defined(_SIMD_02_)
		if constexpr (std::is_same_v<Data, float>) {
			_mm256_store_ps(gamma, _mm256_set1_ps(alpha));
		}
		else {
			gamma[0] = alpha; gamma[1] = alpha; gamma[2] = alpha; gamma[3] = alpha;
			gamma[4] = alpha; gamma[5] = alpha; gamma[6] = alpha; gamma[7] = alpha;
		}
#else
		gamma[0] = alpha; gamma[1] = alpha; gamma[2] = alpha; gamma[3] = alpha;
#endif
#ifdef _DEBUG_MODE_
		printf("~tuple set finish~\n");
#endif
		return;
	}
	/*below are the functions you don't need to use*/
	template <typename Data>
	static inline __attribute__((__always_inline__)) void tuple_load(Data* const& alpha, Data* const& gamma) {
#ifdef _DEBUG_MODE_
		printf("~tuple load from %p to %p~\n", alpha, gamma);
#endif
#if defined(_SIMD_01_)
		if constexpr (std::is_same_v<Data, float>) {
			_mm_store_ps(gamma, _mm_loadu_ps(alpha));
		}
		else {
			gamma[0] = alpha[0]; gamma[1] = alpha[1]; gamma[2] = alpha[2]; gamma[3] = alpha[3];
		}
#elif defined(_SIMD_02_)
		if constexpr (std::is_same_v<Data, float>) {
			_mm256_store_ps(gamma, _mm256_loadu_ps(alpha));
		}
		else {
			gamma[0] = alpha[0]; gamma[1] = alpha[1]; gamma[2] = alpha[2]; gamma[3] = alpha[3];
			gamma[4] = alpha[4]; gamma[5] = alpha[5]; gamma[6] = alpha[6]; gamma[7] = alpha[7];
		}
#else
		gamma[0] = alpha[0]; gamma[1] = alpha[1]; gamma[2] = alpha[2]; gamma[3] = alpha[3];
#endif
		return;
		}
#endif //THREAD MODE
	}
namespace Linalg {
	//the shape of Matrix
	typedef struct
	{
		int rows = 1;
		int lines = 1;
	} MaShape;
	bool operator==(MaShape const&, MaShape const&);
	bool operator<(MaShape const&, MaShape const&);
	bool operator<=(MaShape const&, MaShape const&);
	std::ostream& operator<<(std::ostream&, MaShape const&);
	inline __attribute__((__always_inline__)) bool check_legal(MaShape const& alpha) { return alpha.rows > 0 && alpha.lines > 0; }
	//Datas with 1 Dimantion
	template <typename Data>
	class Vector;
	//Datas with 2 Dimantion
	template <typename Data>
	class Matrix;
	//Datas with 3 Dimantion but is not supportable for operate
	template <typename Data>
	class Tensor;
	//Shape of Tensor
	class Teshape;
	//a function which can and a Vector into a Matrix
	template <typename Data>
	void AddLine_(Matrix<Data>&, Vector<Data> const&);
	//a function which can and a Vector into a Matrix
	template <typename Data>
	void AddRow_(Matrix<Data>&, Vector<Data> const&);
}
#define Ln Linalg
namespace Memory_Maintain {
	/*you don't need to know what this mean*/
	typedef enum { Vi, Vb, Vf, Mi, Mb, Mf, Ti, Tb, Tf, S }_mmy_type;
	/*you don't need to know what this mean*/
	typedef union {
		Ln::Vector<int>* vi; Ln::Vector<bool>* vb; Ln::Vector<float>* vf;
		Ln::Matrix<int>* mi; Ln::Matrix<bool>* mb; Ln::Matrix<float>* mf;
		Ln::Tensor<int>* ti; Ln::Tensor<bool>* tb; Ln::Tensor<float>* tf;
		Ln::Teshape* s;
	}_mmy_pointer;
	/*you don't need to know what this mean*/
	typedef struct {
		_mmy_type type;
		_mmy_pointer ptr;
	}_mmy_data;
	/*you don't need to know what this mean*/
	typedef struct _mmy_node {
		struct _mmy_node* front = nullptr;
		struct _mmy_node* back = nullptr;
		int size = 0;
		_mmy_data data;
	}_mmy_node;
	/*don't touch it*/
	extern unsigned long long _mmy_heap;
	/*don't touch it*/
	extern int _mmy_block;
	/*don't touch it*/
	extern _mmy_node* _mmy_top;
	/*don't touch it*/
	extern _mmy_node* _mmy_buttom;
	/*below is the function you don't need to use*/
	template <typename Data>
	static inline __attribute__((__always_inline__)) bool _mmy_order(_mmy_data& alpha, Data const& beta) {
		if constexpr (std::is_same_v<Data, Ln::Vector<int>*>) { alpha.type = Vi; alpha.ptr.vi = beta; return true; }
		else if constexpr (std::is_same_v<Data, Ln::Vector<bool>*>) { alpha.type = Vb; alpha.ptr.vb = beta; return true; }
		else if constexpr (std::is_same_v<Data, Ln::Vector<float>*>) { alpha.type = Vf; alpha.ptr.vf = beta; return true; }
		else if constexpr (std::is_same_v<Data, Ln::Matrix<int>*>) { alpha.type = Mi; alpha.ptr.mi = beta; return true; }
		else if constexpr (std::is_same_v<Data, Ln::Matrix<bool>*>) { alpha.type = Mb; alpha.ptr.mb = beta; return true; }
		else if constexpr (std::is_same_v<Data, Ln::Matrix<float>*>) { alpha.type = Mf; alpha.ptr.mf = beta; return true; }
		else if constexpr (std::is_same_v<Data, Ln::Tensor<int>*>) { alpha.type = Ti; alpha.ptr.ti = beta; return true; }
		else if constexpr (std::is_same_v<Data, Ln::Tensor<bool>*>) { alpha.type = Tb; alpha.ptr.tb = beta; return true; }
		else if constexpr (std::is_same_v<Data, Ln::Tensor<float>*>) { alpha.type = Tf; alpha.ptr.tf = beta; return true; }
		else if constexpr (std::is_same_v<Data, Ln::Teshape*>) { alpha.type = S; alpha.ptr.s = beta; return true; }
		else { return false; }
	}
	/*below is the function you don't need to use*/
	template <typename Data>
	static inline __attribute__((__unused__)) bool _mmy_catch(_mmy_data const& alpha, Data& beta) {
		if (alpha.type == Vi) { beta = alpha.ptr.vi; return true; }
		else if (alpha.type == Vb) { beta = alpha.ptr.vb; return true; }
		else if (alpha.type == Vf) { beta = alpha.ptr.vb; return true; }
		else if (alpha.type == Mi) { beta = alpha.ptr.mi; return true; }
		else if (alpha.type == Mb) { beta = alpha.ptr.mb; return true; }
		else if (alpha.type == Mf) { beta = alpha.ptr.mf; return true; }
		else if (alpha.type == Ti) { beta = alpha.ptr.ti; return true; }
		else if (alpha.type == Tb) { beta = alpha.ptr.tb; return true; }
		else if (alpha.type == Tf) { beta = alpha.ptr.tf; return true; }
		else if (alpha.type == S) { beta = alpha.ptr.s; return true; }
		else { return false; }
	}
	/*below is the function you don't need to use*/
	template <typename Data>
	static inline __attribute__((__always_inline__)) bool _mmy_cmp(_mmy_data const& alpha, Data const& beta) {
		if constexpr (std::is_same_v<Data, Ln::Vector<int>*>) { return (alpha.ptr.vi == beta); }
		else if constexpr (std::is_same_v<Data, Ln::Vector<bool>*>) { return (alpha.ptr.vb == beta); }
		else if constexpr (std::is_same_v<Data, Ln::Vector<float>*>) { return (alpha.ptr.vf == beta); }
		else if constexpr (std::is_same_v<Data, Ln::Matrix<int>*>) { return (alpha.ptr.mi == beta); }
		else if constexpr (std::is_same_v<Data, Ln::Matrix<bool>*>) { return (alpha.ptr.mb == beta); }
		else if constexpr (std::is_same_v<Data, Ln::Matrix<float>*>) { return (alpha.ptr.mf == beta); }
		else if constexpr (std::is_same_v<Data, Ln::Tensor<int>*>) { return (alpha.ptr.ti == beta); }
		else if constexpr (std::is_same_v<Data, Ln::Tensor<bool>*>) { return (alpha.ptr.tb == beta); }
		else if constexpr (std::is_same_v<Data, Ln::Tensor<float>*>) { return (alpha.ptr.tf == beta); }
		else if constexpr (std::is_same_v<Data, Ln::Teshape*>) { return (alpha.ptr.s == beta); }
		else { return false; }
	}
	/*to sign up for memory manage*/
	template <typename Data>
	inline bool _mmy_sign(int const& alpha, Data const& beta) {
		if ((alpha <= 0) || (beta == nullptr))return false;
		_mmy_node* object = new _mmy_node;
		object->size = alpha;
		if (!_mmy_order(object->data, beta)) {
			delete object;
			return false;
		}
		if (_mmy_block == 0) {
			_mmy_top = object;
			_mmy_buttom = object;
			object->back = nullptr;
			object->front = nullptr;
			_mmy_block += 1;
			_mmy_heap += alpha;
			return true;
		}
		_mmy_node* temp = _mmy_top;
		object->front = nullptr;
		object->back = temp;
		temp->front = object;
		_mmy_top = object;
		_mmy_block += 1;
		_mmy_heap += alpha;
		return true;
	}
	/*to modify the memory usage*/
	template <typename Data>
	inline bool _mmy_modify(int const& alpha, Data const& beta) {
		_mmy_node* omega = _mmy_top;
		while (omega != nullptr) {
			if (_mmy_cmp(omega->data, beta)) {
				_mmy_heap += alpha - (omega->size);
				omega->size = alpha;
				return true;
			}
			omega = omega->back;
		}
		return false;
	}
	/*to delete the memory usage*/
	template <typename Data>
	inline bool _mmy_delete(Data const& alpha) {
		_mmy_node* omega = _mmy_top;
		_mmy_node* gamma;
		while (omega != nullptr) {
			if (_mmy_cmp(omega->data, alpha)) {
				if ((omega->front == nullptr) && (omega->back == nullptr)) {
					_mmy_block = _mmy_heap = 0;
					_mmy_top = _mmy_buttom = nullptr;
					delete omega;
					return true;
				}
				else if (omega->front == nullptr) {
					gamma = omega->back;
					_mmy_block -= 1;
					_mmy_heap -= omega->size;
					_mmy_top = gamma;
					gamma->front = nullptr;
					delete omega;
					return true;
				}
				else if (omega->back == nullptr) {
					gamma = omega->front;
					_mmy_block -= 1;
					_mmy_heap -= omega->size;
					_mmy_buttom = gamma;
					gamma->back = nullptr;
					delete omega;
					return true;
				}
				else {
					gamma = omega->front;
					gamma->back = omega->back;
					gamma = omega->back;
					gamma->front = omega->front;
					_mmy_block -= 1;
					_mmy_heap -= omega->size;
					delete omega;
					return true;
				}
			}
			omega = omega->back;
		}
		return false;
	}
	/*check how much block in usage*/
	inline unsigned long long _mmy_usage() { return _mmy_heap; }
	/*check how much block in usage*/
	inline int _mmy_zone() { return _mmy_block; }
	/*show all the usage*/
	inline void _mmy_all() {
		_mmy_node* alpha = _mmy_top;
		for (int i = 0; i < Basic_Math::terminal_width; i++) { printf("-"); }
		printf("\n%d blocks and %lld bytes were alloced in total\n", _mmy_block, _mmy_heap);
		while (alpha != nullptr) {
			printf("ID: %p uses %d bytes ", alpha, alpha->size);
			if (alpha->data.type == Vi) { printf("type: Vector<int>\n"); }
			else if (alpha->data.type == Vf) { printf("type: Vector<float>\n"); }
			else if (alpha->data.type == Vb) { printf("type: Vector<bool>\n"); }
			else if (alpha->data.type == Mi) { printf("type: Matrix<int>\n"); }
			else if (alpha->data.type == Mf) { printf("type: Matrix<float>\n"); }
			else if (alpha->data.type == Mb) { printf("type: Matrix<bool>\n"); }
			else if (alpha->data.type == Ti) { printf("type: Tensor<int>\n"); }
			else if (alpha->data.type == Tf) { printf("type: Tensor<float>\n"); }
			else if (alpha->data.type == Tb) { printf("type: Tensor<bool>\n"); }
			else if (alpha->data.type == S) { printf("type: Teshape\n"); }
			else { printf("type: unknown\n"); }
			alpha = alpha->back;
		}
		for (int i = 0; i < Basic_Math::terminal_width; i++) { printf("-"); }
		printf("\n");
		return;
	}
}
#undef Ln
namespace Basic_Math {
	/*status
	Enter: 1.flag
	show the status of mode and memory, if the flag is true, then show the memory detail
	no return*/
	static inline __attribute__((__always_inline__, __used__)) void status(bool const& alpha) {
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
		if (alpha) {
			Memory_Maintain::_mmy_all();
		}
		else {
			printf("memory block: %d memory usage: %lld bytes\n", Memory_Maintain::_mmy_block, Memory_Maintain::_mmy_heap);
		}
		for (int i = 0; i < terminal_width; i++) printf("-");
		printf("\n\n");
		return;
	}
}
#endif //BASIC_H