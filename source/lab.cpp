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
            backbtn = new ui::Button; {
                backbtn->AddTo(flat);
                backbtn->SetPreset(ui::Control::Preset::WRAP_AT_FRONT);
                backbtn->SetCaption("返回");//private
            }
            auto hbox1 = new ui::HorizontalBox();{
                hbox1->AddTo(flat);
                hbox1->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                hbox1->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                hbox1->SetHSize(75);
                hbox1->SetVAnchor(5);
            }
            {   
                input = new ui::InputBox;{
                    input->AddTo(hbox1);
                    input->SetPreset(ui::Control::Preset::FILL_FROM_END);//private
                }
                auto hbtnbox1 = new ui::HorizontalBox();{
                    hbtnbox1->AddTo(hbox1);
                    hbtnbox1->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                    hbtnbox1->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                }
                {
                    btn1 = new ui::Button;{
                        btn1->AddTo(hbtnbox1);
                        btn1->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        btn1->SetCaption("查询");//private
                    }
                }
                
            }
            glabel=new ui::Label();{
                glabel->AddTo(flat);
                glabel->SetHPreset(ui::Control::Preset::WRAP_AT_CENTER);
                glabel->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                glabel->SetVAnchor(15);
                glabel->SetSizeWrap(ui::Control::Direction::HORIZONTAL, false);
                glabel->SetHSize(700);//private
            }
            addbtn = new ui::Button;{
                addbtn->AddTo(flat);
                addbtn->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                addbtn->SetVAnchor(30);
                addbtn->SetCaption("添加课程");//private
            }
            debtn = new ui::Button;{
                debtn->AddTo(flat);
                debtn->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                debtn->SetVAnchor(45);
                debtn->SetCaption("删除课程");//private
            }
            btn2 = new ui::Button;{
                    btn2->AddTo(flat);
                    btn2->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                    btn2->SetCaption("查看全部课程");//private
                    btn2->SetVAnchor(60);
            }
            hbox = new ui::HorizontalBox; {
                hbox->AddTo(flat);
                hbox->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                hbox->SetHSize(80);
                hbox->SetVSize(20);
            }
            {
                tempbackbtn =new ui::Button; {
                    tempbackbtn->AddTo(hbox);
                    tempbackbtn->SetPreset(ui::Control::Preset::WRAP_AT_FRONT);
                    tempbackbtn->SetCaption("返回");//private
                }
                label0 = new ui::Label; {
                    label0->AddTo(hbox);
                    label0->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                }
                label1 = new ui::Label; {
                    label1->AddTo(hbox);
                    label1->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                }
                label2 = new ui::Label; {
                    label2->AddTo(hbox);
                    label2->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                }
                label3 = new ui::Label; {
                    label3->AddTo(hbox);
                    label3->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                }
                label4 = new ui::Label; {
                    label4->AddTo(hbox);
                    label4->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                }
            }
        }
    }
}

void lab::EnterCourse::Logic(ui::Screen *screen) noexcept
{
    backbtn->SetClickCallback(UI_CALLBACK{
        SwitchTo(new eea::MainPage);
    });
    btn2->SetClickCallback(UI_CALLBACK{
        SwitchTo(new lab::CourseList);
    });
    input->SetInputCallback(UI_CALLBACK{
        coursename = input->GetText();
        glabel->SetContent("请输入课程名称");//inputing 
        glabel->Show();
    });
    btn1->SetClickCallback(UI_CALLBACK{
        btn1->Enable(false);
       if(coursename=="") 
       {
        glabel->SetContent("课程名称不能为空");
        glabel->Show();
       }
       else
       {
        Listen(new trm::Sender({trm::rqs::SEARCH_COURSE_INFORMATION,account.code,coursename}),SD_CALLBACK{
        //if (reply[0] == trm::rpl::TIME_OUT) {
        //    glabel->SetContent("服务端未响应，请检查后重试");
        //    glabel->Show();
        //}
        if(reply[0] == trm::rpl::NO) {
            glabel->SetContent("无匹配课程,请重新输入");
            glabel->Show();
        }
        else {
            btn2->Hide();
            addbtn->Hide();
            hbox->ShowAll();
            tempbackbtn->Enable();
            auto coursereply=trm::Split(reply[2]);
            label0->SetContent("课程编号:"+reply[1]);
            label1->SetContent("课程名称:"+coursereply[0]);
            label2->SetContent("上课老师:"+coursereply[1]);
            label3->SetContent("上课地点:"+coursereply[2]);
            label4->SetContent("上课周数:"+coursereply[3]);
            label4->SetFontSize(20);//待改善
        }});
        }
            btn1->Enable();
        }
    );
    addbtn->SetClickCallback(UI_CALLBACK{
        SwitchTo(new lab::AddCourse);
    });
    debtn->SetClickCallback(UI_CALLBACK{
        SwitchTo(new lab::DeleteCourse);
    });
    tempbackbtn->SetClickCallback(UI_CALLBACK{
        btn2->Show();
        addbtn->Show();
        debtn->Show();
        hbox->HideAll();
    });
}

void lab::EnterCourse::Ready(ui::Screen *screen) noexcept
{
    hbox->HideAll();
    tempbackbtn->Enable(false);
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
            backbtn = new ui::Button; {
                backbtn->AddTo(flat);
                backbtn->SetPreset(ui::Control::Preset::WRAP_AT_FRONT);
                backbtn->SetCaption("返回");//private
            }
            vsbox = new ui::VerticalScrollingBox;{
                vsbox->AddTo(flat);
                vsbox->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                vsbox->SetSize(ui::Control::Direction::HORIZONTAL,90);
                vsbox->SetSize(ui::Control::Direction::VERTICAL, 80);
            }
        }
    }
}

void lab::CourseList::Logic(ui::Screen *screen) noexcept
{
    backbtn->SetClickCallback(UI_CALLBACK{
        SwitchTo(new lab::EnterCourse);
    });
   
}

void lab::CourseList::Ready(ui::Screen *screen) noexcept
{
    Listen(new trm::Sender({trm::rqs::CHECK_ALL_COURSE,account.code}),SD_CALLBACK{
        if(reply[0] == trm::rpl::FAIL) {
            auto glabel = new ui::Label; {
                glabel->AddTo(vsbox);
                glabel->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                glabel->SetContent("没有课程存在");//private
            }
        }
        else {
            for(int i=1;i<reply.size();i++) {
                auto hbox = new ui::HorizontalBox; {
                    hbox->AddTo(vsbox);
                    hbox->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                    hbox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    hbox->SetGap(50);
                }
                auto coursereply=trm::Split(reply[i]);
                {
                    label0 = new ui::Label;{
                        label0->AddTo(hbox);
                        label0->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        label0->SetContent("课程编号:"+coursereply[0]);
                    }
                    auto inforeply=trm::Split(coursereply[1]);
                    auto label1 = new ui::Label;{
                        label1->AddTo(hbox);
                        label1->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        label1->SetContent("课程名称:"+inforeply[0]);
                    }
                    auto label2 = new ui::Label;{
                        label2->AddTo(hbox);
                        label2->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        label2->SetContent("上课老师:"+inforeply[1]);
                    }
                    auto label3 = new ui::Label;{
                        label3->AddTo(hbox);
                        label3->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        label3->SetContent("上课地点:"+inforeply[2]);
                    }
                    auto label4 = new ui::Label;{
                        label4->AddTo(hbox);
                        label4->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        label4->SetContent("上课周数:"+inforeply[3]);
                        label4->SetFontSize(20);
                    }
                }
            } 
       }
    });
}

void lab::AddCourse::Load(ui::Screen *screen) noexcept
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
            auto hbox1=new ui::HorizontalBox; {
                hbox1->AddTo(flat);
                hbox1->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                hbox1->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                hbox1->SetVAnchor(10);
                hbox1->SetHSize(80);
            }
            {
                input = new ui::InputBox; {
                    input->AddTo(hbox1);
                    input->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);//private
                }
                btn1 = new ui::Button; {
                    btn1->AddTo(hbox1);
                    btn1->SetPreset(ui::Control::Preset::WRAP_AT_END);//private
                    btn1->SetCaption("查找");
                }
            }
            glabel = new ui::Label; {
                glabel->AddTo(flat);
                glabel->SetHPreset(ui::Control::Preset::WRAP_AT_CENTER);
                glabel->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                glabel->SetVAnchor(25);
                glabel->SetSizeWrap(ui::Control::Direction::HORIZONTAL, false);
                glabel->SetHSize(700);//private
            }
            backbtn = new ui::Button; {
                backbtn->AddTo(flat);
                backbtn->SetPreset(ui::Control::Preset::WRAP_AT_FRONT);
                backbtn->SetCaption("返回");//private
            }
            hbox = new ui::HorizontalBox; {
                hbox->AddTo(flat);
                hbox->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                hbox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                hbox->SetSizeWrap(ui::Control::Direction::VERTICAL, false);
                hbox->SetVSize(200);
                hbox->SetVAnchor(55);
                }//hideall
                {
                    label0 = new ui::Label; {
                        label0->AddTo(hbox);
                        label0->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);//private
                    }
                    label1 = new ui::Label; {
                    label1->AddTo(hbox);
                    label1->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);//private
                    }
                    addbtn = new ui::Button; {
                        addbtn->AddTo(hbox);
                        addbtn->SetHPreset(ui::Control::Preset::WRAP_AT_END);
                        addbtn->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        addbtn->SetCaption("添加");//private
                    }
                }
            rpllabel = new ui::Label; {
                rpllabel->AddTo(flat);
                rpllabel->SetPreset(ui::Control::Preset::PLACE_AT_END);//maybe
                rpllabel->SetHSize(600);
                rpllabel->SetVSize(100);
                rpllabel->SetHAnchor(95);
                rpllabel->SetVAnchor(95);
            }//private
        }
    }
}

void lab::AddCourse::Logic(ui::Screen *screen) noexcept
{
    backbtn->SetClickCallback(UI_CALLBACK{
        SwitchTo(new lab::EnterCourse);
    });
    input->SetInputCallback(UI_CALLBACK{
        coursename = input->GetText();
        glabel->SetContent("请输入课程代号");
        glabel->Show();
    });
    btn1->SetClickCallback(UI_CALLBACK{
        btn1->Enable(false);
        if(coursename=="") 
        {
            glabel->SetContent("课程代号不能为空");
            glabel->Show();
        }
        Listen(new trm::Sender({trm::rqs::ADD_COURSE,account.code,account.hashedPassword,coursename}),SD_CALLBACK{
            if(reply[0] == trm::rpl::FAIL&&reply[1] == trm::rpl::NO_MATCH_COURSE) {
                glabel->SetContent("无匹配课程,请重新输入");
                glabel->Show();
            }
            else if(reply[0] == trm::rpl::FAIL&&reply[1] == trm::rpl::COURSE_EXISTS) {
                glabel->SetContent("课程已存在,请重新输入");
                glabel->Show();
            }
            else if(reply[0]==trm::rpl::ACCESS_DENIED) {
                glabel->SetContent("权限不足");
                glabel->Show();
            }
            else {
                hbox->ShowAll();
                label0->SetContent("课程编号："+coursename);
                label1->SetContent("课程名称："+reply[1]);
                addbtn->Enable();
            }
        });
    });
    addbtn->SetClickCallback(UI_CALLBACK{
                rpllabel->SetContent("添加成功");
                rpllabel->Show();
    });
}

void lab::AddCourse::Ready(ui::Screen *screen) noexcept
{
    hbox->HideAll();
    addbtn->Enable(false);
}

void lab::DeleteCourse::Load(ui::Screen *screen) noexcept
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
            auto hbox1=new ui::HorizontalBox; {
                hbox1->AddTo(flat);
                hbox1->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                hbox1->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                hbox1->SetVAnchor(10);
                hbox1->SetHSize(80);
            }
            {
                input = new ui::InputBox; {
                    input->AddTo(hbox1);//inputting
                    input->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);//private
                }
                btn1 = new ui::Button; {
                    btn1->AddTo(hbox1);
                    btn1->SetPreset(ui::Control::Preset::WRAP_AT_END);//private
                    btn1->SetCaption("查找");
                }
            }
            glabel = new ui::Label; {
                glabel->AddTo(flat);
                glabel->SetHPreset(ui::Control::Preset::WRAP_AT_CENTER);
                glabel->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                glabel->SetVAnchor(25);
                glabel->SetSizeWrap(ui::Control::Direction::HORIZONTAL, false);
                glabel->SetHSize(700);//private
            }
            backbtn = new ui::Button; {
                backbtn->AddTo(flat);
                backbtn->SetPreset(ui::Control::Preset::WRAP_AT_FRONT);
                backbtn->SetCaption("返回");//private
            }
            hbox = new ui::HorizontalBox; {
                hbox->AddTo(flat);
                hbox->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                hbox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                hbox->SetSizeWrap(ui::Control::Direction::VERTICAL, false);
                hbox->SetVSize(200);
                hbox->SetVAnchor(55);
                }//hideall
                {
                    label0 = new ui::Label; {
                        label0->AddTo(hbox);
                        label0->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);//private
                    }
                    label1 = new ui::Label; {
                    label1->AddTo(hbox);
                    label1->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);//private
                    }
                    debtn = new ui::Button; {
                        debtn->AddTo(hbox);
                        debtn->SetHPreset(ui::Control::Preset::WRAP_AT_END);
                        debtn->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        debtn->SetCaption("删除");//private
                    }
                }
            rpllabel = new ui::Label; {
                rpllabel->AddTo(flat);
                rpllabel->SetPreset(ui::Control::Preset::PLACE_AT_END);//maybe
                rpllabel->SetHSize(600);
                rpllabel->SetVSize(100);
                rpllabel->SetHAnchor(95);
                rpllabel->SetVAnchor(95);
            }//private
        }
    }
}

void lab::DeleteCourse::Logic(ui::Screen *screen) noexcept
{
    backbtn->SetClickCallback(UI_CALLBACK{
        SwitchTo(new lab::EnterCourse);
    });
    input->SetInputCallback(UI_CALLBACK{
        coursename = input->GetText();
        glabel->SetContent("请输入课程代号");//inputting
        glabel->Show();
    });
    btn1->SetClickCallback(UI_CALLBACK{
        btn1->Enable(false);
        if(coursename=="") 
        {
            glabel->SetContent("课程代号不能为空");
            glabel->Show();
        }
        Listen(new trm::Sender({trm::rqs::DELETE_COURSE,account.code,account.hashedPassword,coursename}),SD_CALLBACK{
            if(reply[0] == trm::rpl::FAIL&&reply[1] == trm::rpl::NO_MATCH_COURSE) {
                glabel->SetContent("待删课程不存在,请重新输入");
                glabel->Show();
            }
           else if(reply[0]==trm::rpl::ACCESS_DENIED) {
                glabel->SetContent("权限不足");
                glabel->Show();
            }
            else {
                hbox->ShowAll();
                label0->SetContent("课程编号："+coursename);
                label1->SetContent("课程名称："+reply[1]);
                debtn->Enable();
            }
        });
    });
    debtn->SetClickCallback(UI_CALLBACK{
                rpllabel->SetContent("删除成功");
                rpllabel->Show();
    });
}

void lab::DeleteCourse::Ready(ui::Screen *screen) noexcept
{
    hbox->HideAll();
    debtn->Enable(false);
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
            backbtn = new ui::Button; {
                backbtn->AddTo(flat);
                backbtn->SetPreset(ui::Control::Preset::WRAP_AT_FRONT);
                backbtn->SetCaption("返回");//private
            }
            auto hbox1 = new ui::HorizontalBox();{
                hbox1->AddTo(flat);
                hbox1->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                hbox1->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                hbox1->SetHSize(75);
                hbox1->SetVAnchor(5);

            }
            {   
                auto vbox2 =new ui::VerticalBox();{
                    vbox2->AddTo(hbox1);
                    vbox2->SetPreset(ui::Control::Preset::FILL_FROM_CENTER); 
                }
                {
                    auto hinput1 =new ui::HorizontalBox();{
                        hinput1->AddTo(vbox2);
                        hinput1->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    }
                    {
                        auto inlabel1 =new ui::Label;{
                            inlabel1->AddTo(hinput1);
                            inlabel1->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                            inlabel1->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                            inlabel1->SetContent("日期");//?
                        }
                        auto vdbox1 =new ui::VerticalBox;{
                            vdbox1->AddTo(hinput1);
                            vdbox1->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        }
                        {
                            auto dlabel1 =new ui::Label;{
                                dlabel1->AddTo(vdbox1);
                                dlabel1->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                                dlabel1->SetContent("月份");
                            }
                            dinput1 = new ui::InputBox;{
                            dinput1->AddTo(vdbox1);
                            dinput1->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);//private
                            }
                        }
                        auto vdbox2 =new ui::VerticalBox;{
                            vdbox2->AddTo(hinput1);
                            vdbox2->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        }
                        {
                            auto dlabel2 =new ui::Label;{
                                dlabel2->AddTo(vdbox2);
                                dlabel2->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                                dlabel2->SetContent("星期");
                            }
                            dinput2 = new ui::InputBox;{
                            dinput2->AddTo(vdbox2);
                            dinput2->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);//private
                            }
                        }
                        auto vdbox3 =new ui::VerticalBox;{
                            vdbox3->AddTo(hinput1);
                            vdbox3->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        }
                        {
                            auto dlabel3 =new ui::Label;{
                                dlabel3->AddTo(vdbox3);
                                dlabel3->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                                dlabel3->SetContent("日期");
                            }
                            dinput3 = new ui::InputBox;{
                            dinput3->AddTo(vdbox3);
                            dinput3->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);//private
                            }
                        }
                    }
                    auto hinput2 =new ui::HorizontalBox();{
                        hinput2->AddTo(vbox2);
                        hinput2->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    }
                    {
                        auto inlabel2 =new ui::Label;{
                            inlabel2->AddTo(hinput2);
                            inlabel2->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                            inlabel2->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                            inlabel2->SetContent("时间");
                        }
                        input2 =new ui::InputBox;{
                            input2->AddTo(hinput2);
                            input2->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);//private
                        }
                    }
                    
                }
                auto vbox1 = new ui::VerticalBox();{
                    vbox1->AddTo(hbox1);
                    vbox1->SetHPreset(ui::Control::Preset::WRAP_AT_END);
                    vbox1->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                }
                {
                    btn1 = new ui::Button;{
                        btn1->AddTo(vbox1);
                        btn1->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        btn1->SetCaption("查询预约时间");//private
                    }
                    btn3 = new ui::Button;{
                        btn3->AddTo(vbox1);
                        btn3->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        btn3->SetCaption("查询预约状态");//private
                    }
                }
            }
            glabel=new ui::Label();{
                glabel->AddTo(flat);
                glabel->SetHPreset(ui::Control::Preset::WRAP_AT_CENTER);
                glabel->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                glabel->SetVAnchor(30);
                glabel->SetSizeWrap(ui::Control::Direction::HORIZONTAL, false);
                glabel->SetHSize(700);
            }//private
           
            btn2 = new ui::Button;{
                btn2->AddTo(flat);
                btn2->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                btn2->SetVAnchor(75);
                btn2->SetCaption("查看预约列表"); // 可能要稍作修改
            } //private
            hbox = new ui::HorizontalBox; {
                hbox->AddTo(flat);
                hbox->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                hbox->SetHSize(80);
                hbox->SetVSize(20); // private
            }
            {
                
                label0 = new ui::Label; {
                    label0->AddTo(hbox);
                    label0->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                }
                label1 = new ui::Label; {
                    label1->AddTo(hbox);
                    label1->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                }
                label2 = new ui::Label; {
                    label2->AddTo(hbox);
                    label2->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                }
            }
            vinput =new ui::VerticalBox();{
                vinput->AddTo(flat);
                vinput->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                vinput->SetVSize(30);
                vinput->SetHSize(80);
                vinput->SetVAnchor(50);
            }
            {
                hinput3 =new ui::HorizontalBox();{
                    hinput3->AddTo(vinput);
                    hinput3->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                }
                {
                    auto inlabel3 =new ui::Label;{
                        inlabel3->AddTo(hinput3);
                        inlabel3->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                        inlabel3->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        inlabel3->SetContent("身份证号");
                    }
                    idinput = new ui::InputBox;{
                        idinput->AddTo(hinput3);
                        idinput->SetPreset(ui::Control::Preset::FILL_FROM_CENTER); // private
                    }
                }
                hinput4 =new ui::HorizontalBox();{
                    hinput4->AddTo(vinput);
                    hinput4->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                }
                {
                    auto inlabel4 =new ui::Label;{
                        inlabel4->AddTo(hinput4);
                        inlabel4->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                        inlabel4->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        inlabel4->SetContent("手机号");
                    }
                    phinput =new ui::InputBox;{
                        phinput->AddTo(hinput4);
                        phinput->SetPreset(ui::Control::Preset::FILL_FROM_CENTER); // private
                    }
                } // idandphoneglabel
                cfbtn1=new ui::Button;{
                    cfbtn1->AddTo(vinput);
                    cfbtn1->SetPreset(ui::Control::Preset::WRAP_AT_END);
                    cfbtn1->SetCaption("确认");
                }
                cfbtn2=new ui::Button;{
                    cfbtn2->AddTo(vinput);
                    cfbtn2->SetPreset(ui::Control::Preset::WRAP_AT_END);
                    cfbtn2->SetCaption("确认");
                }
                relbtn = new ui::Button;{
                    relbtn->AddTo(vinput);
                    relbtn->SetVPreset(ui::Control::Preset::WRAP_AT_END);
                    relbtn->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                    relbtn->SetCaption("取消");
                }
            }
        }
    }
}

void lab::EnterReserve::Logic(ui::Screen *screen) noexcept
{
    backbtn->SetClickCallback(UI_CALLBACK{
        SwitchTo(new eea::MainPage);
    });
    btn2->SetClickCallback(UI_CALLBACK{
        vinput->ShowAll();
        cfbtn1->Hide();
        cfbtn2->Enable();
        relbtn->Enable();
    });
    dinput1->SetInputCallback(UI_CALLBACK{
        rdate.month=dinput1->GetText();
    });
    dinput2->SetInputCallback(UI_CALLBACK{
        rdate.week=dinput2->GetText();
    });
    dinput3->SetInputCallback(UI_CALLBACK{
        rdate.date=dinput3->GetText();
    });
    input2->SetInputCallback(UI_CALLBACK{
       std::string tmp=input2->GetText();
       std::replace(tmp.begin(),tmp.end(),':','-'); 
       rtime=tmp;//不确定
    });
    idinput->SetInputCallback(UI_CALLBACK{
        idandphone.id=idinput->GetText();
    });
    phinput->SetInputCallback(UI_CALLBACK{
        idandphone.phone=phinput->GetText();
    });
    btn1->SetClickCallback(UI_CALLBACK{
        if(std::string(rdate)=="")
        {
            glabel->SetContent("日期不能为空");
            glabel->Show();
        }
        if(rtime=="")
        {
            SwitchTo(new lab::ReserveTimeList);
        }
        SwitchTo(new lab::Request);
    });
    btn3->SetClickCallback(UI_CALLBACK{
        btn2->Hide();
        vinput->ShowAll();
        cfbtn1->Enable();
        cfbtn2->Hide();
        hbox->HideAll();
        relbtn->Enable();
    });
    cfbtn1->SetClickCallback(UI_CALLBACK{
        SwitchTo(new lab::Cancel);
    });
    cfbtn2->SetClickCallback(UI_CALLBACK{
        SwitchTo(new lab::ReserveStatusList);
    });
    relbtn->SetClickCallback(UI_CALLBACK{
        vinput->HideAll();
        btn2->Show();
    });
}

void lab::EnterReserve::Ready(ui::Screen *screen) noexcept
{
    hbox->HideAll();
    vinput->HideAll();
    cfbtn1->Enable(false);
    cfbtn2->Enable(false);
    relbtn->Enable(false);
}

void lab::ReserveTimeList::Load(ui::Screen *screen) noexcept
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
            backbtn = new ui::Button; {
                backbtn->AddTo(flat);
                backbtn->SetPreset(ui::Control::Preset::WRAP_AT_FRONT);
                backbtn->SetCaption("返回");//private
            }
            vsbox = new ui::VerticalScrollingBox;{
                vsbox->AddTo(flat);
                vsbox->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                vsbox->SetSize(ui::Control::Direction::HORIZONTAL,90);
                vsbox->SetSize(ui::Control::Direction::VERTICAL, 80);
            }
        }
    }
}

void lab::ReserveTimeList::Logic(ui::Screen *screen) noexcept
{
    backbtn->SetClickCallback(UI_CALLBACK{
        SwitchTo(new lab::EnterReserve);
    });
}

void lab::ReserveTimeList::Ready(ui::Screen *screen) noexcept
{
    Listen(new trm::Sender({trm::rqs::CHECK_TIME,rdate}),SD_CALLBACK{
        if(reply[0]==trm::rpl::FAIL){
            auto glabel = new ui::Label;{
                glabel->AddTo(vsbox);
                glabel->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                glabel->SetContent("没有预约存在");
            }
        }
        else{
            for(int i=1;i<reply.size();i++)
            {
                auto hbox = new ui::HorizontalBox; {
                    hbox->AddTo(vsbox);
                    hbox->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                    hbox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    hbox->SetGap(50);
                }
                auto reservereply=trm::Split(reply[i],' ');
                {
                    auto label0 = new ui::Label;{
                        label0->AddTo(hbox);
                        label0->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        label0->SetContent("日期:"+reservereply[0]);
                    }
                    auto label1 = new ui::Label;{
                        label1->AddTo(hbox);
                        label1->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        label1->SetContent("时间:"+reservereply[1]);
                    }
                    auto label2 = new ui::Label;{
                        label2->AddTo(hbox);
                        label2->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        label2->SetContent("剩余人数:"+reservereply[2]);
                    }
                }
            }
        }});
}

void lab::ReserveStatusList::Load(ui::Screen *screen) noexcept
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
            backbtn = new ui::Button; {
                backbtn->AddTo(flat);
                backbtn->SetPreset(ui::Control::Preset::WRAP_AT_FRONT);
                backbtn->SetCaption("返回");//private
            }
            vsbox = new ui::VerticalScrollingBox;{
                vsbox->AddTo(flat);
                vsbox->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                vsbox->SetSize(ui::Control::Direction::HORIZONTAL,90);
                vsbox->SetSize(ui::Control::Direction::VERTICAL, 80);
            }
        }
    }
}

void lab::ReserveStatusList::Logic(ui::Screen *screen)noexcept
{
    backbtn->SetClickCallback(UI_CALLBACK{
        SwitchTo(new lab::EnterReserve);
    });
}

void lab::ReserveStatusList::Ready(ui::Screen *screen)noexcept
{
    Listen(new trm::Sender({trm::rqs::CHECK_RESERVE_STATUS_LIST,idandphone.id,idandphone.phone}),SD_CALLBACK{
        if(reply[0]==trm::rpl::FAIL){//timeout
            auto glabel = new ui::Label;{
                glabel->AddTo(vsbox);
                glabel->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                glabel->SetContent("没有预约记录");
            }
        }
        else{
            for(int i=1;i<reply.size();i++)
            {
                auto hbox = new ui::HorizontalBox; {
                    hbox->AddTo(vsbox);
                    hbox->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                    hbox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    hbox->SetGap(50);
                }
                auto reservereply=trm::Split(reply[i],'_');
                {
                    auto label0 = new ui::Label;{
                        label0->AddTo(hbox);
                        label0->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        label0->SetContent("日期:"+reservereply[0]);
                    }
                    auto label1 = new ui::Label;{
                        label1->AddTo(hbox);
                        label1->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        label1->SetContent("时间:"+reservereply[1]);
                    }
                    auto label2 = new ui::Label;{
                        label2->AddTo(hbox);
                        label2->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        label2->SetContent("预约状态:"+reservereply[2]);
                        label2->SetFontSize(20);
                    }
                }
            }
        }});
}

void lab::Request::Load(ui::Screen *screen) noexcept
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
            hbox = new ui::HorizontalBox; {
                hbox->AddTo(flat);
                hbox->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                hbox->SetHSize(80);
                hbox->SetVSize(20);//private
            }
            {
                label0 = new ui::Label; {
                    label0->AddTo(hbox);
                    label0->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                }
                label1 = new ui::Label; {
                    label1->AddTo(hbox);
                    label1->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                }
                label2 = new ui::Label; {
                    label2->AddTo(hbox);
                    label2->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                }
                addbtn =new ui::Button; {
                    addbtn->AddTo(hbox);
                    addbtn->SetHPreset(ui::Control::Preset::WRAP_AT_END);
                    addbtn->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    addbtn->SetCaption("添加预约");//private
                }
            }//private
            vbox = new ui::VerticalBox; {
                vbox->AddTo(flat);
                vbox->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                vbox->SetVSize(30);
                vbox->SetHSize(80);
                vbox->SetVAnchor(50);
            }
            {
                hinput3 =new ui::HorizontalBox();{
                    hinput3->AddTo(vbox);
                    hinput3->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                }
                {
                    auto inlabel3 =new ui::Label;{
                        inlabel3->AddTo(hinput3);
                        inlabel3->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                        inlabel3->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        inlabel3->SetContent("身份证号");
                    }
                    idinput = new ui::InputBox;{
                        idinput->AddTo(hinput3);
                        idinput->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);//private
                    }
                }
                hinput4 =new ui::HorizontalBox();{
                    hinput4->AddTo(vbox);
                    hinput4->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                }
                {
                    auto inlabel4 =new ui::Label;{
                        inlabel4->AddTo(hinput4);
                        inlabel4->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                        inlabel4->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        inlabel4->SetContent("手机号");
                    }
                    phinput =new ui::InputBox;{
                        phinput->AddTo(hinput4);
                        phinput->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);//private
                    }
                }
                cfbtn=new ui::Button;{
                    cfbtn->AddTo(vbox);
                    cfbtn->SetPreset(ui::Control::Preset::WRAP_AT_END);
                    cfbtn->SetCaption("确认");
                }
            }
            rpllabel = new ui::Label; {
                rpllabel->AddTo(flat);
                rpllabel->SetPreset(ui::Control::Preset::PLACE_AT_END);//maybe
                rpllabel->SetHSize(600);
                rpllabel->SetVSize(100);
                rpllabel->SetHAnchor(95);
                rpllabel->SetVAnchor(95);
            }//private
            backbtn = new ui::Button; {
                backbtn->AddTo(flat);
                backbtn->SetPreset(ui::Control::Preset::WRAP_AT_FRONT);
                backbtn->SetCaption("返回");//private
            }
            glabel = new ui::Label; {
                glabel->AddTo(flat);
                glabel->SetHPreset(ui::Control::Preset::WRAP_AT_CENTER);
                glabel->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                glabel->SetVAnchor(25);
                glabel->SetSizeWrap(ui::Control::Direction::HORIZONTAL, false);
                glabel->SetHSize(700);//private
            }

        }
    }
}

void lab::Request::Logic(ui::Screen *screen) noexcept
{
    backbtn->SetClickCallback(UI_CALLBACK{
        SwitchTo(new lab::EnterReserve);
    });
    idinput->SetInputCallback(UI_CALLBACK{
        idandphone.id = idinput->GetText();
    });
    phinput->SetInputCallback(UI_CALLBACK{
        idandphone.phone = phinput->GetText();
    });
    addbtn->SetClickCallback(UI_CALLBACK{
        vbox->ShowAll();
        cfbtn->Enable();
        hbox->HideAll();
    });
    cfbtn->SetClickCallback(UI_CALLBACK{
        cfbtn->Enable(false);
        vbox->HideAll();
        hbox->ShowAll();
        glabel->Show();
        rpllabel->Show(); 
        Listen(new trm::Sender({trm::rqs::REQUEST_RESERVE, rdate, rtime,idandphone.id,idandphone.phone}), SD_CALLBACK{
            if(reply[0] == trm::rpl::FAIL && reply[1] == trm::rpl::NO_MATCH_TIME)
            {
                rpllabel->SetContent("该时间不在可预约的时间段中");
            }
            else if(reply[0] == trm::rpl::FAIL && reply[1] == trm::rpl::NO_LEFT_RESERVE)
            {
                rpllabel->SetContent("该预约时间名额已满");
            }
            else if(reply[0]==trm::rpl::FAIL&&reply[1]==trm::rpl::RESERVE_EXISTS)
            {
               rpllabel->SetContent("该预约已存在");
            }
            else
            {
               rpllabel->SetContent("预约成功"); 
            }
        });
    });
}
// 还是push不上
void lab::Request::Ready(ui::Screen *screen) noexcept
{
    vbox->HideAll();
    cfbtn->Enable(false);
    Listen(new trm::Sender({trm::rqs::CHECK_RESERVE_TIME,rdate,rtime}),SD_CALLBACK{
           if(reply[0]==trm::rpl::NO&&reply[1]==trm::rpl::NO_MATCH_TIME) 
           {
               glabel->SetContent("该时间不在可预约的时间段中");
               glabel->Show();
               hbox->HideAll();
           }
           else if(reply[0]==trm::rpl::NO&&reply[1]==trm::rpl::NO_LEFT_RESERVE)
           {
               glabel->SetContent("该预约时间名额已满");
               glabel->Show(); 
               hbox->HideAll();
           }
           else{
            label0->SetContent("日期:"+reply[1]); // 待改善
            label1->SetContent("时间:"+reply[2]);
            label2->SetContent("剩余名额:"+reply[3]);
           }
        });
}

void lab::Cancel::Load(ui::Screen *screen) noexcept
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
            hbox = new ui::HorizontalBox; {
                hbox->AddTo(flat);
                hbox->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                hbox->SetHSize(80);
                hbox->SetVSize(20);//private
            }
            {
                label0 = new ui::Label; {
                    label0->AddTo(hbox);
                    label0->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                }
                label1 = new ui::Label; {
                    label1->AddTo(hbox);
                    label1->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                }
                label2 = new ui::Label; {
                    label2->AddTo(hbox);
                    label2->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                }
                debtn =new ui::Button; {
                    debtn->AddTo(hbox);
                    debtn->SetHPreset(ui::Control::Preset::WRAP_AT_END);
                    debtn->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    debtn->SetCaption("取消预约");//private
                }
            }//private
            vbox = new ui::VerticalBox; {
                vbox->AddTo(flat);
                vbox->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                vbox->SetVSize(30);
                vbox->SetHSize(80);
                vbox->SetVAnchor(50);
            }
            {
                hinput3 =new ui::HorizontalBox();{
                    hinput3->AddTo(vbox);
                    hinput3->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                }
                {
                    auto inlabel3 =new ui::Label;{
                        inlabel3->AddTo(hinput3);
                        inlabel3->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                        inlabel3->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        inlabel3->SetContent("身份证号");
                    }
                    idinput = new ui::InputBox;{
                        idinput->AddTo(hinput3);
                        idinput->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);//private
                    }
                }
                hinput4 =new ui::HorizontalBox();{
                    hinput4->AddTo(vbox);
                    hinput4->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                }
                {
                    auto inlabel4 =new ui::Label;{
                        inlabel4->AddTo(hinput4);
                        inlabel4->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                        inlabel4->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        inlabel4->SetContent("手机号");
                    }
                    phinput =new ui::InputBox;{
                        phinput->AddTo(hinput4);
                        phinput->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);//private
                    }
                }
                cfbtn=new ui::Button;{
                    cfbtn->AddTo(vbox);
                    cfbtn->SetPreset(ui::Control::Preset::WRAP_AT_END);
                    cfbtn->SetCaption("确认");
                }
            }
            rpllabel = new ui::Label; {
                rpllabel->AddTo(flat);
                rpllabel->SetPreset(ui::Control::Preset::PLACE_AT_END);//maybe
                rpllabel->SetHSize(600);
                rpllabel->SetVSize(100);
                rpllabel->SetHAnchor(95);
                rpllabel->SetVAnchor(95);
            }//private
            backbtn = new ui::Button; {
                backbtn->AddTo(flat);
                backbtn->SetPreset(ui::Control::Preset::WRAP_AT_FRONT);
                backbtn->SetCaption("返回");//private
            }
            glabel = new ui::Label; {
                glabel->AddTo(flat);
                glabel->SetHPreset(ui::Control::Preset::WRAP_AT_CENTER);
                glabel->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                glabel->SetVAnchor(25);
                glabel->SetSizeWrap(ui::Control::Direction::HORIZONTAL, false);
                glabel->SetHSize(700);//private
            }

        }
    }
}

void lab::Cancel::Logic(ui::Screen *screen) noexcept
{
    backbtn->SetClickCallback(UI_CALLBACK{
        SwitchTo(new lab::EnterReserve);
    });
    idinput->SetInputCallback(UI_CALLBACK{
        idandphone.id = idinput->GetText();
    });
    phinput->SetInputCallback(UI_CALLBACK{
        idandphone.phone = phinput->GetText();
    });
    debtn->SetClickCallback(UI_CALLBACK{
        vbox->ShowAll();
        cfbtn->Enable();
        hbox->HideAll();
    });
    cfbtn->SetClickCallback(UI_CALLBACK{
        cfbtn->Enable(false);
        vbox->HideAll();
        hbox->ShowAll();
        glabel->Show();
        rpllabel->Show(); 
        Listen(new trm::Sender({trm::rqs::CANCEL_RESERVE, rdate, rtime,idandphone.id,idandphone.phone}), SD_CALLBACK{
            if(reply[0] == trm::rpl::FAIL && reply[1] == trm::rpl::NO_MATCH_RESERVE)
            {
                rpllabel->SetContent("待删除预约不存在");
            }
            else if(reply[0] == trm::rpl::FAIL && reply[1] == trm::rpl::NO_DERESERVE_ACCESS)
            {
                rpllabel->SetContent("无取消预约权限");
            }
            else
            {
               rpllabel->SetContent("取消成功"); 
            }
        });
    });
}

void lab::Cancel::Ready(ui::Screen *screen) noexcept
{
    vbox->HideAll();
    cfbtn->Enable(false);
    Listen(new trm::Sender({trm::rqs::CHECK_RESERVE_STATUS,rdate,rtime,idandphone.id,idandphone.phone}),SD_CALLBACK{
        if(reply[0]==trm::rpl::FAIL)
            {
                glabel->SetContent("查询的预约不存在");//不对劲
            }
        else{
            label0->SetContent("日期:"+reply[1]);
            label1->SetContent("时间:"+reply[2]);
            label2->SetContent("预约状态:"+reply[3]);
            label2->SetFontSize(20);//这几个label要清空,能清空吗
        }
    });

}