#ifndef __EEA_HPP__
#define __EEA_HPP__

#include "page_header.hpp"

namespace eea{
using namespace clpg;

class Retry : public PageBase {
private:
    ;
protected:
    void Load(ui::Screen *screen) noexcept;
    void Logic(ui::Screen *screen) noexcept;
    void Ready(ui::Screen *screen) noexcept;
};
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
    ;
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
    ui::Button *l3 = nullptr;
    ui::Button *l2 = nullptr;
    ui::Button *l1 = nullptr;
    ui::Label *cur = nullptr;
    ui::Button *r1 = nullptr;
    ui::Button *r2 = nullptr;
    ui::Button *r3 = nullptr;
    ui::LoadingRing *loading = nullptr;
protected:
    void Load(ui::Screen *screen) noexcept;
    void Logic(ui::Screen *screen) noexcept;
    void Ready(ui::Screen *screen) noexcept;
private:
    void UpdateButton();
};

}

#endif
