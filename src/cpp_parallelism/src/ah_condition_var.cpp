#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include "ah_condition_var/module.h"

bool have_i_arrived = false;
int dist_my_distination = 10;
int dist_covered = 0;
std::condition_variable cv;
std::mutex m;

bool keep_driving(){
    while (true){
        if (dist_covered == dist_my_distination)
            cv.notify_one();
        std::cout << std::this_thread::get_id() << " driver station... " << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        dist_covered ++;
    }
    return false;
};

void keep_awake_all_night(){
    while (dist_covered < dist_my_distination){
        std::cout << std::this_thread::get_id() << " keep check, whether i am there. " << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    std::cout << std::this_thread::get_id() << " finally i am there, distance covered = " << dist_covered << std::endl;
}

void set_alarm_and_take_nap(){
    while (dist_covered < dist_my_distination){
        std::cout << std::this_thread::get_id() << " let me take a nap. " << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    }
    std::cout << std::this_thread::get_id() << " finally i am there, distance covered = " << dist_covered << std::endl;
}

void notify_me(){
    std::unique_lock<std::mutex> ul(m);
    cv.wait(ul, [] {return dist_covered==dist_my_distination;});
    std::cout << std::this_thread::get_id() << " finally i am there, distance covered = " << dist_covered << std::endl;
}

void naive_bus_arrival(){
    std::thread driver(keep_driving);
    // std::thread keep_awake_strategy(keep_awake_all_night);
    std::thread set_alarm_strategy(set_alarm_and_take_nap);

    // keep_awake_strategy.join();
    set_alarm_strategy.join();
    driver.join();
}

void condition_var_bus_arrival(){
    std::thread driver(keep_driving);
    std::thread passenger(notify_me);

    passenger.join();
    driver.join();
}