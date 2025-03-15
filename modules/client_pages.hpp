#ifndef __CLIENT_PAGES_HPP__
#define __CLIENT_PAGES_HPP__

/**
 * @brief 客户端主程序。
 * @namespace clpg
 * 
 * @par REQUIRES
 * - @ref ui.hpp
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
    LOGIN_PAGE, 

    BREAK
};
using Handler = std::function<PageID (ui::Screen &screen)>;
Handler GetPage(PageID id);

PageID EnterSystemPage(ui::Screen &screen);
PageID LoginPage(ui::Screen &screen);

}

#endif
