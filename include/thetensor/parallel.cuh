#include "define.h"

#ifndef PARALLEL_CUH
#define PARALLEL_CUH 1

#include <cuda.h>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>

#ifdef __cplusplus
extern "C" {
#endif

#define THREADS (1024UL)
void vv_add_b(bool*,bool*,bool*,size_t);
void vv_add_i8(int8_t*, int8_t*, int8_t*, size_t);
void vv_add_i16(int16_t*, int16_t*, int16_t*, size_t);
void vv_add_i32(int32_t*, int32_t*, int32_t*, size_t);
void vv_add_i64(int64_t*, int64_t*, int64_t*, size_t);
void vv_add_u8(uint8_t*, uint8_t*, uint8_t*, size_t);
void vv_add_u16(uint16_t*, uint16_t*, uint16_t*, size_t);
void vv_add_u32(uint32_t*, uint32_t*, uint32_t*, size_t);
void vv_add_u64(uint64_t*, uint64_t*, uint64_t*, size_t);
void vv_add_f(float_t*, float_t*, float_t*, size_t);
void vv_add_d(double_t*, double_t*, double_t*, size_t);
void vs_add_b(bool*,bool,bool*,size_t);
void vs_add_i8(int8_t*, int8_t, int8_t*, size_t);
void vs_add_i16(int16_t*, int16_t, int16_t*, size_t);
void vs_add_i32(int32_t*, int32_t, int32_t*, size_t);
void vs_add_i64(int64_t*, int64_t, int64_t*, size_t);
void vs_add_u8(uint8_t*, uint8_t, uint8_t*, size_t);
void vs_add_u16(uint16_t*, uint16_t, uint16_t*, size_t);
void vs_add_u32(uint32_t*, uint32_t, uint32_t*, size_t);
void vs_add_u64(uint64_t*, uint64_t, uint64_t*, size_t);
void vs_add_f(float_t*, float_t, float_t*, size_t);
void vs_add_d(double_t*, double_t, double_t*, size_t);
void vv_mns_b(bool*,bool*,bool*,size_t);
void vv_mns_i8(int8_t*, int8_t*, int8_t*, size_t);
void vv_mns_i16(int16_t*, int16_t*, int16_t*, size_t);
void vv_mns_i32(int32_t*, int32_t*, int32_t*, size_t);
void vv_mns_i64(int64_t*, int64_t*, int64_t*, size_t);
void vv_mns_u8(uint8_t*, uint8_t*, uint8_t*, size_t);
void vv_mns_u16(uint16_t*, uint16_t*, uint16_t*, size_t);
void vv_mns_u32(uint32_t*, uint32_t*, uint32_t*, size_t);
void vv_mns_u64(uint64_t*, uint64_t*, uint64_t*, size_t);
void vv_mns_f(float_t*, float_t*, float_t*, size_t);
void vv_mns_d(double_t*, double_t*, double_t*, size_t);
void vs_mns_b(bool*,bool,bool*,size_t);
void vs_mns_i8(int8_t*, int8_t, int8_t*, size_t);
void vs_mns_i16(int16_t*, int16_t, int16_t*, size_t);
void vs_mns_i32(int32_t*, int32_t, int32_t*, size_t);
void vs_mns_i64(int64_t*, int64_t, int64_t*, size_t);
void vs_mns_u8(uint8_t*, uint8_t, uint8_t*, size_t);
void vs_mns_u16(uint16_t*, uint16_t, uint16_t*, size_t);
void vs_mns_u32(uint32_t*, uint32_t, uint32_t*, size_t);
void vs_mns_u64(uint64_t*, uint64_t, uint64_t*, size_t);
void vs_mns_f(float_t*, float_t, float_t*, size_t);
void vs_mns_d(double_t*, double_t, double_t*, size_t);
void sv_mns_b(bool,bool*,bool*,size_t);
void sv_mns_i8(int8_t, int8_t*, int8_t*, size_t);
void sv_mns_i16(int16_t, int16_t*, int16_t*, size_t);
void sv_mns_i32(int32_t, int32_t*, int32_t*, size_t);
void sv_mns_i64(int64_t, int64_t*, int64_t*, size_t);
void sv_mns_u8(uint8_t, uint8_t*, uint8_t*, size_t);
void sv_mns_u16(uint16_t, uint16_t*, uint16_t*, size_t);
void sv_mns_u32(uint32_t, uint32_t*, uint32_t*, size_t);
void sv_mns_u64(uint64_t, uint64_t*, uint64_t*, size_t);
void sv_mns_f(float_t, float_t*, float_t*, size_t);
void sv_mns_d(double_t, double_t*, double_t*, size_t);
void vv_mul_b(bool*,bool*,bool*,size_t);
void vv_mul_i8(int8_t*, int8_t*, int8_t*, size_t);
void vv_mul_i16(int16_t*, int16_t*, int16_t*, size_t);
void vv_mul_i32(int32_t*, int32_t*, int32_t*, size_t);
void vv_mul_i64(int64_t*, int64_t*, int64_t*, size_t);
void vv_mul_u8(uint8_t*, uint8_t*, uint8_t*, size_t);
void vv_mul_u16(uint16_t*, uint16_t*, uint16_t*, size_t);
void vv_mul_u32(uint32_t*, uint32_t*, uint32_t*, size_t);
void vv_mul_u64(uint64_t*, uint64_t*, uint64_t*, size_t);
void vv_mul_f(float_t*, float_t*, float_t*, size_t);
void vv_mul_d(double_t*, double_t*, double_t*, size_t);
void vs_mul_b(bool*,bool,bool*,size_t);
void vs_mul_i8(int8_t*, int8_t, int8_t*, size_t);
void vs_mul_i16(int16_t*, int16_t, int16_t*, size_t);
void vs_mul_i32(int32_t*, int32_t, int32_t*, size_t);
void vs_mul_i64(int64_t*, int64_t, int64_t*, size_t);
void vs_mul_u8(uint8_t*, uint8_t, uint8_t*, size_t);
void vs_mul_u16(uint16_t*, uint16_t, uint16_t*, size_t);
void vs_mul_u32(uint32_t*, uint32_t, uint32_t*, size_t);
void vs_mul_u64(uint64_t*, uint64_t, uint64_t*, size_t);
void vs_mul_f(float_t*, float_t, float_t*, size_t);
void vs_mul_d(double_t*, double_t, double_t*, size_t);
void vv_div_b(bool*,bool*,bool*,size_t);
void vv_div_i8(int8_t*, int8_t*, int8_t*, size_t);
void vv_div_i16(int16_t*, int16_t*, int16_t*, size_t);
void vv_div_i32(int32_t*, int32_t*, int32_t*, size_t);
void vv_div_i64(int64_t*, int64_t*, int64_t*, size_t);
void vv_div_u8(uint8_t*, uint8_t*, uint8_t*, size_t);
void vv_div_u16(uint16_t*, uint16_t*, uint16_t*, size_t);
void vv_div_u32(uint32_t*, uint32_t*, uint32_t*, size_t);
void vv_div_u64(uint64_t*, uint64_t*, uint64_t*, size_t);
void vv_div_f(float_t*, float_t*, float_t*, size_t);
void vv_div_d(double_t*, double_t*, double_t*, size_t);
void vs_div_b(bool*,bool,bool*,size_t);
void vs_div_i8(int8_t*, int8_t, int8_t*, size_t);
void vs_div_i16(int16_t*, int16_t, int16_t*, size_t);
void vs_div_i32(int32_t*, int32_t, int32_t*, size_t);
void vs_div_i64(int64_t*, int64_t, int64_t*, size_t);
void vs_div_u8(uint8_t*, uint8_t, uint8_t*, size_t);
void vs_div_u16(uint16_t*, uint16_t, uint16_t*, size_t);
void vs_div_u32(uint32_t*, uint32_t, uint32_t*, size_t);
void vs_div_u64(uint64_t*, uint64_t, uint64_t*, size_t);
void vs_div_f(float_t*, float_t, float_t*, size_t);
void vs_div_d(double_t*, double_t, double_t*, size_t);
void sv_div_b(bool,bool*,bool*,size_t);
void sv_div_i8(int8_t, int8_t*, int8_t*, size_t);
void sv_div_i16(int16_t, int16_t*, int16_t*, size_t);
void sv_div_i32(int32_t, int32_t*, int32_t*, size_t);
void sv_div_i64(int64_t, int64_t*, int64_t*, size_t);
void sv_div_u8(uint8_t, uint8_t*, uint8_t*, size_t);
void sv_div_u16(uint16_t, uint16_t*, uint16_t*, size_t);
void sv_div_u32(uint32_t, uint32_t*, uint32_t*, size_t);
void sv_div_u64(uint64_t, uint64_t*, uint64_t*, size_t);
void sv_div_f(float_t, float_t*, float_t*, size_t);
void sv_div_d(double_t, double_t*, double_t*, size_t);
void h_sum_b(bool*, size_t*, size_t, size_t);
void h_sum_i8(int8_t*, int8_t*, size_t, size_t);
void h_sum_i16(int16_t*, int16_t*, size_t, size_t);
void h_sum_i32(int32_t*, int32_t*, size_t, size_t);
void h_sum_i64(int64_t*, int64_t*, size_t, size_t);
void h_sum_u8(uint8_t*, uint8_t*, size_t, size_t);
void h_sum_u16(uint16_t*, uint16_t*, size_t, size_t);
void h_sum_u32(uint32_t*, uint32_t*, size_t, size_t);
void h_sum_u64(uint64_t*, uint64_t*, size_t, size_t);
void h_sum_f(float_t*, float_t*, size_t, size_t);
void h_sum_d(double_t*, double_t*, size_t, size_t);
void v_sum_b(bool*, size_t*, size_t, size_t);
void v_sum_i8(int8_t*, int8_t*, size_t, size_t);
void v_sum_i16(int16_t*, int16_t*, size_t, size_t);
void v_sum_i32(int32_t*, int32_t*, size_t, size_t);
void v_sum_i64(int64_t*, int64_t*, size_t, size_t);
void v_sum_u8(uint8_t*, uint8_t*, size_t, size_t);
void v_sum_u16(uint16_t*, uint16_t*, size_t, size_t);
void v_sum_u32(uint32_t*, uint32_t*, size_t, size_t);
void v_sum_u64(uint64_t*, uint64_t*, size_t, size_t);
void v_sum_f(float_t*, float_t*, size_t, size_t);
void v_sum_d(double_t*, double_t*, size_t, size_t);
void dot_b(bool*, bool*, bool*, size_t, size_t, size_t);
void dot_i8(int8_t*, int8_t*, int8_t*, size_t, size_t, size_t);
void dot_i16(int16_t*, int16_t*, int16_t*, size_t, size_t, size_t);
void dot_i32(int32_t*, int32_t*, int32_t*, size_t, size_t, size_t);
void dot_i64(int64_t*, int64_t*, int64_t*, size_t, size_t, size_t);
void dot_u8(uint8_t*, uint8_t*, uint8_t*, size_t, size_t, size_t);
void dot_u16(uint16_t*, uint16_t*, uint16_t*, size_t, size_t, size_t);
void dot_u32(uint32_t*, uint32_t*, uint32_t*, size_t, size_t, size_t);
void dot_u64(uint64_t*, uint64_t*, uint64_t*, size_t, size_t, size_t);
void dot_f(float_t*, float_t*, float_t*, size_t, size_t, size_t);
void dot_d(double_t*, double_t*, double_t*, size_t, size_t, size_t);

#ifdef __cplusplus
}
#endif

#endif