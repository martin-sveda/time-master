#pragma once

#include "time_sources/i_time_source.h"
#include "time_sources/time_sources_types.h"
#include <string>
#include <chrono>

namespace time_sources {

class GPSTimeSource : public ITimeSource {
public:

    std::chrono::system_clock::time_point getTime() const override;
    std::string getSourceName() const override;

private:
};


} // namespace time_sources


