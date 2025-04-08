#include "student_system.hpp"

trm::Infomation SSys::CheckAccount(const trm::Infomation &infomation) noexcept
{
    assert(infomation[0] == trm::rqs::CHECK_ACCOUNT); // Procession not matched.

    for (auto acc : accounts) {
        if (acc.code == infomation[1] && acc.passwordHash == trm::Hash(infomation[2])) {
            return {trm::rpl::YES};
        }
    }

    return {trm::rpl::NO};
}

SSys::~SSys()
{
}

SSys::SSys()
{
    auto filePath = file::GetFilePath(DATA_PATH, "accounts.txt");
    if (!file::CheckFileExists(filePath)) {
        if (!file::WriteFile(filePath, trm::Combine({trm::Combine({"adm", trm::Hash("123")})}, '\n'))) {
            assert(false); // Failed to create file.
            std::cout << __FILE__ << ":" << __LINE__ << ":Failed to create file: " << filePath << std::endl;
            exit(2);
        }
    }
    auto ok_content = file::ReadFile(filePath);
    if (!ok_content.first) {
        assert(false); // Failed to read file.
        std::cout << __FILE__ << ":" << __LINE__ << ":Failed to read file: " << filePath << std::endl;
        exit(3);
    }

    for (const auto &accountContent : trm::Split(ok_content.second, '\n')) {
        auto accountList = trm::Split(accountContent);
        accounts.push_back({accountList[0], accountList[1]});
    }
}
