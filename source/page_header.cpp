#include "subpages/page_header.hpp"

clpg::Atstr clpg::PageBase::username = "";
clpg::Atstr clpg::PageBase::password = "";
trm::Account clpg::PageBase::account;
bool clpg::PageBase::initialized = false;

clpg::Atstr::operator std::string() const
{
    std::string result;
    for (auto c : this->toUtf8()) {
        result.push_back(c);
    }
    return std::move(result);
}

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
        screen->Tick();
        if (nextPage) {
            break;
        }
        Tick(screen);
        if (clock.getElapsedTime().asMilliseconds() >= interval) {
            for (auto [sender, callback] : queue) {
                auto reply = sender->Poll();
                if (reply.first) {
                    callback(sender->GetID(), reply.second);
                } else {
                    if (sender->GetCount() > limit) {
                        callback(sender->GetID(), {trm::rpl::TIME_OUT});
                    }
                }
            }
            std::vector toDelete = {queue.end()};
            for (auto iter = queue.begin(); iter != queue.end(); ++iter) {
                if (iter->first->GetCount() > limit) {
                    toDelete.push_back(iter);
                }
            }
            for (auto each : toDelete) {
                if (each != queue.end()) {
                    queue.erase(each);
                }
            }
            TickAtSpecificIntervals(screen);
            clock.restart();
        }
        screen->Draw();
    }
    Unload(screen);
    screen->FreeAll();
    for (auto [sender, callback] : queue) {
        delete sender;
    }
    return nextPage;
}

std::pair<int, trm::Information> clpg::PageBase::WaitServer(ui::Screen *screen, const trm::Information &information, const Atstr &tips) noexcept
{
    bool pass = false;
    trm::Information result;
    bool finished = false;
    
    auto load = new ui::LoadingRingWithText;{
        load->AddTo(screen);
        load->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
        load->SetText(tips);}
    auto sender = trm::Sender(information);
    
    load->SetCountCallback([&](const Atstr &name, const sf::Event &event) -> void {
        auto reply = sender.Poll();
        if (reply.first) {
            pass = true;
            result = reply.second;
        }
    });
    load->SetFinishedCallback([&](const Atstr &name, const sf::Event &event) -> void {
        finished = true;
    });
    
    load->Start();

    while (screen->IsOpen()) {
        screen->Tick();
        if (pass) {
            return {1, std::move(result)};
        } else if (finished) {
            return {0, {}};
        }
        screen->Draw();
    }
    return {-1, {}};
}

void clpg::PageBase::Listen(trm::Sender *sender, Callback &&callback) noexcept
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
