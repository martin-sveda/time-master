#pragma once

#include <chrono>   


namespace time_sources {
    

class ITimeSource;

class MasterClock {
private:
    ITimeSource* timeSource;

public:
    MasterClock(ITimeSource* source);
    void setTimeSource(ITimeSource* source);
    void displayCurrentTime();  
};

}



