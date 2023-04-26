#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <iostream>

__global__ void hello_cuda(){
    printf("Hello CUDA world \n");
}

void play_hello_cuda() {
    std::cout << "aa. Hello Cuda ..." << std::endl;
    hello_cuda <<<1,4>>> ();
    cudaDeviceSynchronize();

    std::cout << "grid, block call 3x2, 1x1, 1x1..." << std::endl;
    dim3 block(2);
    dim3 grid(3);
    hello_cuda <<<grid,block>>> ();
    cudaDeviceSynchronize();

    std::cout << "grid, block call 2x8, 2x2, 1x1..." << std::endl;
    dim3 blockex(8,2,1);
    dim3 gridex(2,2,1);
    hello_cuda <<<gridex,blockex>>> ();
    cudaDeviceSynchronize();


    cudaDeviceReset();
}