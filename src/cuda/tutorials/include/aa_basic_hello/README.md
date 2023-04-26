```
kernel_name <<< number_of_blocks, thread_per_block >>> (args);

// each grid is a repetiton of block, can be arranged in xyz directions
dim3 block(num_of_threads_per_block);
dim3 grid(num_of_blocks);
kernel_name <<< grid, block >>> (args);

// xyz 
dim3 block(x,y,z);
dim3 grid(x,y,z);
```