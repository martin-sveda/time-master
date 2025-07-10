#pragma once

#include "Clock.h"
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

