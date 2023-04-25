#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>

__global__ void hello_cuda(){
    printf("Hello CUDA world \n");
}

void play_hello_cuda() {
    hello_cuda <<<1,20>>> ();
    cudaDeviceSynchronize();

    cudaDeviceReset();
}