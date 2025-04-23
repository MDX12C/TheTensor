#include "define.h"

#ifndef PARALLEL_CUH
#define PARALLEL_CUH 1

#include <cuda.h>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>

#ifdef __cplusplus
extern "C" {
#endif

void vv_add_i32(int32_t*, int32_t*, int32_t*, size_t);

#ifdef __cplusplus
}
#endif

#endif