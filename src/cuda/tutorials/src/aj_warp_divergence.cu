#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "aj_warp_divergence/module.cuh"

__global__ void code_without_divergence() {
    int gid = threadIdx.x + blockDim.x*blockIdx.x;

    float a,b;
    a = b = 0;

    int warp_id = gid/32;

    if (warp_id % 2 == 0){
        a = 100.0;
        b = 50.0;
    } else {
        a = 200.0;
        b = 75.0;
    }
}

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
}


void test_warp_divergence(){
    printf("\n---------------------WARP DIVERGENCE EXAMPLE--------------------\n\n");

    int size = 1<<22;

    dim3 block(128);
    dim3 grid((size+block.x-1)/block.x);

    code_without_divergence <<<grid,block>>> ();
    cudaDeviceSynchronize();

    divergence_code <<<grid,block>>> ();
    cudaDeviceSynchronize();

    cudaDeviceReset(); 
}