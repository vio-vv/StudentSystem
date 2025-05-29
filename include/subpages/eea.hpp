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
    void Load(ui::Screen *screen) noexcept;
    void Logic(ui::Screen *screen) noexcept;
    void Ready(ui::Screen *screen) noexcept;
};
class Forget : public PageBase {
private:
    ;
protected:
    void Load(ui::Screen *screen) noexcept;
    void Logic(ui::Screen *screen) noexcept;
    void Ready(ui::Screen *screen) noexcept;
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
protected:
    void Load(ui::Screen *screen) noexcept;
    void Logic(ui::Screen *screen) noexcept;
    void Ready(ui::Screen *screen) noexcept;
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
    void Load(ui::Screen *screen) noexcept;
    void Logic(ui::Screen *screen) noexcept;
    void Ready(ui::Screen *screen) noexcept;
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
    void Load(ui::Screen *screen) noexcept;
    void Logic(ui::Screen *screen) noexcept;
    void Ready(ui::Screen *screen) noexcept;
};

class EnterCanteen : public PageBase {
private:
    ;
protected:
    void Load(ui::Screen *screen) noexcept;
    void Logic(ui::Screen *screen) noexcept;
    void Ready(ui::Screen *screen) noexcept;
};
class EnterMailSystem : public PageBase {
private:
    ui::Button *backBtn = nullptr;

    ui::VerticalBox *list = nullptr;
    ui::VerticalScrollingBox *msgBox = nullptr;
    ui::PageTurner *turner = nullptr;
    ui::Center *loading = nullptr;
    std::function<void ()> refreshList = [](){};
protected:
    void Load(ui::Screen *screen) noexcept;
    void Logic(ui::Screen *screen) noexcept;
    void Ready(ui::Screen *screen) noexcept;
};

}

#endif
