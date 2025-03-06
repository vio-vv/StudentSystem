#include "ui.hpp"

int main()
{
    ui::Screen screen;
    auto *label = new ui::Label;
    label->SetContent(L"你好，世界！");
    auto *ctr = new ui::Center;
    ctr->Add(label);
    ctr->SetSizeValueType(ui::Control::Direction::HORIZONTAL, ui::Control::ValueType::PERCENTAGE);
    ctr->SetSizeValueType(ui::Control::Direction::VERTICAL, ui::Control::ValueType::PERCENTAGE);
    ctr->SetSize(ui::Control::Direction::HORIZONTAL, 100);
    ctr->SetSize(ui::Control::Direction::VERTICAL, 100);
    screen.Add(ctr);
    while (screen.IsOpen()) {
        screen.Tick();
    }
    return 0;
}


