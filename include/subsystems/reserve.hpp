#ifndef __SUBSYSTEMS_RESERVE_HPP__
#define __SUBSYSTEMS_RESERVE_HPP__

/**
 * @brief 预约入校系统。
 * @namespace ssys
 * 
 * @par REQUIRES
 * TO_COMPLETE
 * 
 * @par PROVIDES
 * TO_COMPLETE
 */

#include "system_header.hpp"

namespace ssys{

class ReserveSystem{
public:
    trm::Information RequestReserve(const trm::Information& infomation) noexcept;
    trm::Information CancelReserve(const trm::Information& infomation) noexcept;
    trm::Information CheckReserveTime(const trm::Information& infomation) noexcept;
protected:
    ReserveSystem() noexcept;
    ~ReserveSystem() noexcept;
    ReserveSystem(const ReserveSystem&) = delete;
    ReserveSystem& operator=(const ReserveSystem&) = delete;
private:
    static const std::string dataPath;
    std::map<std::string,std::vector<trm::ReserveInformation::Client>> reserveRequestList; // 预约申请列表
    std::map<std::string,std::vector<trm::ReserveInformation::Server>> reserveReplyList; // 预约列表
};

}
    
#endif
