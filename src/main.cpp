#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <iomanip>

#include "clock/clock.h"
#include "timer/timer.h"
#include "time_sources/gps_time_source.h"
#include "time_sources/ntp_time_source.h"



using namespace time_sources;

int main() {
    Clock clock;
    Timer timer(clock, 200);

    // Create instances of GPS and NTP time sources
    GPSTimeSource gpsTimeSource;
    NTPTimeSource ntpTimeSource;


    // Display the GPS time source name
    std::cout << "Using time source: " << gpsTimeSource.getSourceName() << std::endl;
    // Display the current GPS time
    auto gpsTime = gpsTimeSource.getTime();
    std::time_t timeT = std::chrono::system_clock::to_time_t(gpsTime);
    std::cout << "Current GPS time: " << std::put_time(std::localtime(&timeT), "%Y-%m-%d %H:%M:%S") << std::endl;

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

