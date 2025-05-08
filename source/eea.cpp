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
    ;

    while (screen.IsOpen()) {
        screen.Tick();
    }
    return ID::BREAK;
}

clpg::ID clpg::MainPage(ui::Screen &screen) noexcept
{
    Atstr which = "";

    auto label = new ui::Label;
    label->SetPosition(50, 50);
    Atstr prefix = L"欢迎你，";
    label->SetContent(prefix + sharedInformation.account["name"]);
    label->SetSizeWrap(true);
    screen.Add(label);

    auto idNum = new ui::Label;
    idNum->SetAnchor(100, 0);
    idNum->SetCenter(100, 0);
    idNum->SetPosition(-50, 50);
    prefix = L"学工号：";
    idNum->SetContent(prefix + sharedInformation.account.code);
    label->SetSizeWrap(true);
    screen.Add(idNum);

    auto ver = new ui::VerticalScrollingBox;
    ver->SetPosition(50, 200);
    ver->SetHSizeValueType(ui::Control::ValueType::ABSOLUTE);
    ver->SetHSize(500);
    ver->SetVSizeValueType(ui::Control::ValueType::PERCENTAGE);
    ver->SetVSize(60);
    screen.Add(ver);
    {
        auto reserveBtn = new ui::Button;
        reserveBtn->SetCaption(L"预约入校");
        reserveBtn->SetName("R");

        auto courseBtn = new ui::Button;
        courseBtn->SetCaption(L"课程系统");
        reserveBtn->SetName("C");

        auto libraryBtn = new ui::Button;
        libraryBtn->SetCaption(L"图书馆");
        reserveBtn->SetName("L");

        auto canteenBtn = new ui::Button;
        canteenBtn->SetCaption(L"在线饭堂");
        reserveBtn->SetName("F");

        auto mailBtn = new ui::Button;
        mailBtn->SetCaption(L"私信");
        reserveBtn->SetName("M");

        auto nolifyBtn = new ui::Button;
        nolifyBtn->SetCaption(L"通知与公示");
        reserveBtn->SetName("N");

        auto accBtn = new ui::Button;
        accBtn->SetCaption(L"帐户权限管理");
        reserveBtn->SetName("A");

        for (auto btn : {reserveBtn, courseBtn, libraryBtn, canteenBtn, mailBtn, nolifyBtn, accBtn}) {
            btn->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
            btn->SetClickCallback([&which](const Atstr &name, const sf::Event &event){
                which = name;
            });
            btn->AddTo(ver);
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
    label->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
    label->SetContent(L"服务端未响应，请检查后再试。");
    screen.Add(label);

    while (screen.IsOpen()) {
        screen.Tick();
    }
    return ID::BREAK;
}

clpg::ID clpg::Login(ui::Screen &screen) noexcept
{
    bool login = false;
    bool forget = false;

    ui::Label *tips = nullptr;

    auto centerBox = new ui::VerticalBox;
    centerBox->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
    screen.Add(centerBox);
    {
        auto box = new ui::VerticalBox;
        box->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
        box->SetGap(80);
        box->AddTo(centerBox);
        {
            auto vertical = new ui::VerticalBox;
            vertical->SetSize(900, 250);
            vertical->AddTo(box);
            {
                auto user = new ui::HorizontalBox;
                user->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                user->AddTo(vertical);
                {
                    auto center = new ui::Center;
                    center->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    center->SetHSize(1);
                    center->AddTo(user);
                    {
                        auto label = new ui::Label;
                        label->SetSizeWrap(true);
                        label->SetContent(L"帐号");
                        label->AddTo(center);
                    }
                    auto input = new ui::InputBox;
                    input->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    input->SetHSize(3);
                    input->SetLengthLimit(64);
                    input->SetContentLimit(ui::InputBox::ContentLimit::ALLOW_SPECIAL_CHARACTERS_ONLY);
                    input->SetSpecialCharacters(ui::InputBox::NUMBER + ui::InputBox::LOWER_LETTER + ui::InputBox::UPPER_LETTER + "_-@.");
                    input->SetInputCallback([&input](const Atstr &name, const sf::Event &event){
                        sharedInformation.username = input->GetText();
                    });
                    input->AddTo(user);
                }
                auto pasw = new ui::HorizontalBox;
                pasw->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                pasw->AddTo(vertical);
                {
                    auto center = new ui::Center;
                    center->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    center->SetHSize(1);
                    center->AddTo(pasw);
                    {
                        auto label = new ui::Label;
                        label->SetSizeWrap(true);
                        label->SetContent(L"密码");
                        label->AddTo(center);
                    }
                    auto input = new ui::InputBox;
                    input->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    input->SetHSize(3);
                    input->SetProtectText(true);
                    input->SetLengthLimit(64);
                    input->SetContentLimit(ui::InputBox::ContentLimit::ALLOW_SPECIAL_CHARACTERS_ONLY);
                    input->SetSpecialCharacters(ui::InputBox::ASCII);
                    input->SetInputCallback([&input](const Atstr &name, const sf::Event &event){
                        sharedInformation.password = input->GetText();
                    });
                    input->AddTo(pasw);
                }
            }
            auto btnBox = new ui::HorizontalBox;
            btnBox->SetHPreset(ui::Control::Preset::PLACR_AT_CENTER);
            btnBox->SetSize(500, 100);
            btnBox->SetGap(50);
            btnBox->AddTo(box);
            {
                auto loginBtn = new ui::Button;
                loginBtn->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                loginBtn->SetCaption(L"登录");
                loginBtn->SetClickCallback([&login](const Atstr &name, const sf::Event &event){
                    login = true;
                });
                loginBtn->AddTo(btnBox);

                auto forgetBtn = new ui::Button;
                forgetBtn->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                forgetBtn->SetCaption(L"忘记密码");
                forgetBtn->SetClickCallback([&forget](const Atstr &name, const sf::Event &event){
                    forget = true;
                });
                forgetBtn->AddTo(btnBox);
            }
        }
        tips = new ui::Label;
        tips->SetPreset(ui::Control::Preset::WRAP_AT_FRONT);
        tips->SetFontColor(sf::Color::Red);
        tips->SetFontSize(30);
        tips->SetVisible(false);
        tips->AddTo(centerBox);
    }

    while (screen.IsOpen()) {
        screen.Tick();
        if (login) {
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
        if (forget) {
            return ID::FORGET;
        }
    }
    return ID::BREAK;
}
