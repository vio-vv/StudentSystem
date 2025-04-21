#include "subsystems/mail.hpp"
#include "student_system.hpp"

trm::Infomation ssys::MailSystem::SendMessage(const trm::Infomation &infomation) noexcept
{
    assert(infomation[0] == trm::rqs::SEND_MESSAGE); // Procession not matched.

    auto reply = SSys::Get().CheckAccess({trm::rqs::CHECK_ACCESS, infomation[1], infomation[2], trm::Access::SEND_MESSAGE});
    if (reply[0] == trm::rpl::NO) {
        return {trm::rpl::ACCESS_DENIED};
    }

    reply = SSys::Get().CheckAccountExist({trm::rqs::CHECK_ACCOUNT_EXISTS, infomation[3]});
    if (reply[0] == trm::rpl::NO) {
        return {trm::rpl::FAIL};
    }

    base[infomation[3]].Push(infomation[4]);

    return {trm::rpl::SUCC};
}

trm::Infomation ssys::MailSystem::GetMessageNumber(const trm::Infomation &infomation) noexcept
{
    assert(infomation[0] == trm::rqs::GET_MESSAGE_NUMBER); // Procession not matched.

    auto reply = SSys::Get().CheckAccountExist({trm::rqs::CHECK_ACCOUNT_EXISTS, infomation[1]});
    if (reply[0] == trm::rpl::NO) {
        return {trm::rpl::NO_ACCOUNT};
    }

    return {ToStr(base[infomation[1]].Size())};
}

ssys::MailSystem::MailSystem() noexcept
{
    ;
}

ssys::MailSystem::~MailSystem() noexcept
{
    ;
}
