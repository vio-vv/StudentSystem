#include "subsystems/mail.hpp"
#include "student_system.hpp"

const std::string ssys::MailSystem::dataPath = file::GetFilePath(DATA_PATH, "mail");

trm::Infomation ssys::MailSystem::SendMessage(const trm::Infomation &infomation) noexcept
{
    assert(infomation[0] == trm::rqs::SEND_MESSAGE); // Procession not matched.

    auto reply = SSys::Get().CheckAccess({trm::rqs::CHECK_ACCESS, infomation[1], infomation[2], trm::Access::SEND_MESSAGE});
    if (reply[0] != trm::rpl::YES) {
        return {trm::rpl::ACCESS_DENIED};
    }

    auto receiver = file::GetFilePath(dataPath, infomation[3]);
    if (!file::CheckDirectoryExists(receiver)) {
        if (!file::CreateDirectory(receiver)) {
            assert(false); // Failed to create directory.
            std::cout << __FILE__ << ':' << __LINE__ << ":Failed to create directory." << std::endl;
            return {trm::rpl::FAIL};
        }
    }

    auto filePath = file::GetFilePath(receiver, trm::Combine({infomation[1], trm::ToStr(trm::GetTimeStamp()), trm::ToStr(trm::GenerateRandomCode())}, '.'));
    if (!file::WriteFile(filePath, infomation[4])) {
        assert(false); // Failed to write file.
        std::cout << __FILE__ << ':' << __LINE__ << ":Failed to write file." << std::endl;
        return {trm::rpl::FAIL};
    }

    return {trm::rpl::SUCC};
}

trm::Infomation ssys::MailSystem::GetMessageNumber(const trm::Infomation &infomation) noexcept
{
    assert(infomation[0] == trm::rqs::GET_MESSAGE_NUMBER); // Procession not matched.

    auto receiver = file::GetFilePath(dataPath, infomation[1]);
    if (!file::CheckDirectoryExists(receiver)) {
        if (!file::CreateDirectory(receiver)) {
            assert(false); // Failed to create directory.
            std::cout << __FILE__ << ':' << __LINE__ << ":Failed to create directory." << std::endl;
            exit(1);
        }
    }

    auto ok_content = file::ListDirectory(receiver);
    if (!ok_content.first) {
        assert(false); // Failed to list directory.
        std::cout << __FILE__ << ':' << __LINE__ << ":Failed to list directory." << std::endl;
        exit(1);
    }

    return {trm::ToStr(ok_content.second.size())};
}

ssys::MailSystem::MailSystem() noexcept
{
    if (!file::CheckDirectoryExists(dataPath)) {
        if (!file::CreateDirectory(dataPath)) {
            assert(false); // Failed to create directory.
            std::cout << __FILE__ << ':' << __LINE__ << ":Failed to create directory." << std::endl;
            exit(1);
        }
    }
}

ssys::MailSystem::~MailSystem() noexcept
{
}
