/**
 * @file gps_time_source.h
 * @brief GPS class based on ITimeInterface providing time from GPS source.
 *
 * Time from GPS is mocked by now() function. 
 */

#include "time_sources/gps_time_source.h"
#include <chrono>


namespace time_sources {

std::chrono::system_clock::time_point GPSTimeSource::getTime() const {

    return std::chrono::system_clock::now();
}

std::string GPSTimeSource::getSourceName() const {
    return "GPS";
}

}   // namespace time_sources


