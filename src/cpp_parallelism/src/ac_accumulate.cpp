#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <vector>
#include <numeric>
#include <functional>
#include "ac_accumulate/module.h"

#define MIN_BLOCK_SIZE 1000

template<typename iterator, typename T>
void accumulate(iterator start, iterator end, T &ref){
    ref = std::accumulate(start, end, 0);
}

template<typename iterator, typename T>
T parallel_accumulate(iterator start, iterator end, T &ref){
    int input_size = std::distance(start, end);
    int allowed_threads_by_elements = (input_size)/MIN_BLOCK_SIZE;
    int allowed_threads_by_hardware = std::thread::hardware_concurrency();
    std::cout << "Allowed Threads by Hardware: " << allowed_threads_by_hardware << std::endl;

    int num_threads = std::min(allowed_threads_by_elements,
        allowed_threads_by_hardware);
    std::cout << "Current no. of threads: " << num_threads << std::endl;
    
    int block_size = (input_size + 1)/num_threads;

    std::vector<T> results(num_threads);
    std::vector<std::thread> threads(num_threads-1);

    iterator last;

    for (size_t i=0; i<num_threads-1; i++){
        last = start;
        std::advance(last, block_size);
        threads[i] = std::thread(accumulate<iterator, T>, 
            start, last, std::ref(results[i]));
        start = last;
    }

    results[num_threads-1] = std::accumulate(start, end, 0);

    std::for_each(threads.begin(), threads.end(), 
        std::mem_fn(&std::thread::join));

    return std::accumulate(results.begin(), results.end(), ref);
}

void accumulate_test() {
    std::vector<int> v{1,2,3,4,5,6,7,8,9,10};
    int sum = std::accumulate(v.begin(), v.end(), 0);
    int product = std::accumulate(v.begin(), v.end(), 1, std::multiplies<int>());
    auto dash_fold = [](std::string a, int b)
    {
        return std::move(a) + '-' + std::to_string(b);
    };

    std::cout << "sum of vector: " << sum << std::endl;
    std::cout << "product of vector: " << product << std::endl;

    std::string s = std::accumulate(std::next(v.begin()), v.end(),
        std::to_string(v[0]), // start with first element
        dash_fold);

    std::cout << s << std::endl;

    const int size = 8000;
    int* my_array = new int[size];
    int ref  = 0;
    srand(0);
    for (size_t i=0; i<size; i++){
        my_array[i] = rand()%10;
    }

    int rer_val = parallel_accumulate<int*, int>(my_array, my_array+size, ref);
    printf("Accumulated value: %d \n", rer_val);
}