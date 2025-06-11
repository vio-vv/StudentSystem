#ifndef __LAB_HPP__
#define __LAB_HPP__

#include "page_header.hpp"

namespace lab{
using namespace clpg;

class EnterCourse : public PageBase {
private:
    ui::InputBox *input = nullptr;
    ui::Button *btn1 = nullptr;
    ui::Label *glabel = nullptr;
    ui::Button *btn2 = nullptr;
    ui::Button *backbtn = nullptr;
    ui::Button *addbtn = nullptr;
    ui::HorizontalBox *hbox = nullptr;
    ui::Label *label0 = nullptr;
    ui::Label *label1 = nullptr;
    ui::Label *label2 = nullptr;
    ui::Label *label3 = nullptr;
    ui::Label *label4 = nullptr;
    ui::Button *tempbackbtn = nullptr;
    ui::Button *debtn = nullptr;
    ui::Button *admaddbtn = nullptr;
    ui::Button *admdebtn = nullptr;
    ui::Label *limit= nullptr;
    bool admadd=false;
    bool admde=false;
    bool add=false;
    bool del=false;
protected:
    void Load(ui::Screen *screen) noexcept override; // # 在这里写页面的布局（根据基类静态成员的值，写页面组件的父子关系，设置组件的属性）。
    void Logic(ui::Screen *screen) noexcept override; // # 在这里写回调逻辑（设置组件回调函数、监听回调函数，进而动态设置组件属性、动态增减组件、跳转页面等）。
    void Ready(ui::Screen *screen) noexcept override; // # 在这里可作初始化逻辑（准备维护基类静态成员的值，发送请求，* 启动定时器等）。
};
class CourseList : public PageBase {
private:
    ui::Button *backbtn = nullptr;
    ui::VerticalScrollingBox *vsbox = nullptr;
    ui::Label *label0 = nullptr;
protected:
    void Load(ui::Screen *screen) noexcept ;
    void Logic(ui::Screen *screen) noexcept ;
    void Ready(ui::Screen *screen) noexcept ;
};
class AddCourse : public PageBase {
private:
    ui::Button *backbtn = nullptr; 
    ui::Button *addbtn = nullptr;
    ui::Label *rpllabel = nullptr;
    ui::Label *label0 = nullptr;
    ui::Label *label1 = nullptr;
    ui::InputBox *input = nullptr;
    ui::Button *btn1 = nullptr;
    ui::Label *glabel = nullptr;
    ui::HorizontalBox *hbox = nullptr;
    ui::Label *limit = nullptr;
protected:
    void Load(ui::Screen *screen) noexcept override; 
    void Logic(ui::Screen *screen) noexcept override;
    void Ready(ui::Screen *screen) noexcept override;
};
class DeleteCourse : public PageBase {
private:
    ui::Button *backbtn = nullptr;
    ui::Button *debtn = nullptr;
    ui::Label *rpllabel = nullptr;
    ui::Label *label0 = nullptr;
    ui::Label *label1 = nullptr;
    ui::InputBox *input = nullptr;
    ui::Button *btn1 = nullptr;
    ui::Label *glabel = nullptr;
    ui::HorizontalBox *hbox = nullptr;
    ui::Label *limit = nullptr;
protected:
    void Load(ui::Screen *screen) noexcept override; 
    void Logic(ui::Screen *screen) noexcept override;
    void Ready(ui::Screen *screen) noexcept override;
};
class AdmAddCourse: public PageBase {
private:
    ui::Button *backbtn = nullptr;
    ui::InputBox *input1 = nullptr;
    ui::InputBox *input2 = nullptr;
    ui::InputBox *input3 = nullptr;
    ui::InputBox *input4 = nullptr;
    ui::Label *glabel = nullptr;
    ui::Button *cfbtn = nullptr;
    ui::Label *limit = nullptr;
    std::vector<ui::ToggleButton *> weeklist;
    static const int MAX_WEEK = 16;
    ui::HorizontalScrollingBox *hsbox = nullptr;
    ui::Button *wbtn = nullptr;
protected:
    void Load(ui::Screen *screen) noexcept override;
    void Logic(ui::Screen *screen) noexcept override;
    void Ready(ui::Screen *screen) noexcept override; 
};
class AdmDeleteCourse: public PageBase {
private:
    ui::InputBox *input = nullptr;
    ui::Button *backbtn = nullptr;
    ui::Button *btn1 = nullptr;
    ui::Label *glabel = nullptr;
    ui::Label *label0 = nullptr;
    ui::Label *label1 = nullptr;
    ui::HorizontalBox *hbox = nullptr;
    ui::Button *debtn = nullptr;
    ui::Label *rpllabel = nullptr;
    ui::Label *limit = nullptr;
protected:
    void Load(ui::Screen *screen) noexcept override;
    void Logic(ui::Screen *screen) noexcept override;
    void Ready(ui::Screen *screen) noexcept override; 
};

class EnterReserve : public PageBase {
private:
    ui::InputBox *idinput = nullptr;
    ui::InputBox *phinput = nullptr;
    ui::Button *backbtn = nullptr;
    ui::Button *btn1 = nullptr;
    ui::Label *glabel = nullptr;
    ui::Button *btn2 = nullptr;
    ui::Button *btn3 = nullptr;
    ui::Button *cfbtn1 =nullptr;
    ui::Button *cfbtn2 =nullptr;
    ui::VerticalBox *vinput=nullptr;
    ui::Button *relbtn = nullptr;
    ui::Button *admaddbtn = nullptr;
    ui::Button *admdebtn = nullptr;
    ui::Button *modifybtn1 = nullptr;
    ui::Button *modifybtn2 = nullptr;
    ui::Button *dbtn1 = nullptr;
    ui::Button *dbtn2 = nullptr;
    ui::Button *dbtn3 = nullptr;
    ui::VerticalScrollingBox *vsbox1 = nullptr;
    ui::VerticalScrollingBox *vsbox2 = nullptr;
    ui::VerticalScrollingBox *vsbox3 = nullptr;
    ui::Button *clbtn1 = nullptr;
    ui::Button *clbtn2 = nullptr;
    ui::Button *clbtn3 = nullptr;
    ui::Label *limit2 = nullptr;
    ui::Button *tbtn = nullptr;
    ui::HorizontalScrollingBox *hsbox = nullptr;
    bool isadmadd = false;
    bool isadmde = false;
    bool isadmmodifyn = false;
    bool isadmmodifys = false;
    std::vector<ui::Button *> months;
    std::vector<ui::Button *> weeks;
    std::vector<ui::Button *> days;
    std::vector<ui::Button *> times;
    static const int MAX_MONTHS = 12;
    static const int MAX_WEEKS = 4;
    static const int MAX_DAYS = 7;
    static const int MAX_TIMES = 14;

    const bool fromLogin;
protected:
    void Load(ui::Screen *screen) noexcept override;
    void Logic(ui::Screen *screen) noexcept override;
    void Ready(ui::Screen *screen) noexcept override;
public:
    EnterReserve(bool fromLogin = false) noexcept : fromLogin(fromLogin) {
        // 构造函数，fromLogin用于判断是否从登录页面进入,是为false
    }
};
class ReserveStatusList : public PageBase {
private:
    ui::Button *backbtn = nullptr;
    ui::VerticalScrollingBox *vsbox = nullptr;
    
protected:
    void Load(ui::Screen *screen) noexcept override;
    void Logic(ui::Screen *screen) noexcept override;
    void Ready(ui::Screen *screen) noexcept override;
};
class ReserveTimeList : public PageBase {
private:
    ui::Button *backbtn = nullptr;
    ui::VerticalScrollingBox *vsbox = nullptr;
    
protected:
    void Load(ui::Screen *screen) noexcept override;
    void Logic(ui::Screen *screen) noexcept override;
    void Ready(ui::Screen *screen) noexcept override;
};
class Request : public PageBase {
private:
    ui::Button *backbtn = nullptr;
    ui::Label *glabel = nullptr;
    ui::HorizontalBox *hbox = nullptr;
    ui::VerticalBox *vbox = nullptr;
    ui::HorizontalBox *hinput3 = nullptr;
    ui::HorizontalBox *hinput4 = nullptr;
    ui::InputBox *idinput = nullptr;
    ui::InputBox *phinput = nullptr;
    ui::Label *label0 = nullptr;
    ui::Label *label1 = nullptr;
    ui::Label *label2 = nullptr;
    ui::Label *rpllabel = nullptr;   
    ui::Button *addbtn = nullptr;
    ui::Button *cfbtn = nullptr;
    ui::Button *clbtn = nullptr;
    ui::Label *label = nullptr;
    ui::Label *limit = nullptr;
protected:
    void Load(ui::Screen *screen) noexcept override;
    void Logic(ui::Screen *screen) noexcept override;
    void Ready(ui::Screen *screen) noexcept override;
};
class Cancel : public PageBase {
private:
    ui::HorizontalBox *hbox = nullptr;
    ui::Button *backbtn = nullptr;
    ui::Button *debtn = nullptr;
    ui::Label *rpllabel = nullptr;
    ui::Label *label0 = nullptr;
    ui::Label *label1 = nullptr;
    ui::Label *label2 = nullptr;
    ui::InputBox *idinput = nullptr;
    ui::InputBox *phinput = nullptr;
    ui::Button *cfbtn = nullptr;
    ui::Label *glabel = nullptr;
    ui::HorizontalBox *hinput3 = nullptr;
    ui::HorizontalBox *hinput4 = nullptr;
    ui::VerticalBox *vbox = nullptr;
    ui::Label *limit = nullptr;
    ui::Label *label = nullptr;
    ui::Button *clbtn = nullptr;
protected:
    void Load(ui::Screen *screen) noexcept override;
    void Logic(ui::Screen *screen) noexcept override;
    void Ready(ui::Screen *screen) noexcept override;
};
class AdmAddReserve : public PageBase {
private:
   ui::Button *backbtn = nullptr;
    ui::InputBox *input1 = nullptr;
    ui::InputBox *input2 = nullptr;
    ui::InputBox *input3 = nullptr;
    ui::InputBox *input4 = nullptr;
    ui::InputBox *input5 = nullptr;
    ui::Label *glabel = nullptr;
    ui::Button *cfbtn = nullptr;
protected:
    void Load(ui::Screen *screen) noexcept override;
    void Logic(ui::Screen *screen) noexcept override;
    void Ready(ui::Screen *screen) noexcept override;
};
class AdmCancelReserve : public PageBase {
private:
    ui::Label *limit = nullptr;
    ui::InputBox *dinput1 = nullptr;
    ui::InputBox *dinput2 = nullptr;
    ui::InputBox *dinput3 = nullptr;
    ui::InputBox *input2 = nullptr;
    ui::Button *backbtn = nullptr;
    ui::Button *btn1 = nullptr;
    ui::Label *glabel = nullptr;
    ui::Label *label0 = nullptr;
    ui::Label *label1 = nullptr;
    ui::Label *label2 = nullptr;
    ui::HorizontalBox *hbox2 = nullptr;
    ui::Button *debtn = nullptr;
    ui::Label *rpllabel = nullptr;
    ui::Button *modifybtn = nullptr;
    ui::VerticalBox *vbox2 = nullptr;
    ui::InputBox *input = nullptr;
    ui::Button *cfbtn = nullptr;
    ui::Label *nlabel = nullptr;
    ui::Button *clbtn = nullptr;

    const bool fromModify;
protected:
    void Load(ui::Screen *screen) noexcept override;
    void Logic(ui::Screen *screen) noexcept override;
    void Ready(ui::Screen *screen) noexcept override;
public:
    AdmCancelReserve(bool fromModify=false) noexcept : fromModify(fromModify) { 
        // 构造函数，fromModify用于判断是否从修改预约按钮进入
    }
}; // 删除预约和修改数量
class AdmModifyReserve:public PageBase {
private:
    ui::InputBox *input1 = nullptr;
    ui::InputBox *input2 = nullptr;
    ui::InputBox *input3 = nullptr;
    ui::InputBox *input4 = nullptr;
    ui::InputBox *input5 = nullptr;
    ui::Button *backbtn = nullptr;
    ui::Label *glabel = nullptr;
    ui::Button *cfbtn = nullptr;
    ui::InputBox *input6 = nullptr;
    ui::Label *limit = nullptr;
protected:
    void Load(ui::Screen *screen) noexcept override;
    void Logic(ui::Screen *screen) noexcept override;
    void Ready(ui::Screen *screen) noexcept override;
}; // 修改状态
}

#endif // __LAB_HPP__