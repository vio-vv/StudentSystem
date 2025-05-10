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
    trm::Information publishNolify(trm::Information&);
    trm::Information deleteNolify(trm::Information&);
    trm::Information updateNolify(trm::Information&);
    trm::Information getNolify(trm::Information&);
    trm::Information markNolifyAsRead(trm::Information&);
    trm::Information markNolifyAsUnread(trm::Information&);
protected:
    Nolify() noexcept;
    ~Nolify() noexcept;
    Nolify(const Nolify&) = delete;
    Nolify& operator=(const Nolify&) = delete;
private:
    dat::DataBase nolifys = DATA_BASE["Nolify"]["content"];
};

}

#endif
