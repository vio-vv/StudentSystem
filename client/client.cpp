/**
 * @brief 客户端主程序。
 * 
 * @par REQUIRES
 * NONE
 * 
 * @par PROVIDES
 * - @fn main 主程序入口
 * 
 * @author 梁祖章
 */

#include <string>
#include <utility>
#include "transmitter.hpp"
#include "ui.hpp"

const std::wstring SERVER_LINK_PATH = L"./server_link.txt";


std::pair<bool, std::wstring> GetServerLink() noexcept
{
    if (!trm::CheckFileExist(SERVER_LINK_PATH)) return std::make_pair(false, L"");
    return trm::ReadFile(SERVER_LINK_PATH);
}

bool CheckServerOK(const std::wstring link) noexcept
{
    trm::Send(link, trm::rqs::CHECK_ONLINE);
}

void ShowInfo(std::wstring info) noexcept
{
    ;
}

int main() noexcept
{
    auto ok_link = GetServerLink();
    if (!ok_link.first) {
        ShowInfo(L"获取服务端链接失败，请检查 " + SERVER_LINK_PATH + L"。");
        return -1;
    }
    if (!CheckServerOK(ok_link.second)) {
        ShowInfo(L"服务端不在线，请确保服务端在线或检查 " + SERVER_LINK_PATH + L" 是否正确。");
        return -2;
    }
    ui::Screen screen;
    screen.SetCaption(L"学生管理系统");
    while (screen.IsOpen()) {
        screen.Tick();
    }
    return 0;
}


