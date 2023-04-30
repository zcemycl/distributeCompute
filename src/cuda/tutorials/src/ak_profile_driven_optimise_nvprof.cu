#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "common.cuh"
#include "common.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

__global__ void sum_arrays_1Dgrid_1Dblock(float * a, float * b, float * c, int nx) {
    int gid = blockIdx.x*blockDim.x + threadIdx.x;

    if (gid<nx)
        c[gid] = a[gid] + b[gid];
}

__global__ void sum_arrays_2Dgrid_2Dblock(float * a, float * b, float * c, int nx, int ny) {
    int gidx = blockIdx.x*blockDim.x + threadIdx.x;
    int gidy = blockIdx.y*blockDim.y + threadIdx.y;

    int gid = gidy*nx + ny;

    if (gidx < nx && gidy < ny)
        c[gid] = a[gid] + b[gid];
}

void run_sum_array_1d(int argc, char** argv) {

}

void run_sum_array_2d(int argc, char** argv) {

}
