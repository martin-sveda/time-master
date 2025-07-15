/**
 * @file ntp_time_source.h
 * @brief NTP class based on ITimeInterface providing time from GPS source.
 *
 * Time from NTP is mocked by now() function. 
 */

#include "time_sources/ntp_time_source.h"
#include <chrono>


namespace time_sources {

std::chrono::system_clock::time_point NTPTimeSource::getTime() const {
    // Mocking NTP time source by returning the current system time
    // In a real implementation, this would query an NTP server for the current time.
    return std::chrono::system_clock::now();
}

std::string NTPTimeSource::getSourceName() const {
    return "NTP";
}

}   // namespace time_sources


