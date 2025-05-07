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
    ui::Screen screen(1500, 1000, L"学生管理系统");
    clpg::Handler handler = clpg::EnterSystem;
    while (handler && screen.IsOpen()) {
        handler = clpg::GetHandler(handler(screen));
        screen.FreeAll();
    }

    return 0;
}
