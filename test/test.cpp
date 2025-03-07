#include <iostream>
#include "ui.hpp"

int main()
{
    ui::Screen screen(800, 600, L"Test");
    
    auto mrg = new ui::Margen;
    mrg->AddTo(&screen);
    mrg->SetPreset(ui::Control::Preset::PLACR_AT_CENTER);

    auto lay = new ui::Vertical;
    lay->SetPreset(ui::Control::Preset::PLACR_AT_CENTER);
    lay->SetPreset(ui::Control::Direction::VERTICAL, ui::Control::Preset::FILL_FROM_CENTER);
    lay->AddTo(mrg);

    auto btn1 = new ui::Button;
    auto btn2 = new ui::Button;
    btn1->AddTo(lay);
    btn2->AddTo(lay);

    btn1->SetCaption(L"我爱你");
    btn2->SetCaption(L"中国");

    while (screen.IsOpen()) {
        screen.Tick();
    }

    return 0;
}


