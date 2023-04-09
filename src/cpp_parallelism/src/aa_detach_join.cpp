#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include "aa_detach_join/module.h"

void task(std::string task_name, int sleep_duration) {
    std::thread::id this_id = std::this_thread::get_id();
    std::cout << "thread " << this_id << " " << task_name << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep_duration));
    std::cout << task_name << std::endl;
}

void foo(int sleep_duration) {
    task("Foo", sleep_duration);
}

void bar(int sleep_duration) {
    task("Bar", sleep_duration);
}

void detach_join(){
    std::cout << "1. Detach join tutorial" << std::endl;
    std::cout << "Bar 0 Detach, Foo 0 Join" << std::endl;
    auto start = std::chrono::steady_clock::now();
    std::thread bar_thread(bar, 0);
    std::thread foo_thread(foo, 0);
    bar_thread.detach();
    foo_thread.join();
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

    std::cout << "Bar 0 Join, Foo 0 Join" << std::endl;
    start = std::chrono::steady_clock::now();
    bar_thread = std::thread(bar, 0);
    foo_thread = std::thread(foo, 0);
    bar_thread.join();
    foo_thread.join();
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end-start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

    std::cout << "Bar 2000 Join, Foo 1000 Join" << std::endl;
    start = std::chrono::steady_clock::now();
    bar_thread = std::thread(bar, 2000);
    foo_thread = std::thread(foo, 1000);
    bar_thread.join();
    foo_thread.join();
    std::cout<<"After Foo Join"<<std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end-start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

    std::cout << "Bar 2000 Detach, Foo 1000 Join" << std::endl;
    start = std::chrono::steady_clock::now();
    bar_thread = std::thread(bar, 2000);
    foo_thread = std::thread(foo, 1000);
    bar_thread.detach();
    foo_thread.join();
    std::cout<<"After Foo Join"<<std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end-start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

    std::cout << "Bar 1000 Detach, Foo 2000 Join" << std::endl;
    start = std::chrono::steady_clock::now();
    bar_thread = std::thread(bar, 1000);
    foo_thread = std::thread(foo, 2000);
    bar_thread.detach();
    foo_thread.join();
    std::cout<<"After Foo Join"<<std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end-start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
};