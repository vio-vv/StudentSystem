#include "subsystems/reserve.hpp"
#include "student_system.hpp"

const std::string ssys::ReserveSystem::dataPath=file::GetFilePath(DATA_PATH,"reserve");

ssys::ReserveSystem::ReserveSystem() noexcept
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
        reserveReplyList.insert({each, {}});
    }
    for (const auto &each : reserveReplyList) {
        auto [success, read] = file::ReadFile(file::GetFilePath(dataPath, each.first));
        if (!success) {
            std::cout << __FILE__ << ':' << __LINE__ << ":Failed to read file." << std::endl;
            exit(1);
        }
        auto reserveContent = trm::Split(read);
        for (const auto &reserve : reserveContent) {
            reserveReplyList[each.first].push_back(trm::ReserveInformation::Server(reserve));
        }
    }
}

ssys::ReserveSystem::~ReserveSystem() noexcept
{
}

trm::Information ssys::ReserveSystem::CheckReserveTime(const trm::Information& information) noexcept
{
    assert(information[0]==trm::rqs::CHECK_RESERVE_TIME);
    auto targetReserve = reserveReplyList.find(information[1]);
    auto time = targetReserve->second[0].leftTime;//不对劲
    trm::Information timeReply;
    for(const auto& each : time) {
        auto splitResult = trm::Split(each);
        timeReply.insert(timeReply.end(), splitResult.begin(), splitResult.end());
    }
    auto  checkTime = std::find(timeReply.begin(), timeReply.end(), information[1]);
    if (checkTime == timeReply.end()) {
        return {trm::rpl::NO_MATCH_TIME};
    }
    auto checkNumber = targetReserve->second[0].leftNumber;
    if (checkNumber == "0") {
        return {trm::rpl::NO_LEFT_RESERVE};
    } 
}

trm::Information ssys::ReserveSystem::RequestReserve(const trm::Information& information) noexcept
{
    assert(information[0] == trm::rqs::REQUEST_RESERVE); // Procession not matched.
    auto it = reserveRequestList.find(information[1]);
    if (it != reserveRequestList.end()) {
        return {trm::rpl::RESERVE_EXISTS};
    }
    auto timeReply=SSys::Get().CheckReserveTime(trm::Split(trm::Combine({trm::rqs::CHECK_RESERVE_TIME, information[3]})));
    if(timeReply[0]!=trm::rpl::YES){
        return {trm::rpl::NO_MATCH_RESERVE};
    }
    reserveRequestList.insert({information[1], {}});
    return {trm::rpl::SUCC};
}

trm::Information ssys::ReserveSystem::CancelReserve(const trm::Information& information) noexcept
{
    assert(information[0] == trm::rqs::CANCEL_RESERVE); // Procession not matched.
    auto it = reserveRequestList.find(information[1]);
    auto reply=SSys::Get().CheckAccess({trm::rqs::CHECK_ACCESS, information[2], information[3], trm::Access::CANCEL_RESERVE});//在reservesystem里面写一个检查权限的函数
    if(reply[0]!=trm::rpl::YES){
        return {trm::rpl::ACCESS_DENIED};
    }
    if (it == reserveRequestList.end()) {
        return {trm::rpl::NO_MATCH_RESERVE};
    }
    reserveRequestList.erase(it);
    return {trm::rpl::SUCC};
}