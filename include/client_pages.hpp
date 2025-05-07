#ifndef __CLIENTS_HPP__
#define __CLIENTS_HPP__

#define LINK "..\\server\\space"
#define SELF ".\\space"
#define SELF_AS_SENDER "..\\client\\space"

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

#include <iostream>
#include <cassert>
#include "ui.hpp"
#include "transmitter.hpp"

namespace clpg{

enum class ID{
    ENTER_SYSTEM, 
    RETRY, 
    LOGIN,
    FORGET,
    MAIN_PAGE,

    BREAK
};
using Handler = std::function<ID (ui::Screen &screen)>;
Handler GetHandler(ID id) noexcept;

ID EnterSystem(ui::Screen &screen) noexcept;
ID Retry(ui::Screen &screen) noexcept;
ID Login(ui::Screen &screen) noexcept;
ID Forget(ui::Screen &screen) noexcept;
ID MainPage(ui::Screen &screen) noexcept;

std::pair<int, trm::Information> WaitServer(ui::Screen &screen, const trm::Information &information, const sf::String &tips) noexcept;

struct{
    sf::String username = "";
    sf::String password = "";
    
    union{
        ;
    };
}sharedInformation;

/**
 * TO_COMPLETE
 */
std::string SfToStr(const sf::String &t) noexcept;

}

#endif
