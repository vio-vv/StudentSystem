/**
 * @brief 客户端主程序。
 * 
 * @par REQUIRES
 * - @ref client_pages.hpp
 * 
 * @par PROVIDES
 * - @fn main 主程序入口
 */

#define _LINK_ "..\\server\\space"
#define _SELF_ ".\\space"
#define _SELF_AS_SENDER_ "..\\client\\space"

#include "client_pages.hpp"

int main() noexcept
{
    ui::Screen screen(1500, 1000, "校园系统 - 大作业");

    std::string link, self, selfAsSender;
    std::ifstream conf("conf.txt", std::ios::in);
    if (conf.good()) {
        conf >> link >> self >> selfAsSender;
    } else {
        link = _LINK_;
        self = _SELF_;
        selfAsSender = _SELF_AS_SENDER_;
    }

    clpg::PageBase *cur = new clpg::EnterSystem(link, self, selfAsSender);
    clpg::PageBase *nxt = nullptr;

    while (cur) {
        nxt = cur->RunOn(&screen);
        delete cur;
        cur = nxt;
    }
    
    return 0;
}
