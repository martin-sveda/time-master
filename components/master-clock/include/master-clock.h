#pragma once

#include <chrono>   

class ITimeSource;

class MasterClock {
private:
    ITimeSource* timeSource;

public:
    MasterClock(ITimeSource* source);
    void setTimeSource(ITimeSource* source);
    void displayCurrentTime();  
};




