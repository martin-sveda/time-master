#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

#include "clock/clock.h"
#include "timer/timer.h"


int main() {
    Clock clock;
    Timer timer(clock);

    // Create threads
    std::thread clockThread(&Clock::display, &clock);
    std::thread timerThread(&Timer::run, &timer);

    // Let it run for 5 seconds
    std::this_thread::sleep_for(std::chrono::seconds(5));

    // Stop the threads
    timer.stop();
    clock.stop();

    // Wait for threads to finish
    timerThread.join();
    clockThread.join();

    return 0;
}

