#include "ui.hpp"
#include <iostream>

using namespace ui;

int main()
{

    ui::Screen *screen = new ui::Screen(1500, 1000, "调试页面");
     
    ui::Label *label = new ui::Label("Hello, world!");
    label->AddTo(screen);

    while (screen->IsOpen()) {
        screen->Draw();
        screen->Tick();
    }
    return 0;
}


