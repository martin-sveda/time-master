
/**
 * @file i_time_source.h
 * @brief Interface for different time sources that can be used in the main program.
 *
 * Defines the ITimeSource abstract class, which provides a common interface for obtaining
 * the current time and identifying the source of time. Implementations of this interface
 * can represent various time sources (e.g., system clock, network time, simulated time).
 */
#pragma once

#include <chrono>
#include <string>

namespace time_sources {

class ITimeSource {
public:
    virtual ~ITimeSource() = default;
    virtual std::chrono::system_clock::time_point getTime() const = 0;
    virtual std::string getSourceName() const = 0;
};


}   // namespace time_sources


