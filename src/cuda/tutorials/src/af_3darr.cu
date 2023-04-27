#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "af_3darr/module.cuh"

__global__ void unique_gid_calc_block2d_grid3d(int * data){
    int tid = blockDim.x * threadIdx.y + threadIdx.x;
    int num_threads_in_block = blockDim.x * blockDim.y;
    int block_offset = blockIdx.x * num_threads_in_block;
    int num_threads_in_row = num_threads_in_block * gridDim.x;
    int row_offset = num_threads_in_row * blockIdx.y;
    int num_threads_in_xy = num_threads_in_row * gridDim.y;
    int xy_offset = num_threads_in_xy *  blockIdx.z;

    int gid = xy_offset + row_offset + block_offset + tid;
    printf("blockIdx.x : %d, blockIdx.y : %d, blockIdx.z : %d, threadIdx.x : %d, threadIdx.z : %d, gid : %d - data : %d \n",
        blockIdx.x, blockIdx.y, blockIdx.z, threadIdx.x, threadIdx.y, gid, data[gid]);

}

void access_3d_arr() {
    int array_size = 64;
    int array_byte_size = sizeof(int) * array_size;
    int * h_data;
    h_data = (int*)malloc(array_byte_size);

    time_t t;
    srand((unsigned)time(&t));
    for (int i=0; i<array_size; i++) {
        h_data[i] = rand() & 0xff;
    }

    int * d_data; // device data
    cudaMalloc((void**)&d_data, array_byte_size);
    cudaMemcpy(d_data, h_data, array_byte_size, cudaMemcpyHostToDevice);

    dim3 block(2,2);
    dim3 grid(2,2,4);

    unique_gid_calc_block2d_grid3d <<<grid,block>>> (d_data);
    cudaDeviceSynchronize();

    cudaDeviceReset();
}