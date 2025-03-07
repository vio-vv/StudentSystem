#include <iostream>
#include "ui.hpp"

int main()
{
    ui::Screen screen(2, 0, L"Test");
    auto *label = new ui::Label;
    label->SetContent(L"零零零零");
    label->SetSizeWrap(ui::Control::Direction::HORIZONTAL, true);
    label->SetSizeWrap(ui::Control::Direction::VERTICAL, true);
    auto *ctr = new ui::Center;
    ctr->Add(label);
    ctr->SetSizeValueType(ui::Control::Direction::HORIZONTAL, ui::Control::ValueType::PERCENTAGE);
    ctr->SetSize(ui::Control::Direction::HORIZONTAL, 50);
    ctr->SetSize(ui::Control::Direction::VERTICAL, 500);
    screen.Add(ctr);
    while (screen.IsOpen()) {
        screen.Tick();
    }
    return 0;
}


