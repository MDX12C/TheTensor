#include <stdio.h>
#include <x86intrin.h>
using namespace std;
signed main() {
  const int size = 40;
  float *alpha = (float *)_mm_malloc(size * sizeof(float), 16);
  __m128 temp = _mm_set_ps(1, 2, 3, 4);
  for (int i = 0; i < size; i += 4) {
    _mm_store_ps(alpha + i, temp);
  }
  for (auto i = 0; i < size; i++) {
    printf("%d : %.3f ", i + 1, alpha[i]);
  }
  _mm_free(alpha);
}
