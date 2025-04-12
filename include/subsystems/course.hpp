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

class Course{
public:
    ;
protected:
    Course() noexcept;
    ~Course() noexcept;
    Course(const Course&) = delete;
    Course& operator=(const Course&) = delete;
};

}

#endif
