#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "module.cuh"
#include <stdio.h>
#include <stdlib.h>

__global__ void unique_gid_calc_2d(int * input){
    int tix = threadIdx.x;
    int tiy = threadIdx.y;
    int bx = blockDim.x;
    int by = blockDim.y;
    int block_offsety = bx*tiy;
    int col_offsetx = bx*by*blockIdx.x;
    int row_offsety = bx*by*gridDim.x*blockIdx.y;
    int gid = tix+block_offsety+col_offsetx+row_offsety;
    printf("gid: %d, value: %d\n",gid,input[gid]);
}

__global__ void square_arr_kernel(float *a, unsigned int numElements){
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < numElements)
        a[i] = a[i] * a[i];
}

void test(float *a, unsigned int numElements){
    size_t size = numElements * sizeof(float);
    float* a_device;

    cudaMalloc((void**)&a_device, size);
    cudaMemcpy(a_device, a, size, cudaMemcpyHostToDevice);

    int block_size = 256;
    int grid_size = (numElements + block_size - 1) / block_size;

    square_arr_kernel <<<grid_size, block_size>>> (a_device, numElements);

    cudaMemcpy(a, a_device, size, cudaMemcpyDeviceToHost);
    cudaFree(a_device);

}