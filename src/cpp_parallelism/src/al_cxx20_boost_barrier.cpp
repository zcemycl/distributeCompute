#include <boost/thread.hpp>
#include <boost/thread/barrier.hpp>
#include <boost/bind.hpp>
#include <boost/atomic.hpp>
#include <iostream>
#include "al_cxx20_boost_barrier/module.h"

void func(boost::barrier& cur_barrier, boost::atomic<int>& counter){
    ++counter;
    cur_barrier.wait(); // comment this will result in different counter printouts
    std::cout << "Current value after barrier : " << counter << std::endl;
}

void play_barrier() {
    boost::barrier bar(3);
    boost::atomic<int> current(0);
    boost::thread t1(boost::bind(&func, boost::ref(bar), boost::ref(current)));
    boost::thread t2(boost::bind(&func, boost::ref(bar), boost::ref(current)));
    boost::thread t3(boost::bind(&func, boost::ref(bar), boost::ref(current)));

    t1.join();
    t2.join();
    t3.join();
}