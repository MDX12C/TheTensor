#include "thetensor/define.h"
#include <stdbool.h>

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