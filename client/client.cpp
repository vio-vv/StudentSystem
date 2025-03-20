/**
 * @brief 客户端主程序。
 * 
 * @par REQUIRES
 * - @ref client_pages.hpp
 * 
 * @par PROVIDES
 * - @fn main 主程序入口
 * 
 * @author 梁祖章
 */

#include "client_pages.hpp"
#include <iostream>

int main()
{
    ui::Screen screen(800, 600, L"学生管理系统");

    clpg::Handler handler = clpg::EnterSystemPage;

    // while (handler && screen.IsOpen()) {
    //     handler = clpg::GetPage(handler(screen));
    //     screen.FreeAll();
    // }

    return 0;
}
