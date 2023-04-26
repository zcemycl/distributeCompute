#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <iostream>
#include "ac_blockgrid/module.cuh"

__global__ void print_blockgrid() {
    printf("blockIdx.x : %d, blockIdx.y : %d, blockIdx.z : %d, blockDim.x : %d, blockDim.y : %d, blockDim.z : %d, gridDim.x : %d, gridDim.y : %d, gridDim.z : %d\n",
        blockIdx.x, blockIdx.y, blockIdx.z, blockDim.x, blockDim.y, blockDim.z, gridDim.x, gridDim.y, gridDim.z);
}

void play_blockgrid(){
    int nx = 16, ny = 16;
    dim3 block(8,8);
    dim3 grid(nx/block.x, ny/block.y);

    print_blockgrid <<<grid,block>>> ();

    cudaDeviceSynchronize();
    cudaDeviceReset();
}