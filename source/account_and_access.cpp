#include "subsystems/account_and_access.hpp"
#include "student_system.hpp"

const std::string ssys::AccountAndAccess::dataPath = file::GetFilePath(DATA_PATH, "acc_acc");

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
    if (!file::WriteFile(file::GetFilePath(dataPath, account.code + ".acc"), account)) {
        assert(false); // Failed to write accounts file.
        std::cout << __FILE__ << ':' << __LINE__ << ":Failed to write accounts file." << std::endl;
        exit(1);
    }
    return {trm::rpl::SUCC};
}

trm::Infomation ssys::AccountAndAccess::DeleteAccount(const trm::Infomation &infomation) noexcept
{
    assert(infomation[0] == trm::rqs::DELETE_ACCOUNT); // Procession not matched.

    auto it = accounts.find(infomation[1]);
    if (it == accounts.end()) {
        return {trm::rpl::FAIL};
    }

    accounts.erase(it);
    if (!file::DeleteFile(file::GetFilePath(dataPath, infomation[1] + ".acc"))) {
        assert(false); // Failed to delete accounts file.
        std::cout << __FILE__ << ':' << __LINE__ << ":Failed to delete accounts file." << std::endl;
        exit(1);
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
            trm::Account{"adm", "123", {trm::Access::ALL}}
        )) {
            assert(false); // Failed to create accounts file.
            std::cout << __FILE__ << ':' << __LINE__ << ":Failed to create accounts file." << std::endl;
            exit(1);
        }
    }

    auto ok_content = file::ListDirectory(dataPath);
    if (!ok_content.first) {
        assert(false); // Failed to read accounts file.
        std::cout << __FILE__ << ':' << __LINE__ << ":Failed to read accounts file." << std::endl;
        exit(1);
    }
    for (const auto &each : ok_content.second) {
        auto ok_account = file::ReadFile(file::GetFilePath(dataPath, each));
        if (!ok_account.first) {
            assert(false); // Failed to read accounts file.
            std::cout << __FILE__ << ':' << __LINE__ << ":Failed to read accounts file." << std::endl;
        }
        auto account = trm::Account(ok_account.second);
        accounts.insert({account.code, account});
    }
}

ssys::AccountAndAccess::~AccountAndAccess() noexcept
{
    ;
}
