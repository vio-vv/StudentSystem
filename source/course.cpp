#include "subsystems/course.hpp"
#include "student_system.hpp"

const std::string ssys::CourseSystem::dataPath =file::GetFilePath(DATA_PATH, "course");

ssys::CourseSystem::CourseSystem() noexcept
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
        courseList.insert({each, {}});
    }
    for (const auto &each : courseList) {
        auto [success, read] = file::ReadFile(file::GetFilePath(dataPath, each.first));
        if (!success) {
            std::cout << __FILE__ << ':' << __LINE__ << ":Failed to read file." << std::endl;
            exit(1);
        }
        auto courseContent = trm::Split(read);
        for (const auto &course : courseContent) {
            courseList[each.first].push_back(trm::CourseInformation(course));
        }
    }
}

ssys::CourseSystem::~CourseSystem() noexcept
{
}

trm::Information ssys::CourseSystem::SearchCourse(const trm::Information& information) noexcept
{
    assert(information[0] == trm::rqs::SEARCH_COURSE); // Procession not matched.
    auto it = courseList.find(information[1]);
    if (it == courseList.end()) {
        return {trm::rpl::NO_MATCH_COURSE};
    }
    return {ToStr(it->second.size())};
}

trm::Information ssys::CourseSystem::AddCourse(const trm::Information& information) noexcept
{
    assert(information[0] == trm::rqs::ADD_COURSE); // Procession not matched.
    auto reply = SSys::Get().CheckAccess({trm::rqs::CHECK_ACCESS, information[1], information[2], trm::Access::ADD_COURSE});//待修改，参数不太对
    if (reply[0] != trm::rpl::YES) {
        return {trm::rpl::ACCESS_DENIED};
    }
    auto it = courseList.find(information[1]);
    if (it != courseList.end()) {
        return {trm::rpl::COURSE_EXISTS};
    }
    courseList[information[1]] = {trm::CourseInformation(information[2], information[3], information[4], std::vector<std::string>{information.begin() + 5, information.end()})};
    return {trm::rpl::SUCC};
}

trm::Information ssys::CourseSystem::DeleteCourse(const trm::Information& information) noexcept
{
    assert(information[0] == trm::rqs::DELETE_COURSE); // Procession not matched.
    auto reply = SSys::Get().CheckAccess({trm::rqs::CHECK_ACCESS, information[1], information[2], trm::Access::DELETE_COURSE});//待修改，参数不太对
    if (reply[0] != trm::rpl::YES) {
        return {trm::rpl::ACCESS_DENIED};
    }
    auto it = courseList.find(information[1]);
    if (it == courseList.end()) {
        return {trm::rpl::NO_MATCH_COURSE};
    }
    courseList.erase(it);
    return {trm::rpl::SUCC};
}

