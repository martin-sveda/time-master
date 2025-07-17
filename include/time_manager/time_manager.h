#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <iostream>
#include <iomanip>
#include <chrono>   

#include "time_sources/i_time_source.h"

using namespace time_sources;

class TimeManager {
public:
    //struct TimeDisciplineSettings {
    //    uint64_t maxDrift;
    //    uint64_t updateInterval;
    //    uint64_t maxStepSize;
    //};

    TimeManager(std::shared_ptr<ITimeSource> masterTimeSource) 
        : m_masterTimeSource(masterTimeSource) {};
    
    
    void setMasterTimeSource(std::shared_ptr<ITimeSource> masterTimeSource);
    std::shared_ptr<ITimeSource> getMasterTimeSource() const;
    std::string getMasterSourceName() const;

    std::chrono::system_clock::time_point getMasterTime() const;
    void displayMasterTime() const;
    
    

    //void setSettings(const TimeDisciplineSettings& settings);
    //const TimeDisciplineSettings& getSettings();

private:
    //TimeDisciplineSettings m_settings;
    std::shared_ptr<ITimeSource> m_masterTimeSource;       // Pointer to the time source (e.g., GPS, NTP)
};

