#include "thetensor/define.h"

#ifdef __cplusplus
extern "C"{
#endif

__global__ void __vv_add_i32(int32_t* __a, int32_t* __b, int32_t* __c, size_t __size, size_t __tuple = 1) {
  size_t position = threadIdx.x + blockDim.x * blockIdx.x;
  position *= __tuple;
  if (__tuple == 1)
    for(size_t i = position; i < __size; i++)
      __c[i] = __a[i] + __b[i];
  else
    for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
      __c[i] = __a[i] + __b[i];
  return;
}
inline void vv_add_i32(int32_t* __a, int32_t* __b, int32_t* __c, size_t __size) {
  if (__size > GROUP) {
    size_t tuple = __size % GROUP ? __size / GROUP + 1 : __size / GROUP;
    size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
    size_t blocks = tuples % THREADS ? tuples / THREADS + 1 : tuples / THREADS;
    __vv_add_i32<<<blocks, THREADS>>>(__a, __b, __c, __size, tuple);
  } else if (__size > THREADS) {
    size_t blocks = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
    __vv_add_i32<<<blocks, THREADS>>>(__a, __b, __c, __size);
  } else {
    __vv_add_i32<<<1, __size>>>(__a, __b, __c, __size);
  }
  return;
}

#ifdef __cplusplus
}
#endif