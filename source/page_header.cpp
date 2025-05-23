#include "subpages/page_header.hpp"
#include "page_header.hpp"

std::string clpg::PageBase::username = "";
std::string clpg::PageBase::password = "";
trm::Account clpg::PageBase::account;

std::vector<std::string> clpg::PageBase::argvs;
bool clpg::PageBase::initialized = false;
std::string clpg::PageBase::coursename = "";

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
    load->SetFinishedCallback([&](const std::string &name, const sf::Event &event) -> void{
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
