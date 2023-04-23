#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <vector>
#include <list>
#include <numeric>
#include <atomic>
#include "af_deadlock/module.h"

std::mutex m1;
std::mutex m2;

void m1_1st_m2_2nd() {
    std::lock_guard<std::mutex> lg1(m1);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "thread " << std::this_thread::get_id() << " has acquired lock for m1 mutex. " << std::endl;
    std::lock_guard<std::mutex> lg2(m2);
    std::cout << "thread " << std::this_thread::get_id() << " has acquired lock for m2 mutex. " << std::endl;
}

void m2_1st_m1_2nd() {
    std::lock_guard<std::mutex> lg1(m2);
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    std::cout << "thread " << std::this_thread::get_id() << " has acquired lock for m2 mutex. " << std::endl;
    // std::lock_guard<std::mutex> lg2(m1); // uncomment to be deadlock
    // std::cout << "thread " << std::this_thread::get_id() << " has acquired lock for m1 mutex. " << std::endl; // uncomment to be deadlock
}

void deadlock_test() {
    std::thread t1(m1_1st_m2_2nd);
    std::thread t2(m2_1st_m1_2nd);

    t1.join();
    t2.join();
}