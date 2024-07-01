#include "simd_add.hpp"

#include <immintrin.h>

void simd_add(float *a, float *b, float *result, int size) {
  int simd_width = 8;  // AVX can handle 8 floats at a time
  int i;
  for (i = 0; i <= size - simd_width; i += simd_width) {
    __m256 vec_a = _mm256_loadu_ps(&a[i]);
    __m256 vec_b = _mm256_loadu_ps(&b[i]);
    __m256 vec_result = _mm256_add_ps(vec_a, vec_b);
    _mm256_storeu_ps(&result[i], vec_result);
  }
  // Handle remaining elements
  for (; i < size; ++i) {
    result[i] = a[i] + b[i];
  }
}