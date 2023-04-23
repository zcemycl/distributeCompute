#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include "ag_uniquelock/module.h"

std::mutex m1;
std::mutex m2;

void m1_1st_m2_2nd2() {
    std::cout << std::this_thread::get_id() << " hold the lock for both mutex." << std::endl;
    std::unique_lock<std::mutex> ul1(m1, std::defer_lock);
    std::unique_lock<std::mutex> ul2(m2, std::defer_lock);
    std::lock(ul1, ul2);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void m2_1st_m1_2nd2() {
    std::cout << std::this_thread::get_id() << " hold the lock for both mutex." << std::endl;
    std::unique_lock<std::mutex> ul1(m2, std::defer_lock);
    std::unique_lock<std::mutex> ul2(m1, std::defer_lock);
    std::lock(ul1, ul2);
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
}

void unique_lock_test(){
    std::thread t1(m1_1st_m2_2nd2);
    std::thread t2(m2_1st_m1_2nd2);

    t1.join();
    t2.join();
}