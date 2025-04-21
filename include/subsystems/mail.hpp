#ifndef __SUBSYSTEMS_MAIL_HPP__
#define __SUBSYSTEMS_MAIL_HPP__

/**
 * @brief 消息与站内信系统。
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

class MailSystem{
public:
    trm::Infomation SendMessage(const trm::Infomation &infomation) noexcept;
    trm::Infomation GetMessageNumber(const trm::Infomation &infomation) noexcept;
protected:
    MailSystem() noexcept;
    ~MailSystem() noexcept;
    MailSystem(const MailSystem&) = delete;
    MailSystem& operator=(const MailSystem&) = delete;
private:
    dat::DataBase base = DATA_BASE["mail"];
};

}
    
#endif
