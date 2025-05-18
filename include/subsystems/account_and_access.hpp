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
    trm::Information CheckAccount(const trm::Information &information) noexcept;
    trm::Information CheckAccess(const trm::Information &information) noexcept;
    trm::Information CreateAccount(const trm::Information &information) noexcept;
    trm::Information DeleteAccount(const trm::Information &information) noexcept;
    trm::Information GrantAccess(const trm::Information &information) noexcept;
    trm::Information RevokeAccess(const trm::Information &information) noexcept;
    trm::Information RevokeAllAccess(const trm::Information &information) noexcept;
    trm::Information AddTag(const trm::Information &information) noexcept;
    trm::Information RemoveTag(const trm::Information &information) noexcept;
    trm::Information ClearTag(const trm::Information &information) noexcept;
    trm::Information ResetAccountAndAccess(const trm::Information &information) noexcept;
    trm::Information ListAccount(const trm::Information &information) noexcept;

    trm::Information CheckAccountExist(const trm::Information &information) noexcept;
    trm::Information QueryTag(const trm::Information &information) noexcept;
protected:
    AccountAndAccess() noexcept;
    ~AccountAndAccess() noexcept;
    AccountAndAccess(const AccountAndAccess &) = delete;
    AccountAndAccess &operator=(const AccountAndAccess &) = delete;
private:
    static std::vector<std::string> AccessCross(const std::vector<std::string> &access, const std::vector<std::string> &creator) noexcept;
    static const std::string ACCOUNTS;

    dat::DataBase base = DATA_BASE["acc_acc"];
};

}

#endif
