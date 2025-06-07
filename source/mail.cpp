#include "student_system.hpp"

const std::string SSys::MailSystem::BOX = "box";
const std::string SSys::MailSystem::UNREAD_NUM = "unread_num";

trm::Information ssys::MailSystem::SendMessage(const trm::Information &information) noexcept
{
    assert(information[0] == trm::rqs::SEND_MESSAGE); // Procession not matched.

    auto reply = SSys::Get().CheckAccess({trm::rqs::CHECK_ACCESS, information[1], information[2], trm::AccessBox{trm::Access::SEND_MESSAGE}});
    if (reply[0] != trm::rpl::YES) {
        return {trm::rpl::ACCESS_DENIED};
    }

    reply = SSys::Get().CheckAccountExist({trm::rqs::CHECK_ACCOUNT_EXISTS, information[3]});
    if (reply[0] != trm::rpl::YES) {
        return {trm::rpl::FAIL};
    }

    base[BOX][information[3]].Push(trm::MailContent{trm::GetTimestamp(), information[1], information[3], information[4], information[5], false});
    base[UNREAD_NUM][information[3]] = ToStr(ToNum<unsigned long long>(base[UNREAD_NUM][information[3]]) + 1);

    return {trm::rpl::SUCC};
}

trm::Information ssys::MailSystem::GetMessageNumber(const trm::Information &information) noexcept
{
    assert(information[0] == trm::rqs::GET_MESSAGE_NUMBER); // Procession not matched.

    return {ToStr(base[BOX][information[1]].Size())};
}

trm::Information ssys::MailSystem::GetMessageProfile(const trm::Information &information) noexcept
{
    assert(information[0] == trm::rqs::GET_MESSAGE_PROFILE); // Procession not matched.

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

    auto reply = SSys::Get().MarkAsRead({trm::rqs::MARK_AS_READ, information[1], information[2], information[3]});
    if (reply[0] != trm::rpl::SUCC) {
        return {trm::rpl::FAIL};
    }

    auto box = base[BOX][information[1]];
    unsigned long long index = ToNum<unsigned long long>(information[3]);

    return {trm::MailContent(box[index])};
}

trm::Information ssys::MailSystem::MarkAsRead(const trm::Information &information) noexcept
{
    assert(information[0] == trm::rqs::MARK_AS_READ); // Procession not matched.

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

    return {ToStr(ToNum<unsigned long long>(base[UNREAD_NUM][information[1]]))};
}

trm::Information ssys::MailSystem::DeleteMessage(const trm::Information &information) noexcept
{
    assert(information[0] == trm::rqs::DELETE_MESSAGE); // Procession not matched.

    auto reply = SSys::Get().CheckAccess({trm::rqs::CHECK_ACCESS, information[1], information[2], trm::AccessBox{trm::Access::DELETE_MESSAGE}});
    if (reply[0] != trm::rpl::YES) {
        return {trm::rpl::ACCESS_DENIED};
    }

    reply = SSys::Get().MarkAsRead({trm::rqs::MARK_AS_READ, information[1], information[2], information[3]});
    if (reply[0] != trm::rpl::SUCC) {
        return {reply[0]};
    }

    auto box = base[BOX][information[1]];
    unsigned long long index = ToNum<unsigned long long>(information[3]);

    box[index].Clear();
    return {trm::rpl::SUCC};
}

trm::Information ssys::MailSystem::ClearMessage(const trm::Information &information) noexcept
{
    assert(information[0] == trm::rqs::CLEAR_MESSAGE); // Procession not matched.

    auto reply = SSys::Get().CheckAccess({trm::rqs::CHECK_ACCESS, information[1], information[2], trm::AccessBox{trm::Access::DELETE_MESSAGE}});
    if (reply[0] != trm::rpl::YES) {
        return {trm::rpl::ACCESS_DENIED};
    }

    auto box = base[BOX][information[1]];
    for (auto [file, mail] : box) {
        mail.Clear();
    }
    base[UNREAD_NUM][information[1]] = "0";

    return {trm::rpl::SUCC};
}

trm::Information ssys::MailSystem::DeleteMessageOfOthers(const trm::Information &information) noexcept
{
    assert(information[0] == trm::rqs::DELETE_MESSAGE_OF_OTHERS); // Procession not matched.

    auto reply = SSys::Get().CheckAccess({trm::rqs::CHECK_ACCESS, information[1], information[2], trm::AccessBox{trm::Access::DELETE_MESSAGE_OF_OTHERS}});
    if (reply[0] != trm::rpl::YES) {
        return {trm::rpl::ACCESS_DENIED};
    }
    
    reply = SSys::Get().CheckAccountExist({trm::rqs::CHECK_ACCOUNT_EXISTS, information[3]});
    if (reply[0] != trm::rpl::YES) {
        return {trm::rpl::FAIL};
    }

    auto box = base[BOX][information[3]];
    unsigned long long index = ToNum<unsigned long long>(information[4]);

    if (index >= box.Size()) {
        return {trm::rpl::FAIL};
    }

    if (!trm::MailContent(box[index]).read) {
        base[UNREAD_NUM][information[3]] = ToStr(ToNum<unsigned long long>(base[UNREAD_NUM][information[3]]) - 1);
    }

    box[index].Clear();
    return {trm::rpl::SUCC};
}

trm::Information ssys::MailSystem::ClearMessageOfOthers(const trm::Information &information) noexcept
{
    assert(information[0] == trm::rqs::CLEAR_MESSAGE_OF_OTHERS); // Procession not matched.

    auto reply = SSys::Get().CheckAccess({trm::rqs::CHECK_ACCESS, information[1], information[2], trm::AccessBox{trm::Access::DELETE_MESSAGE_OF_OTHERS}});
    if (reply[0] != trm::rpl::YES) {
        return {trm::rpl::ACCESS_DENIED};
    }

    reply = SSys::Get().CheckAccountExist({trm::rqs::CHECK_ACCOUNT_EXISTS, information[3]});
    if (reply[0] != trm::rpl::YES) {
        return {trm::rpl::FAIL};
    }

    auto box = base[BOX][information[3]];
    for (auto [file, mail] : box) {
        mail.Clear();
    }
    base[UNREAD_NUM][information[3]] = "0";

    return {trm::rpl::SUCC};
}

trm::Information ssys::MailSystem::ResetMailSystem(const trm::Information &information) noexcept
{
    assert(information[0] == trm::rqs::RESET_MAIL_SYSTEM); // Procession not matched.

    auto reply = SSys::Get().CheckAccess({trm::rqs::CHECK_ACCESS, information[1], information[2], trm::AccessBox{trm::Access::RESET_MAIL_SYSTEM}});
    if (reply[0] != trm::rpl::YES) {
        return {trm::rpl::ACCESS_DENIED};
    }

    base.Remove();
    return {trm::rpl::SUCC};
}

ssys::MailSystem::MailSystem() noexcept
{
    ;
}

ssys::MailSystem::~MailSystem() noexcept
{
    ;
}
