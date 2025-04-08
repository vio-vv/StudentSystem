#ifndef __ACCESS_HPP__
#define __ACCESS_HPP__

#define DATA_PATH ".\\data"

/**
 * @brief 学生管理系统。
 * @class SSys
 * 
 * @par REQUIRES
 * TO_COMPLETE
 * 
 * @par PROVIDES
 * TO_COMPLETE
 */

#include <iostream>
#include <cassert>
#include "transmitter.hpp"

struct Account{
    std::string code;
    std::string passwordHash;
};

class SSys{
public:
    static SSys& Get() noexcept
    {
        static SSys instance;
        return instance;
    }

    trm::Infomation CheckAccount(const trm::Infomation &infomation) noexcept;
    trm::Infomation ListAccess(const trm::Infomation &infomation) noexcept;
protected:
    SSys();
    ~SSys();
    SSys(const SSys&) = delete;
    SSys& operator=(const SSys&) = delete;

    std::vector<Account> accounts;
};

#endif