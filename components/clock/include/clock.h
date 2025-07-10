#pragma once

#include <mutex>
#include <condition_variable>

class Clock {
private:
    int ticks = 0;
    bool running = true;
    std::mutex mtx;
    std::condition_variable cv;
    bool new_tick = false;

public:
    void increment();
    void display();
    void stop();
};

