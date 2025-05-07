#ifndef __STUDENT_SYSTEM_HPP__
#define __STUDENT_SYSTEM_HPP__

/**
 * @brief 学生管理系统。
 * @class SSys
 * 
 * @par REQUIRES
 * TO_COMPLETE
 * 
 * @par PROVIDES
 * TO_COMPLETE
 */

#include "subsystems/account_and_access.hpp"
#include "subsystems/course.hpp"
#include "subsystems/library.hpp"
#include "subsystems/canteen.hpp"
#include "subsystems/reserve.hpp"
#include "subsystems/nolify.hpp"
#include "subsystems/mail.hpp"

class SSys : 
    public ssys::AccountAndAccess, 
    public ssys::CourseSystem, 
    public ssys::Library, 
    public ssys::Canteen, 
    public ssys::ReserveSystem, 
    public ssys::Nolify, 
    public ssys::MailSystem{
public:
    static SSys &Get() noexcept
    {
        static SSys instance;
        return instance;
    }
protected:
    SSys() = default;
    ~SSys() = default;
    SSys(const SSys&) = delete;
    SSys& operator=(const SSys&) = delete;
};

#endif