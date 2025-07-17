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




int main() {

    // Base tick of mock HW timer
    static constexpr uint64_t TICK_PERIOD_NS = 10000000; // 10 milliseconds in nanoseconds

    // Create instances of GPS and NTP master time sources
    auto gpsTimeSource = std::make_shared<GPSTimeSource>();
    auto ntpTimeSource = std::make_shared<NTPTimeSource>(); 

    // Setting the time manager
    auto timeManager = std::make_shared<TimeManager>(gpsTimeSource);


    // Create a Clock and Timer instance with the specified tick period
    Clock clock(TICK_PERIOD_NS);
    Timer timer(clock, TICK_PERIOD_NS);

    // Create threads
    //std::thread clockThread(&Clock::display, &clock);
    std::thread timerThread(&Timer::run, &timer);


    // Display the precision of the system (host) clock
    std::cout << "system_clock precision: "
              << std::chrono::system_clock::period::num << "/"
              << std::chrono::system_clock::period::den << " seconds"
              << std::endl << std::endl;


    // Display current clock time
    clock.displayCurrentTime();
    // Display current master time
    timeManager->displayMasterTime();
    std::cout << std::endl;


    // Let it run for some seconds
    std::cout << "Sleep the main thread for 10 seconds and see what will happen with internal clock..." << std::endl << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(10));


    // Change and display master time source to NTP
    timeManager->setMasterTimeSource(ntpTimeSource);
    timeManager->displayMasterTime();
    
    // Display current clock time
    clock.displayCurrentTime();


    // Now I want to see what was the time duration between two GPS time points
    // and the internal clock time point to see the difference
    // Then I will calculate the PPM correction factor
    // and run the clock with this correction factor
    // and see the difference in the clock time point and set the PPM correction factor again and again

    //auto diff = gpsTime - currentTimeInfo.timePoint;
    
    //std::cout << "Difference between GPS time and INT clock time: " 
    //          << std::chrono::duration_cast<std::chrono::nanoseconds>(diff).count() 
    //          << " nanoseconds" << std::endl;   



    // Stop the threads
    timer.stop();
    //clock.stop();

    // Wait for threads to finish
    timerThread.join();
    //clockThread.join();

    return 0;
    
}

