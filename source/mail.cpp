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
            std::cout << __FILE__ << ':' << __LINE__ << ":Failed to create directory." << std::endl;
            return {trm::rpl::FAIL};
        }
    }

    auto filePath = file::GetFilePath(receiver, trm::Combine({infomation[1], ToStr(trm::GetTimeStamp()), ToStr(trm::GenerateRandomCode())}, '.'));
    if (!file::WriteFile(filePath, infomation[4])) {
        std::cout << __FILE__ << ':' << __LINE__ << ":Failed to write file." << std::endl;
        return {trm::rpl::FAIL};
    }

    return {trm::rpl::SUCC};
}

trm::Infomation ssys::MailSystem::GetMessageNumber(const trm::Infomation &infomation) noexcept
{
    assert(infomation[0] == trm::rqs::GET_MESSAGE_NUMBER); // Procession not matched.

    auto it = mailBoxes.find(infomation[1]);
    if (it == mailBoxes.end()) {
        return {trm::rpl::NO_ACCOUNT};
    }

    return {ToStr(it->second.size())};
}

ssys::MailSystem::MailSystem() noexcept
{
    if (!file::CheckDirectoryExists(dataPath)) {
        if (!file::CreateDirectory(dataPath)) {
            std::cout << __FILE__ << ':' << __LINE__ << ":Failed to create directory." << std::endl;
            exit(1);
        }
    }

    auto [success, content] = file::ListDirectory(dataPath);
    if (!success) {
        std::cout << __FILE__ << ':' << __LINE__ << ":Failed to list directory." << std::endl;
        exit(1);
    }

    for (const auto &each : content) {
        mailBoxes.insert({each, {}});

        auto receiver = file::GetFilePath(dataPath, each);

        auto [success, messages] = file::ListDirectory(receiver);
        if (!success) {
            std::cout << __FILE__ << ':' << __LINE__ << ":Failed to list directory." << std::endl;
            exit(1);
        }
        
        for (const auto &message : messages) {
            auto [success, mailContent] = file::ReadFile(file::GetFilePath(receiver, message));
            if (!success) {
                std::cout << __FILE__ << ':' << __LINE__ << ":Failed to read file." << std::endl;
                exit(1);
            }
            mailBoxes[each].push_back(trm::MailContent(mailContent));
        }

        std::sort(mailBoxes[each].begin(), mailBoxes[each].end(), [](const trm::MailContent &a, const trm::MailContent &b) {
            return a.timeStamp < b.timeStamp;
        });
    }
}

ssys::MailSystem::~MailSystem() noexcept
{
}
