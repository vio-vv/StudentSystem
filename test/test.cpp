#include <iostream>
#include "ui.hpp"

int main()
{
    ui::Screen screen(800, 600, "Test");
    // auto mrg = new ui::Margen;
    // mrg->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
    // mrg->SetSize(50, 50);
    // screen.Add(mrg);
    auto ver = new ui::VerticalScrollingBox;
    ver->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
    ver->SetSize(50, 50);
    // ver->AddTo(mrg);
    screen.Add(ver);

    auto bar = new ui::HorizontalScrollBar;
    bar->SetPreset(ui::Control::Preset::PLACR_AT_CENTER);
    bar->AddTo(ver);

    auto bar2 = new ui::VerticalScrollBar;
    bar2->SetPreset(ui::Control::Preset::PLACR_AT_CENTER);
    bar2->AddTo(ver);
    bar2->SetDragCallback([&screen, &bar2](const sf::String &name, const sf::Event &event){
        auto pos = sf::Mouse::getPosition(screen.Get());
        std::cout << pos.x << ' ' << pos.y << std::endl;
    });

    auto inp = new ui::InputBox;
    inp->AddTo(ver);

    while (screen.IsOpen()) {
        screen.Tick();
    }

    return 0;
}


