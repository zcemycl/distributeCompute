#include "ag_sum_arr/module.cuh"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <cstring>

__global__ void sum_arr_gpu(int * a, int * b, int * c, int size){
    // 1d grid, 1d block, all along x
    int gid = blockIdx.x * blockDim.x + threadIdx.x;

    if (gid < size)
        c[gid] = a[gid] + b[gid];

}

void play_sum_arr_gpu(){
    int size = 10000;
    int block_size = 128;

    int NO_BYTES = size * sizeof(int);

    // host pointer
    int *h_a, *h_b, *gpu_results;
    h_a = (int*)malloc(NO_BYTES);
    h_b = (int*)malloc(NO_BYTES);
    gpu_results = (int*)malloc(NO_BYTES);

    time_t t;
    srand((unsigned)time(&t));
    for (int i=0; i<size; i++){
        h_a[i] = (int)(rand() & 0xFF);
        if (i<=10)
            std::cout << h_a[i] << " ";
    }
    std::cout << std::endl;
    for (int i=0; i<size; i++){
        h_b[i] = (int)(rand() & 0xFF);
        if (i<=10)
            std::cout << h_b[i] << " ";
    }
    std::cout << std::endl;
    memset(gpu_results, 0, NO_BYTES);

    // device pointer
    int *d_a, *d_b, *d_c;
    cudaMalloc((int **)&d_a, NO_BYTES);
    cudaMalloc((int **)&d_b, NO_BYTES);
    cudaMalloc((int **)&d_c, NO_BYTES);

    cudaMemcpy(d_a, h_a, NO_BYTES, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, h_b, NO_BYTES, cudaMemcpyHostToDevice);

    //launch the grid
    dim3 block(block_size);
    dim3 grid((size/block.x) + 1);

    sum_arr_gpu <<<grid,block>>> (d_a, d_b, d_c, size);
    cudaDeviceSynchronize();

    cudaMemcpy(gpu_results, d_c, NO_BYTES, cudaMemcpyDeviceToHost);

    cudaFree(d_c);
    cudaFree(d_b);
    cudaFree(d_a);

    for (int i=0; i<11; i++){
        std::cout << gpu_results[i] << " ";
    }
    std::cout << std::endl;

    free(gpu_results);
    free(h_a);
    free(h_b);

    cudaDeviceReset();

}