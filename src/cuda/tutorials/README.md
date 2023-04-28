## How to start?
```
docker build -t cuda_gtest:latest .
docker run cuda_gtest
docker run --gpus all cuda_gtest # use gpu in your host
```

## Computer Architectures classification
+ Single instruction single data (SISD)
    - single instruction pool, single data pool
+ Single instruction multiple data (SIMD)
    - single instruction pool, multiple data pools
+ Multiple instruction single data (MISD)
+ Multiple instruction multiple data (MIMD)
+ Single instruction multiple threads (SIMT)
    - single instruction running in multiple threads
+ Streaming Multiprocessor (SM)
    |Software|Hardware|
    |---|---|
    |Thread|CUDA Core|
    |Thread Block|SM|
    |Grid|Device|
+ Threads
    - Not all of them run in parallel (hardware point of view). 
    - Device with 13 SM, each SM has 128 cores.
        - There are only 1664 cores. (only 1664 threads in parallel) 
        - 1 Block only runs in 1 SM. SO only 128 cores/threads can run in parallel. 
        - If we define a million threads with block size of 512 (Thread Block) in software, the hardware cannot run 512 in parallel since there is a 128 cores limitation for each SM.
+ Thread Blocks
    - Divide into smaller units -- warps = 32 consecutive threads.
    - All warps in the same thread block is executing in same streaming multiprocessor (SM).
        ```
        No of warps per block = Block size / warp size = 512/32 = 16
        ```
    - 128 cores per SM `128/32=4`?
+ Warps
    - Basic unit of execution in a SM.
    - All threads in a warp are executed in SIMT.
        ```mermaid
        flowchart LR
            B[SM]-->|scheduled| A[Thread Block];
            A -->|partiton| C[Warps]; 
        ```
    - Software defines 128 threads in x dimension, there are 4 warps in hardware, each thread in a wrap is consecutive indexed (0-31, 32-63, ...). 
    - Software: 2 thread blocks along y direction, each thread block has 40 threads along x. Hardware: 4 warps, first 2 are for 1 thread block, another for another thread block. There are 14 inactive threads in each last warp.
        - Software
            |0|1|...|38|39|
            |---|---|---|---|---|
            |0|1|...|38|39|
        - Hardware
            |0|...|31|\||32|...|39|(14 idle)\||40|...|71|\||72|...|79|(14 idle)|
            |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
    - Therefore, a multiple of 32 in block size is avoiding the waste of resources.
    - Warp Divergence (avoid switch if else statements which split cases into smaller than number of threads in warp.)
        - Odd/even: active half , inactive half. 
        - If/else: active one case, inactive the rest. 

### References
1. [Github Nvidia Cuda Samples](https://github.com/nvidia/cuda-samples)