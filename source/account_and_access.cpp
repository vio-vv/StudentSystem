#include "subsystems/account_and_access.hpp"
#include "student_system.hpp"

const std::string ssys::AccountAndAccess::dataPath = file::GetFilePath(DATA_PATH, "acc_acc");

trm::Infomation ssys::AccountAndAccess::CheckAccountExist(const trm::Infomation &infomation) noexcept
{
    assert(infomation[0] == trm::rqs::CHECK_ACCOUNT_EXISTS); // Procession not matched.

    if (accounts.find(infomation[1]) == accounts.end()) {
        return {trm::rpl::NO};
    } else {
        return {trm::rpl::YES};
    }
}

trm::Infomation ssys::AccountAndAccess::CheckAccount(const trm::Infomation &infomation) noexcept
{
    assert(infomation[0] == trm::rqs::CHECK_ACCOUNT); // Procession not matched.

    auto it = accounts.find(infomation[1]);
    if (it == accounts.end()) {
        return {trm::rpl::NO, trm::rpl::NO_ACCOUNT};
    }
    if (trm::Hash(infomation[2]) == it->second.hashedPassword) {
        return {trm::rpl::YES, it->second};
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
    if (accounts.find(account.code) != accounts.end()) {
        return {trm::rpl::FAIL};
    }
    reply = SSys::Get().CheckAccount({trm::rqs::CHECK_ACCOUNT, infomation[1], infomation[2]});
    if (reply[0] != trm::rpl::YES) {
        return {trm::rpl::ACCESS_DENIED};
    }
    auto creatorAccess = trm::Account(reply[1]).access;
    account.access = AccessCross(account.access, creatorAccess);

    accounts.insert({account.code, account});
    if (!file::WriteFile(file::GetFilePath(dataPath, account.code + ".acc"), account)) {
        assert(false); // Failed to write accounts file.
        std::cout << __FILE__ << ':' << __LINE__ << ":Failed to write accounts file." << std::endl;
        return {trm::rpl::FAIL};
    }
    return {trm::rpl::SUCC};
}

trm::Infomation ssys::AccountAndAccess::DeleteAccount(const trm::Infomation &infomation) noexcept
{
    assert(infomation[0] == trm::rqs::DELETE_ACCOUNT); // Procession not matched.

    auto reply = SSys::Get().CheckAccess({trm::rqs::CHECK_ACCESS, infomation[1], infomation[2], trm::Access::DELETE_ACCOUNT});
    if (reply[0] != trm::rpl::YES) {
        return {trm::rpl::ACCESS_DENIED};
    }

    auto it = accounts.find(infomation[3]);
    if (it == accounts.end()) {
        return {trm::rpl::FAIL};
    }

    accounts.erase(it);
    if (!file::DeleteFile(file::GetFilePath(dataPath, infomation[3] + ".acc"))) {
        assert(false); // Failed to delete accounts file.
        std::cout << __FILE__ << ':' << __LINE__ << ":Failed to delete accounts file." << std::endl;
        return {trm::rpl::FAIL};
    }
    return {trm::rpl::SUCC};

}
ssys::AccountAndAccess::AccountAndAccess() noexcept
{
    if (!file::CheckDirectoryExists(dataPath)) {
        if (!file::CreateDirectory(dataPath)) {
            assert(false); // Failed to create accounts directory.
            std::cout << __FILE__ << ':' << __LINE__ << ":Failed to create accounts directory." << std::endl;
            exit(1);
        }
    }
    if (!file::CheckFileExists(file::GetFilePath(dataPath, "adm.acc"))) {
        if (!file::WriteFile(file::GetFilePath(dataPath, "adm.acc"), 
            trm::Account{"adm", "123", {trm::Access::ADM}}
        )) {
            assert(false); // Failed to create accounts file.
            std::cout << __FILE__ << ':' << __LINE__ << ":Failed to create accounts file." << std::endl;
            exit(1);
        }
    }

    auto [success, content] = file::ListDirectory(dataPath);
    if (!success) {
        assert(false); // Failed to read accounts file.
        std::cout << __FILE__ << ':' << __LINE__ << ":Failed to read accounts file." << std::endl;
        exit(1);
    }
    for (const auto &each : content) {
        auto [success, account] = file::ReadFile(file::GetFilePath(dataPath, each));
        if (!success) {
            assert(false); // Failed to read accounts file.
            std::cout << __FILE__ << ':' << __LINE__ << ":Failed to read accounts file." << std::endl;
        }
        auto accountObj = trm::Account(account);
        accounts.insert({accountObj.code, accountObj});
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
    return result;
}
