#include "student_system.hpp"

const std::string ssys::AccountAndAccess::ACCOUNTS = "accounts";

trm::Information ssys::AccountAndAccess::CheckAccountExist(const trm::Information &information) noexcept
{
    assert(information[0] == trm::rqs::CHECK_ACCOUNT_EXISTS); // Procession not matched.

    if (base[ACCOUNTS][information[1]].Exists()) {
        return {trm::rpl::YES};
    } else {
        return {trm::rpl::NO};
    }
}

trm::Information ssys::AccountAndAccess::QueryTag(const trm::Information &information) noexcept
{
    assert(information[0] == trm::rqs::QUERY_TAG); // Procession not matched.

    auto accountBase = base[ACCOUNTS][information[1]];
    if (!accountBase.Exists()) {
        return {trm::rpl::NO, trm::rpl::NO_ACCOUNT};
    }
    auto account = trm::Account(accountBase);

    for (const auto &tag : account.tags) {
        if (tag.first == information[2]) {
            return {trm::rpl::YES, tag.second};
        }
    }
    return {trm::rpl::NO, trm::rpl::NO_TAG};
}

trm::Information ssys::AccountAndAccess::CheckAccount(const trm::Information &information) noexcept
{
    assert(information[0] == trm::rqs::CHECK_ACCOUNT); // Procession not matched.

    auto accountBase = base[ACCOUNTS][information[1]];
    if (!accountBase.Exists()) {
        return {trm::rpl::NO, trm::rpl::NO_ACCOUNT};
    }

    auto account = trm::Account(accountBase);
    if (trm::Hash(information[2]) == account.hashedPassword) {
        return {trm::rpl::YES, account};
    } else {
        return {trm::rpl::NO, trm::rpl::WRONG_PASSWORD};
    }
}

trm::Information ssys::AccountAndAccess::CheckAccess(const trm::Information &information) noexcept
{
    assert(information[0] == trm::rqs::CHECK_ACCESS); // Procession not matched.
    
    auto reply = SSys::Get().CheckAccount({trm::rqs::CHECK_ACCOUNT, information[1], information[2]});

    if (reply[0] == trm::rpl::YES) {
        if (information[3] == trm::Access::EVERYONE_OWN) {
            return {trm::rpl::YES};
        }

        auto account = trm::Account(reply[1]);

        for (const auto &each : account.access) {
            if (each == trm::Access::ADM || each == information[3]) {
                return {trm::rpl::YES};
            }
        }
    }

    return {trm::rpl::NO};
}

trm::Information ssys::AccountAndAccess::CreateAccount(const trm::Information &information) noexcept
{
    assert(information[0] == trm::rqs::CREATE_ACCOUNT); // Procession not matched.

    auto reply = SSys::Get().CheckAccess({trm::rqs::CHECK_ACCESS, information[1], information[2], trm::Access::CREATE_ACCOUNT});
    if (reply[0] != trm::rpl::YES) {
        return {trm::rpl::ACCESS_DENIED};
    }

    auto account = trm::Account(information[3]);
    auto accountBase = base[ACCOUNTS][account.code];
    if (accountBase.Exists()) {
        return {trm::rpl::FAIL};
    }

    reply = SSys::Get().CheckAccount({trm::rqs::CHECK_ACCOUNT, information[1], information[2]});
    if (reply[0] != trm::rpl::YES) {
        return {trm::rpl::ACCESS_DENIED};
    }
    auto creatorAccess = trm::Account(reply[1]).access;
    account.access = AccessCross(account.access, creatorAccess);

    accountBase = account;
    return {trm::rpl::SUCC};
}

trm::Information ssys::AccountAndAccess::DeleteAccount(const trm::Information &information) noexcept
{
    assert(information[0] == trm::rqs::DELETE_ACCOUNT); // Procession not matched.

    auto reply = SSys::Get().CheckAccess({trm::rqs::CHECK_ACCESS, information[1], information[2], trm::Access::DELETE_ACCOUNT});
    if (reply[0] != trm::rpl::YES) {
        return {trm::rpl::ACCESS_DENIED};
    }

    auto accountBase = base[ACCOUNTS][information[3]];
    if (!accountBase.Exists()) {
        return {trm::rpl::FAIL};
    }

    accountBase.Clear();
    return {trm::rpl::SUCC};

}

trm::Information ssys::AccountAndAccess::GrantAccess(const trm::Information &information) noexcept
{
    assert(information[0] == trm::rqs::GRANT_ACCESS); // Procession not matched.

    auto reply = SSys::Get().CheckAccess({trm::rqs::CHECK_ACCESS, information[1], information[2], trm::Access::GRANT_ACCESS});
    if (reply[0] != trm::rpl::YES) {
        return {trm::rpl::ACCESS_DENIED};
    }

    reply = SSys::Get().CheckAccess({trm::rqs::CHECK_ACCESS, information[1], information[2], information[4]});
    if (reply[0] != trm::rpl::YES) {
        return {trm::rpl::ACCESS_DENIED};
    }

    auto accountBase = base[ACCOUNTS][information[3]];
    if (!accountBase.Exists()) {
        return {trm::rpl::FAIL};
    }

    auto account = trm::Account(accountBase);
    auto iter = std::find(account.access.begin(), account.access.end(), information[4]);
    if (iter == account.access.end()) {
        account.access.push_back(information[4]);
    }
    accountBase = account;
    return {trm::rpl::SUCC};
}

trm::Information ssys::AccountAndAccess::RevokeAccess(const trm::Information &information) noexcept
{
    assert(information[0] == trm::rqs::REVOKE_ACCESS); // Procession not matched.

    auto reply = SSys::Get().CheckAccess({trm::rqs::CHECK_ACCESS, information[1], information[2], trm::Access::REVOKE_ACCESS});
    if (reply[0] != trm::rpl::YES) {
        return {trm::rpl::ACCESS_DENIED};
    }

    reply = SSys::Get().CheckAccess({trm::rqs::CHECK_ACCESS, information[1], information[2], information[4]});
    if (reply[0] != trm::rpl::YES) {
        return {trm::rpl::ACCESS_DENIED};
    }

    auto accountBase = base[ACCOUNTS][information[3]];
    if (!accountBase.Exists()) {
        return {trm::rpl::FAIL};
    }

    auto account = trm::Account(accountBase);
    auto iter = std::find(account.access.begin(), account.access.end(), information[4]);
    if (iter != account.access.end()) {
        account.access.erase(iter);
    }
    accountBase = account;
    return {trm::rpl::SUCC};
}

trm::Information ssys::AccountAndAccess::RevokeAllAccess(const trm::Information &information) noexcept
{
    assert(information[0] == trm::rqs::REVOKE_ALL_ACCESS); // Procession not matched.

    auto reply = SSys::Get().CheckAccess({trm::rqs::CHECK_ACCESS, information[1], information[2], trm::Access::REVOKE_ACCESS});
    if (reply[0] != trm::rpl::YES) {
        return {trm::rpl::ACCESS_DENIED};
    }

    auto accountBase = base[ACCOUNTS][information[3]];
    if (!accountBase.Exists()) {
        return {trm::rpl::FAIL};
    }
    auto account = trm::Account(accountBase);

    reply = SSys::Get().CheckAccount({trm::rqs::CHECK_ACCOUNT, information[1], information[2]});
    if (reply[0] != trm::rpl::YES) {
        return {trm::rpl::ACCESS_DENIED};
    }
    auto creatorAccess = trm::Account(reply[1]).access;

    for (const auto &each : AccessCross(account.access, creatorAccess)) {
        auto iter = std::find(account.access.begin(), account.access.end(), each);
        if (iter != account.access.end()) {
            account.access.erase(iter);
        }
    }
    
    accountBase = account;
    return {trm::rpl::SUCC};
}

trm::Information ssys::AccountAndAccess::AddTag(const trm::Information &information) noexcept
{
    assert(information[0] == trm::rqs::ADD_TAG); // Procession not matched.

    auto reply = SSys::Get().CheckAccess({trm::rqs::CHECK_ACCESS, information[1], information[2], trm::Access::ADD_TAG});
    if (reply[0] != trm::rpl::YES) {
        return {trm::rpl::ACCESS_DENIED};
    }

    auto accountBase = base[ACCOUNTS][information[3]];
    if (!accountBase.Exists()) {
        return {trm::rpl::FAIL};
    }

    auto account = trm::Account(accountBase);
    for (auto &tag : account.tags) {
        if (tag.first == information[4]) {
            tag.second = information[5];
            accountBase = account;
            return {trm::rpl::SUCC};
        }
    }

    account.tags.push_back({information[4], information[5]});
    accountBase = account;
    return {trm::rpl::SUCC};
}

trm::Information ssys::AccountAndAccess::RemoveTag(const trm::Information &information) noexcept
{
    assert(information[0] == trm::rqs::REMOVE_TAG); // Procession not matched.

    auto reply = SSys::Get().CheckAccess({trm::rqs::CHECK_ACCESS, information[1], information[2], trm::Access::REMOVE_TAG});
    if (reply[0] != trm::rpl::YES) {
        return {trm::rpl::ACCESS_DENIED};
    }

    auto accountBase = base[ACCOUNTS][information[3]];
    if (!accountBase.Exists()) {
        return {trm::rpl::FAIL};
    }

    auto account = trm::Account(accountBase);
    for (auto iter = account.tags.begin(); iter != account.tags.end(); ++iter) {
        if (iter->first == information[4]) {
            account.tags.erase(iter);
            accountBase = account;
            return {trm::rpl::SUCC};
        }
    }
    return {trm::rpl::FAIL};
}

trm::Information ssys::AccountAndAccess::ClearTag(const trm::Information &information) noexcept
{
    assert(information[0] == trm::rqs::CLEAR_TAG); // Procession not matched.

    auto reply = SSys::Get().CheckAccess({trm::rqs::CHECK_ACCESS, information[1], information[2], trm::Access::REMOVE_TAG});
    if (reply[0] != trm::rpl::YES) {
        return {trm::rpl::ACCESS_DENIED};
    }

    auto accountBase = base[ACCOUNTS][information[3]];
    if (!accountBase.Exists()) {
        return {trm::rpl::FAIL};
    }

    auto account = trm::Account(accountBase);
    account.tags.clear();
    accountBase = account;
    return {trm::rpl::SUCC};
}

trm::Information ssys::AccountAndAccess::ResetAccountAndAccess(const trm::Information &information) noexcept
{
    assert(information[0] == trm::rqs::RESET_ACCOUNT_AND_ACCESS); // Procession not matched.

    auto reply = SSys::Get().CheckAccess({trm::rqs::CHECK_ACCESS, information[1], information[2], trm::Access::RESET_ACCOUNT_AND_ACCESS});
    if (reply[0] != trm::rpl::YES) {
        return {trm::rpl::ACCESS_DENIED};
    }

    base.Remove();
    return {trm::rpl::SUCC};
}

ssys::AccountAndAccess::AccountAndAccess() noexcept
{
    auto admBase = base[ACCOUNTS]["adm"];
    if (!admBase.Exists()) {
        admBase = trm::Account{"adm", "123", {trm::Access::ADM}};
    }
}

ssys::AccountAndAccess::~AccountAndAccess() noexcept
{
    ;
}

std::vector<std::string> ssys::AccountAndAccess::AccessCross(const std::vector<std::string> &access, const std::vector<std::string> &creator) noexcept
{
    if (std::find(creator.begin(), creator.end(), trm::Access::ADM) != creator.end()) {
        return access;
    }
    std::vector<std::string> result;
    for (const auto &each : access) {
        if (std::find(creator.begin(), creator.end(), each) != creator.end()) {
            result.push_back(each);
        }
    }
    return std::move(result);
}
