#pragma once

#include <atomic>
#include <chrono> 
#include <mutex>
#include <condition_variable>

#include "time_manager/time_manager.h"
#include "time_sources/i_time_source.h"

using namespace time_sources;

class Clock {
public:
    // Structure to hold both time and tick count
    struct TimeInfo {
        std::chrono::system_clock::time_point timePoint;    // Current time point
        uint64_t tickCount;                                 // Number of ticks at this time point
        uint64_t ppmCorrection;                             // Current PPM correction factor
    };

    explicit Clock(uint64_t tickPeriodNs);                  // Initi clock with a tick period in nanoseconds

    
    // Main interface methods
    void tick() noexcept;                                   // Method to increment the tick count (called from mock HW timer)

    TimeInfo getCurrentTime() const;                        // Method to get the current time and tick count
    void setTime(const std::chrono::system_clock::time_point& time); // Method to set the current time of the clock
    void setInitialTime(const std::chrono::system_clock::time_point& initialTime); // Method to set the initial time of the clock

    std::chrono::system_clock::time_point getLastSyncedTime() const; // Get last synced time
    void setLastSyncedTime(const std::chrono::system_clock::time_point& lastSyncedTime); // Set last synced time
    
    // PPM correction methods
    void setPPMCorrection(uint64_t ppmCorrection);          // Method to set the PPM correction factor
    uint64_t getPPMCorrection() const;                      // Method to get the current PPM correction factor
    //int64_t calculateRequiredPPMcorrection(int64_t timeDifference) const; // Method to calculate the required PPM correction factor

    // Tick information
    uint64_t getTickCount() const;                          // Method to get the current tick count
    uint64_t getTickPeriodNs() const;                       // Method to get the tick period in nanoseconds


    void stop();
    void displayCurrentTime() const;                        // Display current time in a human-readable format

private:
    // Member variables

    const uint64_t m_tickPeriodNs;                          // Tick period in nanoseconds
    std::atomic<uint64_t> m_tickCount;                      // Number of ticks since the clock started
    std::atomic<uint64_t> m_ppmCorrection;                  // Parts per million correction factor
    std::chrono::system_clock::time_point m_initialTime;    // Start time of the clock
    std::chrono::system_clock::time_point m_time;           // Current time of the clock
    std::chrono::system_clock::time_point m_lastSyncedTime; // Last synced time
    bool running = true;
    std::mutex mtx;
    std::condition_variable cv;
    bool new_tick = false;


    // Private methods
    std::chrono::system_clock::time_point calculateTimeFromTicks(uint64_t ticks) const; // Method to calculate the time point from the tick count   

    // Helper constants
    static constexpr uint64_t NSEC_PER_SEC = 1000000000ULL; // Nanoseconds per second
    static constexpr uint64_t PPM_PRECISION = 1000000ULL;   // Precision for PPM calculations (1 million)
    static constexpr uint64_t PPM_MAX = 500;                // Maximum PPM correction value 

};

