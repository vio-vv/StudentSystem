#ifndef __PAGE_HEADER_HPP__
#define __PAGE_HEADER_HPP__

#define LINK "..\\server\\space"
#define SELF ".\\space"
#define SELF_AS_SENDER "..\\client\\space"

#include <iostream>
#include <cassert>
#include "ui.hpp"
#include "transmitter.hpp"

namespace clpg{

enum class ID{
    ENTER_SYSTEM, 

    /*******************************
     * @attention EEA 请在此处添加。*
     * *****************************
     */
    RETRY, 
    LOGIN,
    FORGET,
    MAIN_PAGE,

    ENTER_ACC_MANAGE,

    ENTER_CANTEEN,
    ENTER_MAILSYSTEM,

    /*******************************
     * @attention LAB 请在此处添加。*
     * *****************************
     */
    ENTER_COURSE,
    ENTER_RESERVE,
    
    /**********************************
     * @attention VIO_VV 请在此处添加。*
     * ********************************
     */
    ENTER_LIBRARY,
    ENTER_NOLIFY,

    BREAK
};

class Atstr : public sf::String {
public:
    Atstr(const sf::String &other) : sf::String(other) {}
    Atstr() : sf::String() {}
    Atstr(const std::string &str) : sf::String(str) {}
    Atstr(const char *str) : sf::String(str) {}
    Atstr(const wchar_t *str) : sf::String(str) {}
    Atstr(const Atstr &other) : sf::String(other) {}
    operator std::string() const;
};

void Init() noexcept;
std::pair<int, trm::Information> WaitServer(ui::Screen &screen, const trm::Information &information, const Atstr &tips) noexcept;

struct{
    Atstr username = "";
    Atstr password = "";
    trm::Account account;

    union{
        ;
    };
}sharedInformation;

}


#endif
