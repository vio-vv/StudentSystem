#include "student_system.hpp"

trm::Information ssys::Nolify::PublishNolify(const trm::Information &content) noexcept
{
    assert(content[0] == trm::rqs::PUBLISH_NOLIFY);

    auto reply = SSys::Get().CheckAccess({trm::rqs::CHECK_ACCESS, content[1], content[2], trm::AccessBox{trm::Access::MANAGE_NOLIFY}});
    if (reply[0] == trm::rpl::NO) return {trm::rpl::ACCESS_DENIED};
    else {
        nolify[content[5]].Push(trm::Notice{content[3], content[4]});
    }
    return {trm::rpl::SUCC};
}

trm::Information ssys::Nolify::DeleteNolify(const trm::Information &content) noexcept
{
    assert(content[0] == trm::rqs::DELETE_NOLIFY);
    
    auto reply = SSys::Get().CheckAccess({trm::rqs::CHECK_ACCESS, content[1], content[2], trm::AccessBox{trm::Access::MANAGE_NOLIFY}});
    if (reply[0] == trm::rpl::NO) return {trm::rpl::ACCESS_DENIED};
    else {
        nolify[content[4]][ToNum<unsigned long long>(content[3])].Clear();
    }

    return {trm::rpl::SUCC};
}

trm::Information ssys::Nolify::GetNolifyNumber(const trm::Information &content) noexcept
{
    assert(content[0] == trm::rqs::GET_NOLIFY_NUMBER);

    return {ToStr(nolify[content[1]].Size())};
}

trm::Information ssys::Nolify::GetNolifyTitle(const trm::Information &content) noexcept
{
    assert(content[0] == trm::rqs::GET_NOLIFY_LIST);

    unsigned long long start = std::max(0 * 1ull, ToNum<unsigned long long>(content[1]));
    unsigned long long end = std::min(nolify[content[3]].Size(), ToNum<unsigned long long>(content[2]));

    trm::Information result;
    for (unsigned long long i = start; i <= end; ++i) {
        auto notice = trm::Notice(nolify[content[3]][i]);
        notice.content = "";
        result.emplace_back(notice);
    }
    return result;
}

trm::Information ssys::Nolify::GetNolifyContent(const trm::Information &content) noexcept
{
    assert(content[0] == trm::rqs::GET_NOLIFY);

    return {trm::Notice(nolify[content[2]][ToNum<unsigned long long>(content[1])])};
}

ssys::Nolify::Nolify() noexcept
{
}

ssys::Nolify::~Nolify() noexcept
{
}
