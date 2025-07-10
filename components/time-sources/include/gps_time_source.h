#pragma once

#include "i_time_source.h"
#include "time_sources_types.h"
#include <string>

namespace time_sources {

class GPSTimeSource : public ITimeSource {
public:

    std::chrono::system_clock::time_point getCurrentTime() override;
    std::string getSourceName() const override;

private:
};

} // namespace time_sources

