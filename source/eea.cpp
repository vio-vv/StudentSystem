#include "client_pages.hpp"
#include "eea.hpp"

void eea::EnterCanteen::Load(ui::Screen *screen) noexcept
{
    ;
}

void eea::EnterCanteen::Logic(ui::Screen *screen) noexcept
{
    ;
}

void eea::EnterCanteen::Ready(ui::Screen *screen) noexcept
{
    ;
}

void eea::Login::Load(ui::Screen *screen) noexcept
{
    auto box = new ui::VerticalBox;{
        box->SetGap(80);
        box->AddTo(screen);
        box->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);}
    {
        auto pic = new ui::PictureBox;{
            pic->AddTo(box);
            pic->SetPicture(_ASSETS_"icon_with_title.png");
            pic->KeepHeight(100);}
        auto vertical = new ui::VerticalBox;{
            vertical->AddTo(box);
            vertical->SetSize(900, 250);}
        {
            auto user = new ui::HorizontalBox;{
                user->AddTo(vertical);
                user->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                user->SetGap(50);}
            {
                auto label = new ui::Label;{
                    label->AddTo(user);
                    label->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                    label->SetContent(L"帐号");}
                userInput = new ui::InputBox;{
                    userInput->AddTo(user);
                    userInput->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    userInput->SetText(username);
                    userInput->SetHSize(3);
                    userInput->SetLengthLimit(64);
                    userInput->SetContentLimit(ui::InputBox::ContentLimit::ALLOW_SPECIAL_CHARACTERS_ONLY);
                    userInput->SetSpecialCharacters(ui::InputBox::NUMBER + ui::InputBox::LOWER_LETTER + ui::InputBox::UPPER_LETTER + "_-@.");}
            }
            auto pasw = new ui::HorizontalBox;{
                pasw->AddTo(vertical);
                pasw->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                pasw->SetGap(50);}
            {
                auto label = new ui::Label;{
                    label->AddTo(pasw);
                    label->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                    label->SetContent(L"密码");}
                paswInput = new ui::InputBox;{
                    paswInput->AddTo(pasw);
                    paswInput->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    paswInput->SetHSize(3);
                    paswInput->SetProtectText(true);
                    paswInput->SetLengthLimit(64);
                    paswInput->SetContentLimit(ui::InputBox::ContentLimit::ALLOW_SPECIAL_CHARACTERS_ONLY);
                    paswInput->SetSpecialCharacters(ui::InputBox::ASCII);}
            }
        }  
        auto feetBox = new ui::VerticalBox;{
            feetBox->AddTo(box);
            feetBox->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);}
        {
            auto btnBox = new ui::HorizontalBox;{
                btnBox->AddTo(feetBox);
                btnBox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                btnBox->SetGap(50);}
            {
                loginBtn = new ui::Button;{
                    loginBtn->AddTo(btnBox);
                    loginBtn->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    loginBtn->SetHSize(2);
                    loginBtn->SetCaption(L"登录");}
                forgetBtn = new ui::Button;{
                    forgetBtn->AddTo(btnBox);
                    forgetBtn->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    forgetBtn->SetHSize(2);
                    forgetBtn->SetCaption(L"忘记密码");}
                reserveBtn = new ui::Button;{
                    reserveBtn->AddTo(btnBox);
                    reserveBtn->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    reserveBtn->SetHSize(1);
                    reserveBtn->SetCaption(L"校外人员\n预约入校");}
            }
            tips = new ui::Label;{
                tips->AddTo(feetBox);
                tips->SetPreset(ui::Control::Preset::WRAP_AT_FRONT);
                tips->SetFontColor(sf::Color::Red);
                tips->SetFontSize(30);
                tips->SetVisible(false);}
        }        
    }
}

void eea::Login::Logic(ui::Screen *screen) noexcept
{
    userInput->SetInputCallback([&](const Atstr &name, const sf::Event &event) -> void {
        username = userInput->GetText();
    });
    userInput->SetExceedLimitCallback([&](const Atstr &name, const sf::Event &event) -> void {
        tips->SetContent(L"帐号只能由数字、大小写字母以及 _-@. 构成，\n且长度不超过 64 个字符。");
        tips->SetVisible(true);
    });
    paswInput->SetInputCallback([&](const Atstr &name, const sf::Event &event) -> void {
        password = paswInput->GetText();
    });
    paswInput->SetExceedLimitCallback([&](const Atstr &name, const sf::Event &event) -> void {
        tips->SetContent(L"密码只能由 ASCII 字符构成，\n且长度不超过 64 个字符。");
        tips->SetVisible(true);
    });
    loginBtn->SetClickCallback([&](const Atstr &name, const sf::Event &event) -> void {
        if (username == "" || password == "") {
            tips->SetContent(L"帐号或密码不能为空。");
            tips->SetVisible(true);
        } else {
            screen->HideAll();
            auto [success, reply] = WaitServer(screen, 
                {trm::rqs::CHECK_ACCOUNT, username, password}, L"登录中");
            screen->FreeAllVisible();
            screen->ShowAll();
            if (success == 1) {
                if (reply[0] == trm::rpl::YES) {
                    account = reply[1];
                    SwitchTo(new MainPage);
                } else if (reply[0] == trm::rpl::NO) {
                    tips->SetContent(L"帐号或密码错误。");
                    tips->SetVisible(true);
                } else {
                    assert(false); // Invalid reply.
                }    
            } else if (success == 0) {
                SwitchTo(new Retry);
            }
        }
    });
    forgetBtn->SetClickCallback([&](const Atstr &name, const sf::Event &event) -> void {
        SwitchTo(new Forget);
    });
    reserveBtn->SetClickCallback([&](const Atstr &name, const sf::Event &event) -> void {
        SwitchTo(new lab::EnterReserve);
    });
}

void eea::Login::Ready(ui::Screen *screen) noexcept
{
    password = "";
    account = {};
}

void eea::Forget::Load(ui::Screen *screen) noexcept
{
    ;
}

void eea::Forget::Logic(ui::Screen *screen) noexcept
{
    ;
}

void eea::Forget::Ready(ui::Screen *screen) noexcept
{
    ;
}

void eea::EnterMailSystem::Load(ui::Screen *screen) noexcept
{
    auto mar = new ui::Margin;{
        screen->Add(mar);
        mar->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
        mar->SetMargin(80, 80, 200, 200);}
    {
        auto hor = new ui::HorizontalBox;{
            hor->AddTo(mar);
            hor->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);}
        {
            auto ver = new ui::VerticalBox;{
                ver->AddTo(hor);
                ver->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                ver->SetHSize(500);
                ver->SetGap(100);}
            {
                auto btnBox = new ui::VerticalBox;{
                    btnBox->AddTo(ver);
                    btnBox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    btnBox->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);}
                {
                    backBtn = new ui::Button;{
                        backBtn->AddTo(btnBox);
                        backBtn->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        backBtn->SetCaption(L"返回主页");}
                    auto writeMailBtn = new ui::Button;{
                        writeMailBtn->AddTo(btnBox);
                        writeMailBtn->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        writeMailBtn->SetCaption(L"写  信");}
                }
                auto inBox = new ui::VerticalBox;{
                    inBox->AddTo(ver);
                    inBox->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);}
                {
                    auto label = new ui::Label;{
                        label->AddTo(inBox);
                        label->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                        label->SetContent(L"↓ 收件箱 ↓");}
                    auto listBox = new ui::VerticalBox;{
                        listBox->AddTo(inBox);
                        listBox->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);}
                    {
                        auto list = new ui::VerticalBox;{
                            list->AddTo(listBox);
                            list->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);}
                        {
                            ;
                        }
                        auto btnBox = new ui::HorizontalBox;{
                            btnBox->AddTo(listBox);
                            btnBox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                            btnBox->SetVPreset(ui::Control::Preset::PLACR_AT_END);
                            btnBox->SetVSize(50);}
                        {
                            auto elp1 = new ui::Label;{
                                elp1->SetContent(L"...");}
                            l3 = new ui::Button;{
                                l3->SetName("-3");}
                            l2 = new ui::Button;{
                                l2->SetName("-2");}
                            l1 = new ui::Button;{
                                l1->SetName("-1");}
                            cur = new ui::Label;{
                                cur->SetContent("1");}
                            r1 = new ui::Button;{
                                r1->SetName("+1");}
                            r2 = new ui::Button;{
                                r2->SetName("+2");}
                            r3 = new ui::Button;{
                                r3->SetName("+3");}
                            auto elp2 = new ui::Label;{
                                elp2->SetContent(L"...");}
                            for (auto e : std::vector<ui::Control *>{elp1, l3, l2, l1, cur, r1, r2, r3, elp2}) {
                                e->AddTo(btnBox);
                                e->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                            }
                        }
                    }
                }
            }
        }
    }
}

void eea::EnterMailSystem::Logic(ui::Screen *screen) noexcept
{
    for (auto e : {l3, l2, l1, r1, r2, r3}) {
        e->SetClickCallback([&](const Atstr &name, const sf::Event &event) -> void {
            ;
        });
        e->SetCaption("-"); // TODO
    }
    backBtn->SetClickCallback([&](const Atstr &name, const sf::Event &event) -> void {
        SwitchTo(new MainPage);
    });
}

void eea::EnterMailSystem::Ready(ui::Screen *screen) noexcept
{
    ;
}

void eea::MainPage::Load(ui::Screen *screen) noexcept
{
    auto margin = new ui::Margin;{
        margin->AddTo(screen);
        margin->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
        margin->SetMargin(80, 80, 200, 200);}
    {
        auto ver = new ui::VerticalBox;{
            ver->AddTo(margin);
            ver->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);}
        {
            auto flat = new ui::Flat;{
                flat->AddTo(ver);
                flat->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                flat->SetVSize(150);}
            {
                auto head = new ui::HorizontalBox;{
                    head->AddTo(flat);
                    head->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    head->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);}
                {
                    auto icon = new ui::PictureBox;{
                        icon->AddTo(head);
                        icon->SetPicture(_ASSETS_"icon.png");
                        screen->Tick();
                        icon->KeepHeight(flat->GetGlobalSize(ui::Control::Direction::VERTICAL));}
                    auto label = new ui::Label;{
                        label->AddTo(head);
                        label->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                        Atstr prefix = L"欢迎您，";
                        Atstr name = account["name"];
                        if (name == "") {
                            name = L"【未设置姓名】";
                        }
                        label->SetContent(prefix + name);}
                }
                auto feet = new ui::HorizontalBox;{
                    feet->AddTo(flat);
                    feet->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    feet->SetHPreset(ui::Control::Preset::WRAP_AT_END);}
                {
                    auto idNum = new ui::Label;{
                        idNum->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                        Atstr prefix = L"学工号：";
                        idNum->SetContent(prefix + account.code);
                        idNum->AddTo(feet);}
                    logoutBtn = new ui::Button;{
                        logoutBtn->AddTo(feet);
                        logoutBtn->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                        logoutBtn->SetCaption(L"登出");}
                }
            }
            auto hor = new ui::HorizontalBox;{
                hor->AddTo(ver);
                hor->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);}
            {
                auto ver = new ui::VerticalScrollingBox;{
                    ver->AddTo(hor);
                    ver->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    ver->SetHSize(500);
                    ver->SetInsideBoxScrollable(true);}
                {
                    reserveBtn = new ui::Button;{
                        reserveBtn->SetCaption(L"预约入校");}
                    courseBtn = new ui::Button;{
                        courseBtn->SetCaption(L"课程系统");}
                    libraryBtn = new ui::Button;{
                        libraryBtn->SetCaption(L"图书馆");}
                    canteenBtn = new ui::Button;{
                        canteenBtn->SetCaption(L"在线饭堂");}
                    mailBtn = new ui::Button;{
                        mailBtn->SetCaption(L"私信");}
                    nolifyBtn = new ui::Button;{
                        nolifyBtn->SetCaption(L"通知与公示");}
                    accBtn = new ui::Button;{
                        accBtn->SetCaption(L"帐户权限管理");}
                    for (auto btn : {reserveBtn, courseBtn, libraryBtn, canteenBtn, mailBtn, nolifyBtn, accBtn}) {
                        btn->AddTo(ver);
                        btn->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    }
                }
            }
        }
    }
}

void eea::MainPage::Logic(ui::Screen *screen) noexcept
{
    logoutBtn->SetClickCallback([&](const Atstr &name, const sf::Event &event) -> void {
        SwitchTo(new Login);
    });
    reserveBtn->SetClickCallback([&](const Atstr &name, const sf::Event &event) -> void {
        SwitchTo(new lab::EnterReserve);
    });
    courseBtn->SetClickCallback([&](const Atstr &name, const sf::Event &event) -> void {
        SwitchTo(new lab::EnterCourse);
    });
    libraryBtn->SetClickCallback([&](const Atstr &name, const sf::Event &event) -> void {
        SwitchTo(new vio::EnterLibrary);
    });
    canteenBtn->SetClickCallback([&](const Atstr &name, const sf::Event &event) -> void {
        SwitchTo(new EnterCanteen);
    });
    mailBtn->SetClickCallback([&](const Atstr &name, const sf::Event &event) -> void {
        SwitchTo(new EnterMailSystem);
    });
    nolifyBtn->SetClickCallback([&](const Atstr &name, const sf::Event &event) -> void {
        SwitchTo(new vio::EnterNolify);
    });
    accBtn->SetClickCallback([&](const Atstr &name, const sf::Event &event) -> void {
        SwitchTo(new EnterAccManage);
    });
}

void eea::MainPage::Ready(ui::Screen *screen) noexcept
{
    ;
}

void eea::Retry::Load(ui::Screen *screen) noexcept
{
    ;
}

void eea::Retry::Logic(ui::Screen *screen) noexcept
{
    ;
}

void eea::Retry::Ready(ui::Screen *screen) noexcept
{
    ;
}

void eea::EnterAccManage::Load(ui::Screen *screen) noexcept
{
    ;
}

void eea::EnterAccManage::Logic(ui::Screen *screen) noexcept
{
    ;
}

void eea::EnterAccManage::Ready(ui::Screen *screen) noexcept
{
    ;
}
