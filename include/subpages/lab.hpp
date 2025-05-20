#ifndef __LAB_HPP__
#define __LAB_HPP__

#include "page_header.hpp"

namespace lab{
using namespace clpg;

class EnterCourse : public PageBase {
private:
   ; 
protected:
    void Load(ui::Screen *screen) noexcept;// # 在这里写页面的布局（根据基类静态成员的值，写页面组件的父子关系，设置组件的属性）。
    void Logic(ui::Screen *screen) noexcept;// # 在这里写回调逻辑（设置组件回调函数、监听回调函数，进而动态设置组件属性、动态增减组件、跳转页面等）。
    void Ready(ui::Screen *screen) noexcept;// # 在这里可作初始化逻辑（准备维护基类静态成员的值，发送请求，* 启动定时器等）。
};
class CourseList : public PageBase {
private:
    ;
protected:
    void Load(ui::Screen *screen) noexcept ;
    void Logic(ui::Screen *screen) noexcept ;
    void Ready(ui::Screen *screen) noexcept ;
};
class AddAndDelete : public PageBase {
private:
    ;
protected:
    void Load(ui::Screen *screen) noexcept;
    void Logic(ui::Screen *screen) noexcept;
    void Ready(ui::Screen *screen) noexcept;
};
class EnterReserve : public PageBase {
private:
    ;
protected:
    void Load(ui::Screen *screen) noexcept;
    void Logic(ui::Screen *screen) noexcept;
    void Ready(ui::Screen *screen) noexcept;
};
class ReserveList : public PageBase {
private:
    ;
protected:
    void Load(ui::Screen *screen) noexcept;
    void Logic(ui::Screen *screen) noexcept;
    void Ready(ui::Screen *screen) noexcept;
};
class Reserve : public PageBase {
private:
    ;   
protected:
    void Load(ui::Screen *screen) noexcept;
    void Logic(ui::Screen *screen) noexcept;
    void Ready(ui::Screen *screen) noexcept;
};
}  
#endif
