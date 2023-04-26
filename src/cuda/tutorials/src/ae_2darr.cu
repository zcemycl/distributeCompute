#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "ae_2darr/module.cuh"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

__global__ void unique_gid_calc_2d(int * data){
    int tid = threadIdx.x;
    int block_offset = blockIdx.x * blockDim.x;
    int row_offset = blockDim.x * gridDim.x * blockIdx.y;

    int gid = row_offset + block_offset + tid;
    printf("blockIdx.x : %d, blockIdx.y : %d, threadIdx.x : %d, gid : %d - data : %d \n",
        blockIdx.x, blockIdx.y, tid, gid, data[gid]);

}

__global__ void unique_gid_calc_2d_2d(int * data){
    int tid = blockDim.x * threadIdx.y + threadIdx.x;
    int num_threads_in_block = blockDim.x * blockDim.y;
    int block_offset = blockIdx.x * num_threads_in_block;
    int num_threads_in_row = num_threads_in_block * gridDim.x;
    int row_offset = num_threads_in_row * blockIdx.y;

    int gid = row_offset + block_offset + tid;
    printf("blockIdx.x : %d, blockIdx.y : %d, threadIdx.x : %d, gid : %d - data : %d \n",
        blockIdx.x, blockIdx.y, tid, gid, data[gid]);

}

void access_2d_arr() {
    int array_size = 16;
    int array_byte_size = sizeof(int) * array_size;
    int h_data[] = {23,9,4,53,65,12,1,33,22,43,56,4,76,81,94,32}; // host data

    int * d_data; // device data
    cudaMalloc((void**)&d_data, array_byte_size);
    cudaMemcpy(d_data, h_data, array_byte_size, cudaMemcpyHostToDevice);

    dim3 block(4);
    dim3 grid(2,2);

    unique_gid_calc_2d <<<grid,block>>> (d_data);
    cudaDeviceSynchronize();
    
    dim3 block2(2,2);
    std::cout << "Grid: 2x2, Block: 2x2 ... " << std::endl;
    unique_gid_calc_2d_2d <<<grid,block2>>> (d_data);
    cudaDeviceSynchronize();
    cudaDeviceReset();


}

