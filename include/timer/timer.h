
/**
 * @file timer.h
 * @brief Declaration of the Timer class for time management.
 *
 * This header defines the Timer class, which provides functionality to manage
 * and control timing operations using a Clock instance. The Timer can be started,
 * stopped, and run, allowing for flexible time-based control in applications.
 * 
 * It is a "fake" implementation of HW timer that ticks every XXX miliseconds to simulate
 * a hardware timer.
 * 
 * @author [Your Name]
 * @date [Date]
 */

 #pragma once

#include "clock/clock.h"
#include <atomic>


class Timer {
private:
    Clock& clock;
    int interval = 200; // Interval in milliseconds
    bool running = true;

public:
    Timer(Clock& c);
    Timer(Clock& c, int interval);
    void run();
    void stop();
};

