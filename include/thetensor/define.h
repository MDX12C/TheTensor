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

#ifndef __GNUC__
#define __attribute__(x)printf("C:digit(%f)=%d\n", a, basic_math::intDigits(a));
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

extern inline void checkBaseType();

#ifdef __cplusplus
}
#endif
#endif