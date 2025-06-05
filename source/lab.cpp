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
            limit = new ui::Label; {
                limit->AddTo(flat);
                limit->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                limit->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                limit->SetHSize(70);//private
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
                addbtn->SetVAnchor(25);
                addbtn->SetCaption("我要选课");//private
            }
            debtn = new ui::Button;{
                debtn->AddTo(flat);
                debtn->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                debtn->SetVAnchor(35);
                debtn->SetCaption("我要退课");//private
            }
            btn2 = new ui::Button;{
                    btn2->AddTo(flat);
                    btn2->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                    btn2->SetCaption("查看全部课程");//private
                    btn2->SetVAnchor(70);
            }
            admaddbtn = new ui::Button; {
                admaddbtn->AddTo(flat);
                admaddbtn->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                admaddbtn->SetCaption("我要开课");//private
                admaddbtn->SetVAnchor(45);
            }
            admdebtn = new ui::Button; {
                admdebtn->AddTo(flat);
                admdebtn->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                admdebtn->SetCaption("我要撤课");//private
                admdebtn->SetVAnchor(55);
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
    });
    input->SetBeginCallback(UI_CALLBACK{
        glabel->SetContent("请输入课程代号");
        glabel->Show();
    });
    input->SetExceedLimitCallback(UI_CALLBACK{
        limit->SetContent("课程代号只能是由字母和数字组成的六个字符");
        limit->Show();
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
        if (reply[0] == trm::rpl::TIME_OUT) {
            glabel->SetContent("服务端未响应，请检查后重试");
            glabel->Show();
        }
        else if(reply[0] == trm::rpl::NO) {
            glabel->SetContent("无匹配课程,请重新输入");
            glabel->Show();
        }
        else {
            btn2->Hide();
            addbtn->Hide();
            debtn->Hide();
            hbox->ShowAll();
            admaddbtn->Hide();
            admdebtn->Hide();
            tempbackbtn->Enable();
            auto coursereply=trm::Split(reply[2]);
            label0->SetContent("课程编号:"+reply[1]);
            label1->SetContent("课程名称:"+coursereply[0]);
            label2->SetContent("上课老师:"+coursereply[1]);
            label3->SetContent("上课地点:"+coursereply[2]);
            label4->SetContent("上课周数:"+coursereply[3]);
            label4->SetMaxCount(10);//待改善
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
        if(admadd)
        {
            admaddbtn->Show();
        }
        if(admde)
        {
            admdebtn->Show();
        }
    });
    admaddbtn->SetClickCallback(UI_CALLBACK{
        SwitchTo(new lab::AdmAddCourse);
    });
    admdebtn->SetClickCallback(UI_CALLBACK{
        SwitchTo(new lab::AdmDeleteCourse);
    });
}

void lab::EnterCourse::Ready(ui::Screen *screen) noexcept
{
    hbox->HideAll();
    tempbackbtn->Enable(false);
    auto add=std::find(account.access.begin(),account.access.end(),trm::acc::ADM_ADD_COUR);
    auto del=std::find(account.access.begin(),account.access.end(),trm::acc::ADM_DELETE_COUR);
    auto adm = std::find(account.access.begin(), account.access.end(), trm::acc::ADM);
    if(adm!=account.access.end()) {
        admaddbtn->Show();
        admdebtn->Show();
        admadd=true;
        admde=true;
    }
    else if(add!=account.access.end() ) {
        admaddbtn->Show();
        admdebtn->Hide();
        admdebtn->Enable(false);
        admadd=true;
    }
    else if(del!=account.access.end()) {
        admaddbtn->Hide();
        admdebtn->Show();
        admaddbtn->Enable(false);
        admde=true;
    }
    else {
        admaddbtn->Hide();
        admdebtn->Hide();
        admaddbtn->Enable(false);
        admdebtn->Enable(false);
    }
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
        if (reply[0] == trm::rpl::TIME_OUT) {
            auto glabel = new ui::Label; {
                glabel->AddTo(vsbox);
                glabel->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                glabel->SetContent("服务端未响应，请检查后重试");
            }
        }
        else if(reply[0] == trm::rpl::FAIL) {
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
                        label4->SetMaxCount(20);//private
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
            limit = new ui::Label; {
                limit->AddTo(flat);
                limit->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                limit->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                limit->SetHSize(70);//private
            }
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
    });
    input->SetBeginCallback(UI_CALLBACK{
        glabel->SetContent("请输入课程代号");
        glabel->Show();
    });
    input->SetExceedLimitCallback(UI_CALLBACK{
        limit->SetContent("课程代号只能是由字母和数字组成的五个字符");
        limit->Show();
    });
    btn1->SetClickCallback(UI_CALLBACK{
        btn1->Enable(false);
        if(coursename=="") 
        {
            glabel->SetContent("课程代号不能为空");
            glabel->Show();
        }
        Listen(new trm::Sender({trm::rqs::ADD_COURSE,account.code,account.hashedPassword,coursename}),SD_CALLBACK{
        if (reply[0] == trm::rpl::TIME_OUT) {
            glabel->SetContent("服务端未响应，请检查后重试");
            glabel->Show();
        }
        else if(reply[0] == trm::rpl::FAIL&&reply[1] == trm::rpl::NO_MATCH_COURSE) {
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
        btn1->Enable();
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
            limit = new ui::Label; {
                limit->AddTo(flat);
                limit->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                limit->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                limit->SetHSize(70);//private
            }
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
    });
    input->SetBeginCallback(UI_CALLBACK{
        glabel->SetContent("请输入课程代号");
        glabel->Show();
    });
    input->SetExceedLimitCallback(UI_CALLBACK{
        limit->SetContent("课程代号只能是由字母和数字组成的五个字符");
        limit->Show();
    });
    btn1->SetClickCallback(UI_CALLBACK{
        btn1->Enable(false);
        if(coursename=="") 
        {
            glabel->SetContent("课程代号不能为空");
            glabel->Show();
        }
        Listen(new trm::Sender({trm::rqs::DELETE_COURSE,account.code,account.hashedPassword,coursename}),SD_CALLBACK{
            if (reply[0] == trm::rpl::TIME_OUT) {
                glabel->SetContent("服务端未响应，请检查后重试");
                glabel->Show();
            }
            else if(reply[0] == trm::rpl::FAIL&&reply[1] == trm::rpl::NO_MATCH_COURSE) {
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
        btn1->Enable();
    }); // 这里的debtn其实是伪debtn
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

void lab::AdmAddCourse::Load(ui::Screen *screen) noexcept
{
    auto mar = new ui::Margin; {
        mar->AddTo(screen);
        mar->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
        mar->SetMargin(200, 200, 200, 200);
    }
    {
            auto vbox1=new ui::VerticalBox; {
                vbox1->AddTo(mar);
                vbox1->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
            }
            {
                backbtn = new ui::Button; {
                    backbtn->AddTo(vbox1);
                    backbtn->SetPreset(ui::Control::Preset::WRAP_AT_FRONT);
                    backbtn->SetCaption("返回");//private
                }
                glabel = new ui::Label; {
                    glabel->AddTo(vbox1);
                    glabel->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    glabel->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                    glabel->SetHSize(70);//private
                }
                auto hbox1 = new ui::HorizontalBox; {
                    hbox1->AddTo(vbox1);
                    hbox1->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                }
                {
                    auto label1 = new ui::Label; {
                        label1->AddTo(hbox1);
                        label1->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                        label1->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        label1->SetContent("课程代号");
                    }
                    input1 = new ui::InputBox; {
                        input1->AddTo(hbox1);
                        input1->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);//private
                    }
                }    
                auto hbox2 = new ui::HorizontalBox; {
                    hbox2->AddTo(vbox1);
                    hbox2->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                }
                {
                    auto label2 = new ui::Label; {
                        label2->AddTo(hbox2);
                        label2->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                        label2->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        label2->SetContent("课程名称");
                    }
                    input2 = new ui::InputBox; {
                        input2->AddTo(hbox2);
                        input2->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);//private
                    }
                }
                auto hbox3 = new ui::HorizontalBox; {
                    hbox3->AddTo(vbox1);
                    hbox3->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                }
                {
                    auto label3 = new ui::Label; {
                        label3->AddTo(hbox3);
                        label3->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                        label3->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        label3->SetContent("上课老师");
                    }
                    input3 = new ui::InputBox; {
                        input3->AddTo(hbox3);
                        input3->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);//private
                    }
                }
                auto hbox4 = new ui::HorizontalBox; {
                    hbox4->AddTo(vbox1);
                    hbox4->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                }
                {
                    auto label4 = new ui::Label; {
                        label4->AddTo(hbox4);
                        label4->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                        label4->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        label4->SetContent("上课地点");
                    }
                    input4 = new ui::InputBox; {
                        input4->AddTo(hbox4);
                        input4->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);//private
                    }
                }
                auto hbox5 = new ui::HorizontalBox; {
                    hbox5->AddTo(vbox1);
                    hbox5->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                }
                {
                    auto label5 = new ui::Label; {
                        label5->AddTo(hbox5);
                        label5->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                        label5->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        label5->SetContent("上课周数");
                    }//待修改
                    wbtn =new ui::Button; {
                        wbtn->AddTo(hbox5);
                        wbtn->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                        wbtn->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        wbtn->SetCaption("请选择周数");//private
                    }
                    hsbox= new ui::HorizontalScrollingBox; {
                        hsbox->AddTo(hbox5);
                        hsbox->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    }
                    {
                       for(int i=1;i<=MAX_WEEK;i++) {
                            auto wbtn = new ui::ToggleButton; {
                                wbtn->AddTo(hsbox);
                                wbtn->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                                wbtn->SetCaption("第"+ToStr(i)+"周");
                            }
                            weeklist.push_back(wbtn); 
                        }
                    }
                }
                limit =new ui::Label; {
                    limit->AddTo(vbox1);
                    limit->SetVPreset(ui::Control::Preset::WRAP_AT_END);
                    limit->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    limit->SetHSize(70);//private
                }
                cfbtn = new ui::Button; {
                    cfbtn->AddTo(vbox1);
                    cfbtn->SetPreset(ui::Control::Preset::WRAP_AT_END);
                    cfbtn->SetCaption("确认");//private
                }
            }
    }
}

void lab::AdmAddCourse::Logic(ui::Screen *screen) noexcept
{
    backbtn->SetClickCallback(UI_CALLBACK{
        SwitchTo(new lab::EnterCourse);
    });
    input1->SetInputCallback(UI_CALLBACK{
        coursename = input1->GetText();
    });
    input1->SetBeginCallback(UI_CALLBACK{
        glabel->SetContent("请输入课程代号");
        glabel->Show();
    });
    input1->SetExceedLimitCallback(UI_CALLBACK{
        limit->SetContent("课程代号只能是由字母和数字组成的五个字符");
        limit->Show();
    });
    input2->SetInputCallback(UI_CALLBACK{
        courseinfo.courseName = input2->GetText();
    });
    input2->SetBeginCallback(UI_CALLBACK{
        glabel->SetContent("请输入课程名称");
        glabel->Show();
    });
    input3->SetInputCallback(UI_CALLBACK{
        courseinfo.teacher = input3->GetText();
    });
    input3->SetBeginCallback(UI_CALLBACK{
        glabel->SetContent("请输入上课老师");
        glabel->Show();
    });
    input4->SetInputCallback(UI_CALLBACK{
        courseinfo.location = input4->GetText();
    });
    input4->SetBeginCallback(UI_CALLBACK{
        glabel->SetContent("请输入上课地点");
        glabel->Show();
    });
    for(auto i:weeklist)
    {
        i->SetToggleCallback(UI_CALLBACK{
            courseinfo.weeks.push_back(i->GetCaption());
        });
    }
    wbtn->SetClickCallback(UI_CALLBACK{
        hsbox->ShowAll();
    });
    cfbtn->SetClickCallback(UI_CALLBACK{
        if(coursename==""||courseinfo.courseName==""||courseinfo.teacher==""||courseinfo.location==""||courseinfo.weeks.empty()) {
            glabel->SetContent("请填写完整信息");
            glabel->Show();
        }
        else {
            Listen(new trm::Sender({trm::rqs::ADM_ADD_COUR,account.code,account.hashedPassword,coursename,courseinfo}),SD_CALLBACK{
                if (reply[0] == trm::rpl::TIME_OUT) { // debug
                    glabel->SetContent("服务端未响应，请检查后重试");
                    glabel->Show();
                }
                else if(reply[0] == trm::rpl::FAIL&&reply[1] == trm::rpl::COURSE_EXISTS) {
                    glabel->SetContent("课程已开设,请重新输入");
                    glabel->Show();
                }
                else if(reply[0]==trm::rpl::ACCESS_DENIED) {
                    glabel->SetContent("权限不足");
                    glabel->Show();
                }
                else {
                    glabel->SetContent("添加成功");
                    glabel->Show();
                }
            });
        }
    });
}

void lab::AdmAddCourse::Ready(ui::Screen *screen) noexcept
{
    hsbox->HideAll();    
}

void lab::AdmDeleteCourse::Load(ui::Screen *screen) noexcept
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
            limit = new ui::Label; {
                limit->AddTo(flat);
                limit->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                limit->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                limit->SetHSize(70);//private
            }
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

void lab::AdmDeleteCourse::Logic(ui::Screen *screen) noexcept
{
    backbtn->SetClickCallback(UI_CALLBACK{
        SwitchTo(new lab::EnterCourse);
    });
    input->SetInputCallback(UI_CALLBACK{
        coursename = input->GetText();
    });
    input->SetBeginCallback(UI_CALLBACK{
        glabel->SetContent("请输入课程代号");
        glabel->Show();
    });
    input->SetExceedLimitCallback(UI_CALLBACK{
        limit->SetContent("课程代号只能是由字母和数字组成的五个字符");
        limit->Show();
    });
    btn1->SetClickCallback(UI_CALLBACK{
        btn1->Enable(false);
        if(coursename=="") 
        {
            glabel->SetContent("课程代号不能为空");
            glabel->Show();
        }
        Listen(new trm::Sender({trm::rqs::ADM_DELETE_COUR,account.code,account.hashedPassword,coursename}),
        SD_CALLBACK{ // debug
            if (reply[0] == trm::rpl::TIME_OUT) {
                glabel->SetContent("服务端未响应，请检查后重试");
                glabel->Show();
            }
            else if(reply[0] == trm::rpl::FAIL&&reply[1] == trm::rpl::NO_MATCH_COURSE) {
                glabel->SetContent("待撤销的课程不存在,请重新输入");
                glabel->Show();
            }
           else if(reply[0]==trm::rpl::ACCESS_DENIED) {
                glabel->SetContent("权限不足");
                glabel->Show();
            }
            else {
                hbox->ShowAll();
                label0->SetContent("课程编号："+reply[1]);
                label1->SetContent("课程名称："+reply[2]);
                debtn->Enable();
            }
        });
        btn1->Enable();
    }); // 这里的debtn其实是伪debtn
    debtn->SetClickCallback(UI_CALLBACK{
        rpllabel->SetContent("删除成功");
        rpllabel->Show();
    });
}

void lab::AdmDeleteCourse::Ready(ui::Screen *screen) noexcept
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
                hbox1->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                hbox1->SetHSize(75);
                hbox1->SetVSize(30);
                hbox1->SetVAnchor(15);

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
                        } // 待修改成可选择的时间
                        {
                            dbtn1 =new ui::Button;{
                                dbtn1->AddTo(vdbox1);
                                dbtn1->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                                dbtn1->SetCaption("月份");
                                dbtn1->SetVSize(10);//private
                            }
                            vsbox1 = new ui::VerticalScrollingBox;{
                                vsbox1->AddTo(vdbox1);
                                vsbox1->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                                vsbox1->SetInsideBoxScrollable(true);
                            }
                            {
                                btn13 = new ui::Button;{
                                    btn13->AddTo(vsbox1);
                                    btn13->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                                    btn13->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                                    btn13->SetCaption("一月");
                                }
                                btn14 = new ui::Button;{
                                    btn14->AddTo(vsbox1);
                                    btn14->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                                    btn14->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                                    btn14->SetCaption("二月");
                                }
                                btn15 = new ui::Button;{
                                    btn15->AddTo(vsbox1);
                                    btn15->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                                    btn15->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                                    btn15->SetCaption("三月");
                                }
                                btn4 = new ui::Button;{
                                    btn4->AddTo(vsbox1);
                                    btn4->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                                    btn4->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                                    btn4->SetCaption("四月");
                                }
                                btn5 = new ui::Button;{
                                    btn5->AddTo(vsbox1);
                                    btn5->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                                    btn5->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                                    btn5->SetCaption("五月");
                                }
                                btn6 = new ui::Button;{
                                    btn6->AddTo(vsbox1);
                                    btn6->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                                    btn6->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                                    btn6->SetCaption("六月");
                                }
                                btn7 = new ui::Button;{
                                    btn7->AddTo(vsbox1);
                                    btn7->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                                    btn7->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                                    btn7->SetCaption("七月");
                                }
                                btn8 = new ui::Button;{
                                    btn8->AddTo(vsbox1);
                                    btn8->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                                    btn8->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                                    btn8->SetCaption("八月");
                                }
                                btn9 = new ui::Button;{
                                    btn9->AddTo(vsbox1);
                                    btn9->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                                    btn9->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                                    btn9->SetCaption("九月");
                                }
                                btn10 = new ui::Button;{
                                    btn10->AddTo(vsbox1);
                                    btn10->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                                    btn10->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                                    btn10->SetCaption("十月");
                                }
                                btn11 = new ui::Button;{
                                    btn11->AddTo(vsbox1);
                                    btn11->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                                    btn11->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                                    btn11->SetCaption("十一月");
                                }
                                btn12 = new ui::Button;{
                                    btn12->AddTo(vsbox1);
                                    btn12->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                                    btn12->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                                    btn12->SetCaption("十二月");
                                }
                                clbtn1 =new ui::Button;{
                                    clbtn1->AddTo(vsbox1);
                                    clbtn1->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                                    clbtn1->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                                    clbtn1->SetCaption("清除");
                                }
                            }
                        }
                        auto vdbox2 =new ui::VerticalBox;{
                            vdbox2->AddTo(hinput1);
                            vdbox2->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        }
                        {
                            dbtn2 =new ui::Button;{
                                dbtn2->AddTo(vdbox2);
                                dbtn2->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                                dbtn2->SetCaption("周数");
                                dbtn2->SetVSize(10);//private
                            }
                            vsbox2 = new ui::VerticalScrollingBox;{
                                vsbox2->AddTo(vdbox2);
                                vsbox2->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                                vsbox2->SetInsideBoxScrollable(true);
                            }
                            {
                               btn20=new ui::Button;{
                                btn20->AddTo(vsbox2);
                                btn20->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                                btn20->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                                btn20->SetCaption("第一周");
                               } 
                               btn21=new ui::Button;{
                                btn21->AddTo(vsbox2);
                                btn21->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                                btn21->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                                btn21->SetCaption("第二周");
                               }
                               btn22=new ui::Button;{
                                btn22->AddTo(vsbox2);
                                btn22->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                                btn22->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                                btn22->SetCaption("第三周");
                               }
                               btn23=new ui::Button;{
                                btn23->AddTo(vsbox2);
                                btn23->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                                btn23->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                                btn23->SetCaption("第四周");
                               }
                               clbtn2 =new ui::Button;{
                                clbtn2->AddTo(vsbox2);
                                clbtn2->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                                clbtn2->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER); 
                                clbtn2->SetCaption("清除");
                               }
                            }
                        }
                        auto vdbox3 =new ui::VerticalBox;{
                            vdbox3->AddTo(hinput1);
                            vdbox3->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        }
                        {
                            dbtn3 =new ui::Button;{
                                dbtn3->AddTo(vdbox3);
                                dbtn3->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                                dbtn3->SetCaption("星期几");
                                dbtn3->SetVSize(10);//private
                            }
                            vsbox3 = new ui::VerticalScrollingBox;{
                                vsbox3->AddTo(vdbox3);
                                vsbox3->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                                vsbox3->SetInsideBoxScrollable(true);
                            }
                            {
                                btn30=new ui::Button;{
                                    btn30->AddTo(vsbox3);
                                    btn30->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                                    btn30->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                                    btn30->SetCaption("星期一");
                                }
                                btn31=new ui::Button;{
                                    btn31->AddTo(vsbox3);
                                    btn31->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                                    btn31->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                                    btn31->SetCaption("星期二");
                                }
                                btn32=new ui::Button;{
                                    btn32->AddTo(vsbox3);
                                    btn32->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                                    btn32->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                                    btn32->SetCaption("星期三");
                                }
                                btn33=new ui::Button;{
                                    btn33->AddTo(vsbox3);
                                    btn33->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                                    btn33->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                                    btn33->SetCaption("星期四");
                                }
                                btn34=new ui::Button;{
                                    btn34->AddTo(vsbox3);
                                    btn34->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                                    btn34->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                                    btn34->SetCaption("星期五");
                                }
                                btn35=new ui::Button;{
                                    btn35->AddTo(vsbox3);
                                    btn35->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                                    btn35->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                                    btn35->SetCaption("星期六");
                                }
                                btn36=new ui::Button;{
                                    btn36->AddTo(vsbox3);
                                    btn36->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                                    btn36->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                                    btn36->SetCaption("星期日");
                                }
                                clbtn3 =new ui::Button;{
                                    clbtn3->AddTo(vsbox3);
                                    clbtn3->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                                    clbtn3->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                                    clbtn3->SetCaption("清除");
                                }
                            }
                        }
                    }
                    auto hinput2 =new ui::HorizontalBox();{
                        hinput2->AddTo(vbox2);
                        hinput2->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        hinput2->SetVSize(15);
                    }
                    {
                        auto inlabel2 =new ui::Label;{
                            inlabel2->AddTo(hinput2);
                            inlabel2->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                            inlabel2->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                            inlabel2->SetContent("时间");
                        }
                        tbtn =new ui::Button;{
                            tbtn->AddTo(hinput2);
                            tbtn->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                            tbtn->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                            tbtn->SetCaption("请选择时间");//private
                        }
                        hsbox = new ui::HorizontalScrollingBox;{
                            hsbox->AddTo(hinput2);
                            hsbox->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                            hsbox->SetInsideBoxScrollable(true);
                        }
                        {
                        int min=9;
                        for(int i = 0; i < MAX_TIMES; ++i) {
                            auto btn = new ui::Button;{
                                btn->AddTo(hsbox);
                                btn->SetHPreset(ui::Control::Preset::WRAP_AT_CENTER);
                                btn->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                            }
                            if(i%2 == 0)
                            {
                                btn->SetCaption(ToStr(min) + ":00");
                            }
                            else
                            {
                                btn->SetCaption(ToStr(min) + ":30");
                                min++;
                            }
                            times.push_back(btn);
                        }
                        auto clbtn = new ui::Button;{
                            clbtn->AddTo(hsbox);
                            clbtn->SetHPreset(ui::Control::Preset::WRAP_AT_CENTER);
                            clbtn->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                            clbtn->SetName("clbtn");
                            clbtn->SetCaption("清除");
                        }
                        times.push_back(clbtn);
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
                btn2->SetVAnchor(45);
                btn2->SetCaption("查看预约列表"); // 可能要稍作修改
            } //private
            admaddbtn = new ui::Button;{
                admaddbtn->AddTo(flat);
                admaddbtn->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                admaddbtn->SetVAnchor(55);
                admaddbtn->SetCaption("添设预约"); // private
            }
            admdebtn = new ui::Button;{
                admdebtn->AddTo(flat);
                admdebtn->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                admdebtn->SetVAnchor(65);
                admdebtn->SetCaption("撤销预约"); // private
            }
            modifybtn1 = new ui::Button;{
                modifybtn1->AddTo(flat);
                modifybtn1->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                modifybtn1->SetVAnchor(75);
                modifybtn1->SetCaption("修改可预约数量"); // private
            }
            modifybtn2 = new ui::Button;{
                modifybtn2->AddTo(flat);
                modifybtn2->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                modifybtn2->SetVAnchor(85);
                modifybtn2->SetCaption("修改预约状态"); // private
            }
            vinput =new ui::VerticalBox();{
                vinput->AddTo(flat);
                vinput->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                vinput->SetVSize(30);
                vinput->SetHSize(80);
                vinput->SetVAnchor(60);
            }
            {
                auto hinput3 =new ui::HorizontalBox();{
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
                auto hinput4 =new ui::HorizontalBox();{
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
                limit2 = new ui::Label;{
                    limit2->AddTo(vinput);
                    limit2->SetVPreset(ui::Control::Preset::WRAP_AT_END);
                    limit2->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    limit2->SetHSize(70);//private
                }
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
        btn2->Hide();
        vinput->ShowAll();
        cfbtn1->Hide();
        cfbtn1->Enable(false);
        cfbtn2->Enable();
        relbtn->Enable();
        admaddbtn->Hide();
        admdebtn->Hide();
        modifybtn1->Hide();
        modifybtn2->Hide();
    });
    dbtn1->SetClickCallback(UI_CALLBACK{
        vsbox1->ShowAll();
    });
    dbtn2->SetClickCallback(UI_CALLBACK{
        vsbox2->ShowAll();
    });
    dbtn3->SetClickCallback(UI_CALLBACK{
        vsbox3->ShowAll();
    });
    tbtn->SetClickCallback(UI_CALLBACK{
        hsbox->ShowAll();
    });
    for(auto i:times)
    {
        i->SetClickCallback(UI_CALLBACK{
            if(i->GetName()=="clbtn")
            {
                rtime="";
                tbtn->SetCaption("请选择时间");
                hsbox->HideAll();
            }
            else
            {
            rtime = i->GetCaption();
            tbtn->SetCaption("已选择时间：" + rtime);
            std::replace(rtime.begin(), rtime.end(), ':', '_');
            hsbox->HideAll();
            }
        });
    }
    idinput->SetInputCallback(UI_CALLBACK{
        idandphone.id=idinput->GetText();
    });
    idinput->SetBeginCallback(UI_CALLBACK{
        glabel->SetContent("请输入身份证号");
        glabel->Show();
    });
    idinput->SetExceedLimitCallback(UI_CALLBACK{
        limit2->SetContent("身份证号只能是18位数字或17位数字加字母X");
        limit2->Show();
    });
    phinput->SetInputCallback(UI_CALLBACK{
        idandphone.phone=phinput->GetText();
    });
    phinput->SetBeginCallback(UI_CALLBACK{
        glabel->SetContent("请输入手机号");
        glabel->Show();
    });
    phinput->SetExceedLimitCallback(UI_CALLBACK{
        limit2->SetContent("手机号只能是11位数字");
        limit2->Show();
    });
    btn1->SetClickCallback(UI_CALLBACK{
        if(ToStr(rdate)=="")
        {
            glabel->SetContent("日期不能为空");
            glabel->Show();
        }
        else if(rtime=="")
        {
            SwitchTo(new lab::ReserveTimeList);
        }
        else
        {
            SwitchTo(new lab::Request);
        }
    });
    btn3->SetClickCallback(UI_CALLBACK{
        btn2->Hide();
        admaddbtn->Hide();
        admdebtn->Hide();
        modifybtn1->Hide();
        modifybtn2->Hide();
        vinput->ShowAll();
        cfbtn1->Enable();
        cfbtn2->Hide();
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
        glabel->SetContent("");
        if(isadmadd)
        {
            admaddbtn->Show();
        }
        if(isadmde)
        {
            admdebtn->Show();
        }
        if(isadmmodifyn)
        {
            modifybtn1->Show();
        }
        if(isadmmodifys)
        {
            modifybtn2->Show();
        }
    });
    admaddbtn->SetClickCallback(UI_CALLBACK{
        SwitchTo(new lab::AdmAddReserve);
    });
    admdebtn->SetClickCallback(UI_CALLBACK{
        SwitchTo(new lab::AdmCancelReserve);
    });
    modifybtn1->SetClickCallback(UI_CALLBACK{
        SwitchTo(new lab::AdmCancelReserve);
    });
    modifybtn2->SetClickCallback(UI_CALLBACK{
        SwitchTo(new lab::AdmModifyReserve);
    });
    btn13->SetClickCallback(UI_CALLBACK{
        rdate.month="1";
        vsbox1->HideAll();
        dbtn1->SetCaption("月份：一月");
    });
    btn14->SetClickCallback(UI_CALLBACK{
        rdate.month="2";
        vsbox1->HideAll();
        dbtn1->SetCaption("月份：二月");
    });
    btn15->SetClickCallback(UI_CALLBACK{
        rdate.month="3";
        vsbox1->HideAll();
        dbtn1->SetCaption("月份：三月");
    });
    btn4->SetClickCallback(UI_CALLBACK{
        rdate.month="4";
        vsbox1->HideAll();
        dbtn1->SetCaption("月份：四月");
    });
    btn5->SetClickCallback(UI_CALLBACK{
        rdate.month="5";
        vsbox1->HideAll();
        dbtn1->SetCaption("月份：五月");
    });
    btn6->SetClickCallback(UI_CALLBACK{
        rdate.month="6";
        vsbox1->HideAll();
        dbtn1->SetCaption("月份：六月");
    });
    btn7->SetClickCallback(UI_CALLBACK{
        rdate.month="7";
        vsbox1->HideAll();
        dbtn1->SetCaption("月份：七月");
    });
    btn8->SetClickCallback(UI_CALLBACK{
        rdate.month="8";
        vsbox1->HideAll();
        dbtn1->SetCaption("月份：八月");
    });
    btn9->SetClickCallback(UI_CALLBACK{
        rdate.month="9";
        vsbox1->HideAll();
        dbtn1->SetCaption("月份：九月");
    });
    btn10->SetClickCallback(UI_CALLBACK{
        rdate.month="10";
        vsbox1->HideAll();
        dbtn1->SetCaption("月份：十月");
    });
    btn11->SetClickCallback(UI_CALLBACK{
        rdate.month="11";
        vsbox1->HideAll();
        dbtn1->SetCaption("月份：十一月");
    });
    btn12->SetClickCallback(UI_CALLBACK{
        rdate.month="12";
        vsbox1->HideAll();
        dbtn1->SetCaption("月份：十二月");
    });
    btn20->SetClickCallback(UI_CALLBACK{
        rdate.week="1";
        vsbox2->HideAll();
        dbtn2->SetCaption("周数：第一周");
    });
    btn21->SetClickCallback(UI_CALLBACK{
        rdate.week="2";
        vsbox2->HideAll();
        dbtn2->SetCaption("周数：第二周");
    });
    btn22->SetClickCallback(UI_CALLBACK{
        rdate.week="3";
        vsbox2->HideAll();
        dbtn2->SetCaption("周数：第三周");
    });
    btn23->SetClickCallback(UI_CALLBACK{
        rdate.week="4";
        vsbox2->HideAll();
        dbtn2->SetCaption("周数：第四周");
    });
    btn30->SetClickCallback(UI_CALLBACK{
        rdate.date="1";
        vsbox3->HideAll();
        dbtn3->SetCaption("星期：星期一");
    });
    btn31->SetClickCallback(UI_CALLBACK{
        rdate.date="2";
        vsbox3->HideAll();
        dbtn3->SetCaption("星期：星期二");
    });
    btn32->SetClickCallback(UI_CALLBACK{
        rdate.date="3";
        vsbox3->HideAll();
        dbtn3->SetCaption("星期：星期三");
    });
    btn33->SetClickCallback(UI_CALLBACK{
        rdate.date="4";
        vsbox3->HideAll();
        dbtn3->SetCaption("星期：星期四");
    });
    btn34->SetClickCallback(UI_CALLBACK{
        rdate.date="5";
        vsbox3->HideAll();
        dbtn3->SetCaption("星期：星期五");
    });
    btn35->SetClickCallback(UI_CALLBACK{
        rdate.date="6";
        vsbox3->HideAll();
        dbtn3->SetCaption("星期：星期六");
    });
    btn36->SetClickCallback(UI_CALLBACK{
        rdate.date="7";
        vsbox3->HideAll();
        dbtn3->SetCaption("星期：星期日");
    });
    clbtn1->SetClickCallback(UI_CALLBACK{
        rdate.month="";
        vsbox1->HideAll();
        dbtn1->SetCaption("月份");
    });
    clbtn2->SetClickCallback(UI_CALLBACK{
        rdate.week="";
        vsbox2->HideAll();
        dbtn2->SetCaption("周数");
    });
    clbtn3->SetClickCallback(UI_CALLBACK{
        rdate.date="";
        vsbox3->HideAll();
        dbtn3->SetCaption("星期");
    });
}

void lab::EnterReserve::Ready(ui::Screen *screen) noexcept
{
    rtime="";
    vsbox1->HideAll();
    vsbox2->HideAll();
    vsbox3->HideAll();
    vinput->HideAll();
    cfbtn1->Enable(false);
    cfbtn2->Enable(false);
    relbtn->Enable(false);
    admaddbtn->Hide();
    admdebtn->Hide();
    modifybtn1->Hide();
    modifybtn2->Hide();
    admaddbtn->Enable(false);
    admdebtn->Enable(false);
    modifybtn1->Enable(false);
    modifybtn2->Enable(false);
    hsbox->HideAll();
    if(account.code!=""&&account.hashedPassword!="")
    {
    Listen(new trm::Sender({trm::rqs::CHECK_ACCESS,account.code,account.hashedPassword,trm::AccessBox{trm::acc::ADM_ADD_RESERVE_TIME}}),SD_CALLBACK{
        if (reply[0] == trm::rpl::TIME_OUT) {
            glabel->SetContent("服务端未响应，请检查后重试");
            glabel->Show();
        }
        else if(reply[0]==trm::rpl::YES){
            admaddbtn->Enable();
            admaddbtn->Show();
            isadmadd=true;
        }
        else{
            //
        }
    });
    Listen(new trm::Sender({trm::rqs::CHECK_ACCESS,account.code,account.hashedPassword,trm::AccessBox{trm::acc::ADM_DELETE_RESERVE_TIME}}),SD_CALLBACK{
        if (reply[0] == trm::rpl::TIME_OUT) {
            glabel->SetContent("服务端未响应，请检查后重试");
            glabel->Show();
        }
        else if(reply[0]==trm::rpl::YES){
            admdebtn->Enable();
            admdebtn->Show();
            isadmde=true;
        }
        else{
            //
        }
    });
    Listen(new trm::Sender({trm::rqs::CHECK_ACCESS,account.code,account.hashedPassword,trm::AccessBox{trm::acc::ADM_MODIFTY_RESERVE_NUMBER}}),SD_CALLBACK{
        if (reply[0] == trm::rpl::TIME_OUT) {
            glabel->SetContent("服务端未响应，请检查后重试");
            glabel->Show();
        }
        else if(reply[0]==trm::rpl::YES){
            modifybtn1->Enable();
            modifybtn1->Show();
            isadmmodifyn=true;
        }
        else{
            //
        }
    });
    Listen(new trm::Sender({trm::rqs::CHECK_ACCESS,account.code,account.hashedPassword,trm::AccessBox{trm::acc::ADM_MODIFY_RESERVE_STATUS}}),SD_CALLBACK{
        if (reply[0] == trm::rpl::TIME_OUT) {
            glabel->SetContent("服务端未响应，请检查后重试");
            glabel->Show();
        }
        else if(reply[0]==trm::rpl::YES){
            modifybtn2->Enable();
            modifybtn2->Show();
            isadmmodifys=true;
        }
        else{
            //
        }
    });
    }
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
        if (reply[0] == trm::rpl::TIME_OUT) {
            auto glabel = new ui::Label;{
                glabel->AddTo(vsbox);
                glabel->SetContent("服务端未响应，请检查后重试");
            }
        }
        else if(reply[0]==trm::rpl::FAIL){
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
                        std::replace(reservereply[1].begin(), reservereply[1].end(), '_', ':');
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
        if (reply[0] == trm::rpl::TIME_OUT) {
            auto glabel = new ui::Label;{
                glabel->AddTo(vsbox);
                glabel->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                glabel->SetContent("服务端未响应，请检查后重试");
            }
        }
        else if(reply[0]==trm::rpl::FAIL){//timeout
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
                        std::replace(reservereply[1].begin(), reservereply[1].end(), '_', ':');
                        label1->SetContent("时间:"+reservereply[1]);
                    }
                    auto label2 = new ui::Label;{
                        label2->AddTo(hbox);
                        label2->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        label2->SetContent("预约状态:"+reservereply[2]);
                        label2->SetMaxCount(20);
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
                label = new ui::Label;{
                    label->AddTo(vbox);
                    label->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    label->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                    label->SetHSize(70);
                }
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
                clbtn=new ui::Button;{
                    clbtn->AddTo(vbox);
                    clbtn->SetVPreset(ui::Control::Preset::WRAP_AT_END);
                    clbtn->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                    clbtn->SetCaption("取消");
                }
                limit = new ui::Label; {
                    limit->AddTo(vbox);
                    limit->SetVPreset(ui::Control::Preset::WRAP_AT_END);
                    limit->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    limit->SetHSize(70);//private
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
    idinput->SetBeginCallback(UI_CALLBACK{
        label->SetContent("请输入身份证号");
        label->Show();
    });
    idinput->SetExceedLimitCallback(UI_CALLBACK{
        limit->SetContent("身份证号只能是18位数字或17位数字加字母X");
        limit->Show();
    });
    phinput->SetInputCallback(UI_CALLBACK{
        idandphone.phone = phinput->GetText();
    });
    phinput->SetBeginCallback(UI_CALLBACK{
        label->SetContent("请输入手机号");
        label->Show();
    });
    phinput->SetExceedLimitCallback(UI_CALLBACK{
        limit->SetContent("手机号只能是11位数字");
        limit->Show();
    });
    addbtn->SetClickCallback(UI_CALLBACK{
        vbox->ShowAll();
        cfbtn->Enable();
        clbtn->Enable();
        hbox->HideAll();
    });
    cfbtn->SetClickCallback(UI_CALLBACK{
        cfbtn->Enable(false);
        vbox->HideAll();
        hbox->ShowAll();
        glabel->Show();
        rpllabel->Show(); 
        Listen(new trm::Sender({trm::rqs::REQUEST_RESERVE, rdate, rtime,idandphone.id,idandphone.phone}), SD_CALLBACK{
            if(reply[0] == trm::rpl::TIME_OUT)
            {
                glabel->SetContent("服务端未响应，请检查后重试");
            }
            else if(reply[0] == trm::rpl::FAIL && reply[1] == trm::rpl::NO_MATCH_TIME)
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
    clbtn->SetClickCallback(UI_CALLBACK{
        vbox->HideAll();
        hbox->ShowAll();
        cfbtn->Enable(false);
        clbtn->Enable(false);
    });
}
// 还是push不上
void lab::Request::Ready(ui::Screen *screen) noexcept
{
    vbox->HideAll();
    cfbtn->Enable(false);
    clbtn->Enable(false);
    Listen(new trm::Sender({trm::rqs::CHECK_RESERVE_TIME,rdate,rtime}),SD_CALLBACK{
            if(reply[0] == trm::rpl::TIME_OUT) {
                glabel->SetContent("服务端未响应，请检查后重试");
                glabel->Show();
                hbox->HideAll();
            }
           else if(reply[0]==trm::rpl::NO&&reply[1]==trm::rpl::NO_MATCH_TIME) 
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
            std::string temp = reply[2];
            std::replace(temp.begin(), temp.end(), '_', ':');
            label1->SetContent("时间:"+temp);
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
                label = new ui::Label();{
                    label->AddTo(vbox);
                    label->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    label->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                    label->SetHSize(70);
                }
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
                clbtn=new ui::Button;{
                    clbtn->AddTo(vbox);
                    clbtn->SetVPreset(ui::Control::Preset::WRAP_AT_END);
                    clbtn->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                    clbtn->SetCaption("取消");
                }
                limit = new ui::Label; {
                    limit->AddTo(vbox);
                    limit->SetVPreset(ui::Control::Preset::WRAP_AT_END);
                    limit->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    limit->SetHSize(70);//private
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
    idinput->SetBeginCallback(UI_CALLBACK{
        label->SetContent("请输入身份证号");
        label->Show();
    });
    idinput->SetExceedLimitCallback(UI_CALLBACK{
        limit->SetContent("身份证号只能是18位数字或17位数字加字母X");
        limit->Show();
    });
    phinput->SetInputCallback(UI_CALLBACK{
        idandphone.phone = phinput->GetText();
    });
    phinput->SetBeginCallback(UI_CALLBACK{
        label->SetContent("请输入手机号");
        label->Show();
    });
    phinput->SetExceedLimitCallback(UI_CALLBACK{
        limit->SetContent("手机号只能是11位数字");
        limit->Show();
    });
    debtn->SetClickCallback(UI_CALLBACK{
        vbox->ShowAll();
        cfbtn->Enable();
        clbtn->Enable();
        hbox->HideAll();
    });
    cfbtn->SetClickCallback(UI_CALLBACK{
        cfbtn->Enable(false);
        vbox->HideAll();
        hbox->ShowAll();
        glabel->Show();
        rpllabel->Show(); 
        Listen(new trm::Sender({trm::rqs::CANCEL_RESERVE, rdate, rtime,idandphone.id,idandphone.phone}), SD_CALLBACK{
            if(reply[0] == trm::rpl::TIME_OUT)
            {
                glabel->SetContent("服务端未响应，请检查后重试");
            }
            else if(reply[0] == trm::rpl::FAIL)
            {
                rpllabel->SetContent("待删除预约不存在");
            }
            else if(reply[0] == trm::rpl::NO_DERESERVE_ACCESS)
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
    clbtn->Enable(false);
    Listen(new trm::Sender({trm::rqs::CHECK_RESERVE_STATUS,rdate,rtime,idandphone.id,idandphone.phone}),SD_CALLBACK{
        if(reply[0] == trm::rpl::TIME_OUT) {
            glabel->SetContent("服务端未响应，请检查后重试");
            glabel->Show();
            hbox->HideAll();
        }
        else if(reply[0]==trm::rpl::FAIL)
        {
            glabel->SetContent("查询的预约不存在");//不对劲
        }
        else{
            label0->SetContent("日期:"+reply[1]);
            std::string temp = reply[2];
            std::replace(temp.begin(), temp.end(), '_', ':');
            label1->SetContent("时间:"+temp);
            label2->SetContent("预约状态:"+reply[3]);
            label2->SetMaxCount(20);//这几个label要清空,能清空吗
        }
    });
}

void lab::AdmAddReserve::Load(ui::Screen *screen) noexcept
{
    auto mar = new ui::Margin; {
        mar->AddTo(screen);
        mar->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
        mar->SetMargin(200, 200, 200, 200);
    }
    {
            auto vbox1=new ui::VerticalBox; {
                vbox1->AddTo(mar);
                vbox1->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
            }
            {
                backbtn = new ui::Button; {
                    backbtn->AddTo(vbox1);
                    backbtn->SetPreset(ui::Control::Preset::WRAP_AT_FRONT);
                    backbtn->SetCaption("返回");//private
                }
                glabel = new ui::Label; {
                    glabel->AddTo(vbox1);
                    glabel->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    glabel->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                    glabel->SetHSize(70);//private
                }
                auto hbox1 = new ui::HorizontalBox; {
                    hbox1->AddTo(vbox1);
                    hbox1->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                }
                {
                    auto label1 = new ui::Label; {
                        label1->AddTo(hbox1);
                        label1->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                        label1->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        label1->SetContent("月份");
                    }
                    input1 = new ui::InputBox; {
                        input1->AddTo(hbox1);
                        input1->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);//private
                    }
                }    
                auto hbox2 = new ui::HorizontalBox; {
                    hbox2->AddTo(vbox1);
                    hbox2->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                }
                {
                    auto label2 = new ui::Label; {
                        label2->AddTo(hbox2);
                        label2->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                        label2->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        label2->SetContent("周数");
                    }
                    input2 = new ui::InputBox; {
                        input2->AddTo(hbox2);
                        input2->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);//private
                    }
                }
                auto hbox3 = new ui::HorizontalBox; {
                    hbox3->AddTo(vbox1);
                    hbox3->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                }
                {
                    auto label3 = new ui::Label; {
                        label3->AddTo(hbox3);
                        label3->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                        label3->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        label3->SetContent("星期几");
                    }
                    input3 = new ui::InputBox; {
                        input3->AddTo(hbox3);
                        input3->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);//private
                    }
                }
                auto hbox4 = new ui::HorizontalBox; {
                    hbox4->AddTo(vbox1);
                    hbox4->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                }
                {
                    auto label4 = new ui::Label; {
                        label4->AddTo(hbox4);
                        label4->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                        label4->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        label4->SetContent("时间");//待修改
                    }
                    input4 = new ui::InputBox; {
                        input4->AddTo(hbox4);
                        input4->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);//private
                    }
                }
                auto hbox5 = new ui::HorizontalBox; {
                    hbox5->AddTo(vbox1);
                    hbox5->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                }
                {
                    auto label5 = new ui::Label; {
                        label5->AddTo(hbox5);
                        label5->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                        label5->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        label5->SetContent("可预约人数");//待修改
                    }
                    input5 = new ui::InputBox; {
                        input5->AddTo(hbox5);
                        input5->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);//private
                    }
                }
                cfbtn = new ui::Button; {
                    cfbtn->AddTo(vbox1);
                    cfbtn->SetPreset(ui::Control::Preset::WRAP_AT_END);
                    cfbtn->SetCaption("确认");//private
                }
            }
    }
}

void lab::AdmAddReserve::Logic(ui::Screen *screen) noexcept
{
    backbtn->SetClickCallback(UI_CALLBACK{
        SwitchTo(new lab::EnterReserve);
    });
    input1->SetInputCallback(UI_CALLBACK{
        rdate.month = input1->GetText();
    });
    input1->SetBeginCallback(UI_CALLBACK{
        glabel->SetContent("请输入月份");
        glabel->Show();
    });
    input2->SetInputCallback(UI_CALLBACK{
        rdate.week = input2->GetText();
    });
    input2->SetBeginCallback(UI_CALLBACK{
        glabel->SetContent("请输入周数");
        glabel->Show();
    });
    input3->SetInputCallback(UI_CALLBACK{
        rdate.date = input3->GetText();
    });
    input3->SetBeginCallback(UI_CALLBACK{
        glabel->SetContent("请输入星期几");
        glabel->Show();
    });
    input4->SetInputCallback(UI_CALLBACK{
        auto temp = input4->GetText();
        std::replace(temp.begin(), temp.end(), ':', '_');
        rtime = temp;
    });
    input4->SetBeginCallback(UI_CALLBACK{
        glabel->SetContent("请输入时间");
        glabel->Show();
    });
    input5->SetInputCallback(UI_CALLBACK{
        rnum = input5->GetText();
    });
    input5->SetBeginCallback(UI_CALLBACK{
        glabel->SetContent("请输入可预约人数");
        glabel->Show();
    });
    cfbtn->SetClickCallback(UI_CALLBACK{
        if(ToStr(rdate)==""||rtime==""||rnum=="") {
            glabel->SetContent("请填写完整信息");
            glabel->Show();
        }
        else {
            Listen(new trm::Sender({trm::rqs::ADM_ADD_RESERVE_TIME,account.code,account.hashedPassword,rdate,rtime,rnum}),SD_CALLBACK{
                if (reply[0] == trm::rpl::TIME_OUT) {
                    glabel->SetContent("服务端未响应，请检查后重试");
                    glabel->Show();
                }
                else if(reply[0] == trm::rpl::FAIL) {
                    glabel->SetContent("该预约时间已设置,请重新输入");
                    glabel->Show();
                }
                else if(reply[0]==trm::rpl::ACCESS_DENIED) {
                    glabel->SetContent("权限不足");
                    glabel->Show();
                }
                else {
                    glabel->SetContent("添加成功");
                    glabel->Show();
                }
            });
        }
    });
}

void lab::AdmAddReserve::Ready(ui::Screen *screen) noexcept
{
   ;
}

void lab::AdmCancelReserve::Load(ui::Screen *screen) noexcept
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
            glabel =new ui::Label;{
                glabel->AddTo(flat);
                glabel->SetHPreset(ui::Control::Preset::WRAP_AT_CENTER);
                glabel->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                glabel->SetVAnchor(25);
                glabel->SetSizeWrap(ui::Control::Direction::HORIZONTAL, false);
                glabel->SetHSize(700);//private
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
                        } // 待修改成可选择的时间
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
                btn1 = new ui::Button;{
                    btn1->AddTo(hbox1);
                    btn1->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    btn1->SetHPreset(ui::Control::Preset::WRAP_AT_END);
                    btn1->SetCaption("查找");//private
                }
            }
            hbox2 = new ui::HorizontalBox; {
                hbox2->AddTo(flat);
                hbox2->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                hbox2->SetHSize(80);
                hbox2->SetVSize(40);//private
                hbox2->SetVAnchor(55);
            }
            {
               label0=new ui::Label;{
                    label0->AddTo(hbox2);
                    label0->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
               }
               label1=new ui::Label;{
                    label1->AddTo(hbox2);
                    label1->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
               }
               modifybtn =new ui::Button; { 
                   modifybtn->AddTo(hbox2);
                   modifybtn->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                   modifybtn->SetCaption("修改可预约人数");//private
               }
               debtn =new ui::Button; { 
                   debtn->AddTo(hbox2);
                   debtn->SetHPreset(ui::Control::Preset::WRAP_AT_END);
                   debtn->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                   debtn->SetCaption("撤除预约");//private
               }
            }
            rpllabel = new ui::Label; {
                rpllabel->AddTo(flat);
                rpllabel->SetPreset(ui::Control::Preset::PLACE_AT_END);//maybe
            }//private
            vbox2 = new ui::VerticalBox; {
                vbox2->AddTo(flat);
                vbox2->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                vbox2->SetHSize(50);
                vbox2->SetVSize(40);
                vbox2->SetVAnchor(50);
            }
            {
                nlabel =new ui::Label;{
                    nlabel->AddTo(vbox2);
                    nlabel->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                    nlabel->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                }
                auto hbox5 =new ui::HorizontalBox;{
                    hbox5->AddTo(vbox2);
                    hbox5->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                }
                {
                    auto label5 =new ui::Label;{
                        label5->AddTo(hbox5);
                        label5->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                        label5->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        label5->SetContent("请输入预约人数");
                    } 
                    input =new ui::InputBox;{
                        input->AddTo(hbox5);
                        input->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);//private
                    }
                }
                cfbtn = new ui::Button; {
                    cfbtn->AddTo(vbox2);
                    cfbtn->SetPreset(ui::Control::Preset::WRAP_AT_END);
                    cfbtn->SetCaption("确认");//private
                }
                clbtn =new ui::Button; {
                    clbtn->AddTo(vbox2);
                    clbtn->SetVPreset(ui::Control::Preset::WRAP_AT_END);
                    clbtn->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                    clbtn->SetCaption("取消");//private
                }
            }
        }
    }
}

void lab::AdmCancelReserve::Logic(ui::Screen *screen) noexcept
{
    backbtn->SetClickCallback(UI_CALLBACK{
        SwitchTo(new lab::EnterReserve);
    });
    dinput1->SetInputCallback(UI_CALLBACK{
        rdate.month = dinput1->GetText();
    });
    dinput1->SetBeginCallback(UI_CALLBACK{
        glabel->SetContent("请输入月份");
        glabel->Show();
    });
    dinput2->SetInputCallback(UI_CALLBACK{
        rdate.week = dinput2->GetText();
    });
    dinput2->SetBeginCallback(UI_CALLBACK{
        glabel->SetContent("请输入周数");
        glabel->Show();
    });
    dinput3->SetInputCallback(UI_CALLBACK{
        rdate.date = dinput3->GetText();
    });
    dinput3->SetBeginCallback(UI_CALLBACK{
        glabel->SetContent("请输入星期几");
        glabel->Show();
    });
    input2->SetInputCallback(UI_CALLBACK{
        auto temp = input2->GetText();
        std::replace(temp.begin(), temp.end(), ':', '_');
        rtime= temp;
    });
    input2->SetBeginCallback(UI_CALLBACK{
        glabel->SetContent("请输入时间");
        glabel->Show();
    });
    btn1->SetClickCallback(UI_CALLBACK{
        if(ToStr(rdate)==""||rtime=="") {
            glabel->SetContent("请填写完整信息");
            glabel->Show();
        }
        else {
            Listen(new trm::Sender({trm::rqs::ADM_SEARCH_RESERVE,account.code,account.hashedPassword,rdate,rtime}),SD_CALLBACK{
            if(reply[0] == trm::rpl::TIME_OUT) {
                glabel->SetContent("服务端未响应，请检查后重试");
            }
            else if(reply[0] == trm::rpl::FAIL ) {
                glabel->SetContent("待撤销的预约不存在");
            }
            else if(reply[0] == trm::rpl::ACCESS_DENIED) {
                glabel->SetContent("无撤消预约权限");
            }
            else {
                label0->SetContent("日期:"+reply[1]);
                std::string temp = reply[2];
                std::replace(temp.begin(), temp.end(), '_', ':');// wrong
                label1->SetContent("时间:"+temp);
                nlabel->SetContent("剩余名额:"+reply[3]);
                hbox2->ShowAll();
                modifybtn->Enable();
                debtn->Enable();
            }
        });
        } 
    });
    debtn->SetClickCallback(UI_CALLBACK{
        Listen(new trm::Sender({trm::rqs::ADM_DELETE_RESERVE_TIME,account.code,account.hashedPassword,rdate,rtime}),SD_CALLBACK{
            if(reply[0] == trm::rpl::TIME_OUT) {
                glabel->SetContent("服务端未响应，请检查后重试");
            }
            else if(reply[0] == trm::rpl::FAIL ) {
                glabel->SetContent("待撤销的预约不存在");
            }
            else if(reply[0] == trm::rpl::ACCESS_DENIED) {
                glabel->SetContent("无撤消预约权限");
            }
            else {
              rpllabel->SetContent("撤销成功"); 
            }
        });
    });
    modifybtn->SetClickCallback(UI_CALLBACK{
       vbox2->ShowAll();
       cfbtn->Enable();
       clbtn->Enable();
       hbox2->HideAll();
   });
   input->SetInputCallback(UI_CALLBACK{
         rnum = input->GetText();
   });
   cfbtn->SetClickCallback(UI_CALLBACK{
       if(rnum == "") {
           glabel->SetContent("请输入预约人数");
           glabel->Show();
       }
       else {
           Listen(new trm::Sender({trm::rqs::ADM_MODIFY_RESERVE_NUMBER,account.code,account.hashedPassword,rdate,rtime,rnum}),SD_CALLBACK{
               if(reply[0] == trm::rpl::TIME_OUT) {
                   glabel->SetContent("服务端未响应，请检查后重试");
               }
               else if(reply[0] == trm::rpl::FAIL) {
                   glabel->SetContent("待修改的时间不存在");
               }
               else {
                   rpllabel->SetContent("修改成功");
                   hbox2->ShowAll();
                   vbox2->HideAll();
                   modifybtn->Enable();
                   debtn->Enable();
               }
           });
       }
   });
   clbtn->SetClickCallback(UI_CALLBACK{
       vbox2->HideAll();
       hbox2->ShowAll();
       modifybtn->Enable();
       debtn->Enable();
       cfbtn->Enable(false);
   });
}

void lab::AdmCancelReserve::Ready(ui::Screen *screen) noexcept
{
    hbox2->HideAll();
    vbox2->HideAll();
    modifybtn->Enable(false);
    debtn->Enable(false);
    cfbtn->Enable(false);
    clbtn->Enable(false);
}

void lab::AdmModifyReserve::Load(ui::Screen *screen) noexcept
{
    auto mar = new ui::Margin; {
        mar->AddTo(screen);
        mar->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
        mar->SetMargin(200, 200, 200, 200);
    }
    {
            auto vbox1=new ui::VerticalBox; {
                vbox1->AddTo(mar);
                vbox1->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
            }
            {
                backbtn = new ui::Button; {
                    backbtn->AddTo(vbox1);
                    backbtn->SetPreset(ui::Control::Preset::WRAP_AT_FRONT);
                    backbtn->SetCaption("返回");//private
                }
                glabel = new ui::Label; {
                    glabel->AddTo(vbox1);
                    glabel->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    glabel->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                    glabel->SetHSize(70);//private
                }
                auto hbox1 = new ui::HorizontalBox; {
                    hbox1->AddTo(vbox1);
                    hbox1->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                }
                {
                    auto label1 = new ui::Label; {
                        label1->AddTo(hbox1);
                        label1->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                        label1->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        label1->SetContent("月份");
                    }
                    input1 = new ui::InputBox; {
                        input1->AddTo(hbox1);
                        input1->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);//private
                    }
                }    
                auto hbox2 = new ui::HorizontalBox; {
                    hbox2->AddTo(vbox1);
                    hbox2->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                }
                {
                    auto label2 = new ui::Label; {
                        label2->AddTo(hbox2);
                        label2->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                        label2->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        label2->SetContent("星期");
                    }
                    input2 = new ui::InputBox; {
                        input2->AddTo(hbox2);
                        input2->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);//private
                    }
                }
                auto hbox3 = new ui::HorizontalBox; {
                    hbox3->AddTo(vbox1);
                    hbox3->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                }
                {
                    auto label3 = new ui::Label; {
                        label3->AddTo(hbox3);
                        label3->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                        label3->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        label3->SetContent("日期");
                    }
                    input3 = new ui::InputBox; {
                        input3->AddTo(hbox3);
                        input3->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);//private
                    }
                }
                auto hbox4 = new ui::HorizontalBox; {
                    hbox4->AddTo(vbox1);
                    hbox4->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                }
                {
                    auto label4 = new ui::Label; {
                        label4->AddTo(hbox4);
                        label4->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                        label4->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        label4->SetContent("时间");//待修改
                    }
                    input4 = new ui::InputBox; {
                        input4->AddTo(hbox4);
                        input4->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);//private
                    }
                }
                auto hbox5 = new ui::HorizontalBox; {
                    hbox5->AddTo(vbox1);
                    hbox5->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                }
                {
                    auto label5 = new ui::Label; {
                        label5->AddTo(hbox5);
                        label5->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                        label5->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        label5->SetContent("身份证号");//待修改
                    }
                    input5 = new ui::InputBox; {
                        input5->AddTo(hbox5);
                        input5->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);//private
                    }
                }
                auto hbox6 = new ui::HorizontalBox; {
                    hbox6->AddTo(vbox1);
                    hbox6->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                }
                {
                    auto label6 = new ui::Label; {
                        label6->AddTo(hbox6);
                        label6->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                        label6->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        label6->SetContent("手机号");//待修改
                    }
                    input6 = new ui::InputBox; {
                        input6->AddTo(hbox6);
                        input6->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);//private
                    }
                }
                cfbtn = new ui::Button; {
                    cfbtn->AddTo(vbox1);
                    cfbtn->SetPreset(ui::Control::Preset::WRAP_AT_END);
                    cfbtn->SetCaption("确认修改该人员的预约状态");//private
                }
            }
    }
}

void lab::AdmModifyReserve::Logic(ui::Screen *screen) noexcept
{
    input1->SetInputCallback(UI_CALLBACK{
        rdate.month = input1->GetText();
    });
    input1->SetBeginCallback(UI_CALLBACK{
        glabel->SetContent("请输入月份");
        glabel->Show();
    });
    input2->SetInputCallback(UI_CALLBACK{
        rdate.week = input2->GetText();
    });
    input2->SetBeginCallback(UI_CALLBACK{
        glabel->SetContent("请输入周数");
        glabel->Show();
    });
    input3->SetInputCallback(UI_CALLBACK{
        rdate.date = input3->GetText();
    });
    input3->SetBeginCallback(UI_CALLBACK{
        glabel->SetContent("请输入星期几");
        glabel->Show();
    });
    input4->SetInputCallback(UI_CALLBACK{
        auto temp = input4->GetText();
        std::replace(temp.begin(), temp.end(), ':', '_');
        rtime = temp;
    });
    input4->SetBeginCallback(UI_CALLBACK{
        glabel->SetContent("请输入时间");
        glabel->Show();
    });
    input5->SetInputCallback(UI_CALLBACK{
        idandphone.id = input5->GetText();
    });
    input5->SetBeginCallback(UI_CALLBACK{
        glabel->SetContent("请输入身份证号");
        glabel->Show();
    });
    input6->SetInputCallback(UI_CALLBACK{
        idandphone.phone = input6->GetText();
    });
    input6->SetBeginCallback(UI_CALLBACK{
        glabel->SetContent("请输入手机号");
        glabel->Show();
    });
    backbtn->SetClickCallback(UI_CALLBACK{
        SwitchTo(new lab::EnterReserve);
    });
    cfbtn->SetClickCallback(UI_CALLBACK{
        if(ToStr(rdate) == "" || rtime == "" || idandphone.id == "" || idandphone.phone == "") {
            glabel->SetContent("请填写完整信息");
            glabel->Show();
        }
        else {
            Listen(new trm::Sender({trm::rqs::ADM_MODIFY_RESERVE_STATUS,account.code,account.hashedPassword,idandphone.id,idandphone.phone,rdate,rtime}), SD_CALLBACK{
                if(reply[0] == trm::rpl::TIME_OUT) {
                    glabel->SetContent("服务端未响应，请检查后重试");
                }
                else if(reply[0] == trm::rpl::FAIL) {
                    glabel->SetContent("待修改的预约不存在");
                }
                else if(reply[0] == trm::rpl::ACCESS_DENIED) {
                    glabel->SetContent("无修改预约权限");
                }
                else {
                    glabel->SetContent("修改预约状态成功");
                }
            });
        }
    });
}

void lab::AdmModifyReserve::Ready(ui::Screen *screen) noexcept
{
    ;
}