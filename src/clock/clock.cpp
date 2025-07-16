
#include "clock/clock.h"
#include <iostream>
#include <chrono>
#include <thread>

Clock::Clock(uint64_t tickPeriodNs)
    : m_tickPeriodNs(tickPeriodNs)
    , m_tickCount(0)
    , m_ppmCorrection(0)
    , m_initialTime(std::chrono::system_clock::now()) 
{
}   


void Clock::tick() {
    std::unique_lock<std::mutex> lock(mtx);
    m_tickCount++;
    new_tick = true;
    cv.notify_one();
}

Clock::TimeInfo Clock::getCurrentTime() const {
    TimeInfo info;
    
    info.tickCount = m_tickCount.load();
    info.ppmCorrection = m_ppmCorrection.load();
    info.timePoint = calculateTimeFromTicks(info.tickCount);

    return info;
}

void Clock::setInitialTime(const std::chrono::system_clock::time_point& initialTime) {
    std::lock_guard<std::mutex> lock(mtx);
    m_initialTime = initialTime;
}

void Clock::setPPMCorrection(uint64_t ppmCorrection) {
    std::lock_guard<std::mutex> lock(mtx);
    // Clamp the PPM correction to the defined limits
    if (ppmCorrection > PPM_MAX) {
        ppmCorrection = PPM_MAX;
    } else if (ppmCorrection < -PPM_MAX) {
        ppmCorrection = -PPM_MAX;
    }
    // Store the PPM correction factor   
    m_ppmCorrection.store(ppmCorrection);
}

uint64_t Clock::getPPMCorrection() const {
    return m_ppmCorrection.load();
}   

uint64_t Clock::getTickCount() const {
    return m_tickCount.load();
}   

uint64_t Clock::getTickPeriodNs() const {
    return m_tickPeriodNs;
}   

std::chrono::system_clock::time_point Clock::calculateTimeFromTicks(uint64_t ticks) const {
    int64_t ppm = m_ppmCorrection.load();
    int64_t correction = PPM_PRECISION + ppm;
    int64_t totalCorrectedNs = (ticks * m_tickPeriodNs * correction) / PPM_PRECISION;
    auto duration = std::chrono::nanoseconds(totalCorrectedNs);

    return m_initialTime + duration;
}



void Clock::display() {
    while (running) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this]() { return new_tick || !running; });
        if (!running) break;
        std::cout << "Clock ticks: " << m_tickCount << std::endl;
        new_tick = false;
    }
}

void Clock::stop() {
    std::unique_lock<std::mutex> lock(mtx);
    running = false;
    cv.notify_one();
}

