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

    // Base tick of mock HW timer
    static constexpr uint64_t TICK_PERIOD_NS = 10000000; // 10 milliseconds in nanoseconds
    
    // Create a Clock and Timer instance with the specified tick period
    Clock clock(TICK_PERIOD_NS);
    Timer timer(clock, TICK_PERIOD_NS);

    // Create instances of GPS and NTP time sources
    GPSTimeSource gpsTimeSource;
    NTPTimeSource ntpTimeSource;

    // Display the precision of the system clock
    std::cout << "system_clock precision: "
              << std::chrono::system_clock::period::num << "/"
              << std::chrono::system_clock::period::den << " seconds"
              << std::endl << std::endl;


    // Display the GPS time source name
    std::cout << "Using time source: " << gpsTimeSource.getSourceName() << std::endl;
    // Display the current GPS time
    auto gpsTime = gpsTimeSource.getTime();
    std::time_t timeT = std::chrono::system_clock::to_time_t(gpsTime);
    std::cout << "Current GPS time: " << std::put_time(std::localtime(&timeT), "%Y-%m-%d %H:%M:%S") << std::endl << std::endl;

    // Create threads
    //std::thread clockThread(&Clock::display, &clock);
    std::thread timerThread(&Timer::run, &timer);

    // Let it run for some seconds
    std::cout << "Sleep the main thread for 10 seconds and see what will happen with internal clock..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(10));


    // Get the current time from the clock and GPS time source (to see if they are in sync)
    Clock::TimeInfo currentTimeInfo = clock.getCurrentTime();
    gpsTime = gpsTimeSource.getTime();
    
    // Display the current time from the clock
    std::time_t clockTimeT = std::chrono::system_clock::to_time_t(currentTimeInfo.timePoint);
    std::cout << "Current INT clock time: " 
              << std::put_time(std::localtime(&clockTimeT), "%Y-%m-%d %H:%M:%S") 
              << ", Tick Count: " << currentTimeInfo.tickCount 
              << ", PPM Correction: " << currentTimeInfo.ppmCorrection << std::endl;

    // Display the current time from the GPS time source
    timeT = std::chrono::system_clock::to_time_t(gpsTime);
    std::cout << "Current GPS clock time: " << std::put_time(std::localtime(&timeT), "%Y-%m-%d %H:%M:%S") << std::endl << std::endl;

    // Now I want to see what was the time duration between two GPS time points
    // and the internal clock time point to see the difference
    // Then I will calculate the PPM correction factor
    // and run the clock with this correction factor
    // and see the difference in the clock time point and set the PPM correction factor again and again

    auto diff = gpsTime - currentTimeInfo.timePoint;
    
    std::cout << "Difference between GPS time and INT clock time: " 
              << std::chrono::duration_cast<std::chrono::nanoseconds>(diff).count() 
              << " nanoseconds" << std::endl;   



    // Stop the threads
    timer.stop();
    //clock.stop();

    // Wait for threads to finish
    timerThread.join();
    //clockThread.join();

    return 0;
    
}

