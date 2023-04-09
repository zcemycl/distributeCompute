#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <vector>
#include "ex1/module.h"

void printFuncName(std::string func_name) {
    std::cout << func_name << std::endl;
}

void test() {
    printFuncName("test");
}

void funcA() {
    printFuncName("funcA");
    std::thread test_thread(test);
    test_thread.join();
}

void funcB() {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    printFuncName("funcB");
}

void ex1() {
    std::thread funcA_thread(funcA);
    std::thread funcB_thread(funcB);

    funcA_thread.join();
    funcB_thread.join();
}