#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "ai_warp_details/module.cuh"


__global__ void warp_details() {
    int gid = threadIdx.x + blockDim.x*blockIdx.x
        + blockDim.x*gridDim.x*blockIdx.y;
    int local_warp_id = threadIdx.x/32;
    int global_block_id = blockIdx.x + gridDim.x*blockIdx.y;
    int warp_x = blockDim.x/32 + 1;
    int global_warp_id = threadIdx.x/32 + warp_x*blockIdx.x 
        + warp_x*gridDim.x*blockIdx.y;

    printf("tid : %d, bid.x : %d, bid.y : %d, gid : %d, lwid : %d, gbid : %d, gwid : %d\n",
        threadIdx.x, blockIdx.x, blockIdx.y, gid, local_warp_id, global_block_id, global_warp_id);
}

void print_warp_details(){
    dim3 block(42);
    dim3 grid(2,2);

    warp_details <<<grid,block>>> ();
    cudaDeviceSynchronize();

    cudaDeviceReset();
}