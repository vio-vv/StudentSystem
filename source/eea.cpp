#include "client_pages.hpp"
#include "eea.hpp"

void eea::AccountDelail::Load(ui::Screen *screen) noexcept
{
    auto mar = new ui::Margin; {
        mar->AddTo(screen);
        mar->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
        mar->SetMargin(80, 80, 200, 200);
    }
    {
        auto ver = new ui::VerticalBox; {
            ver->AddTo(mar);
            ver->SetGap(100);
        }
        {
            backBtn = new ui::Button; {
                backBtn->AddTo(ver);
                backBtn->SetCaption("返回上一级");
            }
            auto box = new ui::VerticalScrollingBox; {
                box->AddTo(ver);
                box->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                box->SetGap(80);
                box->SetInsideBoxScrollable(true);
            }
            {
                auto base = new ui::VerticalBox; {
                    base->AddTo(box);
                    base->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    base->SetHSize(80);
                    base->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                }
                {
                    auto hbox = new ui::HorizontalBox; {
                        hbox->AddTo(base);
                        hbox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        hbox->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                    }
                    {
                        auto label = new ui::Label; {
                            label->AddTo(hbox);
                            label->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);  
                            label->SetHSize(175);
                            label->SetContent("学工号");      
                        }
                        userInput = new ui::InputBox; {
                            userInput->AddTo(hbox);
                            userInput->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                            userInput->SetLengthLimit(64);
                            userInput->SetContentLimit(ui::InputBox::ContentLimit::ALLOW_SPECIAL_CHARACTERS_ONLY);
                            userInput->SetSpecialCharacters(ui::InputBox::NUMBER + ui::InputBox::LOWER_LETTER + ui::InputBox::UPPER_LETTER + "_-@.");
                        }
                    }
                    hbox = new ui::HorizontalBox; {
                        hbox->AddTo(base);
                        hbox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        hbox->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                    }
                    {
                        auto label = new ui::Label; {
                            label->AddTo(hbox);
                            label->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER); 
                            label->SetHSize(175);
                            label->SetContent("密码");
                        }
                        paswInput = new ui::InputBox; {
                            paswInput->AddTo(hbox);
                            paswInput->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                            paswInput->SetLengthLimit(64);
                            paswInput->SetContentLimit(ui::InputBox::ContentLimit::ALLOW_SPECIAL_CHARACTERS_ONLY);
                            paswInput->SetSpecialCharacters(ui::InputBox::ASCII);
                        }
                        randPaswBtn = new ui::Button; {
                            randPaswBtn->AddTo(hbox);
                            randPaswBtn->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                            randPaswBtn->SetCaption("随机");
                        }
                    }
                    limitTips = new ui::Label; {
                        limitTips->AddTo(base);  
                        limitTips->SetFontColor(sf::Color::Red);
                        limitTips->SetFontSize(30);
                        limitTips->Hide();
                        limitTips->SetContent((std::string)"帐号只能由数字、大小写字母以及 _-@. 构成，\n且长度不超过 64 个字符。\n"
                            + "密码只能由 ASCII 字符构成，\n且长度不超过 64 个字符。");
                    };
                }
                base = new ui::VerticalBox; {
                    base->AddTo(box);
                    base->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    base->SetHSize(80);
                    base->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                }
                {
                    auto label = new ui::Label; {
                        label->AddTo(base);
                        label->SetContent("* 权限");
                    }
                    accessBox = new ui::HorizontalBox; {
                        accessBox->AddTo(base);
                        accessBox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        accessBox->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                    }
                    {
                        ;
                    }
                    auto flat = new ui::Flat; {
                        flat->AddTo(base);
                        flat->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        flat->SetVSize(50);
                    }
                    {
                        columnAdd = new ui::Button; {
                            columnAdd->AddTo(flat);
                            columnAdd->SetHPreset(ui::Control::Preset::PLACE_AT_END);
                            columnAdd->SetHSize(100);
                            columnAdd->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                            columnAdd->SetCaption("+");
                        }    
                        columnDel = new ui::Button; {
                            columnDel->AddTo(flat);
                            columnDel->SetPreset(ui::Control::Preset::PLACE_AT_FRONT);
                            columnDel->SetHSize(100);
                            columnDel->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                            columnDel->SetCaption("-");
                        }
                    }
                }
                base = new ui::VerticalBox; {
                    base->AddTo(box);
                    base->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    base->SetHSize(80);
                    base->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                }
                {
                    auto label = new ui::Label; {
                        label->AddTo(base);
                        label->SetContent("* 标签");
                    }
                    editBox = new ui::VerticalBox; {
                        editBox->AddTo(base);
                        editBox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        editBox->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                    }
                    addTagBtn = new ui::Button; {
                        addTagBtn->AddTo(base);
                        addTagBtn->SetPreset(ui::Control::Preset::PLACE_AT_CENTER);
                        addTagBtn->SetCaption("创建标签");
                    }
                }
            }
            okBtn = new ui::Button; {
                okBtn->AddTo(ver);
                okBtn->SetCaption("确认新建");
                okBtn->SetHPreset(ui::Control::Preset::PLACE_AT_END);
            }
        }
    }
}

void eea::AccountDelail::Logic(ui::Screen *screen) noexcept
{
    backBtn->SetClickCallback(UI_CALLBACK{
        screen->HideAll();
        auto click = MessageBox(screen, "您将丢弃当前编辑的内容，继续返回吗？", {"确认", "取消"});
        if (click == 0) {
            SwitchTo(new EnterAccManage);
        } else {
            screen->FreeAllVisible();
            screen->ShowAll();
        }
    });

    userInput->SetInputCallback(UI_CALLBACK{
        newAccount.code = userInput->GetText();
    });
    userInput->SetExceedLimitCallback(UI_CALLBACK{
        limitTips->Show();
    });
    paswInput->SetExceedLimitCallback(UI_CALLBACK{
        limitTips->Show();
    });

    auto rand = [=, this](){
        auto g = trm::GenerateRandomCode;
        char c;
        static char s[] = "!@#$%?&*";
        do {
            if (g() % 2) {
                if (g() % 2) {
                    c = '0' + (g() % 10); // 数字
                } else {
                    c = s[g() % 8]; // 特殊字符
                }
            } else {
                if (g() % 2) {
                    c = 'a' + (g() % 26); // 小写字母
                } else {
                    c = 'A' + (g() % 26); // 大写字母
                }
            }
        } while (c == '1' || c == 'l' || c == 'I' || c == '0' || c == 'O');
        return c;
    };
    randPaswBtn->SetClickCallback(UI_CALLBACK{
        std::string newPasw;
        for (int c = 10; c--; ) newPasw += rand();
        paswInput->SetText(newPasw);
    });

    columnAdd->SetClickCallback(UI_CALLBACK{
        if (columnNum < 7) {
            ++columnNum;
            reorganizeAccessBox();
        }
    });
    columnDel->SetClickCallback(UI_CALLBACK{
        if (columnNum > 1) {
            --columnNum;
            reorganizeAccessBox();
        }
    });

    auto accessOn = UI_CALLBACK{
        newAccount.access.push_back((trm::Access)ToNum(name));
    };
    auto accessOff = UI_CALLBACK{
        auto toDelete = newAccount.access.end();
        for (auto it = newAccount.access.begin(); it != newAccount.access.end(); ++it) {
            if (*it == (trm::Access)ToNum(name)) {
                toDelete = it;
                break;
            }
        }
        if (toDelete != newAccount.access.end()) {
            newAccount.access.erase(toDelete);
        }
    };

    reorganizeAccessBox = [=, this](){
        accessBox->FreeAll();
        accessList.clear();
        std::vector<ui::VerticalBox *> vers;
        for (int c = columnNum; c--; ) {
            auto ver = new ui::VerticalBox; {
                ver->AddTo(accessBox);
                ver->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                ver->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
            }
            vers.push_back(ver);
        }
        int col = 0;
        for (int access = 0; access < trm::Access::_COMMON; ++access) {
            if (std::find(account.access.begin(), account.access.end(), trm::Access::ADM) == account.access.end() && 
                std::find(account.access.begin(), account.access.end(), (trm::Access)access) == account.access.end()) {
                continue;
            }
            auto btn = new ui::ToggleButton(trm::GetAccessInfo((trm::Access)access).name, ToStr(access),
                accessOn, accessOff);
            btn->SetPreset(ui::Control::Preset::PLACE_AT_CENTER);
            accessList.push_back(btn);
            vers[col]->Add(btn);
            if (std::find(newAccount.access.begin(), newAccount.access.end(), (trm::Access)access) != newAccount.access.end()) {
                btn->SetOn();
            }
            ++col;
            if (col == columnNum) col = 0;
        }
    };

    auto delTag = UI_CALLBACK{
        int idx = ToNum(name);
        QueueFree(tagHors[idx]);
        tagHors.erase(idx);
        tagNames.erase(idx);
        tagValues.erase(idx);
    };

    addTagBtn->SetClickCallback(UI_CALLBACK{
        ++tagHorsNum;
        auto &hbox = tagHors[tagHorsNum] = new ui::HorizontalBox; {
            hbox->AddTo(editBox);
            hbox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
            hbox->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
        }
        {
            auto label = new ui::Label; {
                label->AddTo(hbox);
                label->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                label->SetContent("标签 " + ToStr(tagHorsNum) + "：");
            }
            label = new ui::Label; {
                label->AddTo(hbox);
                label->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                label->SetContent("标签名：");
            }
            auto &input = tagNames[tagHorsNum] = new ui::InputBox; {
                input->AddTo(hbox);
                input->SetVPreset(ui::Control::Preset::PLACE_AT_CENTER);
                input->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                input->SetHMinSize(200);
                input->SetLengthLimit(20);
                input->SetContentLimit(ui::InputBox::ContentLimit::BAN_SPECIAL_CHARACTERS);
                input->SetSpecialCharacters("\n");
            }
            label = new ui::Label; {
                label->AddTo(hbox);
                label->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                label->SetContent("* 标签值：");
            }
            auto &value = tagValues[tagHorsNum] = new ui::InputBox; {
                value->AddTo(hbox);
                value->SetVPreset(ui::Control::Preset::PLACE_AT_CENTER);
                value->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                value->SetHMinSize(200);
                value->SetLengthLimit(64);
                value->SetContentLimit(ui::InputBox::ContentLimit::BAN_SPECIAL_CHARACTERS);
                value->SetSpecialCharacters("\n");
            }
            auto delBtn = new ui::Button("删除", delTag, ToStr(tagHorsNum)); {
                delBtn->AddTo(hbox);
                delBtn->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
            }
        }
    });

    okBtn->SetClickCallback(UI_CALLBACK{
        auto pasw = paswInput->GetText();
        if (newAccount.code == "" || pasw == "") {
            screen->HideAll();
            MessageBox(screen, "学工号或密码不能为空。");
            screen->FreeAllVisible();
            screen->ShowAll();
            return;
        }
        for (auto [k, name] : tagNames) {
            if (name->GetText() == "") {
                screen->HideAll();
                MessageBox(screen, "标签名不能为空。");
                screen->FreeAllVisible();
                screen->ShowAll();
                return;
            }
        }

        newAccount.hashedPassword = trm::Hash(pasw);
        for (auto [k, name] : tagNames) {
            newAccount.tags.push_back({name->GetText(), tagValues[k]->GetText()});
        }

        screen->HideAll();
        auto [success, reply] = WaitServer(screen, 
            {trm::rqs::CREATE_ACCOUNT, username, password, newAccount}, "正在与服务端通信");
        screen->FreeAllVisible();
        if (success == 1) {
            if (reply[0] == trm::rpl::SUCC) {
                auto click = MessageBox(screen, "创建成功", {"返回帐户管理主页", "再新建一个"});
                if (click == 0) {
                    SwitchTo(new EnterAccManage);
                } else if (click == 1) {
                    SwitchTo(new AccountDelail);
                } else {
                    assert(false); // Impossible click.
                }
            } else if (reply[0] == trm::rpl::FAIL) {
                MessageBox(screen, "创建失败！\n可能系统中已经存在该帐户");
                screen->FreeAllVisible();
                screen->ShowAll();
            } else if (reply[0] == trm::rpl::ACCESS_DENIED) {
                MessageBox(screen, "对不起，您没有在系统内新建帐户的权限");
                screen->FreeAllVisible();
                screen->ShowAll();
            } else {
                assert(false); // Unexpected reply.
            }
        } else if (success == 0) {
            MessageBox(screen, "服务端未响应，请检查后重试");
            screen->FreeAllVisible();
            screen->ShowAll();
        }
    });
}

void eea::AccountDelail::Ready(ui::Screen *screen) noexcept
{
    reorganizeAccessBox();
}

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
                    assert(false); // Unexpected reply.
                }    
            } else if (success == 0) {
                screen->HideAll();
                MessageBox(screen, "服务端未响应，请检查后重试");
                screen->FreeAllVisible();
                screen->ShowAll();
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
        mar->AddTo(screen);
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
                    backBtn = new ui::Button("返回主页");
                    writeMailBtn = new ui::Button("写  信");
                    refreshBtn = new ui::Button("刷新");
                    for (auto btn : {backBtn, writeMailBtn, refreshBtn}) {
                        btn->AddTo(btnBox);
                        btn->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        btn->SetHSize(80);
                        btn->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
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
                    list = new ui::VerticalBox; {
                        list->AddTo(inBox);
                        list->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    }
                    {
                        list->Add(new ui::Spacer(0, 50));
                        msgBox = new ui::VerticalScrollingBox; {
                            msgBox->AddTo(list);
                            msgBox->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                            msgBox->SetInsideBoxScrollable(true);
                        }
                        {
                            ;
                        }
                        list->Add(new ui::Spacer(0, 50));
                        turner = new ui::PageTurner; {
                            turner->AddTo(list);
                            turner->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                            turner->SetFontSize(30);
                            turner->SetSingle(50);
                            turner->SetGap(15);
                        }
                    }
                    loading = new ui::Center; {
                        loading->AddTo(inBox);
                        loading->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        loading->Hide();
                    }
                    {
                        auto ring = new ui::LoadingRing; {
                            ring->AddTo(loading);
                            ring->SetSize(60, 60);
                            ring->Start();
                        }
                    }
                }
            }
            auto mailDetail = new ui::VerticalBox; {
                mailDetail->AddTo(hor);
                mailDetail->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
            }
            {
                subject = new ui::Label; {
                    subject->AddTo(mailDetail);
                    subject->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                    subject->SetFontSize(75);
                }
                auto elseInfo = new ui::HorizontalBox; {
                    elseInfo->AddTo(mailDetail);
                    elseInfo->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    elseInfo->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                    elseInfo->SetGap(50);
                }
                {
                    sender = new ui::Label;
                    receiver = new ui::Label;
                    dateTime = new ui::Label;
                    state = new ui::Label;
                    for (auto each : {sender, receiver, dateTime, state}) {
                        each->AddTo(elseInfo);
                        each->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                        each->SetFontSize(30);
                        each->SetFontColor({199, 199, 199});
                    }
                }
                auto content = new ui::VerticalScrollingBox; {
                    content->AddTo(mailDetail);
                    content->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    content->SetInsideBoxScrollable(true);
                }
                {
                    mailContent = new ui::Label; {
                        mailContent->AddTo(content);
                        mailContent->SetMaxCount(32);
                    }
                }
            }
        }
    }
}

void eea::EnterMailSystem::Logic(ui::Screen *screen) noexcept
{
    backBtn->SetClickCallback(UI_CALLBACK{
        SwitchTo(new MainPage);
    });

    auto checkMail = [=, this](const std::string &name){
        Listen(new trm::Sender({trm::rqs::GET_MESSAGE, username, password, name}), SD_CALLBACK{
            if (reply[0] == trm::rpl::TIME_OUT) {
                ;
            } else if (reply[0] == trm::rpl::FAIL) {
                ;
            } else {
                auto con = trm::MailContent(reply[0]);
                subject->SetContent("主题：" + con.subject);
                sender->SetContent("发件人：" + con.sender);
                receiver->SetContent("收件人：" + con.receiver);
                dateTime->SetContent("时间：" + ToStr(con.timeStamp));
                if (con.read) state->SetContent("已读");
                else state->SetContent("未读");
                mailContent->SetContent(con.content);
            }
        });
    };

    auto getMsgItem = [=, this](const trm::MailContent &pro, unsigned long long index){
        std::string content = "";
        if (!pro.read) {
            content += "【*】";
        }
        content += pro.subject + " | ";
        content += pro.sender;

        auto res = new ui::HorizontalBox; {
            res->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
            res->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
        }
        {
            auto btn = new ui::Button; {
                btn->AddTo(res);
                btn->SetCaption("查看");
                btn->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                btn->SetName(ToStr(index));
                btn->SetClickCallback(UI_CALLBACK{ checkMail(name); });
                btn->SetFontSize(40);
            }
            auto label = new ui::Label; {
                label->AddTo(res);
                label->SetContent(content);
                label->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                label->SetFontSize(40);
            }
        }
        return res;
    };

    auto refreshMsgbox = UI_CALLBACK{
        if (!turnable) return;
        turnable = false;
        turner->Disable();
        refreshBtn->Disable();
        msgBox->FreeAll();
        auto label = new ui::Label("加载中..."); {
            msgBox->Add(new ui::Center(label, ui::Control::Preset::FILL_FROM_CENTER));
            label->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
        }
        unsigned long long from = (turner->GetCurrentPage() - 1) * eachPageNum;
        Listen(new trm::Sender({trm::rqs::GET_MESSAGE_PROFILE, username, password, ToStr(from), ToStr(eachPageNum)}), SD_CALLBACK{
            if (reply[0] == trm::rpl::TIME_OUT) {
                label->SetContent("加载失败，请重试");
            } else {
                msgBox->FreeAll();
                for (int i = 0; i < std::min(eachPageNum, (int)reply.size()); ++i) {
                    auto pro = trm::MailContent(reply[i]);
                    msgBox->Add(getMsgItem(pro, from + i));
                }
            }
            turnable = true;
            turner->Enable();
            refreshBtn->Enable();
        });
    };

    turner->SetTurnCallback(refreshMsgbox);

    refreshList = [=, this](){
        if (loading->GetVisible()) return;

        loading->Show();
        list->Hide();
        turnable = false;

        msgBox->FreeAll();
        Listen(new trm::Sender({trm::rqs::GET_MESSAGE_NUMBER, username, password}), SD_CALLBACK{
            if (reply[0] == trm::rpl::TIME_OUT) {
                msgBox->Add(new ui::Center(
                    new ui::Label("服务端未响应，请检查后重试。", ui::Control::Preset::WRAP_AT_CENTER), 
                    ui::Control::Preset::FILL_FROM_CENTER)
                );
                turner->SetMaxPage(1);
                loading->Hide();
                list->Show();
            } else {
                auto num = ToNum<unsigned long long>(reply[0]);
                auto page = num / eachPageNum + (num % eachPageNum ? 1 : 0);
                turner->SetMaxPage(page);
                turner->SetCurrentPage(1);
                loading->Hide();
                list->Show();
                turnable = true;
                refreshMsgbox({}, {});
            }
        });
    };

    refreshBtn->SetClickCallback(UI_CALLBACK{
        refreshList();
    });
}

void eea::EnterMailSystem::Ready(ui::Screen *screen) noexcept
{
    refreshList();
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

void eea::EnterAccManage::Load(ui::Screen *screen) noexcept
{
    auto mar = new ui::Margin; {
        mar->AddTo(screen);
        mar->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
        mar->SetMargin(80, 80, 200, 200);
    }
    {
        auto hor = new ui::HorizontalBox; {
            hor->AddTo(mar);
            hor->SetGap(40);
        }
        {
            auto verBox = new ui::VerticalBox; {
                verBox->AddTo(hor);
                verBox->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                verBox->SetHSize(1);
                verBox->SetGap(50);
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
                    refreshBtn = new ui::Button; {
                        refreshBtn->AddTo(btnBox);
                        refreshBtn->SetCaption("刷新");
                        refreshBtn->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    }
                }
                labelCenter = new ui::Center; {
                    labelCenter->AddTo(verBox);
                    labelCenter->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    labelCenter->Hide();
                }
                {
                    resultLabel = new ui::Label; {
                        resultLabel->AddTo(labelCenter);
                        resultLabel->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                    }
                }
                ringCenter = new ui::Center; {
                    ringCenter->AddTo(verBox);
                    ringCenter->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    ringCenter->Hide();
                }
                {
                    auto ring = new ui::LoadingRing; {
                        ring->AddTo(ringCenter);
                        ring->SetSize(80, 80);
                        ring->Start();
                    }
                }
                list = new ui::VerticalScrollingBox; {
                    list->AddTo(verBox);
                    list->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    list->SetInsideBoxScrollable(true);
                }
                {
                    ;
                }
                btnBox = new ui::HorizontalBox; {
                    btnBox->AddTo(verBox);
                    btnBox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    btnBox->SetVSize(80);
                }
                {
                    newBtn = new ui::Button; {
                        newBtn->AddTo(btnBox);
                        newBtn->SetCaption("新建帐户");
                        newBtn->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    }
                    resetBtn = new ui::Button; {
                        resetBtn->AddTo(btnBox);
                        resetBtn->SetCaption("重置帐户与权限系统");
                        resetBtn->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    }
                }
            }
            detailBox = new ui::VerticalScrollingBox; {
                detailBox->AddTo(hor);
                detailBox->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                detailBox->SetHSize(2);
                detailBox->SetGap(80);
                detailBox->SetInsideBoxScrollable(true);
            }
            {
                auto center = new ui::Center; {
                    center->AddTo(detailBox);
                    center->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                }
                {
                    auto label = new ui::Label; {
                        label->AddTo(center);
                        label->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                        label->SetContent("选择一个帐户，\n在这里查看详细信息");
                    }
                }
            }
        }
    }
}

void eea::EnterAccManage::Logic(ui::Screen *screen) noexcept
{
    resetBtn->SetClickCallback(UI_CALLBACK{
        screen->HideAll();
        auto click = MessageBox(screen, "你正在进行一个危险操作！\n您将重置帐户与权限系统，这意味着清空系统内所有的帐户信息，并退出登录。\n确认吗？", {"确认", "取消"});
        screen->FreeAllVisible();
        if (click == 0) {
            auto [success, reply] = WaitServer(screen, {trm::rqs::RESET_ACCOUNT_AND_ACCESS, username, password}, "正在与服务端通信");
            screen->FreeAllVisible();
            if (success == 1) {
                if (reply[0] == trm::rpl::SUCC) {
                    MessageBox(screen, "重置成功\n稍后请重新登录");
                    SwitchTo(new Login);
                } else {
                    MessageBox(screen, "重置失败！");
                    screen->ShowAll();
                }
            } else if (success == 0) {
                MessageBox(screen, "服务端未响应，请检查后重试");
                screen->ShowAll();
            }
        } else {
            screen->ShowAll();
        }
    });

    auto deleteCallback = UI_CALLBACK{
        if (name == username) {
            screen->HideAll();
            MessageBox(screen, "不能删除自己！");
            screen->FreeAllVisible();
            screen->ShowAll();
            return;
        }
        screen->HideAll();
        auto click = MessageBox(screen, "您将删除该帐户 " + name + "，确认吗？", {"确认", "取消"});
        if (click == 0) {
            screen->FreeAllVisible();
            auto [success, reply] = WaitServer(screen, 
                {trm::rqs::DELETE_ACCOUNT, username, password, name}, "正在与服务端通信");
            if (success == 1) {
                if (reply[0] == trm::rpl::SUCC) {
                    screen->FreeAllVisible();
                    MessageBox(screen, "删除成功");
                    SwitchTo(new EnterAccManage);
                } else if (reply[0] == trm::rpl::FAIL) {
                    screen->FreeAllVisible();
                    MessageBox(screen, "删除失败！\n可能待删除的帐户不存在");
                    screen->FreeAllVisible();
                    screen->ShowAll();
                } else if (reply[0] == trm::rpl::ACCESS_DENIED) {
                    screen->FreeAllVisible();
                    MessageBox(screen, "对不起，您没有删除系统内帐户的权限");
                    screen->FreeAllVisible();
                    screen->ShowAll();
                }
            } else if (success == 0) {
                screen->FreeAllVisible();
                MessageBox(screen, "服务端未响应，请检查后重试");
                screen->FreeAllVisible();
                screen->ShowAll();
            }
        } else {
            screen->FreeAllVisible();
            screen->ShowAll();
        }
    };

    auto print = [=, this](const trm::Account &acc){
        auto label = new ui::Label; {
            label->AddTo(detailBox);
            label->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
            label->SetContent("==== 详细信息 ====");
        }
        auto box = new ui::VerticalBox; {
            box->AddTo(detailBox);
            box->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
            box->SetHSize(80);
            box->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
        }
        {
            box->Add(new ui::Label("学工号：" + acc.code));
            box->Add(new ui::Label("密码哈希值：" + acc.hashedPassword));
        }
        box = new ui::VerticalBox; {
            box->AddTo(detailBox);
            box->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
            box->SetHSize(80);
            box->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
        }
        {
            box->Add(new ui::Label("权限列表：" ));
            for (auto access : acc.access) {
                box->Add(new ui::Label("- " + trm::GetAccessInfo(access).name));
            }
        }
        box = new ui::VerticalBox; {
            box->AddTo(detailBox);
            box->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
            box->SetHSize(80);
            box->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
        }
        {
            box->Add(new ui::Label("标签列表：" ));
            for (auto tag : acc.tags) {
                box->Add(new ui::Label("- " + tag.first));
                box->Add(new ui::Label("  " + tag.second));
            }
        }
        auto deleteBtn = new ui::Button("删除帐户", deleteCallback, acc.code); {
            deleteBtn->AddTo(detailBox);
            deleteBtn->SetHPreset(ui::Control::Preset::PLACE_AT_CENTER);
        }
    };
    auto detailBtnCallback = UI_CALLBACK{
        if (detailCalling) return;
        detailCalling = true;
        detailBox->FreeAll();
        auto center = new ui::Center; {
            center->AddTo(detailBox);
            center->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
        }
        {
            auto ring = new ui::LoadingRing; {
                ring->AddTo(center);
                ring->SetSize(80, 80);
                ring->Start();
            }
        }
        Listen(new trm::Sender({trm::rqs::GET_ACCOUNT_DETAIL, username, password, name}), SD_CALLBACK{
            center->FreeAll();
            if (reply[0] == trm::rpl::TIME_OUT) {
                center->Add(new ui::Label("服务端未响应，请检查后重试"));
            } else if (reply[0] == trm::rpl::ACCESS_DENIED) {
                center->Add(new ui::Label("对不起，您没有查看系统内帐户的权限"));
            } else {
                detailBox->FreeAll();
                print(trm::Account(reply[0]));
            }
            detailCalling = false;
        });
    };
    backBtn->SetClickCallback(UI_CALLBACK{
        SwitchTo(new MainPage);
    });
    refreshBtn->SetClickCallback(refresh = UI_CALLBACK{
        refreshBtn->Enable(false);
        list->FreeAll();
        auto label = new ui::Label; {
            label->AddTo(list);
            label->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
            label->SetContent("-- 帐户列表 --");
        }

        list->Hide();
        labelCenter->Hide();
        ringCenter->Show();
        Listen(new trm::Sender({trm::rqs::LIST_ACCOUNT, username, password}), SD_CALLBACK{
            list->Hide();
            labelCenter->Hide();
            ringCenter->Hide();
            if (reply[0] == trm::rpl::TIME_OUT) {
                labelCenter->Show();
                resultLabel->SetContent("服务端未响应，请检查后刷新重试");
            } else if (reply[0] == trm::rpl::ACCESS_DENIED) {
                labelCenter->Show();
                resultLabel->SetContent("对不起，您没有查看系统内帐户的权限");
            } else {
                list->Show();
                for (auto acc : reply) {
                    auto btn = new ui::Button; {
                        btn->AddTo(list);
                        btn->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        btn->SetName(acc);
                        btn->SetCaption(acc);
                        btn->SetClickCallback(detailBtnCallback);
                    }
                }
            }

            refreshBtn->Enable();
        });
    });
    newBtn->SetClickCallback(UI_CALLBACK{
        SwitchTo(new AccountDelail);
    });
}

void eea::EnterAccManage::Ready(ui::Screen *screen) noexcept
{
    refresh("", {});
}
