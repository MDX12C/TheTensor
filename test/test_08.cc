#include<iostream>
#include<type_traits>
#include<cstdlib>
#define SIMD_ON 1
using namespace std;
template <class T>
struct is_simd_on {
#if SIMD_ON
    constexpr static bool value = is_same_v<T, float>;
#else 
    constexpr static bool value = false;
#endif
};
template <class T>
constexpr bool check_simd = is_simd_on<T>::value;

signed main() {
    printf("int: %d\nfloat: %d\n", check_simd<int>, check_simd<float>);
    return 0;
}