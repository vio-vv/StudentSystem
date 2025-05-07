#ifndef __SUBSYSTEMS_SYSTEM_HEADER_HPP__
#define __SUBSYSTEMS_SYSTEM_HEADER_HPP__

#define DATA_PATH ".\\data"

/**
 * @brief 子系统的共同依赖。
 * @namespace ssys
 * 
 * @par REQUIRES
 * TO_COMPLETE
 * 
 * @par PROVIDES
 * TO_COMPLETE
 */

#include <iostream>
#include <map>
#include <cassert>
#include "transmitter.hpp"
#include "data_base.hpp"

namespace ssys {

const dat::DataBase DATA_BASE = dat::DataBase(DATA_PATH);

}

#endif
