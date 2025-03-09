#include <iostream>
#include "ui.hpp"

int main()
{
    ui::Screen screen(800, 600, L"Test");
    auto mrg = new ui::Margen;
    mrg->AddTo(&screen);
    mrg->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
    mrg->SetSize(50, 50);
    auto ver = new ui::Vertical;
    ver->AddTo(mrg);

    auto inp1 = new ui::InputBox;
    auto inp2 = new ui::InputBox;
    for (auto inp : {inp1, inp2}) {
        inp->AddTo(ver);
        inp->SetBeginCallback([](const sf::String &name, const sf::Event &event){
            std::cout << "InputBox begin" << std::endl;
        });
        inp->SetInputCallback([](const sf::String &name, const sf::Event &event){
            std::cout << "InputBox input" << std::endl;
        });
        inp->SetEndCallback([](const sf::String &name, const sf::Event &event){
            std::cout << "InputBox end" << std::endl;
        });
    }

    while (screen.IsOpen()) {
        screen.Tick();
    }

    return 0;
}


