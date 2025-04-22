#ifndef DEFINE_H
#define DEFINE_H 1

/*constants*/
// #define DEBUG_MODE 1
// #define SPEED_MODE 1
// #define F16 1
// #define LIMIT_MODE 1

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
  int8_t i8;
  int16_t i16;
  int32_t i32;
  int64_t i64;
  uint8_t u8;
  uint16_t u16;
  uint32_t u32;
  uint64_t u64;
  float_t f;
  double_t d;
  printf("interal:\ni8= %d i16= %d i32= %d i64= %d\n", sizeof(int8_t),
         sizeof(int16_t), sizeof(int32_t), sizeof(int64_t));
  printf("unsigned interal:\nu8= %d u16= %d u32= %d u64= %d\n", sizeof(uint8_t),
         sizeof(uint16_t), sizeof(uint32_t), sizeof(uint64_t));
  printf("floating form: %d\nf= %d d= %d\n", FLT_EVAL_METHOD, sizeof(float_t),
         sizeof(double_t));
  return;
}
#ifdef __cplusplus
}
#endif
#endif