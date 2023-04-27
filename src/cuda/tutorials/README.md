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
+ Streaming Multiprocessor
    |Software|Hardware|
    |---|---|
    |Thread|CUDA Core|
    |Thread Block|SM|
    |Grid|Device|

### References
1. [Github Nvidia Cuda Samples](https://github.com/nvidia/cuda-samples)