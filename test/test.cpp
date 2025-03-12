#include <iostream>
#include "ui.hpp"

int main()
{
    ui::Screen screen(800, 600, "Test");
    auto ver = new ui::VerticalBox;
    ver->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
    ver->SetSize(50, 50);
    screen.Add(ver);

    auto bar = new ui::HorizontalScrollBar;
    bar->SetPreset(ui::Control::Preset::PLACR_AT_CENTER);
    bar->AddTo(ver);

    auto bar2 = new ui::VerticalScrollBar;
    bar2->SetPreset(ui::Control::Preset::PLACR_AT_CENTER);
    bar2->AddTo(ver);
    bar2->SetDragCallback([&bar2](const sf::String &name, const sf::Event &event){
        float expected = event.mouseMove.y - 10 - bar2->GetGlobalPosition(ui::Control::Direction::VERTICAL);
        expected /= bar2->GetGlobalSize(ui::Control::Direction::VERTICAL) - 20;
        if (expected < 0) expected = 0;
        if (expected > 1) expected = 1;
        std::cout << expected << std::endl;
    });

    while (screen.IsOpen()) {
        screen.Tick();
    }

    return 0;
}


