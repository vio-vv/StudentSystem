#include <iostream>
#include "ui.hpp"

int main()
{
    ui::Screen screen(800, 600, L"Test");
    auto mrg = new ui::Margen;
    mrg->AddTo(&screen);
    mrg->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
    mrg->SetSize(50, 50);

    auto inp = new ui::InputBox;
    inp->AddTo(mrg);

    while (screen.IsOpen()) {
        screen.Tick();
    }

    return 0;
}


