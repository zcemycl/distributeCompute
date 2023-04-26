#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "ad_1darr/module.cuh"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

__global__ void unique_idx_calc_threadIdx(int * input) {
    int tid = threadIdx.x;
    printf("threadIdx : %d, value : %d\n", tid, input[tid]);
}

__global__ void unique_gid_calc(int * input) {
    int tid = threadIdx.x;
    int offset = blockIdx.x * blockDim.x;
    int gid = tid + offset;
    printf("blockIdx.x : %d, threadIdx.x : %d, gid : %d, value : %d \n", 
        blockIdx.x, tid, gid, input[gid]);
}

void access_1d_arr() {
    int array_size = 8;
    int array_byte_size = sizeof(int) * array_size;
    int h_data[] = {23,9,4,53,65,12,1,33}; // host data
    
    for (int i=0; i<array_size; i++) {
        std::cout << h_data[i] << " ";
    }
    std::cout << std::endl;

    int * d_data; // device data
    cudaMalloc((void**)&d_data, array_byte_size);
    cudaMemcpy(d_data, h_data, array_byte_size, cudaMemcpyHostToDevice);

    dim3 block(8);
    dim3 grid(1);

    unique_idx_calc_threadIdx <<<grid,block>>> (d_data);
    cudaDeviceSynchronize();

    dim3 block_4x2(4);
    dim3 grid_4x2(2);

    unique_gid_calc <<<grid_4x2,block_4x2>>> (d_data);
    cudaDeviceSynchronize();
    

    cudaDeviceReset();
}