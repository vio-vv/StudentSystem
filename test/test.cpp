#include <iostream>
#include "ui.hpp"

int main()
{
    ui::Screen screen(800, 600, "Test");
    
    auto ver = new ui::VerticalScrollingBox;
    screen.Add(ver);

    ver->Add(new ui::Button);
    ver->Add(new ui::Label);
    ver->Add(new ui::Label);
    ver->Add(new ui::Button);
    ver->Add(new ui::Label);

    while (screen.IsOpen()) {
        screen.Tick();
    }

    return 0;
}


