#ifndef __CLIENT_PAGES_HPP__
#define __CLIENT_PAGES_HPP__

#include <iostream>
#define LINK "..\\server\\space"
#define SELF ".\\space"
#define SELF_AS_SENDER "..\\client\\space"

/**
 * @brief 客户端主程序。
 * @namespace clpg
 * 
 * @par REQUIRES
 * - @ref ui.hpp
 * - @ref transmitter.hpp
 * 
 * @par PROVIDES
 * 各种客户端页面的实现。
 * 
 * @author 梁祖章
 */

 #include "ui.hpp"
 #include "transmitter.hpp"

namespace clpg{

enum class PageID{
    ENTER_SYSTEM_PAGE, 
    CHECK_SERVER_ONLINE_PAGE, 
    LOGIN_PAGE, 

    BREAK
};
using Handler = std::function<PageID (ui::Screen &screen)>;
Handler GetPage(PageID id) noexcept;

PageID EnterSystemPage(ui::Screen &screen) noexcept;
PageID CheckServerOnlinePage(ui::Screen &screen) noexcept;
PageID LoginPage(ui::Screen &screen) noexcept;

}

#endif
