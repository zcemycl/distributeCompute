#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "module.cuh"
#include <stdio.h>
#include <stdlib.h>

int main() {
    int size = 16;
    int byte_size = sizeof(int)*size;
    int h_data[] = {23,9,4,53,65,12,1,33,10,11,50,49,38,5,2,7};
    for (int i=0;i<size;i++){
        printf("%d ",h_data[i]);
    }
    printf("\n");

    int * d_data;
    cudaMalloc((void**)&d_data,byte_size);
    cudaMemcpy(d_data,h_data,byte_size,cudaMemcpyHostToDevice);

    dim3 block(2,2);
    dim3 grid(2,2);
    unique_gid_calc_2d <<<grid,block>>> (d_data);
    cudaDeviceSynchronize();
    cudaDeviceReset();

    return 0;
}