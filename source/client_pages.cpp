#include "client_pages.hpp"

clpg::Handler clpg::GetHandler(ID id) noexcept
{
    switch (id)
    {
        case ID::ENTER_SYSTEM:
            return EnterSystem;
            break;
        case ID::RETRY:
            return Retry;
            break;
        case ID::LOGIN:
            return Login;
            break;
        case ID::FORGET:
            return Forget;
            break;
        case ID::MAIN_PAGE:
            return MainPage;
            break;
        case ID::BREAK:
            return nullptr;
            break;
        default:
            assert(false); // Unknown Page ID.
            return nullptr;
            break;
    }
}

clpg::ID clpg::EnterSystem(ui::Screen &screen) noexcept
{
    bool clicked = false;

    auto btn = new ui::Button;
    btn->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
    btn->SetCaption(L"进入系统");
    btn->SetClickCallback([&clicked](const sf::String &name, const sf::Event &event){
        clicked = true;
    });
    screen.Add(btn);

    while (screen.IsOpen()) {
        screen.Tick();
        if (clicked) {
            screen.FreeAll();
            auto [success, reply] = WaitServer(screen, {trm::rqs::CHECK_ONLINE}, "正在检查服务端在线状态");
            if (success == 1) {
                if (reply[0] == trm::rpl::YES) {
                    return ID::LOGIN;
                } else {
                    assert(false); // Invalid reply.
                }
            } else if (success == 0) {
                return ID::RETRY;
            }
        }
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
                    // input->SetContentLimit(ui::InputBox::ContentLimit::ALLOW_SPECIAL_CHARACTERS_ONLY);
                    // input->SetSpecialCharacters(ui::InputBox::NUMBER + ui::InputBox::LOWER_LETTER + ui::InputBox::UPPER_LETTER + "_-@.");
                    input->SetInputCallback([&input](const sf::String &name, const sf::Event &event){
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
                    input->SetInputCallback([&input](const sf::String &name, const sf::Event &event){
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
                loginBtn->SetClickCallback([&login](const sf::String &name, const sf::Event &event){
                    login = true;
                });
                loginBtn->AddTo(btnBox);

                auto forgetBtn = new ui::Button;
                forgetBtn->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                forgetBtn->SetCaption(L"忘记密码");
                forgetBtn->SetClickCallback([&forget](const sf::String &name, const sf::Event &event){
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
            auto [success, reply] = WaitServer(screen, {trm::rqs::CHECK_ACCOUNT, SfToStr(sharedInformation.username), sharedInformation.password}, L"登录中");
            if (success == 1) {
                if (reply[0] == trm::rpl::YES) {
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

clpg::ID clpg::Forget(ui::Screen &screen) noexcept
{
    while (screen.IsOpen()) {
        screen.Tick();
    }
    return ID::BREAK;
}

std::pair<int, trm::Information> clpg::WaitServer(ui::Screen &screen, const trm::Information &information, const sf::String &tips) noexcept
{
    auto id = trm::GenerateID();
    bool pass = false;
    trm::Information result;
    bool finished = false;
    if (!trm::MakeRequest(LINK, {id, SELF_AS_SENDER, information})) {
        std::cout << __FILE__ << ':' << __LINE__ << ":Failed to make request." << std::endl;
        exit(1);
    }

    auto load = new ui::LoadingRingWithText;
    load->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
    load->SetText(tips);
    load->SetCountCallback([&id, &pass, &result](const sf::String &name, const sf::Event &event){
        auto reply = trm::PollReply(SELF, id);
        if (reply.first) {
            pass = true;
            result = reply.second;
        }
    });
    load->SetFinishedCallback([&finished](const sf::String &name, const sf::Event &event){
        finished = true;
    });
    load->Start();
    screen.Add(load);

    while (screen.IsOpen()) {
        screen.Tick();
        if (pass) {
            return {1, std::move(result)};
        } else if (finished) {
            return {0, {}};
        }
    }
    return {-1, {}};
}

std::string clpg::SfToStr(const sf::String &t) noexcept
{
    std::string result;
    for (auto c : t.toUtf8()) {
        result.push_back(c);
    }
    return std::move(result);
}

clpg::ID clpg::MainPage(ui::Screen &screen) noexcept
{
    ;

    while (screen.IsOpen()) {
        screen.Tick();
    }
    return ID::BREAK;
}
