#ifndef __PAGE_HEADER_HPP__
#define __PAGE_HEADER_HPP__

#define LINK "..\\server\\space"
#define SELF ".\\space"
#define SELF_AS_SENDER "..\\client\\space"

#define UI_CALLBACK [=, this](const std::string &name, const sf::Event &event) -> void 
#define SD_CALLBACK [=, this](int id, const trm::Information &reply) -> void 

#include <iostream>
#include <cassert>
#include "ui.hpp"
#include "transmitter.hpp"

namespace clpg{

class PageBase {
public:
    using Callback = std::function<void (int, const trm::Information &)>;
    PageBase();
    PageBase *RunOn(ui::Screen *screen) noexcept;
protected:
    virtual void Load(ui::Screen *screen) noexcept = 0;
    virtual void Logic(ui::Screen *screen) noexcept = 0;
    virtual void Ready(ui::Screen *screen) noexcept = 0;
    virtual void Tick(ui::Screen *screen) noexcept {}
    virtual void TickAtSpecificIntervals(ui::Screen *screen) noexcept {}
    virtual void Unload(ui::Screen *screen) noexcept {}

    static std::pair<int, trm::Information> WaitServer(ui::Screen *screen, const trm::Information &information, const std::string &tips) noexcept;
    static int MessageBox(ui::Screen *screen, const std::string &tips, const std::vector<std::string> &options = {"确定"}) noexcept;
    static std::string username;
    static std::string password;
    static trm::Account account;
    static std::string coursename;
    static trm::IdAndPhone idandphone;
    static trm::ReserveDate rdate;
    static std::string rtime;
    static trm::Notice selectedNotice;
    static trm::CourseInformation courseinfo;
    static std::string rnum;
    static unsigned long long selectedNoticeNum;

    static trm::Information argvs;
    
    void Listen(trm::Sender *sender, const Callback &callback) noexcept;
    void SwitchTo(PageBase *page);
    void SetInterval(int newInterval) noexcept;
    void SetLimit(int newLimit) noexcept;
    void QueueFree(ui::Control *control) noexcept;
private:
    static bool initialized;
    std::vector<std::pair<trm::Sender *, Callback>> queue;
    PageBase *nextPage = nullptr;
    int interval = 500;
    int limit = 15;
    std::vector<ui::Control *> freeQueue;
};

class Example : public PageBase {
private:
    ; // # 在这里声明页面的关键成员（有回调函数的组件、被回调函数需要的组件、Sender 对象、* 定时器即 sf::Clock 对象等）。
protected:
    Example() noexcept = default; // * 在这里可自定义长间隔监测的间隔即监听间隔，以及监听次数等。
    void Load(ui::Screen *screen) noexcept = 0; // # 在这里写页面的布局（根据基类静态成员的值，写页面组件的父子关系，设置组件的属性等）。
    void Logic(ui::Screen *screen) noexcept = 0; // # 在这里写回调逻辑（设置组件回调函数、监听回调函数，进而动态设置组件属性、动态增减组件、跳转页面等）。
    void Ready(ui::Screen *screen) noexcept = 0; // # 在这里可作初始化逻辑（准备维护基类静态成员的值，发送请求，* 启动定时器等）。
    void Tick(ui::Screen *screen) noexcept = 0; // * 在这里可作页面的监测（定时器等）。
    void TickAtSpecificIntervals(ui::Screen *screen) noexcept = 0; // * 在这里可作页面的长间隔监测（可当作一个定时器等）。
    void Unload(ui::Screen *screen) noexcept = 0; // * 在这里作页面的卸载逻辑（释放拥有所有权的指针，停止定时器等）。
};

class Copy : public PageBase {
private:
    ;
protected:
    void Load(ui::Screen *screen) noexcept = 0;
    void Logic(ui::Screen *screen) noexcept = 0;
    void Ready(ui::Screen *screen) noexcept = 0; // ! 复制后，这些 = 0 要删掉的
};

}


#endif
