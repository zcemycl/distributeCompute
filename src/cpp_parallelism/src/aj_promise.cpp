#include <iostream>
#include <thread>
#include <future>
#include <chrono>
#include <functional>
#include <stdexcept>
#include "aj_promise/module.h"

void step2(std::future<int>& fut){
    int tmp_val = fut.get()+2;

    std::cout << "step 2 waiting for value..." << std::endl;
    std::cout << "step 2 value: " << tmp_val << std::endl;
}


void step1(std::future<int>& fut){
    std::promise<int> tmp_prom;
    std::future<int> tmp_fut = tmp_prom.get_future();
    int tmp_val = fut.get()+1;

    std::cout << "step 1 waiting for value..." << std::endl;
    std::cout << "step 1 value: " << tmp_val << std::endl;

    std::thread t2(step2, std::ref(tmp_fut));
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    tmp_prom.set_value(tmp_val);
    t2.join();
}

void play_promise() {
    std::promise<int> prom;
    std::future<int> fut = prom.get_future();

    std::thread t1(step1, std::ref(fut));
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    prom.set_value(10);
    t1.join();
}