#include "timer/timer.h"
#include <chrono>
#include <thread>

Timer::Timer(Clock& c) : clock(c) {}

void Timer::run() {
    while (running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        clock.increment();
    }
}

void Timer::stop() {
    running = false;
}


