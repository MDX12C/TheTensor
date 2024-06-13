#include <cmath>
#include <iostream>
#include <ostream>
#include <x86intrin.h>
using namespace std;
constexpr unsigned int VEC_SIZE = 40;
signed main() {
  float *alpha;
  alpha = (float *)_mm_malloc(VEC_SIZE * sizeof(float), 16);
  cerr << "finish alloc\n";
  for (auto i = 0; i < VEC_SIZE; i++) {
    alpha[i] = log(i + 1) / static_cast<float>(i + 1);
  }
  cerr << "finish init\n";
  for (auto i = 0; i < VEC_SIZE; i++)
    cout << "alpha " << i + 1 << '=' << alpha[i] << endl;
  for (int i = 0; i < 20; i += 4) {
    cerr << "loop in " << i + 1 << " load from " << &alpha[i] << " to  "
         << &alpha[i + 1] << endl;
    _mm_storeu_ps(&alpha[i + 1], _mm_load_ps(&alpha[i]));
  }
  for (auto i = 0; i < VEC_SIZE; i++)
    cout << "alpha " << i + 1 << '=' << alpha[i] << endl;
  _mm_free(alpha);
  return 0;
}
