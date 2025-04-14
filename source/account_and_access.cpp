#include "subsystems/account_and_access.hpp"
#include "student_system.hpp"

trm::Infomation SSys::CheckAccount(const trm::Infomation &infomation) noexcept
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

trm::Infomation ssys::AccountAndAccess::CreateAccount(const trm::Infomation &infomation) noexcept
{
    assert(infomation[0] == trm::rqs::CREATE_ACCOUNT); // Procession not matched.

    auto account = trm::Account(infomation[1]);
    if (accounts.find(account.code) != accounts.end()) {
        return {trm::rpl::FAIL};
    }

    accounts.insert({account.code, account});
    Save();
    return {trm::rpl::SUCC};
}

void ssys::AccountAndAccess::Save() const noexcept
{
    if (!file::WriteFile(file::GetFilePath(DATA_PATH, "accounts.acc"), trm::Combine(
        trm::Foreach<std::string, std::pair<const std::string, trm::Account>>(accounts, [](const std::pair<const std::string, trm::Account> &each) {
            return (std::string)each.second;
        })
    ))) {
        assert(false); // Failed to create accounts file.
        std::cout << __FILE__ << ':' << __LINE__ << ":Failed to create accounts file." << std::endl;
        exit(1);
    }
}

ssys::AccountAndAccess::AccountAndAccess() noexcept
{
    if (!file::CheckFileExists(file::GetFilePath(DATA_PATH, "accounts.acc"))) {
        if (!file::WriteFile(file::GetFilePath(DATA_PATH, "accounts.acc"), trm::Combine({
            trm::Account{"adm", "123", {trm::Access::ALL}}
        }))) {
            assert(false); // Failed to create accounts file.
            std::cout << __FILE__ << ':' << __LINE__ << ":Failed to create accounts file." << std::endl;
            exit(1);
        }
    }

    auto ok_content = file::ReadFile(file::GetFilePath(DATA_PATH, "accounts.acc"));
    if (!ok_content.first) {
        assert(false); // Failed to read accounts file.
        std::cout << __FILE__ << ':' << __LINE__ << ":Failed to read accounts file." << std::endl;
        exit(1);
    }
    auto content = trm::Split(ok_content.second);

    for (const auto &each : content) {
        auto account = trm::Account(each);
        accounts.insert({account.code, account});
    }
}

ssys::AccountAndAccess::~AccountAndAccess() noexcept
{
    Save();
}
