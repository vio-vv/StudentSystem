#ifndef __SUBSYSTEMS_COURSE_HPP__
#define __SUBSYSTEMS_COURSE_HPP__

/**
 * @brief 课程系统。
 * @namespace ssys
 * 
 * @par REQUIRES
 * TO_COMPLETE
 * 
 * @par PROVIDES
 * TO_COMPLETE
 */

#include "system_header.hpp"

namespace ssys{

class CourseSystem{
public:
    trm::Information SearchCourseInformation(const trm::Information& information) noexcept;
    trm::Information CheckAllCourse(const trm::Information& information) noexcept;
    trm::Information AddCourse(const trm::Information& information) noexcept;
    trm::Information DeleteCourse(const trm::Information& information) noexcept;
    trm::Information AdmAddCour(const trm::Information& information) noexcept;
    trm::Information AdmDeleteCour(const trm::Information& information) noexcept;
protected:
    CourseSystem() noexcept;
    ~CourseSystem() noexcept;
    CourseSystem(const CourseSystem&) = delete;
    CourseSystem& operator=(const CourseSystem&) = delete;  
private:
    dat::DataBase studentBase = DATA_BASE["course"]["studentCourse"];
    dat::DataBase courseBase = DATA_BASE["course"]["courseList"]; // 一个存学生选课，一个存课程信息
};

}

#endif
