
/**
 * @file time_sources_types.h
 * @brief Defines types related to time sources.
 *
 * This header declares the TimeSourceType enumeration, which specifies
 * the available types of time sources that can be used in the system.
 * Supported time sources include GPS, NTP, and RTC.
 */
#pragma once

namespace time_sources {

enum class TimeSourceType {
    GPS,
    NTP,
    RTC
};

}   // namespace time_sources

