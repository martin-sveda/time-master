#include "clock/clock.h"
#include <iostream>

void Clock::increment() {
    std::unique_lock<std::mutex> lock(mtx);
    ticks++;
    new_tick = true;
    cv.notify_one();
}

void Clock::display() {
    while (running) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this]() { return new_tick || !running; });
        if (!running) break;
        std::cout << "Clock ticks: " << ticks << std::endl;
        new_tick = false;
    }
}

void Clock::stop() {
    std::unique_lock<std::mutex> lock(mtx);
    running = false;
    cv.notify_one();
}

