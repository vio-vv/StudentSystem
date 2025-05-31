#ifndef __SUBSYSTEMS_NOLIFY_HPP__
#define __SUBSYSTEMS_NOLIFY_HPP__

/**
 * @brief 通知与公示系统。
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

class Nolify{
public:
    trm::Information PublishNolify(const trm::Information&) noexcept;
    trm::Information DeleteNolify(const trm::Information&) noexcept;
    trm::Information GetNolifyNumber(const trm::Information&) noexcept;   
    trm::Information GetNolifyTitle(const trm::Information&) noexcept;
    trm::Information GetNolifyContent(const trm::Information&) noexcept;
protected:
    Nolify() noexcept;
    ~Nolify() noexcept;
    Nolify(const Nolify&) = delete;
    Nolify& operator=(const Nolify&) = delete;
private:
    dat::DataBase nolify = DATA_BASE["Nolify"];
    // dat::DataBase headline = DATA_BASE["Nolify"]["headline"];
    // dat::DataBase news = DATA_BASE["Nolify"]["news"];
    // dat::DataBase notice = DATA_BASE["Nolify"]["notice"];
};

}

#endif
