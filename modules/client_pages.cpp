#include "client_pages.hpp"

std::function<clpg::PageID (ui::Screen &screen)> clpg::GetPage(PageID id)
{
    switch (id)
    {
        case PageID::ENTER_SYSTEM_PAGE:
            return EnterSystemPage;
            break;
        case PageID::LOGIN_PAGE:
            return LoginPage;
            break;
        case PageID::BREAK:
        default:
            return nullptr;
            break;
    }
}

clpg::PageID clpg::EnterSystemPage(ui::Screen &screen)
{
    auto centerVertical = new ui::VerticalBox;
    screen.Add(centerVertical);
    centerVertical->SetHPreset(ui::Control::Preset::WRAP_AT_CENTER);
    centerVertical->SetVPreset(ui::Control::Preset::PLACR_AT_CENTER);
    centerVertical->SetVSize(200);

    auto label = new ui::Label;
    label->AddTo(centerVertical);
    label->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
    label->SetVSize(2);
    label->SetContent(L"正在检查服务端在线状态...5");

    auto ring = new ui::LoadingRing;
    ring->AddTo(centerVertical);
    ring->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
    ring->SetVSize(1);

    int count = 5;
    sf::Clock clock;

    ring->SetCallback([&count, &clock, &label](const sf::String &name, const sf::Event &event){
        if (clock.getElapsedTime().asMilliseconds() > 1000) {
            --count;
            label->SetContent(label->GetContent().substring(0, label->GetContent().getSize() - 1) + trm::ToStr(count));
            clock.restart();
        }
    });

    while (screen.IsOpen() && count > 0) {
        screen.Tick();
    }
    return PageID::LOGIN_PAGE;
}

clpg::PageID clpg::LoginPage(ui::Screen &screen)
{
    while (screen.IsOpen()) {
        screen.Tick();
    }
    return PageID::BREAK;
}
