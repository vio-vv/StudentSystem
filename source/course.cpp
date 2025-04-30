#include "subsystems/course.hpp"
#include "student_system.hpp"

ssys::CourseSystem::CourseSystem() noexcept
{
   
}

ssys::CourseSystem::~CourseSystem() noexcept
{
}

trm::Information ssys::CourseSystem::SearchCourseInformation(const trm::Information& information) noexcept
{
    assert(information[0] == trm::rqs::SEARCH_COURSE_INFORMATION); // Procession not matched.
    auto it= studentBase[information[1]];//找到指定学生的课程列表
    for(auto [courseName,courseInformation]:it)
    {
       if(courseName==information[2])
       {
           return {trm::rpl::YES,courseInformation};
       }
    }
   return {trm::rpl::NO, trm::rpl::NO_MATCH_COURSE};
}

trm::Information ssys::CourseSystem::AddCourse(const trm::Information& information) noexcept
{
    assert(information[0] == trm::rqs::ADD_COURSE); // Procession not matched.
    auto accessReply = SSys::Get().CheckAccess({trm::rqs::CHECK_ACCESS, information[1], information[2], trm::Access::ADD_COURSE});//待修改，参数不太对
    if (accessReply[0] != trm::rpl::YES) {
        return {trm::rpl::ACCESS_DENIED};
    }
    for(auto [courseName, courseInformation] : courseBase ){//遍历课程列表
        if (courseName == information[3]) {
            return {trm::rpl::FAIL,trm::rpl::COURSE_EXISTS};
        }
    }
    //待实现，按年级和课程属性来增加（模拟真实选课）
    return {trm::rpl::SUCC};
}

trm::Information ssys::CourseSystem::DeleteCourse(const trm::Information& information) noexcept
{
    assert(information[0] == trm::rqs::DELETE_COURSE); // Procession not matched.
    auto accessReply = SSys::Get().CheckAccess({trm::rqs::CHECK_ACCESS, information[1], information[2], trm::Access::DELETE_COURSE});//待修改，参数不太对
    if (accessReply[0] != trm::rpl::YES) {
        return {trm::rpl::ACCESS_DENIED};
    }
    auto courseReply = SSys::Get().SearchCourseInformation({trm::rqs::SEARCH_COURSE_INFORMATION, information[1], information[3]});//待修改，参数不太对
    if (courseReply[0] != trm::rpl::YES) {
        return {trm::rpl::FAIL, trm::rpl::NO_MATCH_COURSE};
    }
    studentBase[information[1]][information[3]].Clear();//删除课程
    return {trm::rpl::SUCC};
}

