// #include "cuda_runtime.h"
// #include "device_launch_parameters.h"
// #include <stdio.h>
// #include <iostream>
// #include "common.cuh"

// #define gpuErrchk(ans) { gpuAssert((ans), __FILE__, __LINE__, true); }

// inline void gpuAssert(cudaError_t code, const char *file, int line, bool abort = true){
//     if (code != cudaSuccess){
//         fprintf(stderr, "GPUassert: %s %s %d\n", cudaGetErrorString(code), file, line);
//         if (abort) exit(code);
//     }
// }