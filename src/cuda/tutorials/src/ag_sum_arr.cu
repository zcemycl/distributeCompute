#include "ag_sum_arr/module.cuh"
#include "common.hpp"
#include "common.cuh"
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

void sum_arr_cpu(int * a, int * b, int * c, int size){
    for (int i=0; i<size; i++)
        c[i] = a[i] + b[i];
}

void play_sum_arr_gpu(){
    cudaError error;
    int size = 10000;
    int block_size = 128;

    int NO_BYTES = size * sizeof(int);

    // host pointer
    int *h_a, *h_b, *gpu_results, *h_c;
    h_a = (int*)malloc(NO_BYTES);
    h_b = (int*)malloc(NO_BYTES);
    gpu_results = (int*)malloc(NO_BYTES);
    h_c = (int*)malloc(NO_BYTES);

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
    clock_t cpu_start, cpu_end;
    cpu_start = clock();
    sum_arr_cpu(h_a, h_b, h_c, size);
    cpu_end = clock();
    memset(gpu_results, 0, NO_BYTES);

    // device pointer
    int *d_a, *d_b, *d_c;
    error = cudaMalloc((int **)&d_a, NO_BYTES);
    if (error!=cudaSuccess)
        fprintf(stderr, "Error : %s\n", cudaGetErrorString(error));
    gpuErrchk(cudaMalloc((int **)&d_b, NO_BYTES));
    cudaMalloc((int **)&d_c, NO_BYTES);

    clock_t h2d_start, h2d_end;
    h2d_start = clock();
    cudaMemcpy(d_a, h_a, NO_BYTES, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, h_b, NO_BYTES, cudaMemcpyHostToDevice);
    h2d_end = clock();

    //launch the grid
    dim3 block(block_size);
    dim3 grid((size/block.x) + 1);

    clock_t gpu_start, gpu_end;
    gpu_start = clock();
    sum_arr_gpu <<<grid,block>>> (d_a, d_b, d_c, size);
    cudaDeviceSynchronize();
    gpu_end = clock();

    clock_t d2h_start, d2h_end;
    d2h_start = clock();
    cudaMemcpy(gpu_results, d_c, NO_BYTES, cudaMemcpyDeviceToHost);
    d2h_end = clock();

    compare_arrs(h_c, gpu_results, size);
    printf("Sum array CPU execution time : %4.6f \n", 
        (double)(double)(cpu_end-cpu_start)/CLOCKS_PER_SEC);
    printf("Sum array GPU execution time : %4.6f \n", 
        (double)(double)(gpu_end-gpu_start)/CLOCKS_PER_SEC);
    printf("htod mem transfer time : %4.6f \n", 
        (double)(double)(h2d_end-h2d_start)/CLOCKS_PER_SEC);
    printf("dtoh mem transfer time : %4.6f \n", 
        (double)(double)(d2h_end-d2h_start)/CLOCKS_PER_SEC);
    printf("Sum array GPU total execution time : %4.6f \n", 
        (double)(double)(d2h_end-h2d_start)/CLOCKS_PER_SEC);

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