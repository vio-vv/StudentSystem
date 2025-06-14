#include "student_system.hpp"

ssys::CourseSystem::CourseSystem() noexcept
{
  ;
}

ssys::CourseSystem::~CourseSystem() noexcept
{
}

trm::Information ssys::CourseSystem::SearchCourseInformation(const trm::Information& information) noexcept
{
    assert(information[0] == trm::rqs::SEARCH_COURSE_INFORMATION); // Procession not matched.
    auto it= studentBase[information[1]];//找到指定学生的课程列表
    if(it[information[2]].Exists())
       {
           return {trm::rpl::YES,information[2],it[information[2]]};
       }
    
   return {trm::rpl::NO, trm::rpl::NO_MATCH_COURSE};
}

trm::Information ssys::CourseSystem::CheckAllCourse(const trm::Information& information) noexcept
{
    assert(information[0] ==trm::rqs::CHECK_ALL_COURSE);
    trm::Information replylist;
    replylist.push_back(trm::rpl::SUCC);
    if(!studentBase[information[1]].Size())
    {
        return {trm::rpl::FAIL, trm::rpl::NO_COURSE_EXITS};
    }
    for( auto[courseID, courseInformation]:studentBase[information[1]])
    {
        replylist.push_back(trm::Combine({courseID,courseInformation}));
    }
    return replylist;
}

trm::Information ssys::CourseSystem::AddCourse(const trm::Information& information) noexcept
{
    assert(information[0] == trm::rqs::ADD_COURSE); // Procession not matched.
    auto accessReply = SSys::Get().CheckAccess({trm::rqs::CHECK_ACCESS, information[1], information[2], trm::AccessBox{trm::Access::ADD_COURSE}});//待修改，参数不太对
    if (accessReply[0] != trm::rpl::YES) {
        return {trm::rpl::ACCESS_DENIED};
    }
    if (studentBase[information[1]][information[3]].Exists()) 
      {
        return {trm::rpl::FAIL,trm::rpl::COURSE_EXISTS};
      }
    if(!courseBase[information[3]].Exists()&&ToStr(courseBase[information[3]])=="")
      {
        return {trm::rpl::FAIL,trm::rpl::NO_MATCH_COURSE};
      }
    studentBase[information[1]].Push(information[3],courseBase[information[3]]);//增加课程
    //待实现，按年级和课程属性来增加（模拟真实选课）
    auto courseInformation = trm::CourseInformation{courseBase[information[3]]};
    return {trm::rpl::SUCC,courseInformation.courseName};
}

trm::Information ssys::CourseSystem::DeleteCourse(const trm::Information& information) noexcept
{
    assert(information[0] == trm::rqs::DELETE_COURSE); // Procession not matched.
    auto accessReply = SSys::Get().CheckAccess({trm::rqs::CHECK_ACCESS, information[1], information[2], trm::AccessBox{trm::Access::DELETE_COURSE}});//待修改，参数不太对
    if (accessReply[0] != trm::rpl::YES) {
        return {trm::rpl::ACCESS_DENIED};
    }
    if(!studentBase[information[1]][information[3]].Exists()) 
      {
        return {trm::rpl::FAIL,trm::rpl::NO_MATCH_COURSE};
      }
    studentBase[information[1]][information[3]].Clear();//删除课程
    return {trm::rpl::SUCC,information[3]};
}

trm::Information ssys::CourseSystem::AdmAddCour(const trm::Information& information) noexcept
{
    assert(information[0] == trm::rqs::ADM_ADD_COUR); // Procession not matched.
    auto accessReply = SSys::Get().CheckAccess({trm::rqs::CHECK_ACCESS, information[1], information[2], trm::AccessBox{trm::Access::ADM_ADD_COUR}});//待修改，参数不太对
    if (accessReply[0] != trm::rpl::YES) {
        return {trm::rpl::ACCESS_DENIED};
    }
    if (courseBase[information[3]].Exists()&&ToStr(courseBase[information[3]])=="")
      {
        return {trm::rpl::FAIL,trm::rpl::COURSE_EXISTS};
      }
    courseBase.Push(information[3],information[4]);//增加课程
    return {trm::rpl::SUCC};
}

trm::Information ssys::CourseSystem::AdmDeleteCour(const trm::Information& information) noexcept
{
    assert(information[0] == trm::rqs::ADM_DELETE_COUR); // Procession not matched.
    auto accessReply = SSys::Get().CheckAccess({trm::rqs::CHECK_ACCESS, information[1], information[2], trm::AccessBox{trm::Access::ADM_DELETE_COUR}});//待修改，参数不太对
    if (accessReply[0] != trm::rpl::YES) {
        return {trm::rpl::ACCESS_DENIED};
    }
    if(!courseBase[information[3]].Exists()) 
    {
        return {trm::rpl::FAIL,trm::rpl::NO_MATCH_COURSE};
    }
    std::string temp= courseBase[information[3]]; // 保存原来的课程信息
    auto course =trm::CourseInformation{temp};
    courseBase[information[3]].Clear();//删除课程
    return {trm::rpl::SUCC, information[3],course.courseName};
}
