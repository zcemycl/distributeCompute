#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <vector>
#include <numeric>
#include <atomic>
#include "ad_local_global/module.h"

std::atomic<int> i = 0;
thread_local std::atomic<int> j = 0;

void local_global_foo() {
    ++i;
    ++j;
    std::cout << i << j;
}

void local_global_test () {
    std::thread t1(local_global_foo);
    std::thread t2(local_global_foo);
    std::thread t3(local_global_foo);

    t1.join();
    t2.join();
    t3.join();

    std::cout << std::endl;

}