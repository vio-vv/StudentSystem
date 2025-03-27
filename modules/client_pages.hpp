#ifndef __CLIENTS_HPP__
#define __CLIENTS_HPP__

#include <iostream>
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
 * 
 * @author 梁祖章
 */

#include <cassert>
#include "ui.hpp"
#include "transmitter.hpp"

namespace clpg{

enum class ID{
    ENTER_SYSTEM, 
    CHECK_SERVER_ONLINE, 
    RETRY, 
    LOGIN, // sharedInfomation required: tips
    FORGET,
    CHECK_ACCOUNT,

    BREAK
};
using Handler = std::function<ID (ui::Screen &screen)>;
Handler GetHandler(ID id) noexcept;

ID EnterSystem(ui::Screen &screen) noexcept;
ID CheckServerOnline(ui::Screen &screen) noexcept;
ID Retry(ui::Screen &screen) noexcept;
ID Login(ui::Screen &screen) noexcept;
ID Forget(ui::Screen &screen) noexcept;
ID CheckAccount(ui::Screen &screen) noexcept;

struct{
    sf::String username = "";
    sf::String password = "";
    
    sf::String tips;
    union{
        ;
    };
}sharedInfomation;

}

#endif
