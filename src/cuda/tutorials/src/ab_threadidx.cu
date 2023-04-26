#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <iostream>
#include "ab_threadidx/module.cuh"

__global__ void print_threadidx() {
    printf("threadIdx.x : %d, threadIdx.y : %d, threadIdx.z : %d\n",
        threadIdx.x, threadIdx.y, threadIdx.z);
}

void play_threadidx(){
    int nx = 16, ny = 16;
    dim3 block(8,8);
    dim3 grid(nx/block.x, ny/block.y);

    print_threadidx <<<grid,block>>> ();

    cudaDeviceSynchronize();
    cudaDeviceReset();
}