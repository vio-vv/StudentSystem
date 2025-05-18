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
    auto box = new ui::VerticalBox; {
        box->SetGap(80);
        box->AddTo(screen);
        box->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
    }
    {
        auto pic = new ui::PictureBox; {
            pic->AddTo(box);
            pic->SetPicture(_ASSETS_"icon_with_title.png");
            pic->KeepHeight(100);
        }
        auto vertical = new ui::VerticalBox; {
            vertical->AddTo(box);
            vertical->SetSize(900, 250);
        }
        {
            auto user = new ui::HorizontalBox; {
                user->AddTo(vertical);
                user->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                user->SetGap(50);
            }
            {
                auto label = new ui::Label; {
                    label->AddTo(user);
                    label->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                    label->SetContent("帐号");
                }
                userInput = new ui::InputBox; {
                    userInput->AddTo(user);
                    userInput->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    userInput->SetText(username);
                    userInput->SetHSize(3);
                    userInput->SetLengthLimit(64);
                    userInput->SetContentLimit(ui::InputBox::ContentLimit::ALLOW_SPECIAL_CHARACTERS_ONLY);
                    userInput->SetSpecialCharacters(ui::InputBox::NUMBER + ui::InputBox::LOWER_LETTER + ui::InputBox::UPPER_LETTER + "_-@.");
                }
            }
            auto pasw = new ui::HorizontalBox; {
                pasw->AddTo(vertical);
                pasw->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                pasw->SetGap(50);
            }
            {
                auto label = new ui::Label; {
                    label->AddTo(pasw);
                    label->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                    label->SetContent("密码");
                }
                paswInput = new ui::InputBox; {
                    paswInput->AddTo(pasw);
                    paswInput->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    paswInput->SetHSize(3);
                    paswInput->SetProtectText(true);
                    paswInput->SetLengthLimit(64);
                    paswInput->SetContentLimit(ui::InputBox::ContentLimit::ALLOW_SPECIAL_CHARACTERS_ONLY);
                    paswInput->SetSpecialCharacters(ui::InputBox::ASCII);
                }
            }
        }  
        auto feetBox = new ui::VerticalBox; {
            feetBox->AddTo(box);
            feetBox->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
        }
        {
            auto btnBox = new ui::HorizontalBox; {
                btnBox->AddTo(feetBox);
                btnBox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                btnBox->SetGap(50);
            }
            {
                loginBtn = new ui::Button; {
                    loginBtn->AddTo(btnBox);
                    loginBtn->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    loginBtn->SetHSize(2);
                    loginBtn->SetCaption("登录");
                }
                forgetBtn = new ui::Button; {
                    forgetBtn->AddTo(btnBox);
                    forgetBtn->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    forgetBtn->SetHSize(2);
                    forgetBtn->SetCaption("忘记密码");
                }
                reserveBtn = new ui::Button; {
                    reserveBtn->AddTo(btnBox);
                    reserveBtn->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    reserveBtn->SetHSize(1);
                    reserveBtn->SetCaption("校外人员\n预约入校");
                }
            }
            tips = new ui::Label; {
                tips->AddTo(feetBox);
                tips->SetPreset(ui::Control::Preset::WRAP_AT_FRONT);
                tips->SetFontColor(sf::Color::Red);
                tips->SetFontSize(30);
                tips->Hide();
            }
        }        
    }
}

void eea::Login::Logic(ui::Screen *screen) noexcept
{
    userInput->SetInputCallback(UI_CALLBACK{
        username = userInput->GetText();
    });
    userInput->SetExceedLimitCallback(UI_CALLBACK{
        tips->SetContent("帐号只能由数字、大小写字母以及 _-@. 构成，\n且长度不超过 64 个字符。");
        tips->Show();
    });
    paswInput->SetInputCallback(UI_CALLBACK{
        password = paswInput->GetText();
    });
    paswInput->SetExceedLimitCallback(UI_CALLBACK{
        tips->SetContent("密码只能由 ASCII 字符构成，\n且长度不超过 64 个字符。");
        tips->Show();
    });
    loginBtn->SetClickCallback(UI_CALLBACK{
        if (username == "" || password == "") {
            tips->SetContent("帐号或密码不能为空。");
            tips->Show();
        } else {
            screen->HideAll();
            auto [success, reply] = WaitServer(screen, 
                {trm::rqs::CHECK_ACCOUNT, username, password}, "登录中");
            screen->FreeAllVisible();
            screen->ShowAll();
            if (success == 1) {
                if (reply[0] == trm::rpl::YES) {
                    account = reply[1];
                    SwitchTo(new MainPage);
                } else if (reply[0] == trm::rpl::NO) {
                    tips->SetContent("帐号或密码错误。");
                    tips->Show();
                } else {
                    assert(false); // Invalid reply.
                }    
            } else if (success == 0) {
                SwitchTo(new Retry);
            }
        }
    });
    forgetBtn->SetClickCallback(UI_CALLBACK{
        SwitchTo(new Forget);
    });
    reserveBtn->SetClickCallback(UI_CALLBACK{
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
    auto mar = new ui::Margin; {
        screen->Add(mar);
        mar->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
        mar->SetMargin(80, 80, 200, 200);
    }
    {
        auto hor = new ui::HorizontalBox; {
            hor->AddTo(mar);
            hor->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
        }
        {
            auto ver = new ui::VerticalBox; {
                ver->AddTo(hor);
                ver->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                ver->SetHSize(500);
                ver->SetGap(100);
            }
            {
                auto btnBox = new ui::VerticalBox; {
                    btnBox->AddTo(ver);
                    btnBox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    btnBox->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                }
                {
                    backBtn = new ui::Button; {
                        backBtn->AddTo(btnBox);
                        backBtn->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        backBtn->SetCaption("返回主页");
                    }
                    auto writeMailBtn = new ui::Button; {
                        writeMailBtn->AddTo(btnBox);
                        writeMailBtn->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        writeMailBtn->SetCaption("写  信");
                    }
                }
                auto inBox = new ui::VerticalBox; {
                    inBox->AddTo(ver);
                    inBox->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                }
                {
                    auto label = new ui::Label; {
                        label->AddTo(inBox);
                        label->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                        label->SetContent("↓ 收件箱 ↓");
                    }
                    auto listBox = new ui::VerticalBox; {
                        listBox->AddTo(inBox);
                        listBox->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    }
                    {
                        auto list = new ui::VerticalBox; {
                            list->AddTo(listBox);
                            list->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        }
                        {
                            loading = new ui::LoadingRing; {
                                loading->AddTo(list);
                                loading->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                                loading->Start();
                            }
                        }
                        auto btnBox = new ui::HorizontalBox; {
                            btnBox->AddTo(listBox);
                            btnBox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                            btnBox->SetVSize(80);
                        }
                        {
                            auto elp1 = new ui::Label; {
                                elp1->SetContent("...");
                            }
                            l3 = new ui::Button; {
                                l3->SetName("-3");
                            }
                            l2 = new ui::Button; {
                                l2->SetName("-2");
                            }
                            l1 = new ui::Button; {
                                l1->SetName("-1");
                            }
                            auto center = new ui::Center; {
                            }
                            {    
                                cur = new ui::Label; {
                                    cur->AddTo(center);
                                    cur->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                                    cur->SetContent("1");
                                }
                            }
                            r1 = new ui::Button; {
                                r1->SetName("+1");
                            }
                            r2 = new ui::Button; {
                                r2->SetName("+2");
                            }
                            r3 = new ui::Button; {
                                r3->SetName("+3");
                            }
                            auto elp2 = new ui::Label; {
                                elp2->SetContent("...");
                            }
                            for (auto e : std::vector<ui::Control *>{elp1, l3, l2, l1, center, r1, r2, r3, elp2}) {
                                e->AddTo(btnBox);
                                e->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                                e->SetHMinSize(80);
                            }
                        }
                        auto gotoBox = new ui::HorizontalBox; {
                            gotoBox->AddTo(listBox);
                            gotoBox->SetHPreset(ui::Control::Preset::WRAP_AT_CENTER);
                            gotoBox->SetVSize(80);
                        }
                        {
                            auto center = new ui::Center; {
                                center->AddTo(gotoBox);
                                center->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                            }
                            {
                                auto label = new ui::Label; {
                                    label->AddTo(center);
                                    label->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                                    label->SetContent("跳转至");
                                }
                            }
                            center = new ui::Center; {
                                center->AddTo(gotoBox);
                                center->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                            }
                            {
                                auto input = new ui::InputBox; {
                                    input->AddTo(center);
                                    input->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                                    input->SetHMinSize(50);
                                }
                            }
                            center = new ui::Center; {
                                center->AddTo(gotoBox);
                                center->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                            }
                            {
                                auto maxNum = new ui::Label; {
                                    maxNum->AddTo(center);
                                    maxNum->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                                    maxNum->SetContent("/ 1");
                                }
                            }
                            auto goBtn = new ui::Button; {
                                goBtn->AddTo(gotoBox);
                                goBtn->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                                goBtn->SetCaption("跳转");
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
        e->SetClickCallback(UI_CALLBACK{
            int d = ToNum(name);
            cur->SetContent(ToStr(ToNum(cur->GetContent()) + d));
            UpdateButton();
        });
    }
    backBtn->SetClickCallback(UI_CALLBACK{
        SwitchTo(new MainPage);
    });
}

void eea::EnterMailSystem::Ready(ui::Screen *screen) noexcept
{
    UpdateButton();
}

void eea::EnterMailSystem::UpdateButton()
{
    for (auto e : {l3, l2, l1, r1, r2, r3}) {
        e->SetCaption(ToStr(ToNum(cur->GetContent()) + ToNum(e->GetName())));
    }
}

void eea::MainPage::Load(ui::Screen *screen) noexcept
{
    auto margin = new ui::Margin; {
        margin->AddTo(screen);
        margin->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
        margin->SetMargin(80, 80, 200, 200);
    }
    {
        auto ver = new ui::VerticalBox; {
            ver->AddTo(margin);
            ver->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
        }
        {
            auto flat = new ui::Flat; {
                flat->AddTo(ver);
                flat->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                flat->SetVSize(150);
            }
            {
                auto head = new ui::HorizontalBox; {
                    head->AddTo(flat);
                    head->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    head->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                }
                {
                    auto icon = new ui::PictureBox; {
                        icon->AddTo(head);
                        icon->SetPicture(_ASSETS_"icon.png");
                        screen->Tick();
                        icon->KeepHeight(flat->GetGlobalSize(ui::Control::Direction::VERTICAL));
                    }
                    auto label = new ui::Label; {
                        label->AddTo(head);
                        label->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                        std::string prefix = "欢迎您，";
                        std::string name = account["name"];
                        if (name == "") {
                            name = "【未设置姓名】";
                        }
                        label->SetContent(prefix + name);
                    }
                }
                auto feet = new ui::HorizontalBox; {
                    feet->AddTo(flat);
                    feet->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    feet->SetHPreset(ui::Control::Preset::WRAP_AT_END);
                }
                {
                    auto idNum = new ui::Label; {
                        idNum->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                        std::string prefix = "学工号：";
                        idNum->SetContent(prefix + account.code);
                        idNum->AddTo(feet);
                    }
                    logoutBtn = new ui::Button; {
                        logoutBtn->AddTo(feet);
                        logoutBtn->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                        logoutBtn->SetCaption("登出");
                    }
                }
            }
            auto hor = new ui::HorizontalBox; {
                hor->AddTo(ver);
                hor->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
            }
            {
                auto ver = new ui::VerticalScrollingBox; {
                    ver->AddTo(hor);
                    ver->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    ver->SetHSize(500);
                    ver->SetInsideBoxScrollable(true);
                }
                {
                    reserveBtn = new ui::Button; {
                        reserveBtn->SetCaption("预约入校");
                    }
                    courseBtn = new ui::Button; {
                        courseBtn->SetCaption("课程系统");
                    }
                    libraryBtn = new ui::Button; {
                        libraryBtn->SetCaption("图书馆");
                    }
                    canteenBtn = new ui::Button; {
                        canteenBtn->SetCaption("在线饭堂");
                    }
                    mailBtn = new ui::Button; {
                        mailBtn->SetCaption("私信");
                    }
                    nolifyBtn = new ui::Button; {
                        nolifyBtn->SetCaption("通知与公示");
                    }
                    accBtn = new ui::Button; {
                        accBtn->SetCaption("帐户权限管理");
                    }
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
    logoutBtn->SetClickCallback(UI_CALLBACK{
        SwitchTo(new Login);
    });
    reserveBtn->SetClickCallback(UI_CALLBACK{
        SwitchTo(new lab::EnterReserve);
    });
    courseBtn->SetClickCallback(UI_CALLBACK{
        SwitchTo(new lab::EnterCourse);
    });
    libraryBtn->SetClickCallback(UI_CALLBACK{
        SwitchTo(new vio::EnterLibrary);
    });
    canteenBtn->SetClickCallback(UI_CALLBACK{
        SwitchTo(new EnterCanteen);
    });
    mailBtn->SetClickCallback(UI_CALLBACK{
        SwitchTo(new EnterMailSystem);
    });
    nolifyBtn->SetClickCallback(UI_CALLBACK{
        SwitchTo(new vio::EnterNolify);
    });
    accBtn->SetClickCallback(UI_CALLBACK{
        SwitchTo(new EnterAccManage);
    });
}

void eea::MainPage::Ready(ui::Screen *screen) noexcept
{
    ;
}

void eea::Retry::Load(ui::Screen *screen) noexcept
{
    auto vbox = new ui::VerticalBox; {
        vbox->AddTo(screen);
        vbox->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
        vbox->SetGap(50);
    }
    {
        auto label = new ui::Label; {
            label->AddTo(vbox);
            label->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
            label->SetContent("服务器未响应，请检查后重试");
        }
        btn = new ui::Button; {
            btn->AddTo(vbox);
            btn->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
            btn->SetCaption("确定");
        }
    }
}

void eea::Retry::Logic(ui::Screen *screen) noexcept
{
    btn->SetClickCallback(UI_CALLBACK{
        SwitchTo(new EnterSystem);
    });
}

void eea::Retry::Ready(ui::Screen *screen) noexcept
{
    ;
}

void eea::EnterAccManage::Load(ui::Screen *screen) noexcept
{
    auto mar = new ui::Margin; {
        screen->Add(mar);
        mar->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
        mar->SetMargin(80, 80, 200, 200);
    }
    {
        auto verBox = new ui::VerticalBox; {
            verBox->AddTo(mar);
        }
        {
            auto btnBox = new ui::HorizontalBox; {
                btnBox->AddTo(verBox);
                btnBox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                btnBox->SetVSize(80);
            }
            {
                backBtn = new ui::Button; {
                    backBtn->AddTo(btnBox);
                    backBtn->SetCaption("返回主页");
                    backBtn->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                }
            }
            ringCenter = new ui::Center; {
                ringCenter->AddTo(verBox);
                ringCenter->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
            }
            {
                ring = new ui::LoadingRing; {
                    ring->AddTo(ringCenter);
                    ring->SetSize(80, 80);
                }
            }
            list = new ui::HorizontalBox; {
                list->AddTo(verBox);
                list->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                list->Hide();
            }
            {
                code = new ui::VerticalBox; {
                    code->AddTo(list);
                    code->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                }
                {
                    auto label = new ui::Label; {
                        label->AddTo(code);
                        label->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                        label->SetContent("学工号");
                    }
                }
                access = new ui::VerticalBox; {
                    access->AddTo(list);
                    access->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                }
                {
                    auto label = new ui::Label; {
                        label->AddTo(access);
                        label->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                        label->SetContent("权限");
                    }
                }
                tags = new ui::VerticalBox; {
                    tags->AddTo(list);
                    tags->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                }
                {
                    auto label = new ui::Label; {
                        label->AddTo(tags);
                        label->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                        label->SetContent("标签");
                    }
                }
            }
        }
    }
}

void eea::EnterAccManage::Logic(ui::Screen *screen) noexcept
{
    backBtn->SetClickCallback(UI_CALLBACK{
        SwitchTo(new MainPage);
    });
}

void eea::EnterAccManage::Ready(ui::Screen *screen) noexcept
{
    ring->Start();
    Listen(new trm::Sender({trm::rqs::LIST_ACCOUNT, username, password}), SD_CALLBACK{
        if (reply[0] == trm::rpl::TIME_OUT) {
            SwitchTo(new Retry);
        } else if (reply[0] == trm::rpl::ACCESS_DENIED) {
            ringCenter->Hide();
            auto center = new ui::Center; {
                center->AddTo(list);
                center->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
            }
            {
                auto label = new ui::Label; {
                    label->AddTo(center);
                    label->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                    label->SetContent("对不起，您没有查看系统内帐户的权限");
                }
            }
        } else {
            ringCenter->Hide();
            list->Show();
            for (trm::Account acc : reply) {
                ui::Label *label;
                label = new ui::Label; {
                    label->AddTo(code);
                    label->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                    label->SetContent(acc.code);
                }
                label = new ui::Label; {
                    label->AddTo(access);
                    label->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                    std::string cnt;
                    for (auto each : acc.access) {
                        cnt += each;
                        cnt += "; ";
                    }
                    label->SetContent(cnt);
                }
                label = new ui::Label; {
                    label->AddTo(tags);
                    label->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                    std::string cnt;
                    for (auto each : acc.tags) {
                        cnt += " [";
                        cnt += each.first;
                        cnt += ": ";
                        cnt += each.second;
                        cnt += "]; ";
                    }
                    label->SetContent(cnt);
                }
            }
        }
    });
}
