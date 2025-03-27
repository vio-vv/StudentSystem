#include "student_system.hpp"

trm::Infomation ssys::CheckValid(const trm::Infomation &infomation)
{
    assert(infomation[0] == trm::rqs::CHECK_ACCOUNT); // Procession not matched.

    if (infomation[1] == "adm" && infomation[2] == "123") {
        return {trm::rpl::YES};
    }
    
    // TODO: check database

    return {trm::rpl::NO};
}
