#include <thread>
#include <iostream>
// #include <jthread.h>

// using namespace std::literals;
// using namespace std::literals::chrono_literals;

void do_sth(std::stop_token token){
    int counter{0};
    while ( counter < 10 ){
        if (token.stop_requested())
            return;
        
        std::this_thread::sleep_for(0.2s);
        std::cerr << "This is interruptible thread: " << counter << std::endl;
        ++counter;
    }
}

void do_sth_else(){
    int counter{0};
    while ( counter < 10 ){
        std::this_thread::sleep_for(0.2s);
        std::cerr << "This is non-interruptible thread: " << counter << std::endl;
        ++counter;
    }
}

void play_jthread(){
    std::jthread nonInterruptable{do_sth_else};
    std::jthread interruptible{do_sth};

    std::this_thread::sleep_for(1.0s);
    nonInterruptable.request_stop();
    interruptible.request_stop();

}