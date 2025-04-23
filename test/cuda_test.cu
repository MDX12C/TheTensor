#include <cuda.h>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <stdio.h>
#include <float.h>
#include <stdint.h>

typedef int Type;
__global__ void mul(Type* __alpha,Type* __beta,Type* __gamma,size_t __lenth){
  auto i=blockDim.x*blockIdx.x+threadIdx.x;
  if (i<__lenth)__gamma[i]=__beta[i]*__alpha[i];
}
signed main() {
  size_t const LENTH=1048576;
  size_t const THREADS=1024;
  size_t const BLOCKS=LENTH/THREADS;
  Type* alpha=(Type*)malloc(LENTH*sizeof(Type));
  Type* beta=(Type*)malloc(LENTH*sizeof(Type));
  Type* gamma=(Type*)malloc(LENTH*sizeof(Type));
  for(size_t i=0;i<LENTH;i++)alpha[i]=beta[i]=16;
  mul<<<BLOCKS,THREADS>>>(alpha,beta,gamma,LENTH);
  cudaDeviceSynchronize();
  for(size_t i=0;i<LENTH;i++){
    if (gamma[i]!=(alpha[i]*beta[i])){
      printf("Error operate when i=%ld\n",i);
      break;
    }
  }
  printf("End test");
  free(alpha);
  free(beta);
  free(gamma);
  return 0;
}