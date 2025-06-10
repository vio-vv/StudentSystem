#ifndef __PAGE_HEADER_HPP__
#define __PAGE_HEADER_HPP__

#define _UI_CALLBACK_ [=, this](const std::string &name, const sf::Event &event) -> void 
#define _SD_CALLBACK_ [=, this](int id, const trm::Information &reply) -> void 

#include <iostream>
#include <cassert>
#include "ui.hpp"
#include "transmitter.hpp"

namespace clpg{

class PageBase {
public:
    using Callback = std::function<void (int, const trm::Information &)>;
    PageBase *RunOn(ui::Screen *screen) noexcept;
protected:
    virtual void Load(ui::Screen *screen) noexcept = 0;
    virtual void Logic(ui::Screen *screen) noexcept = 0;
    virtual void Ready(ui::Screen *screen) noexcept = 0;
    virtual void Tick(ui::Screen *screen) noexcept {}
    virtual void TickAtSpecificIntervals(ui::Screen *screen) noexcept {}
    virtual void Unload(ui::Screen *screen) noexcept {}

    /**
     * @brief 向服务器发送请求并等待回复。
     * @param screen 屏幕指针
     * @param information 请求信息
     * @param tips 提示信息
     * @return 服务器返回的状态码和回复信息
     * @note 该函数会阻塞线程，直到收到回复或超时。
     * @note 状态码定义：1 成功；0 超时；-1 窗口被关闭。
     */
    static std::pair<int, trm::Information> WaitServer(ui::Screen *screen, const trm::Information &information, const std::string &tips) noexcept;
    /**
     * @brief 弹出消息框。
     * @param screen 屏幕指针
     * @param tips 提示信息
     * @param options 选项列表
     * @return 选项序号
     * @note 该函数会阻塞线程，直到用户选择选项或关闭窗口。
     * @note 选项序号从 0 开始。
     */
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

    static std::vector<std::string> argvs;
    
    /**
     * @brief 监听指定 Sender 对象。
     * @param sender 待监听的 Sender 对象
     * @param callback 回调函数
     * @note 该函数不会会阻塞线程，收到回复或超时才会调用回调函数。
     * @note 回调函数的第一个参数为请求的 ID，第二个参数为回复信息。
     * @note 超时时，回调函数的第二个参数为 trm::rpl::TIME_OUT。
     */
    void Listen(trm::Sender *sender, const Callback &callback) noexcept;
    /**
     * @brief 切换到指定页面。
     * @param page 目标页面
     */
    void SwitchTo(PageBase *page);
    /**
     * @brief 设置监听间隔。
     * @param newInterval 新的监听间隔（毫秒）
     */
    void SetInterval(int newInterval) noexcept;
    /**
     * @brief 设置监听次数限制。
     * @param newLimit 新的监听次数限制
     */
    void SetLimit(int newLimit) noexcept;
    /**
     * @brief 将某个组件放入释放队列，以使其在这一帧结束时被释放。
     * @param control 待释放的组件
     */
    void QueueFree(ui::Control *control) noexcept;
private:
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
    void Load(ui::Screen *screen) noexcept override = 0; // # 在这里写页面的布局（根据基类静态成员的值，写页面组件的父子关系，设置组件的属性等）。
    void Logic(ui::Screen *screen) noexcept override = 0; // # 在这里写回调逻辑（设置组件回调函数、监听回调函数，进而动态设置组件属性、动态增减组件、跳转页面等）。
    void Ready(ui::Screen *screen) noexcept override = 0; // # 在这里可作初始化逻辑（准备维护基类静态成员的值，发送请求，* 启动定时器等）。
    void Tick(ui::Screen *screen) noexcept override = 0; // * 在这里可作页面的监测（定时器等）。
    void TickAtSpecificIntervals(ui::Screen *screen) noexcept override = 0; // * 在这里可作页面的长间隔监测（可当作一个定时器等）。
    void Unload(ui::Screen *screen) noexcept override = 0; // * 在这里作页面的卸载逻辑（释放拥有所有权的指针，停止定时器等）。
};

class Copy : public PageBase {
private:
    ;
protected:
    void Load(ui::Screen *screen) noexcept override = 0;
    void Logic(ui::Screen *screen) noexcept override = 0;
    void Ready(ui::Screen *screen) noexcept override = 0; // ! 复制后，这些 = 0 要删掉的
};

}


#endif
