#include <components/time-sources/include/gps_time_source.h>
#include "gps_time_source.h"

namespace time_sources {


std::chrono::system_clock::time_point GPSTimeSource::getCurrentTime() 
{
    return std::chrono::system_clock::now();
}

std::string GPSTimeSource::getSourceName() const
{
    return "GPS";
}


} // namespace time_sources
