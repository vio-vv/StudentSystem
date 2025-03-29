#ifndef __ACCESS_HPP__
#define __ACCESS_HPP__

#define DATA_PATH ".\\data"

/**
 * @brief 学生管理系统。
 * @namespace ssys
 * 
 * @par REQUIRES
 * TO_COMPLETE
 * 
 * @par PROVIDES
 * TO_COMPLETE
 */

#include <cassert>
#include "transmitter.hpp"

namespace ssys{

trm::Infomation CheckValid(const trm::Infomation &infomation);
trm::Infomation ModifyScore(const trm::Infomation &infomation);

}

#endif