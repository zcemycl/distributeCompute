#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

__global__ void divergence_code() {
    int gid = threadIdx.x + blockDim.x*blockIdx.x;

    float a,b;
    a = b = 0;

    if (gid % 2 == 0){
        a = 100.0;
        b = 50.0;
    } else {
        a = 200.0;
        b = 75.0;
    }

    // printf("a: %f, b: %f, gid: %d", a, b, gid);
}


int main(){
    printf("\n---------------------WARP DIVERGENCE EXAMPLE--------------------\n\n");

    int size = 1<<22;

    dim3 block(128);
    dim3 grid((size+block.x-1)/block.x);

    divergence_code <<<grid,block>>> ();
    cudaDeviceSynchronize();

    cudaDeviceReset(); 

    return 0;
}
