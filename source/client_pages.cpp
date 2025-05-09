#include "client_pages.hpp"

clpg::Handler clpg::GetHandler(ID id) noexcept
{
    switch (id)
    {
        case ID::ENTER_SYSTEM:
            return EnterSystem;
            break;
        
        /*******************************
         * @attention EEA 请在此处添加。*
         * *****************************
         */
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
        
        case ID::ENTER_CANTEEN:
            return EnterCanteen;
            break;
        case ID::ENTER_MAILSYSTEM:
            return EnterMailSystem;
            break;
        
        /*******************************
         * @attention LAB 请在此处添加。*
         * *****************************
         */
        case ID::ENTER_ACC_MANAGE:
            return EnterAccManage;
            break;
            
        case ID::ENTER_COURSE:
            return EnterCourse;
            break;
        case ID::ENTER_RESERVE:
            return EnterReserve;
            break;
        
        /*******************************
         * @attention VIO_VV 请在此处添加。*
         * *****************************
         */
        case ID::ENTER_LIBRARY:
            return EnterLibrary;
            break;
        case ID::ENTER_NOLIFY:
            return EnterNolify;
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
    Init();

    bool clicked = false;

    auto btn = new ui::Button;
    screen.Add(btn);
    btn->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
    btn->SetCaption(L"进入系统");
    btn->SetClickCallback([&clicked](const Atstr &name, const sf::Event &event){
        clicked = true;
    });

    while (screen.IsOpen()) {
        screen.Tick();
        if (clicked) {
            screen.FreeAll();
            auto [success, reply] = WaitServer(screen, {trm::rqs::CHECK_ONLINE}, L"正在检查服务端在线状态");
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

void clpg::Init() noexcept
{
    trm::Sender::Init(LINK, SELF, SELF_AS_SENDER);
}

std::pair<int, trm::Information> clpg::WaitServer(ui::Screen &screen, const trm::Information &information, const Atstr &tips) noexcept
{
    bool pass = false;
    trm::Information result;
    bool finished = false;
    auto sender = trm::Sender(information);

    auto load = new ui::LoadingRingWithText;
    screen.Add(load);
    load->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
    load->SetText(tips);
    load->SetCountCallback([&pass, &result, &sender](const Atstr &name, const sf::Event &event){
        auto reply = sender.Poll();
        if (reply.first) {
            pass = true;
            result = reply.second;
        }
    });
    load->SetFinishedCallback([&finished](const Atstr &name, const sf::Event &event){
        finished = true;
    });
    load->Start();

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

clpg::Atstr::operator std::string() const
{
    std::string result;
    for (auto c : this->toUtf8()) {
        result.push_back(c);
    }
    return std::move(result);
}
