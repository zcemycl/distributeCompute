#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include "ag_uniquelock/module.h"

std::mutex mg1;
std::mutex mg2;

void m1_1st_m2_2nd2() {
    std::cout << std::this_thread::get_id() << " hold the lock for both mutex." << std::endl;
    std::unique_lock<std::mutex> ul1(mg1, std::defer_lock);
    std::unique_lock<std::mutex> ul2(mg2, std::defer_lock);
    std::lock(ul1, ul2);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void m2_1st_m1_2nd2() {
    std::cout << std::this_thread::get_id() << " hold the lock for both mutex." << std::endl;
    std::unique_lock<std::mutex> ul1(mg2, std::defer_lock);
    std::unique_lock<std::mutex> ul2(mg1, std::defer_lock);
    std::lock(ul1, ul2);
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
}

void unique_lock_test(){
    std::thread t1(m1_1st_m2_2nd2);
    std::thread t2(m2_1st_m1_2nd2);

    t1.join();
    t2.join();
}