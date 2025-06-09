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
    trm::Information CheckTime(const trm::Information& infomation) noexcept;
    trm::Information CheckReserveTime(const trm::Information& infomation) noexcept;
    trm::Information CheckReserveStatus(const trm::Information& infomation) noexcept;
    trm::Information CheckReserveStatusList(const trm::Information& infomation) noexcept;
    trm::Information AdmAddReserveTime(const trm::Information& infomation) noexcept;
    trm::Information AdmDeleteReserveTime(const trm::Information& infomation) noexcept;
    trm::Information AdmModifyReserveNumber(const trm::Information& infomation) noexcept;
    trm::Information AdmModifyReserveStatus(const trm::Information& infomation) noexcept;
    trm::Information AdmSearchReserve(const trm::Information& information) noexcept;
protected:
    ReserveSystem() noexcept;
    ~ReserveSystem() noexcept;
    ReserveSystem(const ReserveSystem&) = delete;
    ReserveSystem& operator=(const ReserveSystem&) = delete;
private:
    dat::DataBase clientBase = DATA_BASE["reserve"]["client"];
    dat::DataBase reserveBase = DATA_BASE["reserve"]["server"]; // 一个存用户预约，一个存预约信息
};

}
    
#endif
