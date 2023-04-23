#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <vector>
#include <list>
#include <numeric>
#include <atomic>
#include "ae_lockguard/module.h"

std::list<int> my_list;
std::mutex m;

void add_to_list1(int const & x){
    m.lock();
    my_list.push_front(x);
    m.unlock();
}

void size1() {
    m.lock();
    int size = my_list.size();
    m.unlock();
    std::cout << "size of the list is: " << size << std::endl;
}

void add_to_list2(int const & x){
    std::lock_guard<std::mutex> lg(m);
    my_list.push_front(x);
}

void lock_test () {
    std::thread t1(add_to_list1, 2);
    std::thread t2(add_to_list2, 10);

    t1.join();
    t2.join();

    int size = my_list.size();
    std::cout << "size of the list is: " << size << std::endl;
}