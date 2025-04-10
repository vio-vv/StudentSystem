#include "subsystems/account_and_access.hpp"

trm::Infomation ssys::AccountAndAccess::CheckAccount(const trm::Infomation &infomation) noexcept
{
    assert(infomation[0] == trm::rqs::CHECK_ACCOUNT); // Procession not matched.

    if (infomation[1] == "adm" && infomation[2] == "123") {
        return {trm::rpl::YES, "adm"};
    }
    
    // TODO: check database

    return {trm::rpl::NO};
}

ssys::AccountAndAccess::AccountAndAccess()
{
}

ssys::AccountAndAccess::~AccountAndAccess()
{
}
