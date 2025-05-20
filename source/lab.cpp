#include "client_pages.hpp"

void lab::EnterCourse::Load(ui::Screen *screen) noexcept
{
    auto mar=new ui::Margin();{
        mar->AddTo(screen);
        mar->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
        mar->SetMargin(80, 80, 200, 200);
    }
    {
        auto flat=new ui::Flat();{
            mar->Add(flat);
            flat->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
        }
        {
            auto backbtn = new ui::Button; {
                backbtn->AddTo(flat);
                backbtn->SetHPreset(ui::Control::Preset::WRAP_AT_END);
                backbtn->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                backbtn->SetCaption("返回");
            }
            auto hbox1 = new ui::HorizontalBox();{
                hbox1->AddTo(flat);
                hbox1->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                hbox1->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                hbox1->SetHSize(75);
                hbox1->SetVAnchor(5);
            }
            {   
                auto input = new ui::InputBox;{
                    input->AddTo(hbox1);
                    input->SetPreset(ui::Control::Preset::FILL_FROM_END);
                }
                auto hbtnbox1 = new ui::HorizontalBox();{
                    hbtnbox1->AddTo(hbox1);
                    hbtnbox1->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                    hbtnbox1->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                }
                {
                    auto btn1 = new ui::Button;{
                        btn1->AddTo(hbtnbox1);
                        btn1->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        btn1->SetCaption("查询");
                    }
                }
                
            }
            auto glabel=new ui::Label();{
                glabel->AddTo(flat);
                glabel->SetHPreset(ui::Control::Preset::WRAP_AT_CENTER);
                glabel->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                glabel->SetVAnchor(15);
                glabel->SetSizeWrap(ui::Control::Direction::HORIZONTAL, false);
                glabel->SetHSize(700);
            }
            auto hbtnbox2 = new ui::HorizontalBox();{
                hbtnbox2->AddTo(flat);
                hbtnbox2->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
            }
            {
                auto btn2 = new ui::Button;{
                    btn2->AddTo(hbtnbox2);
                    btn2->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    btn2->SetCaption("查看课程");
                }
            }
        }
    }
}

void lab::EnterCourse::Logic(ui::Screen *screen) noexcept
{
    ;
}

void lab::EnterCourse::Ready(ui::Screen *screen) noexcept
{
    ;
}

void lab::CourseList::Load(ui::Screen *screen) noexcept
{
    auto mar = new ui::Margin; {
        mar->AddTo(screen);
        mar->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
        mar->SetMargin(80, 80, 200, 200);
    }
    {
        auto flat = new ui::Flat; {
            mar->Add(flat);
            flat->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
        }
        {
            auto backbtn = new ui::Button; {
                backbtn->AddTo(flat);
                backbtn->SetHPreset(ui::Control::Preset::WRAP_AT_END);
                backbtn->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                backbtn->SetCaption("返回");
            }
            auto vsbox = new ui::VerticalScrollingBox;{
                vsbox->AddTo(flat);
                vsbox->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                vsbox->SetSize(ui::Control::Direction::HORIZONTAL,90);
                vsbox->SetSize(ui::Control::Direction::VERTICAL, 80);
            }
            {
                auto hbox1 = new ui::HorizontalBox;{
                    hbox1->AddTo(vsbox);
                    hbox1->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                    hbox1->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    hbox1->SetGap(50);
                }
                {
                    auto label10 = new ui::Label;{
                        label10->AddTo(hbox1);
                        label10->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        label10->SetContent("课程编号");
                    }
                    auto label11 = new ui::Label;{
                        label11->AddTo(hbox1);
                        label11->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        label11->SetContent("课程名称");
                    }
                    auto label12 = new ui::Label;{
                        label12->AddTo(hbox1);
                        label12->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        label12->SetContent("教师");
                    }
                    auto label13 = new ui::Label;{
                        label13->AddTo(hbox1);
                        label13->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        label13->SetContent("教室");
                    }
                    auto label14 = new ui::Label;{
                        label14->AddTo(hbox1);
                        label14->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        label14->SetContent("上课周数");
                    }
                }
                auto hbox2 = new ui::HorizontalBox;{
                    hbox2->AddTo(vsbox);
                    hbox2->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                    hbox2->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    hbox2->SetGap(50);
                }
                {
                    auto label20 = new ui::Label;{
                        label20->AddTo(hbox2);
                        label20->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        label20->SetContent("课程编号");
                    }
                    auto label21 = new ui::Label;{
                        label21->AddTo(hbox2);
                        label21->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        label21->SetContent("课程名称");
                    }
                    auto label22 = new ui::Label;{
                        label22->AddTo(hbox2);
                        label22->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        label22->SetContent("教师");
                    }
                    auto label23 = new ui::Label;{
                        label23->AddTo(hbox2);
                        label23->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        label23->SetContent("教室");
                    }
                    auto label24 = new ui::Label;{
                        label24->AddTo(hbox2);
                        label24->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        label24->SetContent("上课周数");
                    }
                }
            } 
        }
    }
}

void lab::CourseList::Logic(ui::Screen *screen) noexcept
{
    ;
}

void lab::CourseList::Ready(ui::Screen *screen) noexcept
{
    ;
}

void lab::AddAndDelete::Load(ui::Screen *screen) noexcept
{
    auto mar = new ui::Margin; {
        mar->AddTo(screen);
        mar->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
        mar->SetMargin(200, 200, 200, 200);
    }
    {
        auto flat = new ui::Flat; {
            mar->Add(flat);
            flat->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
        }
        {
            auto backbtn = new ui::Button; {
                backbtn->AddTo(flat);
                backbtn->SetHPreset(ui::Control::Preset::WRAP_AT_END);
                backbtn->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                backbtn->SetCaption("返回");
            }
            auto hbox = new ui::HorizontalBox; {
                hbox->AddTo(flat);
                hbox->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                hbox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                hbox->SetSizeWrap(ui::Control::Direction::VERTICAL, false);
                hbox->SetVSize(250);
            }
            {
                auto label = new ui::Label; {
                    label->AddTo(hbox);
                    label->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    label->SetContent("课程编号");
                }
                auto label2 = new ui::Label; {
                    label2->AddTo(hbox);
                    label2->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    label2->SetContent("课程名称");
                }
                auto vbox = new ui::VerticalBox; {
                    vbox->AddTo(hbox);
                    vbox->SetHPreset(ui::Control::Preset::FILL_FROM_END);
                    vbox->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    vbox->SetSizeWrap(ui::Control::Direction::HORIZONTAL, false);
                    vbox->SetHSize(50);
                }
                {
                    auto btn1 = new ui::Button; {
                        btn1->AddTo(vbox);
                        btn1->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        btn1->SetCaption("添加");
                    }
                    auto btn2 = new ui::Button; {
                        btn2->AddTo(vbox);
                        btn2->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        btn2->SetCaption("删除");
                    }
                }
            }
            auto label = new ui::Label; {
                label->AddTo(flat);
                label->SetPreset(ui::Control::Preset::WRAP_AT_END);
                label->SetSizeWrap(ui::Control::Direction::HORIZONTAL, false);
                label->SetSizeWrap(ui::Control::Direction::VERTICAL, false);
                label->SetHSize(700);
                label->SetVSize(100);
                label->SetHAnchor(95);
                label->SetVAnchor(95);
            }
        }
    }
}

void lab::AddAndDelete::Logic(ui::Screen *screen) noexcept
{
    ;
}

void lab::AddAndDelete::Ready(ui::Screen *screen) noexcept
{
    ;
}

void lab::EnterReserve::Load(ui::Screen *screen) noexcept
{
    auto mar=new ui::Margin();{
        screen->Add(mar);
        mar->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
        mar->SetMargin(80, 80, 200, 200);
    }
    {
        auto flat=new ui::Flat();{
            mar->Add(flat);
            flat->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
        }
        {
            auto backbtn = new ui::Button; {
                backbtn->AddTo(flat);
                backbtn->SetHPreset(ui::Control::Preset::WRAP_AT_END);
                backbtn->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                backbtn->SetCaption("返回");
            }
            auto hbox1 = new ui::HorizontalBox();{
                hbox1->AddTo(flat);
                hbox1->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                hbox1->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                hbox1->SetHSize(75);
                hbox1->SetVAnchor(5);

            }
            {   
                auto input = new ui::InputBox;{
                    input->AddTo(hbox1);
                    input->SetPreset(ui::Control::Preset::FILL_FROM_END);
                }
                auto hbtnbox1 = new ui::HorizontalBox();{
                    hbtnbox1->AddTo(hbox1);
                    hbtnbox1->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                    hbtnbox1->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                }
                {
                    auto btn1 = new ui::Button;{
                        btn1->AddTo(hbtnbox1);
                        btn1->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        btn1->SetCaption("查询");
                    }
                }
            }
            auto glabel=new ui::Label();{
                glabel->AddTo(flat);
                glabel->SetHPreset(ui::Control::Preset::WRAP_AT_CENTER);
                glabel->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                glabel->SetVAnchor(15);
                glabel->SetSizeWrap(ui::Control::Direction::HORIZONTAL, false);
                glabel->SetHSize(700);
            }
            auto hbtnbox2 = new ui::HorizontalBox();{
                hbtnbox2->AddTo(flat);
                hbtnbox2->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
            }
            {
                auto btn2 = new ui::Button;{
                    btn2->AddTo(hbtnbox2);
                    btn2->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    btn2->SetCaption("查看全部预约");//可能要稍作修改
                }
            }
        }
    }
}

void lab::EnterReserve::Logic(ui::Screen *screen) noexcept
{
    ;
}

void lab::EnterReserve::Ready(ui::Screen *screen) noexcept
{
    ;
}

void lab::ReserveList::Load(ui::Screen *screen) noexcept
{
    auto mar = new ui::Margin; {
        screen->Add(mar);
        mar->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
        mar->SetMargin(80, 80, 200, 200);
    }
    {
        auto flat = new ui::Flat; {
            mar->Add(flat);
            flat->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
        }
        {
            auto backbtn = new ui::Button; {
                backbtn->AddTo(flat);
                backbtn->SetHPreset(ui::Control::Preset::WRAP_AT_END);
                backbtn->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                backbtn->SetCaption("返回");
            }
            auto vsbox = new ui::VerticalScrollingBox;{
                vsbox->AddTo(flat);
                vsbox->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                vsbox->SetSize(ui::Control::Direction::HORIZONTAL,90);
                vsbox->SetSize(ui::Control::Direction::VERTICAL, 80);
            }
            {
                auto hbox1 = new ui::HorizontalBox;{
                    hbox1->AddTo(vsbox);
                    hbox1->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                    hbox1->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    hbox1->SetGap(50);
                }
                {
                    auto label10 = new ui::Label;{
                        label10->AddTo(hbox1);
                        label10->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        label10->SetContent("日期");
                    }
                    auto label11 = new ui::Label;{
                        label11->AddTo(hbox1);
                        label11->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        label11->SetContent("时间");
                    }
                    auto label12 = new ui::Label;{
                        label12->AddTo(hbox1);
                        label12->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        label12->SetContent("剩余名额");
                    }
                    auto label13 = new ui::Label;{
                        label13->AddTo(hbox1);
                        label13->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        label13->SetContent("预约状态");
                    }
                }
                auto hbox2 = new ui::HorizontalBox;{
                    hbox2->AddTo(vsbox);
                    hbox2->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                    hbox2->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    hbox2->SetGap(50);
                }
                {
                    auto label20 = new ui::Label;{
                        label20->AddTo(hbox2);
                        label20->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        label20->SetContent("日期");
                    }
                    auto label21 = new ui::Label;{
                        label21->AddTo(hbox2);
                        label21->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        label21->SetContent("时间");
                    }
                    auto label22 = new ui::Label;{
                        label22->AddTo(hbox2);
                        label22->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        label22->SetContent("剩余名额");
                    }
                    auto label23 = new ui::Label;{
                        label23->AddTo(hbox2);
                        label23->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        label23->SetContent("预约状态");
                    }
                }
            } 
        }
    }
}

void lab::ReserveList::Logic(ui::Screen *screen) noexcept
{
    ;
}

void lab::ReserveList::Ready(ui::Screen *screen) noexcept
{
    ;
}

void lab::Reserve::Load(ui::Screen *screen) noexcept
{
    auto mar = new ui::Margin; {
        screen->Add(mar);
        mar->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
        mar->SetMargin(200, 200, 200, 200);
    }
    auto flat = new ui::Flat; {
        mar->Add(flat);
        flat->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
    }
    {
        auto backbtn = new ui::Button; {
            backbtn->AddTo(flat);
            backbtn->SetHPreset(ui::Control::Preset::WRAP_AT_END);
            backbtn->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
            backbtn->SetCaption("返回");
        }
        auto hbox = new ui::HorizontalBox; {
            hbox->AddTo(flat);
            hbox->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
            hbox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
            hbox->SetSizeWrap(ui::Control::Direction::VERTICAL, false);
            hbox->SetVSize(250);
        }
        {
            auto label = new ui::Label; {
                label->AddTo(hbox);
                label->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                label->SetContent("日期");
            }
            auto label2 = new ui::Label; {
                label2->AddTo(hbox);
                label2->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                label2->SetContent("时间");
            }
            auto label3 = new ui::Label; {
                label3->AddTo(hbox);
                label3->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                label3->SetContent("剩余名额");
            }
            auto label4 = new ui::Label; {
                label4->AddTo(hbox);
                label4->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                label4->SetContent("预约状态");
            }
            auto vbox = new ui::VerticalBox; {
                vbox->AddTo(hbox);
                vbox->SetHPreset(ui::Control::Preset::FILL_FROM_END);
                vbox->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                vbox->SetSizeWrap(ui::Control::Direction::HORIZONTAL, false);
                vbox->SetHSize(50);
            }
            {
                auto btn1 = new ui::Button; {
                    btn1->AddTo(vbox);
                    btn1->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    btn1->SetCaption("添加");
                }
                auto btn2 = new ui::Button; {
                    btn2->AddTo(vbox);
                    btn2->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    btn2->SetCaption("删除");
                }
            }
        }
        auto label = new ui::Label; {
            label->AddTo(flat);
            label->SetPreset(ui::Control::Preset::WRAP_AT_END);
            label->SetSizeWrap(ui::Control::Direction::HORIZONTAL, false);
            label->SetSizeWrap(ui::Control::Direction::VERTICAL, false);
            label->SetHSize(700);
            label->SetVSize(100);
            label->SetHAnchor(95);
            label->SetVAnchor(95);
        }
    }
}

void lab::Reserve::Logic(ui::Screen *screen) noexcept
{
    ;
}
//刚才push不上去，写个注释
void lab::Reserve::Ready(ui::Screen *screen) noexcept
{
    ;
}