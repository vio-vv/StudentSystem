#include "subsystems/account_and_access.hpp"
#include "student_system.hpp"

const std::string ssys::AccountAndAccess::ACCOUNTS = "accounts";

trm::Infomation ssys::AccountAndAccess::CheckAccountExist(const trm::Infomation &infomation) noexcept
{
    assert(infomation[0] == trm::rqs::CHECK_ACCOUNT_EXISTS); // Procession not matched.

    if (base[ACCOUNTS][infomation[1]].Exists()) {
        return {trm::rpl::YES};
    } else {
        return {trm::rpl::NO};
    }
}

trm::Infomation ssys::AccountAndAccess::CheckAccount(const trm::Infomation &infomation) noexcept
{
    assert(infomation[0] == trm::rqs::CHECK_ACCOUNT); // Procession not matched.

    auto accountBase = base[ACCOUNTS][infomation[1]];
    if (!accountBase.Exists()) {
        return {trm::rpl::NO, trm::rpl::NO_ACCOUNT};
    }

    auto account = trm::Account(accountBase);
    if (trm::Hash(infomation[2]) == account.hashedPassword) {
        return {trm::rpl::YES, account};
    } else {
        return {trm::rpl::NO, trm::rpl::WRONG_PASSWORD};
    }
}

trm::Infomation ssys::AccountAndAccess::CheckAccess(const trm::Infomation &infomation) noexcept
{
    assert(infomation[0] == trm::rqs::CHECK_ACCESS); // Procession not matched.
    
    auto reply = SSys::Get().CheckAccount({trm::rqs::CHECK_ACCOUNT, infomation[1], infomation[2]});

    if (reply[0] == trm::rpl::YES) {
        auto account = trm::Account(reply[1]);

        for (const auto &each : account.access) {
            if (each == trm::Access::ADM || each == infomation[3]) {
                return {trm::rpl::YES};
            }
        }
    }

    return {trm::rpl::NO};
}

trm::Infomation ssys::AccountAndAccess::CreateAccount(const trm::Infomation &infomation) noexcept
{
    assert(infomation[0] == trm::rqs::CREATE_ACCOUNT); // Procession not matched.

    auto reply = SSys::Get().CheckAccess({trm::rqs::CHECK_ACCESS, infomation[1], infomation[2], trm::Access::CREATE_ACCOUNT});
    if (reply[0] != trm::rpl::YES) {
        return {trm::rpl::ACCESS_DENIED};
    }

    auto account = trm::Account(infomation[3]);
    auto accountBase = base[ACCOUNTS][account.code];
    if (accountBase.Exists()) {
        return {trm::rpl::FAIL};
    }

    reply = SSys::Get().CheckAccount({trm::rqs::CHECK_ACCOUNT, infomation[1], infomation[2]});
    if (reply[0] != trm::rpl::YES) {
        return {trm::rpl::ACCESS_DENIED};
    }
    auto creatorAccess = trm::Account(reply[1]).access;
    account.access = AccessCross(account.access, creatorAccess);

    accountBase = account;
    return {trm::rpl::SUCC};
}

trm::Infomation ssys::AccountAndAccess::DeleteAccount(const trm::Infomation &infomation) noexcept
{
    assert(infomation[0] == trm::rqs::DELETE_ACCOUNT); // Procession not matched.

    auto reply = SSys::Get().CheckAccess({trm::rqs::CHECK_ACCESS, infomation[1], infomation[2], trm::Access::DELETE_ACCOUNT});
    if (reply[0] != trm::rpl::YES) {
        return {trm::rpl::ACCESS_DENIED};
    }

    auto accountBase = base[ACCOUNTS][infomation[3]];
    if (!accountBase.Exists()) {
        return {trm::rpl::FAIL};
    }

    accountBase.Clear();
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
