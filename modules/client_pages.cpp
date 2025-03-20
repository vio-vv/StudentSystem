#include "client_pages.hpp"

std::function<clpg::PageID (ui::Screen &screen)> clpg::GetPage(PageID id) noexcept
{
    switch (id)
    {
        case PageID::ENTER_SYSTEM_PAGE:
            return EnterSystemPage;
            break;
        case PageID::CHECK_SERVER_ONLINE_PAGE:
            return CheckServerOnlinePage;
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

clpg::PageID clpg::EnterSystemPage(ui::Screen &screen) noexcept
{
    bool clicked = false;

    auto btn = new ui::Button;
    screen.Add(btn);
    btn->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
    btn->SetCaption(L"进入系统");
    btn->SetClickCallback([&clicked](const sf::String &name, const sf::Event &event){
        clicked = true;
    });

    while (screen.IsOpen()) {
        screen.Tick();
        if (clicked) {
            return PageID::CHECK_SERVER_ONLINE_PAGE;
        } 
    }
    return PageID::BREAK;
    {
        int count = 5;
        sf::Clock clock;
        bool pass = false;

        // ring->SetCallback([&count, &clock, &label, &id, &pass](const sf::String &name, const sf::Event &event){
        //     if (clock.getElapsedTime().asMilliseconds() > 1000) {
        //         --count;
        //         label->SetContent(label->GetContent().substring(0, label->GetContent().getSize() - 1) + trm::ToStr(count));
        //         clock.restart();
        //         auto reply = trm::PollReply(SELF, id);
        //         if (reply.first) {
        //             pass = true;
        //         }
        //     }
        // });
        while (screen.IsOpen() && count > 0 && !pass) {
            screen.Tick();
        }
        if (pass) {
            return PageID::LOGIN_PAGE;
        }
        screen.FreeAll();
    }

    auto label = new ui::Label;
    screen.Add(label);
    label->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
    label->SetContent(L"服务器未响应，请检查后再试。");

    while (screen.IsOpen()) {
        screen.Tick();
    }
    return PageID::BREAK;
}

clpg::PageID clpg::CheckServerOnlinePage(ui::Screen &screen) noexcept
{
    auto id = trm::GenerateID();
    trm::MakeRequest(LINK, trm::Request{id, SELF_AS_SENDER, {trm::rqs::CHECK_ONLINE}});

    auto centerVertical = new ui::VerticalBox;
    screen.Add(centerVertical);
    centerVertical->SetHPreset(ui::Control::Preset::WRAP_AT_CENTER);
    centerVertical->SetVPreset(ui::Control::Preset::PLACR_AT_CENTER);
    centerVertical->SetVSize(200);
    {
        auto label = new ui::Label;
        label->AddTo(centerVertical);
        label->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
        label->SetVSize(2);
        label->SetContent(L"正在检查服务端在线状态...5");

        auto ring = new ui::LoadingRing;
        ring->AddTo(centerVertical);
        ring->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
        ring->SetVSize(1);
    }
}

clpg::PageID clpg::LoginPage(ui::Screen &screen) noexcept
{
    auto vertical = new ui::VerticalBox;
    screen.Add(vertical);
    vertical->SetPreset(ui::Control::Preset::PLACR_AT_CENTER);
    vertical->SetSize(800, 300);
    {
        auto user = new ui::HorizontalBox;
        user->AddTo(vertical);
        user->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
        {
            auto center = new ui::Center;
            center->AddTo(user);
            center->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
            center->SetHSize(1);
            {
                auto label = new ui::Label;
                label->AddTo(center);
                label->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                label->SetContent(L"学工号");
            }
            auto input = new ui::InputBox;
            input->AddTo(user);
            input->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
            input->SetHSize(3);
        }
        auto pasw = new ui::HorizontalBox;
        pasw->AddTo(vertical);
        pasw->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
        {
            auto center = new ui::Center;
            center->AddTo(pasw);
            center->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
            center->SetHSize(1);
            {
                auto label = new ui::Label;
                label->AddTo(center);
                label->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                label->SetContent(L"密码");
            }

            auto input = new ui::InputBox;
            input->AddTo(pasw);
            input->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
            input->SetHSize(3);
        }
    }

    while (screen.IsOpen()) {
        screen.Tick();
    }
    return PageID::BREAK;
}
