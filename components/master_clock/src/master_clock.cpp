#include <iostream>
#include <chrono>

#include "i_time_source.h"
#include "master_clock.h"

namespace time_sources {

MasterClock::MasterClock(ITimeSource* source) {
    timeSource = source;
}

void MasterClock::setTimeSource(ITimeSource* source) {
    timeSource = source;
}

void MasterClock::displayCurrentTime() {
    auto now = timeSource->getCurrentTime();
    auto currentTime = std::chrono::system_clock::to_time_t(now);
    std::cout << "Current time from " << timeSource->getSourceName() 
              << ": " << std::ctime(&currentTime);
}


}
