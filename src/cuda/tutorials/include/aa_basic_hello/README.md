```
kernel_name <<< number_of_blocks, thread_per_block >>> (args);

// each grid is a repetiton of block, can be arranged in xyz directions
dim3 block(num_of_threads_per_block);
dim3 grid(num_of_blocks);
kernel_name <<< grid, block >>> (args);

// block: (x<=1024, y<=1024, z<=64), x*y*z <= 1024
// thread: x<=2**32-1, y<=2**16, z<=2**16
dim3 block(x,y,z);
dim3 grid(x,y,z);
```

|B1|B2|B3|B4|B5|B6|B7|B8|B9|
|---|---|---|---|---|---|---|---|---|
|TTT|TTT|TTT|TTT|TTT|TTT|TTT|TTT|TTT|

For example, in the above diagram, there are 9 blocks in x direction, 3 threads in each block. For y and z axis, it is just 1 block 1 thread.