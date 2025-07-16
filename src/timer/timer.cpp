
/**
 * @file timer.cpp
 * @brief Implementation of the Timer class for periodic clock incrementing.
 *
 * This file contains the implementation of the Timer class, which is responsible for
 * periodically incrementing a Clock instance in a separate thread. The timer runs in
 * a loop, sleeping for a fixed interval (200 milliseconds) between increments, and can
 * be stopped by setting the running flag to false.
 *
 * Classes:
 *  - Timer: Manages periodic updates to a Clock object.
 *
 * Dependencies:
 *  - timer/timer.h: Timer class declaration.
 *  - <chrono>: For time intervals.
 *  - <thread>: For sleeping and threading support.
 */

#include "timer/timer.h"
#include <chrono>
#include <thread>
#include <iostream>


Timer::Timer(Clock& c) : clock(c) {};
Timer::Timer(Clock& c, int interval) : clock(c), m_intervalNs(interval) {};

void Timer::run() {
    while (m_running) {
        std::this_thread::sleep_for(std::chrono::nanoseconds(m_intervalNs));
        // std::cout << "Timer tick: incrementing clock." << std::endl;
        clock.tick();
    }
}

void Timer::stop() {
    m_running = false;
}


