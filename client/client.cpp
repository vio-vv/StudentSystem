/**
 * @brief 客户端主程序。
 * 
 * @par REQUIRES
 * - @ref client_pages.hpp
 * 
 * @par PROVIDES
 * - @fn main 主程序入口
 */

#include "client_pages.hpp"

int main() noexcept
{
    ui::Screen screen(1500, 1000, "校园系统 - 大作业");

    clpg::PageBase *cur = new clpg::EnterSystem;
    clpg::PageBase *nxt = nullptr;

    while (cur) {
        nxt = cur->RunOn(&screen);
        delete cur;
        cur = nxt;
    }
    
    return 0;
}
