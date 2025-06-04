#include "subpages/page_header.hpp"
#include "page_header.hpp"

std::string clpg::PageBase::username = "";
std::string clpg::PageBase::password = "";
trm::Account clpg::PageBase::account;

std::vector<std::string> clpg::PageBase::argvs;
bool clpg::PageBase::initialized = false;
std::string clpg::PageBase::coursename = "";
trm::IdAndPhone clpg::PageBase::idandphone;
trm::ReserveDate clpg::PageBase::rdate;
std::string clpg::PageBase::rtime="";
trm::CourseInformation clpg::PageBase::courseinfo;
std::string clpg::PageBase::rnum = "";

unsigned long long clpg::PageBase::selectedNoticeNum = 0;

clpg::PageBase::PageBase()
{
    if (!initialized) {

        trm::Sender::Init(LINK, SELF, SELF_AS_SENDER);

        initialized = true;
    }
}

clpg::PageBase *clpg::PageBase::RunOn(ui::Screen *screen) noexcept
{
    Load(screen);
    Logic(screen);
    Ready(screen);
    sf::Clock clock;
    while (screen->IsOpen()) {
        if (nextPage) {
            break;
        }
        for (auto control : freeQueue) {
            delete control;
        }
        freeQueue.clear();
        Tick(screen);
        if (clock.getElapsedTime().asMilliseconds() >= interval) {
            std::vector<trm::Sender *> toDelete;
            for (auto [sender, callback] : queue) {
                auto [success, reply] = sender->Poll();
                if (success) {
                    callback(sender->GetID(), reply);
                    toDelete.push_back(sender);
                } else {
                    if (sender->GetCount() > limit) {
                        callback(sender->GetID(), {trm::rpl::TIME_OUT});
                        toDelete.push_back(sender);
                    }
                }
            }
            for (auto each : toDelete) {
                std::vector itList = {queue.end()};
                for (auto iter = queue.begin(); iter != queue.end(); ++iter) {
                    if (iter->first == each) {
                        itList.push_back(iter);
                    }
                }
                for (auto iter : itList) {
                    if (iter != queue.end()){
                        queue.erase(iter);
                    }
                }
                delete each;
            }
            TickAtSpecificIntervals(screen);
            clock.restart();
        }
        screen->Tick();
        screen->Draw();
    }
    Unload(screen);
    screen->FreeAll();
    for (auto [sender, callback] : queue) {
        delete sender;
    }
    return nextPage;
}

/**
 * @example
        auto [success, reply] = WaitServer(screen, {trm::rqs::CHECK_ONLINE}, "正在检查服务端在线状态");
        screen->FreeAllVisible();
        screen->ShowAll();
        if (success == 1) {
            if (reply[0] == trm::rpl::YES) {
                SwitchTo(new eea::Login);
            } else {
                assert(false); // Unexpected reply.
            }
        } else if (success == 0) {
            SwitchTo(new eea::Retry);
        }
 * 
 */
std::pair<int, trm::Information> clpg::PageBase::WaitServer(ui::Screen *screen, const trm::Information &information, const std::string &tips) noexcept
{
    bool pass = false;
    trm::Information result;
    bool finished = false;
    
    auto load = new ui::LoadingRingWithText;{
        load->AddTo(screen);
        load->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
        load->SetText(tips);}
    auto sender = trm::Sender(information);
    
    load->SetCountCallback([&](const std::string &name, const sf::Event &event) -> void{
        auto [success, reply] = sender.Poll();
        if (success) {
            pass = true;
            result = reply;
        }
    });
    load->SetFinishedCallback([&](const std::string &name, const sf::Event &event) -> void {
        finished = true;
    });
    
    load->Start();

    while (screen->IsOpen()) {
        if (pass) {
            return {1, std::move(result)};
        } else if (finished) {
            return {0, {}};
        }
        screen->Tick();
        screen->Draw();
    }
    return {-1, {}};
}

/**
 * @example @see @fn WaitServer
 * @return 被点击的按钮的索引，从 0 开始
 * @retval -1 窗口被关闭
 */
int clpg::PageBase::MessageBox(ui::Screen *screen, const std::string &tips, const std::vector<std::string> &options) noexcept
{
    int res = -1;

    auto vbox = new ui::VerticalBox; {
        vbox->AddTo(screen);
        vbox->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
        vbox->SetGap(50);
    }
    {
        auto label = new ui::Label; {
            label->AddTo(vbox);
            label->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
            label->SetContent(tips);
        }
        int cur = 0;
        for (const auto &option : options) {
            auto btn = new ui::Button; {
                btn->AddTo(vbox);
                btn->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                btn->SetCaption(option);
                btn->SetName(ToStr(cur));
                btn->SetClickCallback([&](const std::string &name, const sf::Event &event) -> void {
                    res = ToNum(name);
                });
            }
            ++cur;
        }
    }

    while (screen->IsOpen()) {
        if (res != -1) {
            return res;
        }
        screen->Tick();
        screen->Draw();
    }
    return -1;
}

void clpg::PageBase::Listen(trm::Sender *sender, const Callback &callback) noexcept
{
    queue.push_back({sender, callback});
}

void clpg::PageBase::SwitchTo(PageBase *page)
{
    nextPage = page;
}

void clpg::PageBase::SetInterval(int newInterval) noexcept
{
    interval = newInterval;
}

void clpg::PageBase::SetLimit(int newLimit) noexcept
{
    limit = newLimit;
}

void clpg::PageBase::QueueFree(ui::Control *control) noexcept
{
    freeQueue.push_back(control);
}
