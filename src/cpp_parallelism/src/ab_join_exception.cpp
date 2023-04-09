#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <vector>
#include "ab_join_exception/module.h"

void foo() {
    std::cout << "Foo" << std::endl;
}

void operation_error() {
    throw std::runtime_error("Run Time Error...");
}

class thread_guard {
    std::thread & t;

public:
    explicit thread_guard(std::thread & _t) : t(_t){}

    ~thread_guard(){
        if (t.joinable()){
            t.join();
        }
    }

    // optional
    // delete copy construct
    thread_guard(thread_guard const &) = delete;
    // delete copy assignment
    thread_guard & operator= (thread_guard const &) = delete;
};

void join_exception() {
    std::cout << "2. Join exception tutorial" << std::endl;
    std::thread foo_thread(foo);
    thread_guard tg(foo_thread);
    try
    {
        operation_error();
    }
    catch(const std::exception& e)
    {
    }
    
    
}