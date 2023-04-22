#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <future>

void printing_thread(){
    std::cout << "printing runs on - " << std::this_thread::get_id() << std::endl;
}

int addition(int x, int y){
    std::cout << "addition runs on - " << std::this_thread::get_id() << std::endl;
    return x+y;
}

int subtract(int x, int y){
    std::cout << "subtract runs on - " << std::this_thread::get_id() << std::endl;
    return x-y;
}

void async_future_play() {
    std::cout << "main thread id - " << std::this_thread::get_id() << std::endl;

    int x = 100, y = 50; 

    std::future<void> f1 = std::async(std::launch::async, printing_thread);
    std::future<int> f2 = std::async(std::launch::deferred, addition, x, y);
    std::future<int> f3 = std::async(std::launch::async | std::launch::deferred, subtract, x, y);

    f1.get();
    std::cout << "value received using f2 future - " << f2.get() << std::endl;
    std::cout << "value received using f3 future - " << f3.get() << std::endl;


}