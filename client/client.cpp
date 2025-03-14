/**
 * @brief 客户端主程序。
 * 
 * @par REQUIRES
 * - @ref transmitter.hpp
 * - @ref ui.hpp
 * 
 * @par PROVIDES
 * - @fn main 主程序入口
 * 
 * @author 梁祖章
 */

#include "ui.hpp"
#include "transmitter.hpp"
#include <iostream>

int main()
{
    ui::Screen screen(800, 600, "学生管理系统");

    return 0;
}
