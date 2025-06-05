#ifndef __EEA_HPP__
#define __EEA_HPP__

#include "page_header.hpp"

namespace eea{
using namespace clpg;

class Login : public PageBase {
private:
    ui::InputBox *userInput = nullptr;
    ui::InputBox* paswInput = nullptr;
    ui::Button *loginBtn = nullptr;
    ui::Button *forgetBtn = nullptr;
    ui::Button *reserveBtn = nullptr;
    ui::Label *tips = nullptr;
protected:
    void Load(ui::Screen *screen) noexcept override;
    void Logic(ui::Screen *screen) noexcept override;
    void Ready(ui::Screen *screen) noexcept override;
};
class Forget : public PageBase {
private:
    ;
protected:
    void Load(ui::Screen *screen) noexcept override;
    void Logic(ui::Screen *screen) noexcept override;
    void Ready(ui::Screen *screen) noexcept override;
};
class MainPage : public PageBase {
private:
    ui::Button *logoutBtn = nullptr;
    ui::Button *reserveBtn = nullptr;
    ui::Button *courseBtn = nullptr;
    ui::Button *libraryBtn = nullptr;
    ui::Button *canteenBtn = nullptr;
    ui::Button *mailBtn = nullptr;
    ui::Button *nolifyBtn = nullptr;
    ui::Button *accBtn = nullptr;

    ui::Button *headlineBtn = nullptr;
    ui::HorizontalBox *headlineBox = nullptr;
    ui::VerticalBox *headlineBtnBox = nullptr;
    ui::VerticalBox *newsBox = nullptr;
    ui::VerticalBox *noticeBox = nullptr;
    ui::VerticalScrollingBox *verNolify = nullptr;
    
    int selected = 0;
    sf::Clock clock;
    sf::Time elapsed;
    sf::Time interval;
    unsigned long long newsNum = 0;
    unsigned long long noticeNum = 0;
    unsigned long long headlineNum = 0;
    std::vector<std::pair<trm::Notice, unsigned long long>> noticeList;
    std::vector<std::pair<trm::Notice, unsigned long long>> newsList;
    std::vector<std::pair<trm::Notice, unsigned long long>> headlineList;
    std::vector<ui::Button*> headlineTurners;
    std::function<void ()> initialize = [](){};
    std::function<void ()> getListLenth = [](){};
protected:
    void Load(ui::Screen *screen) noexcept override;
    void Logic(ui::Screen *screen) noexcept override;
    void Ready(ui::Screen *screen) noexcept override;
    void Tick(ui::Screen *screen) noexcept override;
};

class EnterAccManage : public PageBase {
private:
    ui::Button *backBtn = nullptr;
    ui::Button *refreshBtn = nullptr;

    ui::Center *labelCenter = nullptr;
    ui::Label *resultLabel = nullptr;

    ui::Center *ringCenter = nullptr;

    ui::VerticalScrollingBox *list = nullptr;

    ui::VerticalScrollingBox *detailBox = nullptr;
    bool detailCalling = false;

    ui::Button *newBtn = nullptr;
    ui::Button *resetBtn = nullptr;

    ui::Control::Callback refresh = ui::Control::DO_NOTHING;
protected:
    void Load(ui::Screen *screen) noexcept override;
    void Logic(ui::Screen *screen) noexcept override;
    void Ready(ui::Screen *screen) noexcept override;
};

class AccountDelail : public PageBase {
private:
    ui::Button *backBtn = nullptr;

    ui::InputBox *userInput = nullptr;
    ui::InputBox* paswInput = nullptr;
    ui::Button *randPaswBtn = nullptr;
    ui::Label *limitTips = nullptr;

    ui::HorizontalBox *accessBox = nullptr;
    int columnNum = 3;
    std::function<void ()> reorganizeAccessBox = [](){};
    ui::Button *columnAdd = nullptr;
    ui::Button *columnDel = nullptr;
    std::vector<ui::ToggleButton *> accessList;

    ui::VerticalBox *editBox = nullptr;
    ui::Button *addTagBtn = nullptr;
    int tagHorsNum = 0;
    std::unordered_map<int, ui::HorizontalBox *> tagHors;
    std::unordered_map<int, ui::InputBox *> tagNames;
    std::unordered_map<int, ui::InputBox *> tagValues;

    trm::Account newAccount;
    ui::Button *okBtn = nullptr;
protected:
    void Load(ui::Screen *screen) noexcept override;
    void Logic(ui::Screen *screen) noexcept override;
    void Ready(ui::Screen *screen) noexcept override;
};

class EnterCanteen : public PageBase {
private:
    ;
protected:
    void Load(ui::Screen *screen) noexcept override;
    void Logic(ui::Screen *screen) noexcept override;
    void Ready(ui::Screen *screen) noexcept override;
};
class EnterMailSystem : public PageBase {
private:
    ui::Button *backBtn = nullptr;
    ui::Button *writeMailBtn = nullptr;
    ui::Button *refreshBtn = nullptr;

    ui::VerticalBox *list = nullptr;
    ui::VerticalScrollingBox *msgBox = nullptr;
    bool turnable = true;
    ui::PageTurner *turner = nullptr;
    ui::Center *loading = nullptr;
    std::function<void ()> refreshList = [](){};

    ui::Label *subject = nullptr;
    ui::Label *sender = nullptr;
    ui::Label *receiver = nullptr;
    ui::Label *dateTime = nullptr;
    ui::Label *state = nullptr;
    ui::Label *mailContent = nullptr;

    const int eachPageNum = 10;
protected:
    void Load(ui::Screen *screen) noexcept override;
    void Logic(ui::Screen *screen) noexcept override;
    void Ready(ui::Screen *screen) noexcept override;
};

class WriteMail : public PageBase {
private:
    ui::Button *backBtn = nullptr;
    ui::InputBox *target = nullptr;
    ui::InputBox *subject = nullptr;
    ui::InputBox *inputB = nullptr;
    ui::Button *sendBtn = nullptr;
protected:
    void Load(ui::Screen *screen) noexcept override;
    void Logic(ui::Screen *screen) noexcept override;
    void Ready(ui::Screen *screen) noexcept override;
};

}

#endif
