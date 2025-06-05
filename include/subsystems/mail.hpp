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
    trm::Information SendMessage(const trm::Information &information) noexcept;
    trm::Information GetMessageNumber(const trm::Information &information) noexcept;
    trm::Information GetMessageProfile(const trm::Information &information) noexcept;
    trm::Information GetMessage(const trm::Information &information) noexcept;
    trm::Information MarkAsRead(const trm::Information &information) noexcept; // TODO
    trm::Information MarkAsUnread(const trm::Information &information) noexcept;
    trm::Information GetUnreadMessageNumber(const trm::Information &information) noexcept;
    trm::Information DeleteMessage(const trm::Information &information) noexcept;
    trm::Information ClearMessage(const trm::Information &information) noexcept;
    trm::Information DeleteMessageOfOthers(const trm::Information &information) noexcept;
    trm::Information ClearMessageOfOthers(const trm::Information &information) noexcept; // TODO
    trm::Information ResetMailSystem(const trm::Information &information) noexcept;
protected:
    MailSystem() noexcept;
    ~MailSystem() noexcept;
    MailSystem(const MailSystem&) = delete;
    MailSystem& operator=(const MailSystem&) = delete;
private:
    static const std::string BOX;
    static const std::string UNREAD_NUM;
    dat::DataBase base = DATA_BASE["mail"];
};

}
    
#endif
