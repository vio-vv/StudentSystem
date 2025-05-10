#include "client_pages.hpp"

clpg::ID clpg::EnterCanteen(ui::Screen &screen) noexcept
{
    ;

    while (screen.IsOpen()) {
        screen.Tick();
    }
    return ID::BREAK;
}

clpg::ID clpg::EnterMailSystem(ui::Screen &screen) noexcept
{
    bool back = false;

    auto mar = new ui::Margin;
    screen.Add(mar);
    mar->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
    mar->SetMargin(80, 80, 200, 200);
    {
        auto hor = new ui::HorizontalBox;
        hor->AddTo(mar);
        hor->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
        {
            auto ver = new ui::VerticalBox;
            ver->AddTo(hor);
            ver->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
            ver->SetHSize(500);
            ver->SetGap(100);
            {
                auto btnBox = new ui::VerticalBox;
                btnBox->AddTo(ver);
                btnBox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                btnBox->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                {
                    auto backBtn = new ui::Button;
                    backBtn->AddTo(btnBox);
                    backBtn->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    backBtn->SetCaption(L"返回主页");
                    backBtn->SetClickCallback([&back](const Atstr &name, const sf::Event &event){
                        back = true;
                    });

                    auto writeMailBtn = new ui::Button;
                    writeMailBtn->AddTo(btnBox);
                    writeMailBtn->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    writeMailBtn->SetCaption(L"写  信");
                }

                auto inBox = new ui::VerticalBox;
                inBox->AddTo(ver);
                inBox->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                {
                    auto label = new ui::Label;
                    label->AddTo(inBox);
                    label->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                    label->SetContent(L"↓ 收件箱 ↓");

                    ;
                }
            }
        }
    }

    while (screen.IsOpen()) {
        screen.Tick();
        if (back) {
            return ID::MAIN_PAGE;
        }
    }
    return ID::BREAK;
}

clpg::ID clpg::MainPage(ui::Screen &screen) noexcept
{
    Atstr which = "";
    bool logout = false;

    auto margin = new ui::Margin;
    screen.Add(margin);
    margin->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
    margin->SetMargin(80, 80, 200, 200);
    {
        auto ver = new ui::VerticalBox;
        ver->AddTo(margin);
        ver->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
        {
            auto flat = new ui::Flat;
            flat->AddTo(ver);
            flat->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
            flat->SetVSize(150);
            {
                auto head = new ui::HorizontalBox;
                head->AddTo(flat);
                head->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                head->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                {
                    auto icon = new ui::PictureBox;
                    icon->AddTo(head);
                    icon->SetPicture(_ASSETS_"icon.png");
                    screen.Tick();
                    icon->KeepHeight(flat->GetGlobalSize(ui::Control::Direction::VERTICAL));

                    auto label = new ui::Label;
                    label->AddTo(head);
                    label->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                    Atstr prefix = L"欢迎您，";
                    Atstr name = sharedInformation.account["name"];
                    if (name == "") {
                        name = L"【未设置姓名】";
                    }
                    label->SetContent(prefix + name);
                }
                auto feet = new ui::HorizontalBox;
                feet->AddTo(flat);
                feet->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                feet->SetHPreset(ui::Control::Preset::WRAP_AT_END);
                {
                    auto idNum = new ui::Label;
                    idNum->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                    Atstr prefix = L"学工号：";
                    idNum->SetContent(prefix + sharedInformation.account.code);
                    idNum->AddTo(feet);

                    auto logoutBtn = new ui::Button;
                    logoutBtn->AddTo(feet);
                    logoutBtn->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                    logoutBtn->SetCaption(L"登出");
                    logoutBtn->SetClickCallback([&logout](const Atstr &name, const sf::Event &event){
                        logout = true;
                    });
                }
            }
            auto hor = new ui::HorizontalBox;
            hor->AddTo(ver);
            hor->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
            {
                auto ver = new ui::VerticalScrollingBox;
                ver->AddTo(hor);
                ver->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                ver->SetHSize(500);
                ver->SetInsideBoxScrollable(true);
                {
                    auto reserveBtn = new ui::Button;
                    reserveBtn->SetCaption(L"预约入校");
                    reserveBtn->SetName("R");

                    auto courseBtn = new ui::Button;
                    courseBtn->SetCaption(L"课程系统");
                    courseBtn->SetName("C");

                    auto libraryBtn = new ui::Button;
                    libraryBtn->SetCaption(L"图书馆");
                    libraryBtn->SetName("L");

                    auto canteenBtn = new ui::Button;
                    canteenBtn->SetCaption(L"在线饭堂");
                    canteenBtn->SetName("F");

                    auto mailBtn = new ui::Button;
                    mailBtn->SetCaption(L"私信");
                    mailBtn->SetName("M");

                    auto nolifyBtn = new ui::Button;
                    nolifyBtn->SetCaption(L"通知与公示");
                    nolifyBtn->SetName("N");

                    auto accBtn = new ui::Button;
                    accBtn->SetCaption(L"帐户权限管理");
                    accBtn->SetName("A");

                    for (auto btn : {reserveBtn, courseBtn, libraryBtn, canteenBtn, mailBtn, nolifyBtn, accBtn}) {
                        btn->AddTo(ver);
                        btn->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        btn->SetClickCallback([&which](const Atstr &name, const sf::Event &event){
                            which = name;
                        });
                    }
                }
            }
        }
    }

    while (screen.IsOpen()) {
        screen.Tick();
        if (which != "") {
            if (which == "R") {
                return ID::ENTER_RESERVE;
            } else if (which == "C") {
                return ID::ENTER_CANTEEN;
            } else if (which == "L") {
                return ID::ENTER_LIBRARY;
            } else if (which == "F") {
                return ID::ENTER_CANTEEN;
            } else if (which == "M") {
                return ID::ENTER_MAILSYSTEM;
            } else if (which == "N") {
                return ID::ENTER_NOLIFY;
            } else if (which == "A") {
                return ID::ENTER_ACC_MANAGE;
            } else {
                assert(false); // Invalid button name.
            }
        }
        if (logout) {
            return ID::LOGIN;
        }
    }
    return ID::BREAK;
}

clpg::ID clpg::EnterAccManage(ui::Screen &screen) noexcept
{
    ;

    while (screen.IsOpen()) {
        screen.Tick();
    }
    return ID::BREAK;
}

clpg::ID clpg::Forget(ui::Screen &screen) noexcept
{
    ;

    while (screen.IsOpen()) {
        screen.Tick();
    }
    return ID::BREAK;
}

clpg::ID clpg::Retry(ui::Screen &screen) noexcept
{
    auto label = new ui::Label;
    screen.Add(label);
    label->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
    label->SetContent(L"服务端未响应，请检查后再试。");

    while (screen.IsOpen()) {
        screen.Tick();
    }
    return ID::BREAK;
}

clpg::ID clpg::Login(ui::Screen &screen) noexcept
{
    bool login = false;
    bool forget = false;
    bool reserve = false;

    ui::Label *tips = nullptr;

    auto box = new ui::VerticalBox;
    box->SetGap(80);
    screen.Add(box);
    box->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
    {
        auto pic = new ui::PictureBox;
        pic->AddTo(box);
        pic->SetPicture(_ASSETS_"icon_with_title.png");
        pic->KeepHeight(100);

        auto vertical = new ui::VerticalBox;
        vertical->AddTo(box);
        vertical->SetSize(900, 250);
        {
            auto user = new ui::HorizontalBox;
            user->AddTo(vertical);
            user->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
            user->SetGap(50);
            {
                auto label = new ui::Label;
                label->AddTo(user);
                label->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                label->SetContent(L"帐号");

                auto input = new ui::InputBox;
                input->AddTo(user);
                input->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                input->SetText(sharedInformation.username);
                sharedInformation.password = "";
                sharedInformation.account = {};
                input->SetHSize(3);
                input->SetLengthLimit(64);
                input->SetContentLimit(ui::InputBox::ContentLimit::ALLOW_SPECIAL_CHARACTERS_ONLY);
                input->SetSpecialCharacters(ui::InputBox::NUMBER + ui::InputBox::LOWER_LETTER + ui::InputBox::UPPER_LETTER + "_-@.");
                input->SetInputCallback([&input](const Atstr &name, const sf::Event &event){
                    sharedInformation.username = input->GetText();
                });
                input->SetExceedLimitCallback([&tips](const Atstr &name, const sf::Event &event){
                    tips->SetContent(L"帐号只能由数字、大小写字母以及 _-@. 构成，\n且长度不超过 64 个字符。");
                    tips->SetVisible(true);
                });
            }
            auto pasw = new ui::HorizontalBox;
            pasw->AddTo(vertical);
            pasw->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
            pasw->SetGap(50);
            {
                auto label = new ui::Label;
                label->AddTo(pasw);
                label->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                label->SetContent(L"密码");

                auto input = new ui::InputBox;
                input->AddTo(pasw);
                input->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                input->SetHSize(3);
                input->SetProtectText(true);
                input->SetLengthLimit(64);
                input->SetContentLimit(ui::InputBox::ContentLimit::ALLOW_SPECIAL_CHARACTERS_ONLY);
                input->SetSpecialCharacters(ui::InputBox::ASCII);
                input->SetInputCallback([&input](const Atstr &name, const sf::Event &event){
                    sharedInformation.password = input->GetText();
                });
                input->SetExceedLimitCallback([&tips](const Atstr &name, const sf::Event &event){
                    tips->SetContent(L"密码只能由 ASCII 字符构成，\n且长度不超过 64 个字符。");
                    tips->SetVisible(true);
                });
            }
        }
        auto feetBox = new ui::VerticalBox;
        feetBox->AddTo(box);
        feetBox->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
        {
            auto btnBox = new ui::HorizontalBox;
            btnBox->AddTo(feetBox);
            btnBox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
            btnBox->SetGap(50);
            {
                auto loginBtn = new ui::Button;
                loginBtn->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                loginBtn->SetHSize(2);
                loginBtn->SetCaption(L"登录");
                loginBtn->SetClickCallback([&login](const Atstr &name, const sf::Event &event){
                    login = true;
                });
                loginBtn->AddTo(btnBox);

                auto forgetBtn = new ui::Button;
                forgetBtn->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                forgetBtn->SetHSize(2);
                forgetBtn->SetCaption(L"忘记密码");
                forgetBtn->SetClickCallback([&forget](const Atstr &name, const sf::Event &event){
                    forget = true;
                });
                forgetBtn->AddTo(btnBox);
                
                auto reserveBtn = new ui::Button;
                reserveBtn->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                reserveBtn->SetHSize(1);
                reserveBtn->SetCaption(L"校外人员\n预约入校");
                reserveBtn->SetClickCallback([&reserve](const Atstr &name, const sf::Event &event){
                    reserve = true;
                });
                reserveBtn->AddTo(btnBox);
            }
            tips = new ui::Label;
            tips->AddTo(feetBox);
            tips->SetPreset(ui::Control::Preset::WRAP_AT_FRONT);
            tips->SetFontColor(sf::Color::Red);
            tips->SetFontSize(30);
            tips->SetVisible(false);
        }        
    }

    while (screen.IsOpen()) {
        screen.Tick();
        if (login) {
            if (sharedInformation.username == "" || sharedInformation.password == "") {
                login = false;
                tips->SetContent(L"帐号或密码不能为空。");
                tips->SetVisible(true);
            } else {
                screen.HideAll();
                auto [success, reply] = WaitServer(screen, 
                    {trm::rqs::CHECK_ACCOUNT, sharedInformation.username, sharedInformation.password}, L"登录中");
                if (success == 1) {
                    if (reply[0] == trm::rpl::YES) {
                        sharedInformation.account = reply[1];
                        return ID::MAIN_PAGE;
                    } else if (reply[0] == trm::rpl::NO) {
                        login = false;
                        tips->SetContent(L"帐号或密码错误。");
                        tips->SetVisible(true);
                        screen.FreeAllVisible();
                        screen.ShowAll();
                    } else {
                        assert(false); // Invalid reply.
                    }    
                } else if (success == 0) {
                    return ID::RETRY;
                }
            }
        }
        if (forget) {
            return ID::FORGET;
        }
        if (reserve) {
            return ID::ENTER_RESERVE;
        }
    }
    return ID::BREAK;
}
