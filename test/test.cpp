#include "ui.hpp"

int main()
{
    ui::Screen screen;
    screen.SetRange(1000, 800);
    screen.SetCaption(L"你好");
    while (screen.IsOpen()) {
        screen.Tick();
    }
    return 0;
}


