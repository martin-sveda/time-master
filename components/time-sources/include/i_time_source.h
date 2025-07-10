#pragma once

#include <chrono>
#include <string>

namespace time_sources {

class ITimeSource {
public:
    virtual ~ITimeSource() = default;
    virtual std::chrono::system_clock::time_point getCurrentTime() = 0;
    virtual std::string getSourceName() const = 0;
};

} // namespace time_sources

