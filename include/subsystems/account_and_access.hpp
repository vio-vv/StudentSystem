#ifndef __SUBSYSTEMS_ACCOUNT_AND_ACCESS_HPP__
#define __SUBSYSTEMS_ACCOUNT_AND_ACCESS_HPP__

/**
 * @brief 帐户与权限系统。
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

class AccountAndAccess{
public:
    trm::Infomation CheckAccount(const trm::Infomation &infomation) noexcept;
    trm::Infomation CreateAccount(const trm::Infomation &infomation) noexcept;
protected:
    void Save() const noexcept;

    AccountAndAccess() noexcept;
    ~AccountAndAccess() noexcept;
    AccountAndAccess(const AccountAndAccess&) = delete;
    AccountAndAccess& operator=(const AccountAndAccess&) = delete;

    std::map<std::string, trm::Account> accounts;
};

}

#endif
