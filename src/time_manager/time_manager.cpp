#include "time_manager/time_manager.h"



std::string TimeManager::getMasterSourceName() const {
    return m_masterTimeSource ? m_masterTimeSource->getSourceName() : "None";
}


std::shared_ptr<ITimeSource> TimeManager::getMasterTimeSource() const {
    return m_masterTimeSource;
}


void TimeManager::setMasterTimeSource(std::shared_ptr<ITimeSource> masterTimeSource) {
   m_masterTimeSource = masterTimeSource;
}


std::chrono::system_clock::time_point TimeManager::getMasterTime() const {
    return m_masterTimeSource->getTime();
}   


void TimeManager::displayMasterTime() const {
    auto masterTime = getMasterTime();
    std::time_t timeT = std::chrono::system_clock::to_time_t(masterTime);
    std::cout << "Current master time: " << std::put_time(std::localtime(&timeT), "%Y-%m-%d %H:%M:%S") 
        << " (" << getMasterSourceName() << ")" << std::endl;
}
