#ifndef __CLIENTS_HPP__
#define __CLIENTS_HPP__

/**
 * @brief 客户端页面。
 * @namespace clpg
 * 
 * @par REQUIRES
 * - @ref ui.hpp
 * - @ref transmitter.hpp
 * 
 * @par PROVIDES
 * 各种客户端页面的实现。
 */

#include "subpages/eea.hpp"
#include "subpages/vio_vv.hpp"
#include "subpages/lab.hpp"

namespace clpg {

using Handler = std::function<ID (ui::Screen &screen)>;
Handler GetHandler(ID id) noexcept;
ID EnterSystem(ui::Screen &screen) noexcept;

}

#endif
