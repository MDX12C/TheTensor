#include "thetensor/define.h"
#include "thetensor/parallel.cuh"

#ifdef __cplusplus
extern "C"{
#endif
//#####################################################################################################################
__global__ void __vv_add_b(bool* __a, bool* __b, bool* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] | __b[i];
  return;
}
/*the add of bool in vector to vector*/
void vv_add_b(bool* __a, bool* __b, bool* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vv_add_b<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vv_add_i8(int8_t* __a, int8_t* __b, int8_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] + __b[i];
  return;
}
/*the add of int8_t in vector to vector*/
void vv_add_i8(int8_t* __a, int8_t* __b, int8_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vv_add_i8<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vv_add_i16(int16_t* __a, int16_t* __b, int16_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] + __b[i];
  return;
}
/*the add of int16_t in vector to vector*/
void vv_add_i16(int16_t* __a, int16_t* __b, int16_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vv_add_i16<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vv_add_i32(int32_t* __a, int32_t* __b, int32_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] + __b[i];
  return;
}
/*the add of int32_t in vector to vector*/
void vv_add_i32(int32_t* __a, int32_t* __b, int32_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vv_add_i32<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vv_add_i64(int64_t* __a, int64_t* __b, int64_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] + __b[i];
  return;
}
/*the add of int64_t in vector to vector*/
void vv_add_i64(int64_t* __a, int64_t* __b, int64_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vv_add_i64<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vv_add_u8(uint8_t* __a, uint8_t* __b, uint8_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] + __b[i];
  return;
}
/*the add of uint8_t in vector to vector*/
void vv_add_u8(uint8_t* __a, uint8_t* __b, uint8_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vv_add_u8<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vv_add_u16(uint16_t* __a, uint16_t* __b, uint16_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] + __b[i];
  return;
}
/*the add of uint16_t in vector to vector*/
void vv_add_u16(uint16_t* __a, uint16_t* __b, uint16_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vv_add_u16<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vv_add_u32(uint32_t* __a, uint32_t* __b, uint32_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] + __b[i];
  return;
}
/*the add of uint32_t in vector to vector*/
void vv_add_u32(uint32_t* __a, uint32_t* __b, uint32_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vv_add_u32<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vv_add_u64(uint64_t* __a, uint64_t* __b, uint64_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] + __b[i];
  return;
}
/*the add of uint64_t in vector to vector*/
void vv_add_u64(uint64_t* __a, uint64_t* __b, uint64_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vv_add_u64<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vv_add_f(float_t* __a, float_t* __b, float_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] + __b[i];
  return;
}
/*the add of float_t in vector to vector*/
void vv_add_f(float_t* __a, float_t* __b, float_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vv_add_f<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vv_add_d(double_t* __a, double_t* __b, double_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] + __b[i];
  return;
}
/*the add of double_t in vector to vector*/
void vv_add_d(double_t* __a, double_t* __b, double_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vv_add_d<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}
//#####################################################################################################################
__global__ void __vs_add_b(bool* __a, bool __b, bool* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] | __b;
  return;
}
/*the add of bool in vector to scalar*/
void vs_add_b(bool* __a, bool __b, bool* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vs_add_b<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vs_add_i8(int8_t* __a, int8_t __b, int8_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] + __b;
  return;
}
/*the add of int8_t in vector to scalar*/
void vs_add_i8(int8_t* __a, int8_t __b, int8_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vs_add_i8<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vs_add_i16(int16_t* __a, int16_t __b, int16_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] + __b;
  return;
}
/*the add of int16_t in vector to scalar*/
void vs_add_i16(int16_t* __a, int16_t __b, int16_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vs_add_i16<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vs_add_i32(int32_t* __a, int32_t __b, int32_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] + __b;
  return;
}
/*the add of int32_t in vector to scalar*/
void vs_add_i32(int32_t* __a, int32_t __b, int32_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vs_add_i32<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vs_add_i64(int64_t* __a, int64_t __b, int64_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] + __b;
  return;
}
/*the add of int64_t in vector to scalar*/
void vs_add_i64(int64_t* __a, int64_t __b, int64_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vs_add_i64<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vs_add_u8(uint8_t* __a, uint8_t __b, uint8_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] + __b;
  return;
}
/*the add of uint8_t in vector to scalar*/
void vs_add_u8(uint8_t* __a, uint8_t __b, uint8_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vs_add_u8<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vs_add_u16(uint16_t* __a, uint16_t __b, uint16_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] + __b;
  return;
}
/*the add of uint16_t in vector to scalar*/
void vs_add_u16(uint16_t* __a, uint16_t __b, uint16_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vs_add_u16<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vs_add_u32(uint32_t* __a, uint32_t __b, uint32_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] + __b;
  return;
}
/*the add of uint32_t in vector to scalar*/
void vs_add_u32(uint32_t* __a, uint32_t __b, uint32_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vs_add_u32<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vs_add_u64(uint64_t* __a, uint64_t __b, uint64_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] + __b;
  return;
}
/*the add of uint64_t in vector to scalar*/
void vs_add_u64(uint64_t* __a, uint64_t __b, uint64_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vs_add_u64<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vs_add_f(float_t* __a, float_t __b, float_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] + __b;
  return;
}
/*the add of float_t in vector to scalar*/
void vs_add_f(float_t* __a, float_t __b, float_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vs_add_f<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vs_add_d(double_t* __a, double_t __b, double_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] + __b;
  return;
}
/*the add of double_t in vector to scalar*/
void vs_add_d(double_t* __a, double_t __b, double_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vs_add_d<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}
//#####################################################################################################################
__global__ void __vv_mns_b(bool* __a, bool* __b, bool* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] & (~__b[i]);
  return;
}
/*the minus of bool in vector to vector*/
void vv_mns_b(bool* __a, bool* __b, bool* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vv_mns_b<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vv_mns_i8(int8_t* __a, int8_t* __b, int8_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] - __b[i];
  return;
}
/*the minus of int8_t in vector to vector*/
void vv_mns_i8(int8_t* __a, int8_t* __b, int8_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vv_mns_i8<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vv_mns_i16(int16_t* __a, int16_t* __b, int16_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] - __b[i];
  return;
}
/*the minus of int16_t in vector to vector*/
void vv_mns_i16(int16_t* __a, int16_t* __b, int16_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vv_mns_i16<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vv_mns_i32(int32_t* __a, int32_t* __b, int32_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] - __b[i];
  return;
}
/*the minus of int32_t in vector to vector*/
void vv_mns_i32(int32_t* __a, int32_t* __b, int32_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vv_mns_i32<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vv_mns_i64(int64_t* __a, int64_t* __b, int64_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] - __b[i];
  return;
}
/*the minus of int64_t in vector to vector*/
void vv_mns_i64(int64_t* __a, int64_t* __b, int64_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vv_mns_i64<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vv_mns_u8(uint8_t* __a, uint8_t* __b, uint8_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] - __b[i];
  return;
}
/*the minus of uint8_t in vector to vector*/
void vv_mns_u8(uint8_t* __a, uint8_t* __b, uint8_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vv_mns_u8<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vv_mns_u16(uint16_t* __a, uint16_t* __b, uint16_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] - __b[i];
  return;
}
/*the minus of uint16_t in vector to vector*/
void vv_mns_u16(uint16_t* __a, uint16_t* __b, uint16_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vv_mns_u16<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vv_mns_u32(uint32_t* __a, uint32_t* __b, uint32_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] - __b[i];
  return;
}
/*the minus of uint32_t in vector to vector*/
void vv_mns_u32(uint32_t* __a, uint32_t* __b, uint32_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vv_mns_u32<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vv_mns_u64(uint64_t* __a, uint64_t* __b, uint64_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] - __b[i];
  return;
}
/*the minus of uint64_t in vector to vector*/
void vv_mns_u64(uint64_t* __a, uint64_t* __b, uint64_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vv_mns_u64<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vv_mns_f(float_t* __a, float_t* __b, float_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] - __b[i];
  return;
}
/*the minus of float_t in vector to vector*/
void vv_mns_f(float_t* __a, float_t* __b, float_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vv_mns_f<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vv_mns_d(double_t* __a, double_t* __b, double_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] - __b[i];
  return;
}
/*the minus of double_t in vector to vector*/
void vv_mns_d(double_t* __a, double_t* __b, double_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vv_mns_d<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}
//#####################################################################################################################
__global__ void __vs_mns_b(bool* __a, bool __b, bool* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] & (~__b);
  return;
}
/*the minus of bool in vector to scalar*/
void vs_mns_b(bool* __a, bool __b, bool* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vs_mns_b<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vs_mns_i8(int8_t* __a, int8_t __b, int8_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] - __b;
  return;
}
/*the minus of int8_t in vector to scalar*/
void vs_mns_i8(int8_t* __a, int8_t __b, int8_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vs_mns_i8<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vs_mns_i16(int16_t* __a, int16_t __b, int16_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] - __b;
  return;
}
/*the minus of int16_t in vector to scalar*/
void vs_mns_i16(int16_t* __a, int16_t __b, int16_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vs_mns_i16<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vs_mns_i32(int32_t* __a, int32_t __b, int32_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] - __b;
  return;
}
/*the minus of int32_t in vector to scalar*/
void vs_mns_i32(int32_t* __a, int32_t __b, int32_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vs_mns_i32<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vs_mns_i64(int64_t* __a, int64_t __b, int64_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] - __b;
  return;
}
/*the minus of int64_t in vector to scalar*/
void vs_mns_i64(int64_t* __a, int64_t __b, int64_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vs_mns_i64<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vs_mns_u8(uint8_t* __a, uint8_t __b, uint8_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] - __b;
  return;
}
/*the minus of uint8_t in vector to scalar*/
void vs_mns_u8(uint8_t* __a, uint8_t __b, uint8_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vs_mns_u8<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vs_mns_u16(uint16_t* __a, uint16_t __b, uint16_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] - __b;
  return;
}
/*the minus of uint16_t in vector to scalar*/
void vs_mns_u16(uint16_t* __a, uint16_t __b, uint16_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vs_mns_u16<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vs_mns_u32(uint32_t* __a, uint32_t __b, uint32_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] - __b;
  return;
}
/*the minus of uint32_t in vector to scalar*/
void vs_mns_u32(uint32_t* __a, uint32_t __b, uint32_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vs_mns_u32<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vs_mns_u64(uint64_t* __a, uint64_t __b, uint64_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] - __b;
  return;
}
/*the minus of uint64_t in vector to scalar*/
void vs_mns_u64(uint64_t* __a, uint64_t __b, uint64_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vs_mns_u64<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vs_mns_f(float_t* __a, float_t __b, float_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] - __b;
  return;
}
/*the minus of float_t in vector to scalar*/
void vs_mns_f(float_t* __a, float_t __b, float_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vs_mns_f<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vs_mns_d(double_t* __a, double_t __b, double_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] - __b;
  return;
}
/*the minus of double_t in vector to scalar*/
void vs_mns_d(double_t* __a, double_t __b, double_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vs_mns_d<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}
//#####################################################################################################################
__global__ void __sv_mns_b(bool __a, bool* __b, bool* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a & (~__b[i]);
  return;
}
/*the minus of bool in scalar to vector*/
void sv_mns_b(bool __a, bool* __b, bool* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __sv_mns_b<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __sv_mns_i8(int8_t __a, int8_t* __b, int8_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a - __b[i];
  return;
}
/*the minus of int8_t in scalar to vector*/
void sv_mns_i8(int8_t __a, int8_t* __b, int8_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __sv_mns_i8<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __sv_mns_i16(int16_t __a, int16_t* __b, int16_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a - __b[i];
  return;
}
/*the minus of int16_t in scalar to vector*/
void sv_mns_i16(int16_t __a, int16_t* __b, int16_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __sv_mns_i16<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __sv_mns_i32(int32_t __a, int32_t* __b, int32_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a - __b[i];
  return;
}
/*the minus of int32_t in scalar to vector*/
void sv_mns_i32(int32_t __a, int32_t* __b, int32_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __sv_mns_i32<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __sv_mns_i64(int64_t __a, int64_t* __b, int64_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a - __b[i];
  return;
}
/*the minus of int64_t in scalar to vector*/
void sv_mns_i64(int64_t __a, int64_t* __b, int64_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __sv_mns_i64<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __sv_mns_u8(uint8_t __a, uint8_t* __b, uint8_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a - __b[i];
  return;
}
/*the minus of uint8_t in scalar to vector*/
void sv_mns_u8(uint8_t __a, uint8_t* __b, uint8_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __sv_mns_u8<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __sv_mns_u16(uint16_t __a, uint16_t* __b, uint16_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a - __b[i];
  return;
}
/*the minus of uint16_t in scalar to vector*/
void sv_mns_u16(uint16_t __a, uint16_t* __b, uint16_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __sv_mns_u16<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __sv_mns_u32(uint32_t __a, uint32_t* __b, uint32_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a - __b[i];
  return;
}
/*the minus of uint32_t in scalar to vector*/
void sv_mns_u32(uint32_t __a, uint32_t* __b, uint32_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __sv_mns_u32<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __sv_mns_u64(uint64_t __a, uint64_t* __b, uint64_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a - __b[i];
  return;
}
/*the minus of uint64_t in scalar to vector*/
void sv_mns_u64(uint64_t __a, uint64_t* __b, uint64_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __sv_mns_u64<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __sv_mns_f(float_t __a, float_t* __b, float_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a - __b[i];
  return;
}
/*the minus of float_t in scalar to vector*/
void sv_mns_f(float_t __a, float_t* __b, float_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __sv_mns_f<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __sv_mns_d(double_t __a, double_t* __b, double_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a - __b[i];
  return;
}
/*the minus of double_t in scalar to vector*/
void sv_mns_d(double_t __a, double_t* __b, double_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __sv_mns_d<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}
//#####################################################################################################################
__global__ void __vv_mul_b(bool* __a, bool* __b, bool* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] & __b[i];
  return;
}
/*the mul of bool in vector to vector*/
void vv_mul_b(bool* __a, bool* __b, bool* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vv_mul_b<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vv_mul_i8(int8_t* __a, int8_t* __b, int8_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] * __b[i];
  return;
}
/*the mul of int8_t in vector to vector*/
void vv_mul_i8(int8_t* __a, int8_t* __b, int8_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vv_mul_i8<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vv_mul_i16(int16_t* __a, int16_t* __b, int16_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] * __b[i];
  return;
}
/*the mul of int16_t in vector to vector*/
void vv_mul_i16(int16_t* __a, int16_t* __b, int16_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vv_mul_i16<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vv_mul_i32(int32_t* __a, int32_t* __b, int32_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] * __b[i];
  return;
}
/*the mul of int32_t in vector to vector*/
void vv_mul_i32(int32_t* __a, int32_t* __b, int32_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vv_mul_i32<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vv_mul_i64(int64_t* __a, int64_t* __b, int64_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] * __b[i];
  return;
}
/*the mul of int64_t in vector to vector*/
void vv_mul_i64(int64_t* __a, int64_t* __b, int64_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vv_mul_i64<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vv_mul_u8(uint8_t* __a, uint8_t* __b, uint8_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] * __b[i];
  return;
}
/*the mul of uint8_t in vector to vector*/
void vv_mul_u8(uint8_t* __a, uint8_t* __b, uint8_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vv_mul_u8<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vv_mul_u16(uint16_t* __a, uint16_t* __b, uint16_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] * __b[i];
  return;
}
/*the mul of uint16_t in vector to vector*/
void vv_mul_u16(uint16_t* __a, uint16_t* __b, uint16_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vv_mul_u16<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vv_mul_u32(uint32_t* __a, uint32_t* __b, uint32_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] * __b[i];
  return;
}
/*the mul of uint32_t in vector to vector*/
void vv_mul_u32(uint32_t* __a, uint32_t* __b, uint32_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vv_mul_u32<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vv_mul_u64(uint64_t* __a, uint64_t* __b, uint64_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] * __b[i];
  return;
}
/*the mul of uint64_t in vector to vector*/
void vv_mul_u64(uint64_t* __a, uint64_t* __b, uint64_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vv_mul_u64<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vv_mul_f(float_t* __a, float_t* __b, float_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] * __b[i];
  return;
}
/*the mul of float_t in vector to vector*/
void vv_mul_f(float_t* __a, float_t* __b, float_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vv_mul_f<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vv_mul_d(double_t* __a, double_t* __b, double_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] * __b[i];
  return;
}
/*the mul of double_t in vector to vector*/
void vv_mul_d(double_t* __a, double_t* __b, double_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vv_mul_d<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}
//#####################################################################################################################
__global__ void __vs_mul_b(bool* __a, bool __b, bool* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] & __b;
  return;
}
/*the mul of bool in vector to scalar*/
void vs_mul_b(bool* __a, bool __b, bool* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vs_mul_b<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vs_mul_i8(int8_t* __a, int8_t __b, int8_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] * __b;
  return;
}
/*the mul of int8_t in vector to scalar*/
void vs_mul_i8(int8_t* __a, int8_t __b, int8_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vs_mul_i8<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vs_mul_i16(int16_t* __a, int16_t __b, int16_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] * __b;
  return;
}
/*the mul of int16_t in vector to scalar*/
void vs_mul_i16(int16_t* __a, int16_t __b, int16_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vs_mul_i16<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vs_mul_i32(int32_t* __a, int32_t __b, int32_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] * __b;
  return;
}
/*the mul of int32_t in vector to scalar*/
void vs_mul_i32(int32_t* __a, int32_t __b, int32_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vs_mul_i32<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vs_mul_i64(int64_t* __a, int64_t __b, int64_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] * __b;
  return;
}
/*the mul of int64_t in vector to scalar*/
void vs_mul_i64(int64_t* __a, int64_t __b, int64_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vs_mul_i64<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vs_mul_u8(uint8_t* __a, uint8_t __b, uint8_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] * __b;
  return;
}
/*the mul of uint8_t in vector to scalar*/
void vs_mul_u8(uint8_t* __a, uint8_t __b, uint8_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vs_mul_u8<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vs_mul_u16(uint16_t* __a, uint16_t __b, uint16_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] * __b;
  return;
}
/*the mul of uint16_t in vector to scalar*/
void vs_mul_u16(uint16_t* __a, uint16_t __b, uint16_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vs_mul_u16<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vs_mul_u32(uint32_t* __a, uint32_t __b, uint32_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] * __b;
  return;
}
/*the mul of uint32_t in vector to scalar*/
void vs_mul_u32(uint32_t* __a, uint32_t __b, uint32_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vs_mul_u32<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vs_mul_u64(uint64_t* __a, uint64_t __b, uint64_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] * __b;
  return;
}
/*the mul of uint64_t in vector to scalar*/
void vs_mul_u64(uint64_t* __a, uint64_t __b, uint64_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vs_mul_u64<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vs_mul_f(float_t* __a, float_t __b, float_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] * __b;
  return;
}
/*the mul of float_t in vector to scalar*/
void vs_mul_f(float_t* __a, float_t __b, float_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vs_mul_f<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vs_mul_d(double_t* __a, double_t __b, double_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] * __b;
  return;
}
/*the mul of double_t in vector to scalar*/
void vs_mul_d(double_t* __a, double_t __b, double_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vs_mul_d<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}
//#####################################################################################################################
__global__ void __vv_div_b(bool* __a, bool* __b, bool* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] ^ __b[i];
  return;
}
/*the divide of bool in vector to vector*/
void vv_div_b(bool* __a, bool* __b, bool* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vv_div_b<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vv_div_i8(int8_t* __a, int8_t* __b, int8_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] / __b[i];
  return;
}
/*the divide of int8_t in vector to vector*/
void vv_div_i8(int8_t* __a, int8_t* __b, int8_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vv_div_i8<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vv_div_i16(int16_t* __a, int16_t* __b, int16_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] / __b[i];
  return;
}
/*the divide of int16_t in vector to vector*/
void vv_div_i16(int16_t* __a, int16_t* __b, int16_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vv_div_i16<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vv_div_i32(int32_t* __a, int32_t* __b, int32_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] / __b[i];
  return;
}
/*the divide of int32_t in vector to vector*/
void vv_div_i32(int32_t* __a, int32_t* __b, int32_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vv_div_i32<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vv_div_i64(int64_t* __a, int64_t* __b, int64_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] / __b[i];
  return;
}
/*the divide of int64_t in vector to vector*/
void vv_div_i64(int64_t* __a, int64_t* __b, int64_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vv_div_i64<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vv_div_u8(uint8_t* __a, uint8_t* __b, uint8_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] / __b[i];
  return;
}
/*the divide of uint8_t in vector to vector*/
void vv_div_u8(uint8_t* __a, uint8_t* __b, uint8_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vv_div_u8<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vv_div_u16(uint16_t* __a, uint16_t* __b, uint16_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] / __b[i];
  return;
}
/*the divide of uint16_t in vector to vector*/
void vv_div_u16(uint16_t* __a, uint16_t* __b, uint16_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vv_div_u16<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vv_div_u32(uint32_t* __a, uint32_t* __b, uint32_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] / __b[i];
  return;
}
/*the divide of uint32_t in vector to vector*/
void vv_div_u32(uint32_t* __a, uint32_t* __b, uint32_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vv_div_u32<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vv_div_u64(uint64_t* __a, uint64_t* __b, uint64_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] / __b[i];
  return;
}
/*the divide of uint64_t in vector to vector*/
void vv_div_u64(uint64_t* __a, uint64_t* __b, uint64_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vv_div_u64<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vv_div_f(float_t* __a, float_t* __b, float_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] / __b[i];
  return;
}
/*the divide of float_t in vector to vector*/
void vv_div_f(float_t* __a, float_t* __b, float_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vv_div_f<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vv_div_d(double_t* __a, double_t* __b, double_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] / __b[i];
  return;
}
/*the divide of double_t in vector to vector*/
void vv_div_d(double_t* __a, double_t* __b, double_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vv_div_d<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}
//#####################################################################################################################
__global__ void __vs_div_b(bool* __a, bool __b, bool* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] ^ __b;
  return;
}
/*the divide of bool in vector to scalar*/
void vs_div_b(bool* __a, bool __b, bool* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vs_div_b<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vs_div_i8(int8_t* __a, int8_t __b, int8_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] / __b;
  return;
}
/*the divide of int8_t in vector to scalar*/
void vs_div_i8(int8_t* __a, int8_t __b, int8_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vs_div_i8<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vs_div_i16(int16_t* __a, int16_t __b, int16_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] / __b;
  return;
}
/*the divide of int16_t in vector to scalar*/
void vs_div_i16(int16_t* __a, int16_t __b, int16_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vs_div_i16<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vs_div_i32(int32_t* __a, int32_t __b, int32_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] / __b;
  return;
}
/*the divide of int32_t in vector to scalar*/
void vs_div_i32(int32_t* __a, int32_t __b, int32_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vs_div_i32<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vs_div_i64(int64_t* __a, int64_t __b, int64_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] / __b;
  return;
}
/*the divide of int64_t in vector to scalar*/
void vs_div_i64(int64_t* __a, int64_t __b, int64_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vs_div_i64<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vs_div_u8(uint8_t* __a, uint8_t __b, uint8_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] / __b;
  return;
}
/*the divide of uint8_t in vector to scalar*/
void vs_div_u8(uint8_t* __a, uint8_t __b, uint8_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vs_div_u8<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vs_div_u16(uint16_t* __a, uint16_t __b, uint16_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] / __b;
  return;
}
/*the divide of uint16_t in vector to scalar*/
void vs_div_u16(uint16_t* __a, uint16_t __b, uint16_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vs_div_u16<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vs_div_u32(uint32_t* __a, uint32_t __b, uint32_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] / __b;
  return;
}
/*the divide of uint32_t in vector to scalar*/
void vs_div_u32(uint32_t* __a, uint32_t __b, uint32_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vs_div_u32<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vs_div_u64(uint64_t* __a, uint64_t __b, uint64_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] / __b;
  return;
}
/*the divide of uint64_t in vector to scalar*/
void vs_div_u64(uint64_t* __a, uint64_t __b, uint64_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vs_div_u64<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vs_div_f(float_t* __a, float_t __b, float_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] / __b;
  return;
}
/*the divide of float_t in vector to scalar*/
void vs_div_f(float_t* __a, float_t __b, float_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vs_div_f<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __vs_div_d(double_t* __a, double_t __b, double_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a[i] / __b;
  return;
}
/*the divide of double_t in vector to scalar*/
void vs_div_d(double_t* __a, double_t __b, double_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __vs_div_d<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}
//#####################################################################################################################
__global__ void __sv_div_b(bool __a, bool* __b, bool* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a ^ __b[i];
  return;
}
/*the divide of bool in scalar to vector*/
void sv_div_b(bool __a, bool* __b, bool* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __sv_div_b<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __sv_div_i8(int8_t __a, int8_t* __b, int8_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a / __b[i];
  return;
}
/*the divide of int8_t in scalar to vector*/
void sv_div_i8(int8_t __a, int8_t* __b, int8_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __sv_div_i8<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __sv_div_i16(int16_t __a, int16_t* __b, int16_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a / __b[i];
  return;
}
/*the divide of int16_t in scalar to vector*/
void sv_div_i16(int16_t __a, int16_t* __b, int16_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __sv_div_i16<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __sv_div_i32(int32_t __a, int32_t* __b, int32_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a / __b[i];
  return;
}
/*the divide of int32_t in scalar to vector*/
void sv_div_i32(int32_t __a, int32_t* __b, int32_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __sv_div_i32<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __sv_div_i64(int64_t __a, int64_t* __b, int64_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a / __b[i];
  return;
}
/*the divide of int64_t in scalar to vector*/
void sv_div_i64(int64_t __a, int64_t* __b, int64_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __sv_div_i64<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __sv_div_u8(uint8_t __a, uint8_t* __b, uint8_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a / __b[i];
  return;
}
/*the divide of uint8_t in scalar to vector*/
void sv_div_u8(uint8_t __a, uint8_t* __b, uint8_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __sv_div_u8<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __sv_div_u16(uint16_t __a, uint16_t* __b, uint16_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a / __b[i];
  return;
}
/*the divide of uint16_t in scalar to vector*/
void sv_div_u16(uint16_t __a, uint16_t* __b, uint16_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __sv_div_u16<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __sv_div_u32(uint32_t __a, uint32_t* __b, uint32_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a / __b[i];
  return;
}
/*the divide of uint32_t in scalar to vector*/
void sv_div_u32(uint32_t __a, uint32_t* __b, uint32_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __sv_div_u32<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __sv_div_u64(uint64_t __a, uint64_t* __b, uint64_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a / __b[i];
  return;
}
/*the divide of uint64_t in scalar to vector*/
void sv_div_u64(uint64_t __a, uint64_t* __b, uint64_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __sv_div_u64<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __sv_div_f(float_t __a, float_t* __b, float_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a / __b[i];
  return;
}
/*the divide of float_t in scalar to vector*/
void sv_div_f(float_t __a, float_t* __b, float_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __sv_div_f<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __sv_div_d(double_t __a, double_t* __b, double_t* __c, size_t __size, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  for(size_t i = position, j = 0; (i < __size) && (j < __tuple); i++, j++)
    __c[i] = __a / __b[i];
  return;
}
/*the divide of double_t in scalar to vector*/
void sv_div_d(double_t __a, double_t* __b, double_t* __c, size_t __size) {
  size_t tuple = __size % THREADS ? __size / THREADS + 1 : __size / THREADS;
  size_t tuples = __size % tuple ? __size / tuple + 1 : __size / tuple;
  __sv_div_d<<<1, tuples>>>(__a, __b, __c, __size, tuple);
  cudaDeviceSynchronize();
  return;
}
//#####################################################################################################################
__global__ void __sum_b(bool* __lib, size_t* __obj, size_t __offest, size_t __strike, size_t __lenth, size_t __strikes, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  bool* ptr;
  for(size_t i = position, j = 0; (i < __lenth) && (j < __tuple); i++, j++){
    ptr = __lib + i * __offest;
    for(size_t j = 0; j < __strikes; j++){
      __obj[i] += (*ptr) ? 1 : 0;
      ptr += __strike;
    }
  }
  return;
}
/*the horizontal summer of bool*/
void h_sum_b(bool* __lib, size_t* __obj, size_t __rows, size_t __cols) {
  size_t tuple = __rows % THREADS ? __rows / THREADS + 1 : __rows / THREADS;
  size_t tuples = __rows % tuple ? __rows / tuple + 1 : __rows / tuple;
  __sum_b<<<1, tuples>>>(__lib, __obj, __cols, 1, __rows, __cols, tuple);
  cudaDeviceSynchronize();
  return;
}
/*the vertical summer of bool*/
void v_sum_b(bool* __lib, size_t* __obj, size_t __rows, size_t __cols) {
  size_t tuple = __cols % THREADS ? __cols / THREADS + 1 : __cols / THREADS;
  size_t tuples = __cols % tuple ? __cols / tuple + 1 : __cols / tuple;
  __sum_b<<<1, tuples>>>(__lib, __obj, 1, __cols, __cols, __rows, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __sum_i8(int8_t* __lib, int8_t* __obj, size_t __offest, size_t __strike, size_t __lenth, size_t __strikes, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  int8_t* ptr;
  for(size_t i = position, j = 0; (i < __lenth) && (j < __tuple); i++, j++){
    ptr = __lib + i * __offest;
    for(size_t j = 0; j < __strikes; j++){
      __obj[i] += (*ptr);
      ptr += __strike;
    }
  }
  return;
}
/*the horizontal summer of int8_t*/
void h_sum_i8(int8_t* __lib, int8_t* __obj, size_t __rows, size_t __cols) {
  size_t tuple = __rows % THREADS ? __rows / THREADS + 1 : __rows / THREADS;
  size_t tuples = __rows % tuple ? __rows / tuple + 1 : __rows / tuple;
  __sum_i8<<<1, tuples>>>(__lib, __obj, __cols, 1, __rows, __cols, tuple);
  cudaDeviceSynchronize();
  return;
}
/*the vertical summer of int8_t*/
void v_sum_i8(int8_t* __lib, int8_t* __obj, size_t __rows, size_t __cols) {
  size_t tuple = __cols % THREADS ? __cols / THREADS + 1 : __cols / THREADS;
  size_t tuples = __cols % tuple ? __cols / tuple + 1 : __cols / tuple;
  __sum_i8<<<1, tuples>>>(__lib, __obj, 1, __cols, __cols, __rows, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __sum_i16(int16_t* __lib, int16_t* __obj, size_t __offest, size_t __strike, size_t __lenth, size_t __strikes, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  int16_t* ptr;
  for(size_t i = position, j = 0; (i < __lenth) && (j < __tuple); i++, j++){
    ptr = __lib + i * __offest;
    for(size_t j = 0; j < __strikes; j++){
      __obj[i] += (*ptr);
      ptr += __strike;
    }
  }
  return;
}
/*the horizontal summer of int16_t*/
void h_sum_i16(int16_t* __lib, int16_t* __obj, size_t __rows, size_t __cols) {
  size_t tuple = __rows % THREADS ? __rows / THREADS + 1 : __rows / THREADS;
  size_t tuples = __rows % tuple ? __rows / tuple + 1 : __rows / tuple;
  __sum_i16<<<1, tuples>>>(__lib, __obj, __cols, 1, __rows, __cols, tuple);
  cudaDeviceSynchronize();
  return;
}
/*the vertical summer of int16_t*/
void v_sum_i16(int16_t* __lib, int16_t* __obj, size_t __rows, size_t __cols) {
  size_t tuple = __cols % THREADS ? __cols / THREADS + 1 : __cols / THREADS;
  size_t tuples = __cols % tuple ? __cols / tuple + 1 : __cols / tuple;
  __sum_i16<<<1, tuples>>>(__lib, __obj, 1, __cols, __cols, __rows, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __sum_i32(int32_t* __lib, int32_t* __obj, size_t __offest, size_t __strike, size_t __lenth, size_t __strikes, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  int32_t* ptr;
  for(size_t i = position, j = 0; (i < __lenth) && (j < __tuple); i++, j++){
    ptr = __lib + i * __offest;
    for(size_t j = 0; j < __strikes; j++){
      __obj[i] += (*ptr);
      ptr += __strike;
    }
  }
  return;
}
/*the horizontal summer of int32_t*/
void h_sum_i32(int32_t* __lib, int32_t* __obj, size_t __rows, size_t __cols) {
  size_t tuple = __rows % THREADS ? __rows / THREADS + 1 : __rows / THREADS;
  size_t tuples = __rows % tuple ? __rows / tuple + 1 : __rows / tuple;
  __sum_i32<<<1, tuples>>>(__lib, __obj, __cols, 1, __rows, __cols, tuple);
  cudaDeviceSynchronize();
  return;
}
/*the vertical summer of int32_t*/
void v_sum_i32(int32_t* __lib, int32_t* __obj, size_t __rows, size_t __cols) {
  size_t tuple = __cols % THREADS ? __cols / THREADS + 1 : __cols / THREADS;
  size_t tuples = __cols % tuple ? __cols / tuple + 1 : __cols / tuple;
  __sum_i32<<<1, tuples>>>(__lib, __obj, 1, __cols, __cols, __rows, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __sum_i64(int64_t* __lib, int64_t* __obj, size_t __offest, size_t __strike, size_t __lenth, size_t __strikes, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  int64_t* ptr;
  for(size_t i = position, j = 0; (i < __lenth) && (j < __tuple); i++, j++){
    ptr = __lib + i * __offest;
    for(size_t j = 0; j < __strikes; j++){
      __obj[i] += (*ptr);
      ptr += __strike;
    }
  }
  return;
}
/*the horizontal summer of int64_t*/
void h_sum_i64(int64_t* __lib, int64_t* __obj, size_t __rows, size_t __cols) {
  size_t tuple = __rows % THREADS ? __rows / THREADS + 1 : __rows / THREADS;
  size_t tuples = __rows % tuple ? __rows / tuple + 1 : __rows / tuple;
  __sum_i64<<<1, tuples>>>(__lib, __obj, __cols, 1, __rows, __cols, tuple);
  cudaDeviceSynchronize();
  return;
}
/*the vertical summer of int64_t*/
void v_sum_i64(int64_t* __lib, int64_t* __obj, size_t __rows, size_t __cols) {
  size_t tuple = __cols % THREADS ? __cols / THREADS + 1 : __cols / THREADS;
  size_t tuples = __cols % tuple ? __cols / tuple + 1 : __cols / tuple;
  __sum_i64<<<1, tuples>>>(__lib, __obj, 1, __cols, __cols, __rows, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __sum_u8(uint8_t* __lib, uint8_t* __obj, size_t __offest, size_t __strike, size_t __lenth, size_t __strikes, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  uint8_t* ptr;
  for(size_t i = position, j = 0; (i < __lenth) && (j < __tuple); i++, j++){
    ptr = __lib + i * __offest;
    for(size_t j = 0; j < __strikes; j++){
      __obj[i] += (*ptr);
      ptr += __strike;
    }
  }
  return;
}
/*the horizontal summer of uint8_t*/
void h_sum_u8(uint8_t* __lib, uint8_t* __obj, size_t __rows, size_t __cols) {
  size_t tuple = __rows % THREADS ? __rows / THREADS + 1 : __rows / THREADS;
  size_t tuples = __rows % tuple ? __rows / tuple + 1 : __rows / tuple;
  __sum_u8<<<1, tuples>>>(__lib, __obj, __cols, 1, __rows, __cols, tuple);
  cudaDeviceSynchronize();
  return;
}
/*the vertical summer of uint8_t*/
void v_sum_u8(uint8_t* __lib, uint8_t* __obj, size_t __rows, size_t __cols) {
  size_t tuple = __cols % THREADS ? __cols / THREADS + 1 : __cols / THREADS;
  size_t tuples = __cols % tuple ? __cols / tuple + 1 : __cols / tuple;
  __sum_u8<<<1, tuples>>>(__lib, __obj, 1, __cols, __cols, __rows, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __sum_u16(uint16_t* __lib, uint16_t* __obj, size_t __offest, size_t __strike, size_t __lenth, size_t __strikes, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  uint16_t* ptr;
  for(size_t i = position, j = 0; (i < __lenth) && (j < __tuple); i++, j++){
    ptr = __lib + i * __offest;
    for(size_t j = 0; j < __strikes; j++){
      __obj[i] += (*ptr);
      ptr += __strike;
    }
  }
  return;
}
/*the horizontal summer of uint16_t*/
void h_sum_u16(uint16_t* __lib, uint16_t* __obj, size_t __rows, size_t __cols) {
  size_t tuple = __rows % THREADS ? __rows / THREADS + 1 : __rows / THREADS;
  size_t tuples = __rows % tuple ? __rows / tuple + 1 : __rows / tuple;
  __sum_u16<<<1, tuples>>>(__lib, __obj, __cols, 1, __rows, __cols, tuple);
  cudaDeviceSynchronize();
  return;
}
/*the vertical summer of uint16_t*/
void v_sum_u16(uint16_t* __lib, uint16_t* __obj, size_t __rows, size_t __cols) {
  size_t tuple = __cols % THREADS ? __cols / THREADS + 1 : __cols / THREADS;
  size_t tuples = __cols % tuple ? __cols / tuple + 1 : __cols / tuple;
  __sum_u16<<<1, tuples>>>(__lib, __obj, 1, __cols, __cols, __rows, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __sum_u32(uint32_t* __lib, uint32_t* __obj, size_t __offest, size_t __strike, size_t __lenth, size_t __strikes, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  uint32_t* ptr;
  for(size_t i = position, j = 0; (i < __lenth) && (j < __tuple); i++, j++){
    ptr = __lib + i * __offest;
    for(size_t j = 0; j < __strikes; j++){
      __obj[i] += (*ptr);
      ptr += __strike;
    }
  }
  return;
}
/*the horizontal summer of uint32_t*/
void h_sum_u32(uint32_t* __lib, uint32_t* __obj, size_t __rows, size_t __cols) {
  size_t tuple = __rows % THREADS ? __rows / THREADS + 1 : __rows / THREADS;
  size_t tuples = __rows % tuple ? __rows / tuple + 1 : __rows / tuple;
  __sum_u32<<<1, tuples>>>(__lib, __obj, __cols, 1, __rows, __cols, tuple);
  cudaDeviceSynchronize();
  return;
}
/*the vertical summer of uint32_t*/
void v_sum_u32(uint32_t* __lib, uint32_t* __obj, size_t __rows, size_t __cols) {
  size_t tuple = __cols % THREADS ? __cols / THREADS + 1 : __cols / THREADS;
  size_t tuples = __cols % tuple ? __cols / tuple + 1 : __cols / tuple;
  __sum_u32<<<1, tuples>>>(__lib, __obj, 1, __cols, __cols, __rows, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __sum_u64(uint64_t* __lib, uint64_t* __obj, size_t __offest, size_t __strike, size_t __lenth, size_t __strikes, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  uint64_t* ptr;
  for(size_t i = position, j = 0; (i < __lenth) && (j < __tuple); i++, j++){
    ptr = __lib + i * __offest;
    for(size_t j = 0; j < __strikes; j++){
      __obj[i] += (*ptr);
      ptr += __strike;
    }
  }
  return;
}
/*the horizontal summer of uint64_t*/
void h_sum_u64(uint64_t* __lib, uint64_t* __obj, size_t __rows, size_t __cols) {
  size_t tuple = __rows % THREADS ? __rows / THREADS + 1 : __rows / THREADS;
  size_t tuples = __rows % tuple ? __rows / tuple + 1 : __rows / tuple;
  __sum_u64<<<1, tuples>>>(__lib, __obj, __cols, 1, __rows, __cols, tuple);
  cudaDeviceSynchronize();
  return;
}
/*the vertical summer of uint64_t*/
void v_sum_u64(uint64_t* __lib, uint64_t* __obj, size_t __rows, size_t __cols) {
  size_t tuple = __cols % THREADS ? __cols / THREADS + 1 : __cols / THREADS;
  size_t tuples = __cols % tuple ? __cols / tuple + 1 : __cols / tuple;
  __sum_u64<<<1, tuples>>>(__lib, __obj, 1, __cols, __cols, __rows, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __sum_f(float_t* __lib, float_t* __obj, size_t __offest, size_t __strike, size_t __lenth, size_t __strikes, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  float_t* ptr;
  for(size_t i = position, j = 0; (i < __lenth) && (j < __tuple); i++, j++){
    ptr = __lib + i * __offest;
    for(size_t j = 0; j < __strikes; j++){
      __obj[i] += (*ptr);
      ptr += __strike;
    }
  }
  return;
}
/*the horizontal summer of float_t*/
void h_sum_f(float_t* __lib, float_t* __obj, size_t __rows, size_t __cols) {
  size_t tuple = __rows % THREADS ? __rows / THREADS + 1 : __rows / THREADS;
  size_t tuples = __rows % tuple ? __rows / tuple + 1 : __rows / tuple;
  __sum_f<<<1, tuples>>>(__lib, __obj, __cols, 1, __rows, __cols, tuple);
  cudaDeviceSynchronize();
  return;
}
/*the vertical summer of float_t*/
void v_sum_f(float_t* __lib, float_t* __obj, size_t __rows, size_t __cols) {
  size_t tuple = __cols % THREADS ? __cols / THREADS + 1 : __cols / THREADS;
  size_t tuples = __cols % tuple ? __cols / tuple + 1 : __cols / tuple;
  __sum_f<<<1, tuples>>>(__lib, __obj, 1, __cols, __cols, __rows, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __sum_d(double_t* __lib, double_t* __obj, size_t __offest, size_t __strike, size_t __lenth, size_t __strikes, size_t __tuple) {
  size_t position = threadIdx.x;
  position *= __tuple;
  double_t* ptr;
  for(size_t i = position, j = 0; (i < __lenth) && (j < __tuple); i++, j++){
    ptr = __lib + i * __offest;
    for(size_t j = 0; j < __strikes; j++){
      __obj[i] += (*ptr);
      ptr += __strike;
    }
  }
  return;
}
/*the horizontal summer of double_t*/
void h_sum_d(double_t* __lib, double_t* __obj, size_t __rows, size_t __cols) {
  size_t tuple = __rows % THREADS ? __rows / THREADS + 1 : __rows / THREADS;
  size_t tuples = __rows % tuple ? __rows / tuple + 1 : __rows / tuple;
  __sum_d<<<1, tuples>>>(__lib, __obj, __cols, 1, __rows, __cols, tuple);
  cudaDeviceSynchronize();
  return;
}
/*the vertical summer of double_t*/
void v_sum_d(double_t* __lib, double_t* __obj, size_t __rows, size_t __cols) {
  size_t tuple = __cols % THREADS ? __cols / THREADS + 1 : __cols / THREADS;
  size_t tuples = __cols % tuple ? __cols / tuple + 1 : __cols / tuple;
  __sum_d<<<1, tuples>>>(__lib, __obj, 1, __cols, __cols, __rows, tuple);
  cudaDeviceSynchronize();
  return;
}
//#####################################################################################################################
__global__ void __dot_b(bool* __a, bool* __b, bool* __c, size_t __row, size_t __line, size_t __col, size_t __tuple) {
  size_t position = threadIdx.x, total = __row * __col;
  position *= __tuple;
  size_t pR, pC;
  auto a = __a, b = __b;
  for(size_t i = position, j = 0; (i < total) && (j < __tuple); i++, j++){
    pR = i / __col;
    pC = i % __col;
    a = __a + __line * pR;
    b = __b + pC;
    for(size_t w = 0; w < __line; w++){
      __c[i] |= (*a) & (*b);
      a++;
      b += __col;
    }
  }
}
/*dot of bool*/
void dot_b(bool* __a, bool* __b, bool* __c, size_t __row, size_t __line, size_t __col){
  size_t total = __row * __col;
  size_t tuple = total % THREADS ? total / THREADS + 1 : total / THREADS;
  size_t tuples = total % tuple ? total / tuple + 1 : total / tuple;
  __dot_b<<<1, tuples>>>(__a, __b, __c, __row, __line, __col, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __dot_i8(int8_t* __a, int8_t* __b, int8_t* __c, size_t __row, size_t __line, size_t __col, size_t __tuple) {
  size_t position = threadIdx.x, total = __row * __col;
  position *= __tuple;
  size_t pR, pC;
  auto a = __a, b = __b;
  for(size_t i = position, j = 0; (i < total) && (j < __tuple); i++, j++){
    pR = i / __col;
    pC = i % __col;
    a = __a + __line * pR;
    b = __b + pC;
    for(size_t w = 0; w < __line; w++){
      __c[i] += (*a) * (*b);
      a++;
      b += __col;
    }
  }
}
/*dot of int8_t*/
void dot_i8(int8_t* __a, int8_t* __b, int8_t* __c, size_t __row, size_t __line, size_t __col){
  size_t total = __row * __col;
  size_t tuple = total % THREADS ? total / THREADS + 1 : total / THREADS;
  size_t tuples = total % tuple ? total / tuple + 1 : total / tuple;
  __dot_i8<<<1, tuples>>>(__a, __b, __c, __row, __line, __col, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __dot_i16(int16_t* __a, int16_t* __b, int16_t* __c, size_t __row, size_t __line, size_t __col, size_t __tuple) {
  size_t position = threadIdx.x, total = __row * __col;
  position *= __tuple;
  size_t pR, pC;
  auto a = __a, b = __b;
  for(size_t i = position, j = 0; (i < total) && (j < __tuple); i++, j++){
    pR = i / __col;
    pC = i % __col;
    a = __a + __line * pR;
    b = __b + pC;
    for(size_t w = 0; w < __line; w++){
      __c[i] += (*a) * (*b);
      a++;
      b += __col;
    }
  }
}
/*dot of int16_t*/
void dot_i16(int16_t* __a, int16_t* __b, int16_t* __c, size_t __row, size_t __line, size_t __col){
  size_t total = __row * __col;
  size_t tuple = total % THREADS ? total / THREADS + 1 : total / THREADS;
  size_t tuples = total % tuple ? total / tuple + 1 : total / tuple;
  __dot_i16<<<1, tuples>>>(__a, __b, __c, __row, __line, __col, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __dot_i32(int32_t* __a, int32_t* __b, int32_t* __c, size_t __row, size_t __line, size_t __col, size_t __tuple) {
  size_t position = threadIdx.x, total = __row * __col;
  position *= __tuple;
  size_t pR, pC;
  auto a = __a, b = __b;
  for(size_t i = position, j = 0; (i < total) && (j < __tuple); i++, j++){
    pR = i / __col;
    pC = i % __col;
    a = __a + __line * pR;
    b = __b + pC;
    for(size_t w = 0; w < __line; w++){
      __c[i] += (*a) * (*b);
      a++;
      b += __col;
    }
  }
}
/*dot of int32_t*/
void dot_i32(int32_t* __a, int32_t* __b, int32_t* __c, size_t __row, size_t __line, size_t __col){
  size_t total = __row * __col;
  size_t tuple = total % THREADS ? total / THREADS + 1 : total / THREADS;
  size_t tuples = total % tuple ? total / tuple + 1 : total / tuple;
  __dot_i32<<<1, tuples>>>(__a, __b, __c, __row, __line, __col, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __dot_i64(int64_t* __a, int64_t* __b, int64_t* __c, size_t __row, size_t __line, size_t __col, size_t __tuple) {
  size_t position = threadIdx.x, total = __row * __col;
  position *= __tuple;
  size_t pR, pC;
  auto a = __a, b = __b;
  for(size_t i = position, j = 0; (i < total) && (j < __tuple); i++, j++){
    pR = i / __col;
    pC = i % __col;
    a = __a + __line * pR;
    b = __b + pC;
    for(size_t w = 0; w < __line; w++){
      __c[i] += (*a) * (*b);
      a++;
      b += __col;
    }
  }
}
/*dot of int64_t*/
void dot_i64(int64_t* __a, int64_t* __b, int64_t* __c, size_t __row, size_t __line, size_t __col){
  size_t total = __row * __col;
  size_t tuple = total % THREADS ? total / THREADS + 1 : total / THREADS;
  size_t tuples = total % tuple ? total / tuple + 1 : total / tuple;
  __dot_i64<<<1, tuples>>>(__a, __b, __c, __row, __line, __col, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __dot_u8(uint8_t* __a, uint8_t* __b, uint8_t* __c, size_t __row, size_t __line, size_t __col, size_t __tuple) {
  size_t position = threadIdx.x, total = __row * __col;
  position *= __tuple;
  size_t pR, pC;
  auto a = __a, b = __b;
  for(size_t i = position, j = 0; (i < total) && (j < __tuple); i++, j++){
    pR = i / __col;
    pC = i % __col;
    a = __a + __line * pR;
    b = __b + pC;
    for(size_t w = 0; w < __line; w++){
      __c[i] += (*a) * (*b);
      a++;
      b += __col;
    }
  }
}
/*dot of uint8_t*/
void dot_u8(uint8_t* __a, uint8_t* __b, uint8_t* __c, size_t __row, size_t __line, size_t __col){
  size_t total = __row * __col;
  size_t tuple = total % THREADS ? total / THREADS + 1 : total / THREADS;
  size_t tuples = total % tuple ? total / tuple + 1 : total / tuple;
  __dot_u8<<<1, tuples>>>(__a, __b, __c, __row, __line, __col, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __dot_u16(uint16_t* __a, uint16_t* __b, uint16_t* __c, size_t __row, size_t __line, size_t __col, size_t __tuple) {
  size_t position = threadIdx.x, total = __row * __col;
  position *= __tuple;
  size_t pR, pC;
  auto a = __a, b = __b;
  for(size_t i = position, j = 0; (i < total) && (j < __tuple); i++, j++){
    pR = i / __col;
    pC = i % __col;
    a = __a + __line * pR;
    b = __b + pC;
    for(size_t w = 0; w < __line; w++){
      __c[i] += (*a) * (*b);
      a++;
      b += __col;
    }
  }
}
/*dot of uint16_t*/
void dot_u16(uint16_t* __a, uint16_t* __b, uint16_t* __c, size_t __row, size_t __line, size_t __col){
  size_t total = __row * __col;
  size_t tuple = total % THREADS ? total / THREADS + 1 : total / THREADS;
  size_t tuples = total % tuple ? total / tuple + 1 : total / tuple;
  __dot_u16<<<1, tuples>>>(__a, __b, __c, __row, __line, __col, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __dot_u32(uint32_t* __a, uint32_t* __b, uint32_t* __c, size_t __row, size_t __line, size_t __col, size_t __tuple) {
  size_t position = threadIdx.x, total = __row * __col;
  position *= __tuple;
  size_t pR, pC;
  auto a = __a, b = __b;
  for(size_t i = position, j = 0; (i < total) && (j < __tuple); i++, j++){
    pR = i / __col;
    pC = i % __col;
    a = __a + __line * pR;
    b = __b + pC;
    for(size_t w = 0; w < __line; w++){
      __c[i] += (*a) * (*b);
      a++;
      b += __col;
    }
  }
}
/*dot of uint32_t*/
void dot_u32(uint32_t* __a, uint32_t* __b, uint32_t* __c, size_t __row, size_t __line, size_t __col){
  size_t total = __row * __col;
  size_t tuple = total % THREADS ? total / THREADS + 1 : total / THREADS;
  size_t tuples = total % tuple ? total / tuple + 1 : total / tuple;
  __dot_u32<<<1, tuples>>>(__a, __b, __c, __row, __line, __col, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __dot_u64(uint64_t* __a, uint64_t* __b, uint64_t* __c, size_t __row, size_t __line, size_t __col, size_t __tuple) {
  size_t position = threadIdx.x, total = __row * __col;
  position *= __tuple;
  size_t pR, pC;
  auto a = __a, b = __b;
  for(size_t i = position, j = 0; (i < total) && (j < __tuple); i++, j++){
    pR = i / __col;
    pC = i % __col;
    a = __a + __line * pR;
    b = __b + pC;
    for(size_t w = 0; w < __line; w++){
      __c[i] += (*a) * (*b);
      a++;
      b += __col;
    }
  }
}
/*dot of uint64_t*/
void dot_u64(uint64_t* __a, uint64_t* __b, uint64_t* __c, size_t __row, size_t __line, size_t __col){
  size_t total = __row * __col;
  size_t tuple = total % THREADS ? total / THREADS + 1 : total / THREADS;
  size_t tuples = total % tuple ? total / tuple + 1 : total / tuple;
  __dot_u64<<<1, tuples>>>(__a, __b, __c, __row, __line, __col, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __dot_f(float_t* __a, float_t* __b, float_t* __c, size_t __row, size_t __line, size_t __col, size_t __tuple) {
  size_t position = threadIdx.x, total = __row * __col;
  position *= __tuple;
  size_t pR, pC;
  auto a = __a, b = __b;
  for(size_t i = position, j = 0; (i < total) && (j < __tuple); i++, j++){
    pR = i / __col;
    pC = i % __col;
    a = __a + __line * pR;
    b = __b + pC;
    for(size_t w = 0; w < __line; w++){
      __c[i] += (*a) * (*b);
      a++;
      b += __col;
    }
  }
}
/*dot of float_t*/
void dot_f(float_t* __a, float_t* __b, float_t* __c, size_t __row, size_t __line, size_t __col){
  size_t total = __row * __col;
  size_t tuple = total % THREADS ? total / THREADS + 1 : total / THREADS;
  size_t tuples = total % tuple ? total / tuple + 1 : total / tuple;
  __dot_f<<<1, tuples>>>(__a, __b, __c, __row, __line, __col, tuple);
  cudaDeviceSynchronize();
  return;
}

__global__ void __dot_d(double_t* __a, double_t* __b, double_t* __c, size_t __row, size_t __line, size_t __col, size_t __tuple) {
  size_t position = threadIdx.x, total = __row * __col;
  position *= __tuple;
  size_t pR, pC;
  auto a = __a, b = __b;
  for(size_t i = position, j = 0; (i < total) && (j < __tuple); i++, j++){
    pR = i / __col;
    pC = i % __col;
    a = __a + __line * pR;
    b = __b + pC;
    for(size_t w = 0; w < __line; w++){
      __c[i] += (*a) * (*b);
      a++;
      b += __col;
    }
  }
}
/*dot of double_t*/
void dot_d(double_t* __a, double_t* __b, double_t* __c, size_t __row, size_t __line, size_t __col){
  size_t total = __row * __col;
  size_t tuple = total % THREADS ? total / THREADS + 1 : total / THREADS;
  size_t tuples = total % tuple ? total / tuple + 1 : total / tuple;
  __dot_d<<<1, tuples>>>(__a, __b, __c, __row, __line, __col, tuple);
  cudaDeviceSynchronize();
  return;
}
//#####################################################################################################################

clock_t test_for_vram(float_t* __a, float_t* __b, float_t* __c, size_t __size) {
  float_t *deviceA, *deviceB, *deviceC;
  auto size = __size * sizeof(float_t);
  clock_t first, second;
  cudaMalloc(&deviceA, size);
  cudaMalloc(&deviceB, size);
  cudaMalloc(&deviceC, size);
  cudaMemcpy(deviceA, __a, size, cudaMemcpyHostToDevice);
  cudaMemcpy(deviceB, __b, size, cudaMemcpyHostToDevice);
  first = clock();
  vv_add_f(deviceA, deviceB, deviceC, __size);
  second = clock();
  cudaMemcpy(__c, deviceC, size, cudaMemcpyDeviceToHost);
  cudaFree(deviceA);
  cudaFree(deviceB);
  cudaFree(deviceC);
  return second - first;
}

#ifdef __cplusplus
}
#endif