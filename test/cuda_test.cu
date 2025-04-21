#include <cuda.h>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <stdio.h>

__global__ void kernelFunction() { printf("the cuda kernel from %d\n",threadIdx.x); }
signed main() {
  printf("hello world\n");
  kernelFunction<<<10, 512>>>();
  cudaDeviceSynchronize();
  return 0;
}