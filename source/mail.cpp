#include "subsystems/mail.hpp"
#include "student_system.hpp"

const std::string SSys::MailSystem::BOX = "box";
const std::string SSys::MailSystem::UNREAD_NUM = "unread_num";

trm::Information ssys::MailSystem::SendMessage(const trm::Information &information) noexcept
{
    assert(information[0] == trm::rqs::SEND_MESSAGE); // Procession not matched.

    auto reply = SSys::Get().CheckAccess({trm::rqs::CHECK_ACCESS, information[1], information[2], trm::Access::SEND_MESSAGE});
    if (reply[0] == trm::rpl::NO) {
        return {trm::rpl::ACCESS_DENIED};
    }

    reply = SSys::Get().CheckAccountExist({trm::rqs::CHECK_ACCOUNT_EXISTS, information[3]});
    if (reply[0] == trm::rpl::NO) {
        return {trm::rpl::FAIL};
    }

    base[BOX][information[3]].Push(trm::MailContent{trm::GetTimeStamp(), information[1], information[3], information[4], information[5], false});
    base[UNREAD_NUM][information[3]] = ToStr(ToNum<unsigned long long>(base[UNREAD_NUM][information[3]]) + 1);

    return {trm::rpl::SUCC};
}

trm::Information ssys::MailSystem::GetMessageNumber(const trm::Information &information) noexcept
{
    assert(information[0] == trm::rqs::GET_MESSAGE_NUMBER); // Procession not matched.

    auto reply = SSys::Get().CheckAccess({trm::rqs::CHECK_ACCESS, information[1], information[2], trm::Access::EVERYONE_OWN});
    if (reply[0] == trm::rpl::NO) {
        return {trm::rpl::ACCESS_DENIED};
    }

    return {ToStr(base[BOX][information[1]].Size())};
}

trm::Information ssys::MailSystem::GetMessageProfile(const trm::Information &information) noexcept
{
    assert(information[0] == trm::rqs::GET_MESSAGE_PROFILE); // Procession not matched.

    auto reply = SSys::Get().CheckAccess({trm::rqs::CHECK_ACCESS, information[1], information[2], trm::Access::EVERYONE_OWN});
    if (reply[0] == trm::rpl::NO) {
        return {trm::rpl::ACCESS_DENIED};
    }

    auto box = base[BOX][information[1]];
    unsigned long long start = ToNum<unsigned long long>(information[3]), count = ToNum<unsigned long long>(information[4]);
    unsigned long long head = std::max(0ull, start);
    unsigned long long tail = std::min(box.Size(), start + count);

    trm::Information result;
    for (unsigned long long i = head; i < tail; ++i) {
        auto each = trm::MailContent(box[i]);
        each.content = "";
        result.push_back(each);
    }
    return std::move(result);
}

trm::Information ssys::MailSystem::GetMessage(const trm::Information &information) noexcept
{
    assert(information[0] == trm::rqs::GET_MESSAGE); // Procession not matched.

    auto reply = SSys::Get().CheckAccess({trm::rqs::CHECK_ACCESS, information[1], information[2], trm::Access::EVERYONE_OWN});
    if (reply[0] == trm::rpl::NO) {
        return {trm::rpl::ACCESS_DENIED};
    }

    auto box = base[BOX][information[1]];
    unsigned long long index = ToNum<unsigned long long>(information[3]);
    if (index >= box.Size()) {
        return {trm::rpl::FAIL};
    }

    SSys::Get().MarkAsRead({trm::rqs::MARK_AS_READ, information[1], information[2], information[3]});
    return {trm::MailContent(box[index])};
}

trm::Information ssys::MailSystem::MarkAsRead(const trm::Information &information) noexcept
{
    assert(information[0] == trm::rqs::MARK_AS_READ); // Procession not matched.

    auto reply = SSys::Get().CheckAccess({trm::rqs::CHECK_ACCESS, information[1], information[2], trm::Access::EVERYONE_OWN});
    if (reply[0] == trm::rpl::NO) {
        return {trm::rpl::ACCESS_DENIED};
    }

    auto box = base[BOX][information[1]];
    unsigned long long index = ToNum<unsigned long long>(information[3]);
    if (index >= box.Size()) {
        return {trm::rpl::FAIL};
    }

    auto mail = trm::MailContent(box[index]);
    if (!mail.read) {
        mail.read = true;
        box[index] = mail;
        base[UNREAD_NUM][information[1]] = ToStr(ToNum<unsigned long long>(base[UNREAD_NUM][information[1]]) - 1);
    }

    return {trm::rpl::SUCC};
}

trm::Information ssys::MailSystem::MarkAsUnread(const trm::Information &information) noexcept
{
    assert(information[0] == trm::rqs::MARK_AS_UNREAD); // Procession not matched.
    
    auto reply = SSys::Get().CheckAccess({trm::rqs::CHECK_ACCESS, information[1], information[2], trm::Access::EVERYONE_OWN});
    if (reply[0] == trm::rpl::NO) {
        return {trm::rpl::ACCESS_DENIED};
    }

    auto box = base[BOX][information[1]];
    unsigned long long index = ToNum<unsigned long long>(information[3]);
    if (index >= box.Size()) {
        return {trm::rpl::FAIL};
    }

    auto mail = trm::MailContent(box[index]);
    if (mail.read) {
        mail.read = false;
        box[index] = mail;
        base[UNREAD_NUM][information[1]] = ToStr(ToNum<unsigned long long>(base[UNREAD_NUM][information[1]]) + 1);
    }

    return {trm::rpl::SUCC};
}

trm::Information ssys::MailSystem::GetUnreadMessageNumber(const trm::Information &information) noexcept
{
    assert(information[0] == trm::rqs::GET_UNREAD_MESSAGE_NUMBER); // Procession not matched.

    auto reply = SSys::Get().CheckAccess({trm::rqs::CHECK_ACCESS, information[1], information[2], trm::Access::EVERYONE_OWN});
    if (reply[0] == trm::rpl::NO) {
        return {trm::rpl::ACCESS_DENIED};
    }

    return {ToStr(ToNum<unsigned long long>(base[UNREAD_NUM][information[1]]))};
}

ssys::MailSystem::MailSystem() noexcept
{
    ;
}

ssys::MailSystem::~MailSystem() noexcept
{
    ;
}
