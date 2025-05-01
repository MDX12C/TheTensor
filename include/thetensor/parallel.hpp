#include "define.hpp"
#ifndef PARALLEL_HH
#include "parallel.cuh"
#define PARALLEL_HH 1
namespace basic_math {
constexpr bool CUDA_DEFAULT = __CUDA_MODE__;
// c = a + b
template <typename T, bool CUDA = CUDA_DEFAULT>
inline void add(T* const& __a, T* const& __b, T* const& __c,
                size_t const& __size) {
  if constexpr (CUDA)
    if constexpr (std::is_same_v<T, bool>)
      return vv_add_b(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, int8_t>)
      return vv_add_i8(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, int16_t>)
      return vv_add_i16(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, int32_t>)
      return vv_add_i32(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, int64_t>)
      return vv_add_i64(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, uint8_t>)
      return vv_add_u8(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, uint16_t>)
      return vv_add_u16(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, uint32_t>)
      return vv_add_u32(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, uint64_t>)
      return vv_add_u64(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, float_t>)
      return vv_add_f(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, double_t>)
      return vv_add_d(__a, __b, __c, __size);
    else
      throw system_message::Error("unsupport type of parallel operation");
  else
    for (size_t i = 0; i < __size; i++) ADD(__a[i], __b[i], __c[i], T)
  return;
}
// c = a + b
template <typename T, bool CUDA = CUDA_DEFAULT>
inline void add(T* const& __a, T const& __b, T* const& __c,
                size_t const& __size) {
  if constexpr (CUDA)
    if constexpr (std::is_same_v<T, bool>)
      return vs_add_b(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, int8_t>)
      return vs_add_i8(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, int16_t>)
      return vs_add_i16(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, int32_t>)
      return vs_add_i32(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, int64_t>)
      return vs_add_i64(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, uint8_t>)
      return vs_add_u8(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, uint16_t>)
      return vs_add_u16(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, uint32_t>)
      return vs_add_u32(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, uint64_t>)
      return vs_add_u64(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, float_t>)
      return vs_add_f(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, double_t>)
      return vs_add_d(__a, __b, __c, __size);
    else
      throw system_message::Error("unsupport type of parallel operation");
  else
    for (size_t i = 0; i < __size; i++) ADD(__a[i], __b, __c[i], T)
  return;
}
// c = a + b
template <typename T, bool CUDA = CUDA_DEFAULT>
inline void add(T const& __a, T* const& __b, T* const& __c,
                size_t const& __size) {
  if constexpr (CUDA)
    if constexpr (std::is_same_v<T, bool>)
      return vs_add_b(__b, __a, __c, __size);
    else if constexpr (std::is_same_v<T, int8_t>)
      return vs_add_i8(__b, __a, __c, __size);
    else if constexpr (std::is_same_v<T, int16_t>)
      return vs_add_i16(__b, __a, __c, __size);
    else if constexpr (std::is_same_v<T, int32_t>)
      return vs_add_i32(__b, __a, __c, __size);
    else if constexpr (std::is_same_v<T, int64_t>)
      return vs_add_i64(__b, __a, __c, __size);
    else if constexpr (std::is_same_v<T, uint8_t>)
      return vs_add_u8(__b, __a, __c, __size);
    else if constexpr (std::is_same_v<T, uint16_t>)
      return vs_add_u16(__b, __a, __c, __size);
    else if constexpr (std::is_same_v<T, uint32_t>)
      return vs_add_u32(__b, __a, __c, __size);
    else if constexpr (std::is_same_v<T, uint64_t>)
      return vs_add_u64(__b, __a, __c, __size);
    else if constexpr (std::is_same_v<T, float_t>)
      return vs_add_f(__b, __a, __c, __size);
    else if constexpr (std::is_same_v<T, double_t>)
      return vs_add_d(__b, __a, __c, __size);
    else
      throw system_message::Error("unsupport type of parallel operation");
  else
    for (size_t i = 0; i < __size; i++) ADD(__a, __b[i], __c[i], T)
  return;
}
// c = a - b
template <typename T, bool CUDA = CUDA_DEFAULT>
inline void mns(T* const& __a, T* const& __b, T* const& __c,
                size_t const& __size) {
  if constexpr (CUDA)
    if constexpr (std::is_same_v<T, bool>)
      return vv_mns_b(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, int8_t>)
      return vv_mns_i8(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, int16_t>)
      return vv_mns_i16(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, int32_t>)
      return vv_mns_i32(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, int64_t>)
      return vv_mns_i64(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, uint8_t>)
      return vv_mns_u8(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, uint16_t>)
      return vv_mns_u16(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, uint32_t>)
      return vv_mns_u32(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, uint64_t>)
      return vv_mns_u64(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, float_t>)
      return vv_mns_f(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, double_t>)
      return vv_mns_d(__a, __b, __c, __size);
    else
      throw system_message::Error("unsupport type of parallel operation");
  else
    for (size_t i = 0; i < __size; i++) MNS(__a[i], __b[i], __c[i], T)
  return;
}
// c = a - b
template <typename T, bool CUDA = CUDA_DEFAULT>
inline void mns(T* const& __a, T const& __b, T* const& __c,
                size_t const& __size) {
  if constexpr (CUDA)
    if constexpr (std::is_same_v<T, bool>)
      return vs_mns_b(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, int8_t>)
      return vs_mns_i8(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, int16_t>)
      return vs_mns_i16(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, int32_t>)
      return vs_mns_i32(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, int64_t>)
      return vs_mns_i64(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, uint8_t>)
      return vs_mns_u8(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, uint16_t>)
      return vs_mns_u16(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, uint32_t>)
      return vs_mns_u32(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, uint64_t>)
      return vs_mns_u64(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, float_t>)
      return vs_mns_f(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, double_t>)
      return vs_mns_d(__a, __b, __c, __size);
    else
      throw system_message::Error("unsupport type of parallel operation");
  else
    for (size_t i = 0; i < __size; i++) MNS(__a[i], __b, __c[i], T)
  return;
}
// c = a - b
template <typename T, bool CUDA = CUDA_DEFAULT>
inline void mns(T const& __a, T* const& __b, T* const& __c,
                size_t const& __size) {
  if constexpr (CUDA)
    if constexpr (std::is_same_v<T, bool>)
      return sv_mns_b(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, int8_t>)
      return sv_mns_i8(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, int16_t>)
      return sv_mns_i16(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, int32_t>)
      return sv_mns_i32(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, int64_t>)
      return sv_mns_i64(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, uint8_t>)
      return sv_mns_u8(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, uint16_t>)
      return sv_mns_u16(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, uint32_t>)
      return sv_mns_u32(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, uint64_t>)
      return sv_mns_u64(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, float_t>)
      return sv_mns_f(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, double_t>)
      return sv_mns_d(__a, __b, __c, __size);
    else
      throw system_message::Error("unsupport type of parallel operation");
  else
    for (size_t i = 0; i < __size; i++) MNS(__a, __b[i], __c[i], T)
  return;
}
// c = a * b
template <typename T, bool CUDA = CUDA_DEFAULT>
inline void mul(T* const& __a, T* const& __b, T* const& __c,
                size_t const& __size) {
  if constexpr (CUDA)
    if constexpr (std::is_same_v<T, bool>)
      return vv_mul_b(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, int8_t>)
      return vv_mul_i8(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, int16_t>)
      return vv_mul_i16(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, int32_t>)
      return vv_mul_i32(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, int64_t>)
      return vv_mul_i64(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, uint8_t>)
      return vv_mul_u8(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, uint16_t>)
      return vv_mul_u16(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, uint32_t>)
      return vv_mul_u32(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, uint64_t>)
      return vv_mul_u64(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, float_t>)
      return vv_mul_f(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, double_t>)
      return vv_mul_d(__a, __b, __c, __size);
    else
      throw system_message::Error("unsupport type of parallel operation");
  else
    for (size_t i = 0; i < __size; i++) MUL(__a[i], __b[i], __c[i], T)
  return;
}
// c = a * b
template <typename T, bool CUDA = CUDA_DEFAULT>
inline void mul(T* const& __a, T const& __b, T* const& __c,
                size_t const& __size) {
  if constexpr (CUDA)
    if constexpr (std::is_same_v<T, bool>)
      return vs_mul_b(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, int8_t>)
      return vs_mul_i8(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, int16_t>)
      return vs_mul_i16(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, int32_t>)
      return vs_mul_i32(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, int64_t>)
      return vs_mul_i64(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, uint8_t>)
      return vs_mul_u8(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, uint16_t>)
      return vs_mul_u16(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, uint32_t>)
      return vs_mul_u32(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, uint64_t>)
      return vs_mul_u64(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, float_t>)
      return vs_mul_f(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, double_t>)
      return vs_mul_d(__a, __b, __c, __size);
    else
      throw system_message::Error("unsupport type of parallel operation");
  else
    for (size_t i = 0; i < __size; i++) MUL(__a[i], __b, __c[i], T)
  return;
}
// c = a * b
template <typename T, bool CUDA = CUDA_DEFAULT>
inline void mul(T const& __a, T* const& __b, T* const& __c,
                size_t const& __size) {
  if constexpr (CUDA)
    if constexpr (std::is_same_v<T, bool>)
      return vs_mul_b(__b, __a, __c, __size);
    else if constexpr (std::is_same_v<T, int8_t>)
      return vs_mul_i8(__b, __a, __c, __size);
    else if constexpr (std::is_same_v<T, int16_t>)
      return vs_mul_i16(__b, __a, __c, __size);
    else if constexpr (std::is_same_v<T, int32_t>)
      return vs_mul_i32(__b, __a, __c, __size);
    else if constexpr (std::is_same_v<T, int64_t>)
      return vs_mul_i64(__b, __a, __c, __size);
    else if constexpr (std::is_same_v<T, uint8_t>)
      return vs_mul_u8(__b, __a, __c, __size);
    else if constexpr (std::is_same_v<T, uint16_t>)
      return vs_mul_u16(__b, __a, __c, __size);
    else if constexpr (std::is_same_v<T, uint32_t>)
      return vs_mul_u32(__b, __a, __c, __size);
    else if constexpr (std::is_same_v<T, uint64_t>)
      return vs_mul_u64(__b, __a, __c, __size);
    else if constexpr (std::is_same_v<T, float_t>)
      return vs_mul_f(__b, __a, __c, __size);
    else if constexpr (std::is_same_v<T, double_t>)
      return vs_mul_d(__b, __a, __c, __size);
    else
      throw system_message::Error("unsupport type of parallel operation");
  else
    for (size_t i = 0; i < __size; i++) MUL(__a, __b[i], __c[i], T)
  return;
}
// c = a / b
template <typename T, bool CUDA = CUDA_DEFAULT>
inline void div(T* const& __a, T* const& __b, T* const& __c,
                size_t const& __size) {
  if constexpr (CUDA)
    if constexpr (std::is_same_v<T, bool>)
      return vv_div_b(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, int8_t>)
      return vv_div_i8(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, int16_t>)
      return vv_div_i16(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, int32_t>)
      return vv_div_i32(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, int64_t>)
      return vv_div_i64(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, uint8_t>)
      return vv_div_u8(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, uint16_t>)
      return vv_div_u16(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, uint32_t>)
      return vv_div_u32(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, uint64_t>)
      return vv_div_u64(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, float_t>)
      return vv_div_f(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, double_t>)
      return vv_div_d(__a, __b, __c, __size);
    else
      throw system_message::Error("unsupport type of parallel operation");
  else
    for (size_t i = 0; i < __size; i++) DIV(__a[i], __b[i], __c[i], T)
  return;
}
// c = a / b
template <typename T, bool CUDA = CUDA_DEFAULT>
inline void div(T* const& __a, T const& __b, T* const& __c,
                size_t const& __size) {
  if constexpr (CUDA)
    if constexpr (std::is_same_v<T, bool>)
      return vs_div_b(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, int8_t>)
      return vs_div_i8(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, int16_t>)
      return vs_div_i16(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, int32_t>)
      return vs_div_i32(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, int64_t>)
      return vs_div_i64(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, uint8_t>)
      return vs_div_u8(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, uint16_t>)
      return vs_div_u16(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, uint32_t>)
      return vs_div_u32(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, uint64_t>)
      return vs_div_u64(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, float_t>)
      return vs_div_f(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, double_t>)
      return vs_div_d(__a, __b, __c, __size);
    else
      throw system_message::Error("unsupport type of parallel operation");
  else
    for (size_t i = 0; i < __size; i++) DIV(__a[i], __b, __c[i], T)
  return;
}
// c = a / b
template <typename T, bool CUDA = CUDA_DEFAULT>
inline void div(T const& __a, T* const& __b, T* const& __c,
                size_t const& __size) {
  if constexpr (CUDA)
    if constexpr (std::is_same_v<T, bool>)
      return sv_div_b(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, int8_t>)
      return sv_div_i8(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, int16_t>)
      return sv_div_i16(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, int32_t>)
      return sv_div_i32(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, int64_t>)
      return sv_div_i64(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, uint8_t>)
      return sv_div_u8(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, uint16_t>)
      return sv_div_u16(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, uint32_t>)
      return sv_div_u32(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, uint64_t>)
      return sv_div_u64(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, float_t>)
      return sv_div_f(__a, __b, __c, __size);
    else if constexpr (std::is_same_v<T, double_t>)
      return sv_div_d(__a, __b, __c, __size);
    else
      throw system_message::Error("unsupport type of parallel operation");
  else
    for (size_t i = 0; i < __size; i++) DIV(__a, __b[i], __c[i], T)
  return;
}
/**
 * @brief put the horizontal summer of matrix into vector
 * @param __lib the pointer of matrix
 * @param __obj the pointer of vector
 * @param __row row of the matrix
 * @param __col col of the matrix
 */
template <typename T, bool CUDA = CUDA_DEFAULT>
inline void hSum(T* const& __lib, void* const& __obj, size_t const& __row,
                 size_t const& __col) {
  if constexpr (CUDA)
    if constexpr (std::is_same_v<T, bool>)
      return h_sum_b(__lib, static_cast<size_t*>(__obj), __row, __col);
    else if constexpr (std::is_same_v<T, int8_t>)
      return h_sum_i8(__lib, static_cast<T*>(__obj), __row, __col);
    else if constexpr (std::is_same_v<T, int16_t>)
      return h_sum_i16(__lib, static_cast<T*>(__obj), __row, __col);
    else if constexpr (std::is_same_v<T, int32_t>)
      return h_sum_i32(__lib, static_cast<T*>(__obj), __row, __col);
    else if constexpr (std::is_same_v<T, int64_t>)
      return h_sum_i64(__lib, static_cast<T*>(__obj), __row, __col);
    else if constexpr (std::is_same_v<T, uint8_t>)
      return h_sum_u8(__lib, static_cast<T*>(__obj), __row, __col);
    else if constexpr (std::is_same_v<T, uint16_t>)
      return h_sum_u16(__lib, static_cast<T*>(__obj), __row, __col);
    else if constexpr (std::is_same_v<T, uint32_t>)
      return h_sum_u32(__lib, static_cast<T*>(__obj), __row, __col);
    else if constexpr (std::is_same_v<T, uint64_t>)
      return h_sum_u64(__lib, static_cast<T*>(__obj), __row, __col);
    else if constexpr (std::is_same_v<T, float_t>)
      return h_sum_f(__lib, static_cast<T*>(__obj), __row, __col);
    else if constexpr (std::is_same_v<T, double_t>)
      return h_sum_d(__lib, static_cast<T*>(__obj), __row, __col);
    else
      throw system_message::Error("unsupport type of parallel operation");
  else {
    if constexpr (std::is_same_v<T, bool>) {
      auto obj = static_cast<size_t*>(__obj);
      for (size_t i = 0, j = 0; j < __row; j++)
        for (size_t w = 0; w < __col; w++, i++) obj[j] += __lib[i] ? 1 : 0;
    } else {
      auto obj = static_cast<T*>(__obj);
      for (size_t i = 0, j = 0; j < __row; j++)
        for (size_t w = 0; w < __col; w++, i++) obj[j] += __lib[i];
    }
  }
  return;
}
/**
 * @brief put vertical summer of matrix into vector
 * @param __lib the pointer of matrix
 * @param __obj the pointer of vector
 * @param __row row of the matrix
 * @param __col col of the matrix
 */
template <typename T, bool CUDA = CUDA_DEFAULT>
inline void vSum(T* const& __lib, void* const& __obj, size_t const& __row,
                 size_t const& __col) {
  if constexpr (CUDA)
    if constexpr (std::is_same_v<T, bool>)
      return v_sum_b(__lib, static_cast<size_t*>(__obj), __row, __col);
    else if constexpr (std::is_same_v<T, int8_t>)
      return v_sum_i8(__lib, static_cast<T*>(__obj), __row, __col);
    else if constexpr (std::is_same_v<T, int16_t>)
      return v_sum_i16(__lib, static_cast<T*>(__obj), __row, __col);
    else if constexpr (std::is_same_v<T, int32_t>)
      return v_sum_i32(__lib, static_cast<T*>(__obj), __row, __col);
    else if constexpr (std::is_same_v<T, int64_t>)
      return v_sum_i64(__lib, static_cast<T*>(__obj), __row, __col);
    else if constexpr (std::is_same_v<T, uint8_t>)
      return v_sum_u8(__lib, static_cast<T*>(__obj), __row, __col);
    else if constexpr (std::is_same_v<T, uint16_t>)
      return v_sum_u16(__lib, static_cast<T*>(__obj), __row, __col);
    else if constexpr (std::is_same_v<T, uint32_t>)
      return v_sum_u32(__lib, static_cast<T*>(__obj), __row, __col);
    else if constexpr (std::is_same_v<T, uint64_t>)
      return v_sum_u64(__lib, static_cast<T*>(__obj), __row, __col);
    else if constexpr (std::is_same_v<T, float_t>)
      return v_sum_f(__lib, static_cast<T*>(__obj), __row, __col);
    else if constexpr (std::is_same_v<T, double_t>)
      return v_sum_d(__lib, static_cast<T*>(__obj), __row, __col);
    else
      throw system_message::Error("unsupport type of parallel operation");
  else {
    if constexpr (std::is_same_v<T, bool>) {
      size_t total = __row * __col;
      auto obj = static_cast<size_t*>(__obj);
      for (size_t i = 0, j = 0; i < total; i++, j++) {
        if (j == __col) j = 0;
        obj[j] += __lib[i] ? 1 : 0;
      }
    } else {
      size_t total = __row * __col;
      auto obj = static_cast<T*>(__obj);
      for (size_t i = 0, j = 0; i < total; i++, j++) {
        if (j == __col) j = 0;
        obj[j] += __lib[i];
      }
    }
  }
  return;
}
template <typename T, bool CUDA = CUDA_DEFAULT>
inline void mDot(T* const& __a, T* const& __b, T* const& __c,
                 size_t const& __row, size_t const& __line,
                 size_t const& __col) {
  if constexpr (CUDA)
    if constexpr (std::is_same_v<T, bool>)
      return dot_b(__a, __b, __c, __row, __line, __col);
    else if constexpr (std::is_same_v<T, int8_t>)
      return dot_i8(__a, __b, __c, __row, __line, __col);
    else if constexpr (std::is_same_v<T, int16_t>)
      return dot_i16(__a, __b, __c, __row, __line, __col);
    else if constexpr (std::is_same_v<T, int32_t>)
      return dot_i32(__a, __b, __c, __row, __line, __col);
    else if constexpr (std::is_same_v<T, int64_t>)
      return dot_i64(__a, __b, __c, __row, __line, __col);
    else if constexpr (std::is_same_v<T, uint8_t>)
      return dot_u8(__a, __b, __c, __row, __line, __col);
    else if constexpr (std::is_same_v<T, uint16_t>)
      return dot_u16(__a, __b, __c, __row, __line, __col);
    else if constexpr (std::is_same_v<T, uint32_t>)
      return dot_u32(__a, __b, __c, __row, __line, __col);
    else if constexpr (std::is_same_v<T, uint64_t>)
      return dot_u64(__a, __b, __c, __row, __line, __col);
    else if constexpr (std::is_same_v<T, float_t>)
      return dot_f(__a, __b, __c, __row, __line, __col);
    else if constexpr (std::is_same_v<T, double_t>)
      return dot_d(__a, __b, __c, __row, __line, __col);
    else
      throw system_message::Error("unsupport type of parallel operation");
  else {
    if constexpr (std::is_same_v<T, bool>) {
      T *beta, *gamma, *alpha = __a;
      for (size_t i = 0, row = 0; row < __row; row++, alpha += __line) {
        beta = __b;
        for (size_t col = 0; col < __col; i++, col++, beta++) {
          gamma = beta;
          for (size_t k = 0; k < __line; k++, gamma += __col)
            __c[i] |= alpha[k] & (*gamma);
        }
      }
    } else {
      T *beta, *gamma, *alpha = __a;
      for (size_t i = 0, row = 0; row < __row; row++, alpha += __line) {
        beta = __b;
        for (size_t col = 0; col < __col; i++, col++, beta++) {
          gamma = beta;
          for (size_t k = 0; k < __line; k++, gamma += __col)
            __c[i] += alpha[k] * (*gamma);
        }
      }
    }
  }
  return;
}

}  // namespace basic_math
#endif