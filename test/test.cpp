#include <iostream>
#include "ui.hpp"
#include <string>

int main()
{
    ui::Screen screen(1200, 800, L"Tese");






    auto ver = new ui::VerticalBox;
    screen.Add(ver);
    ver->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);

    auto func = [](const sf::String &name, const sf::Event &event){
        std::cout << (std::string)name << std::endl;
    };
    auto lbl = new ui::Button;
    auto lbl2 = new ui::Button;
    lbl->SetName("123");
    lbl->SetEnterCallback(func);
    lbl->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
    lbl->SetVSize(1);
    lbl2->SetEnterCallback(func);
    lbl2->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
    lbl2->SetVSize(2);

    lbl->AddTo(ver);
    lbl2->AddTo(ver);





    while (screen.IsOpen()) {
        screen.Tick();
    }

    return 0;
}


