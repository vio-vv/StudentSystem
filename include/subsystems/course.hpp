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
    trm::Infomation SearchCourse(const trm::Infomation& information) noexcept;
    trm::Infomation AddCourse(const trm::Infomation& information) noexcept;
    trm::Infomation DeleteCourse(const trm::Infomation& information) noexcept;
protected:
    CourseSystem() noexcept;
    ~CourseSystem() noexcept;
    CourseSystem(const CourseSystem&) = delete;
    CourseSystem& operator=(const CourseSystem&) = delete;  
private:
    static const std::string dataPath;
    std::map<std::string,std::vector<trm::CourseInformation>> courseList; // 课程列表
};

}

#endif
