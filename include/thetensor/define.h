#ifndef DEFINE_H
#define DEFINE_H 1

/*constants*/
// #define DEBUG_MODE 1
// #define SPEED_MODE 1
// #define F16 1
// #define LIMIT_MODE 1
// #define CUDA_MODE

/*constants control*/
#ifndef DEBUG_MODE
#define __DEBUG_MODE__ 0
#else
#define __DEBUG_MODE__ 1
#endif
#ifndef SPEED_MODE
#define __SPEED_MODE__ 0
#else
#define __SPEED_MODE__ 1
#endif
#ifndef F16
#define __F16__ 0
#else
#define __F16__ 1
#endif
#ifndef LIMIT_MODE
#define __LIMIT_MODE__ 0
#else
#define __LIMIT_MODE__ 1
#endif
#ifndef CUDA_MODE
#define __CUDA_MODE__ 0
#else
#define __CUDA_MODE__ 1
#endif

#include <float.h>
#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <unistd.h>
#ifdef __cplusplus
extern "C" {
#endif
inline void checkBaseType() {
  bool b __attribute__((__unused__));
  int8_t i8 __attribute__((__unused__));
  int16_t i16 __attribute__((__unused__));
  int32_t i32 __attribute__((__unused__));
  int64_t i64 __attribute__((__unused__));
  uint8_t u8 __attribute__((__unused__));
  uint16_t u16 __attribute__((__unused__));
  uint32_t u32 __attribute__((__unused__));
  uint64_t u64 __attribute__((__unused__));
  float_t f __attribute__((__unused__));
  double_t d __attribute__((__unused__));
  printf("interal:\ni8= %ld i16= %ld i32= %ld i64= %ld\n", sizeof(int8_t),
         sizeof(int16_t), sizeof(int32_t), sizeof(int64_t));
  printf("unsigned interal:\nu8= %ld u16= %ld u32= %ld u64= %ld\n",
         sizeof(uint8_t), sizeof(uint16_t), sizeof(uint32_t), sizeof(uint64_t));
  printf("floating form: %d\nf= %ld d= %ld\n", FLT_EVAL_METHOD, sizeof(float_t),
         sizeof(double_t));
  return;
}

#ifdef __cplusplus
}
#endif
#endif