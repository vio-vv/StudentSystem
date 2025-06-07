#include "client_pages.hpp"

void clpg::EnterSystem::Load(ui::Screen *screen) noexcept
{
    auto ver = new ui::VerticalBox;{
        ver->AddTo(screen);
        ver->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
        ver->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
        ver->SetHSize(50);
    }
    {
        auto hor = new ui::HorizontalBox;{
            hor->AddTo(ver);
            hor->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
        }
        {
            hor->Add(new ui::Label("link: ", ui::Control::Preset::WRAP_AT_CENTER));
            link = new ui::InputBox;{
                link->AddTo(hor);
                link->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                link->SetText(LINK);
            }
        }
        hor = new ui::HorizontalBox;{
            hor->AddTo(ver);
            hor->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
        }
        {
            hor->Add(new ui::Label("self: ", ui::Control::Preset::WRAP_AT_CENTER));
            self = new ui::InputBox;{
                self->AddTo(hor);
                self->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                self->SetText(SELF);
            }
        }
        hor = new ui::HorizontalBox;{
            hor->AddTo(ver);
            hor->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
        }
        {
            hor->Add(new ui::Label("selfAsSender: ", ui::Control::Preset::WRAP_AT_CENTER));
            selfAsSender = new ui::InputBox;{
                selfAsSender->AddTo(hor);
                selfAsSender->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                selfAsSender->SetText(SELF_AS_SENDER);
            }
        }
        btn = new ui::Button;{
            btn->AddTo(ver);
            btn->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
            btn->SetCaption("进入系统");
        }
    }
}

void clpg::EnterSystem::Logic(ui::Screen *screen) noexcept
{
    auto fail = [=, this](){
        screen->HideAll();
        MessageBox(screen, "利用参数初始化失败！请检查输入参数是否正确。");
        screen->FreeAllVisible();
        screen->ShowAll();
    };
    btn->SetClickCallback(_UI_CALLBACK_{
        if (!trm::Initialize(self->GetText())) {
            fail();
        }
        trm::Sender::Init(link->GetText(), self->GetText(), selfAsSender->GetText());
        screen->HideAll();
        auto [success, reply] = WaitServer(screen, {trm::rqs::CHECK_ONLINE}, "正在检查服务端在线状态");
        screen->FreeAllVisible();
        screen->ShowAll();
        if (success == 1) {
            if (reply[0] == trm::rpl::YES) {
                SwitchTo(new eea::Login);
            } else {
                fail();
            }
        } else if (success == 0) {
            screen->HideAll();
            MessageBox(screen, "服务端未响应，请检查后重试。");
            screen->FreeAllVisible();
            screen->ShowAll();
        }
    });
}

void clpg::EnterSystem::Ready(ui::Screen *screen) noexcept
{
    ;
}
