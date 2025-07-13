#pragma once

#include "clock/clock.h"
#include <atomic>

class Timer {
private:
    Clock& clock;
    bool running = true;

public:
    Timer(Clock& c);
    void run();
    void stop();
};

