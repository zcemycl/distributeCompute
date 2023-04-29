#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

__global__ void no_divergence_code() {
    int gid = threadIdx.x + blockDim.x*blockIdx.x;

    float a,b;
    a = b = 0;

    // printf("a: %f, b: %f, gid: %d", a, b, gid);
}


int main(){
    printf("\n---------------------WARP DIVERGENCE EXAMPLE--------------------\n\n");

    int size = 1<<22;

    dim3 block(128);
    dim3 grid((size+block.x-1)/block.x);

    no_divergence_code <<<grid,block>>> ();
    cudaDeviceSynchronize();

    cudaDeviceReset(); 

    return 0;
}
