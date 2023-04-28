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
}

void print_warp_details(){

}