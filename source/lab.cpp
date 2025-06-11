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
                    input->SetLengthLimit(6);
                    input->SetContentLimit(ui::InputBox::ContentLimit::ALLOW_SPECIAL_CHARACTERS_ONLY);
                    input->SetSpecialCharacters(ui::InputBox::NUMBER+ui::InputBox::LOWER_LETTER+ui::InputBox::UPPER_LETTER);
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
                addbtn->SetHAnchor(10);
                addbtn->SetCaption("我要选课");//private
            }
            debtn = new ui::Button;{
                debtn->AddTo(flat);
                debtn->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                debtn->SetVAnchor(35);
                debtn->SetHAnchor(10);
                debtn->SetCaption("我要退课");//private
            }
            btn2 = new ui::Button;{
                btn2->AddTo(flat);
                btn2->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                btn2->SetCaption("查看全部课程");//private
                btn2->SetVAnchor(70);
                btn2->SetHAnchor(10);
            }
            admaddbtn = new ui::Button; {
                admaddbtn->AddTo(flat);
                admaddbtn->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                admaddbtn->SetCaption("我要开课");//private
                admaddbtn->SetVAnchor(45);
                admaddbtn->SetHAnchor(10);
            }
            admdebtn = new ui::Button; {
                admdebtn->AddTo(flat);
                admdebtn->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                admdebtn->SetCaption("我要撤课");//private
                admdebtn->SetVAnchor(55);
                admdebtn->SetHAnchor(10);
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
    backbtn->SetClickCallback(_UI_CALLBACK_{
        SwitchTo(new eea::MainPage);
    });
    btn2->SetClickCallback(_UI_CALLBACK_{
        SwitchTo(new lab::CourseList);
    });
    input->SetInputCallback(_UI_CALLBACK_{
        coursename = input->GetText();
        
    });
    input->SetBeginCallback(_UI_CALLBACK_{
        glabel->SetContent("请输入课程代号");
        glabel->Show();
    });
    input->SetExceedLimitCallback(_UI_CALLBACK_{
        limit->SetContent("课程代号只能是由字母和数字组成的六个字符");
        limit->Show();
    });
    btn1->SetClickCallback(_UI_CALLBACK_{
        btn1->Enable(false);
       if(coursename=="") 
       {
        SwitchTo(new lab::CourseList);
       }
       else if(coursename.length()!=6) {
           limit->SetContent("课程代号只能是由字母和数字组成的六个字符");
           limit->Show();
       }
       else
       {
        Listen(new trm::Sender({trm::rqs::SEARCH_COURSE_INFORMATION,username,coursename}),_SD_CALLBACK_{
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
            label4->SetMaxCount(15);//待改善
            label4->SetFontSize(30);
        }});
        }
        btn1->Enable();
        }
    );
    addbtn->SetClickCallback(_UI_CALLBACK_{
        SwitchTo(new lab::AddCourse);
    });
    debtn->SetClickCallback(_UI_CALLBACK_{
        SwitchTo(new lab::DeleteCourse);
    });
    tempbackbtn->SetClickCallback(_UI_CALLBACK_{
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
    admaddbtn->SetClickCallback(_UI_CALLBACK_{
        SwitchTo(new lab::AdmAddCourse);
    });
    admdebtn->SetClickCallback(_UI_CALLBACK_{
        SwitchTo(new lab::AdmDeleteCourse);
    });
}

void lab::EnterCourse::Ready(ui::Screen *screen) noexcept
{
    hbox->HideAll();
    tempbackbtn->Enable(false);
    addbtn->Hide();
    debtn->Hide();
    admaddbtn->Hide();
    admdebtn->Hide();
    admadd=false;
    admde=false;
    add=false;
    del=false;
    if(username!=""&&password!=""){
        Listen(new trm::Sender({trm::rqs::CHECK_ACCESS,username,password,trm::AccessBox{trm::acc::ADD_COURSE}}),_SD_CALLBACK_{
            if(reply[0]==trm::rpl::YES){
                addbtn->Show();
                addbtn->Enable();
                add=true;
            }
            else
            {
                ;
            }
        });
        Listen(new trm::Sender({trm::rqs::CHECK_ACCESS,username,password,trm::AccessBox{trm::acc::DELETE_COURSE}}),_SD_CALLBACK_{
            if(reply[0]==trm::rpl::YES)
            {
                debtn->Show();
                debtn->Enable();
                del=true;
            }
            else
            {
                ;
            }
        });
        Listen(new trm::Sender({trm::rqs::CHECK_ACCESS,username,password,trm::AccessBox{trm::acc::ADM_ADD_COUR}}),_SD_CALLBACK_{
            if(reply[0] == trm::rpl::YES) {
                admaddbtn->Show();
                admaddbtn->Enable();
                admadd=true;
            }
            else {
                ;
            }
        });
        Listen(new trm::Sender({trm::rqs::CHECK_ACCESS,username,password,trm::AccessBox{trm::acc::ADM_DELETE_COUR}}),_SD_CALLBACK_{
            if(reply[0] == trm::rpl::YES) {
                admdebtn->Show();
                admdebtn->Enable();
                admde=true;
            }
            else {
                ;
            }
        });
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
    backbtn->SetClickCallback(_UI_CALLBACK_{
        SwitchTo(new lab::EnterCourse);
    });
   
}

void lab::CourseList::Ready(ui::Screen *screen) noexcept
{
    Listen(new trm::Sender({trm::rqs::CHECK_ALL_COURSE,username}),_SD_CALLBACK_{
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
                        label4->SetMaxCount(10);//private
                        label4->SetFontSize(30);
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
                    input->SetLengthLimit(6);
                    input->SetContentLimit(ui::InputBox::ContentLimit::ALLOW_SPECIAL_CHARACTERS_ONLY);
                    input->SetSpecialCharacters(ui::InputBox::NUMBER+ui::InputBox::LOWER_LETTER+ui::InputBox::UPPER_LETTER);
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
    backbtn->SetClickCallback(_UI_CALLBACK_{
        SwitchTo(new lab::EnterCourse);
    });
    input->SetInputCallback(_UI_CALLBACK_{
        coursename = input->GetText();
        
    });
    input->SetBeginCallback(_UI_CALLBACK_{
        glabel->SetContent("请输入课程代号");
        glabel->Show();
    });
    input->SetExceedLimitCallback(_UI_CALLBACK_{
        limit->SetContent("课程代号只能是由字母和数字组成的六个字符");
        limit->Show();
    });
    btn1->SetClickCallback(_UI_CALLBACK_{
        btn1->Enable(false);
        if(coursename=="") 
        {
            glabel->SetContent("课程代号不能为空");
            glabel->Show();
        }
        else if(coursename.length()!=6) {
            limit->SetContent("课程代号只能是由字母和数字组成的六个字符");
            limit->Show();
        }
        else
        {
        Listen(new trm::Sender({trm::rqs::ADD_COURSE,username,password,coursename}),_SD_CALLBACK_{
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
        }
        btn1->Enable();
    });
    addbtn->SetClickCallback(_UI_CALLBACK_{
            rpllabel->SetContent("选课成功");
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
                    input->SetLengthLimit(6);
                    input->SetContentLimit(ui::InputBox::ContentLimit::ALLOW_SPECIAL_CHARACTERS_ONLY);
                    input->SetSpecialCharacters(ui::InputBox::NUMBER+ui::InputBox::LOWER_LETTER+ui::InputBox::UPPER_LETTER);

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
    backbtn->SetClickCallback(_UI_CALLBACK_{
        SwitchTo(new lab::EnterCourse);
    });
    input->SetInputCallback(_UI_CALLBACK_{
        coursename = input->GetText();
        
    });
    input->SetBeginCallback(_UI_CALLBACK_{
        glabel->SetContent("请输入课程代号");
        glabel->Show();
    });
    input->SetExceedLimitCallback(_UI_CALLBACK_{
        limit->SetContent("课程代号只能是由字母和数字组成的六个字符");
        limit->Show();
    });
    btn1->SetClickCallback(_UI_CALLBACK_{
        btn1->Enable(false);
        if(coursename=="") 
        {
            glabel->SetContent("课程代号不能为空");
            glabel->Show();
        }
        else if(coursename.length()!=6) {
            limit->SetContent("课程代号只能是由字母和数字组成的六个字符");
            limit->Show();
        }
        else
        {
        Listen(new trm::Sender({trm::rqs::DELETE_COURSE,username,password,coursename}),_SD_CALLBACK_{
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
        }
        btn1->Enable();
    }); // 这里的debtn其实是伪debtn
    debtn->SetClickCallback(_UI_CALLBACK_{
                rpllabel->SetContent("退课成功");
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
                        input1->SetLengthLimit(6);
                        input1->SetContentLimit(ui::InputBox::ContentLimit::ALLOW_SPECIAL_CHARACTERS_ONLY);
                        input1->SetSpecialCharacters(ui::InputBox::NUMBER+ui::InputBox::LOWER_LETTER+ui::InputBox::UPPER_LETTER);

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
                        hsbox->SetInsideBoxScrollable(true);
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
    backbtn->SetClickCallback(_UI_CALLBACK_{
        SwitchTo(new lab::EnterCourse);
    });
    input1->SetInputCallback(_UI_CALLBACK_{
        coursename = input1->GetText();
        
    });
    input1->SetBeginCallback(_UI_CALLBACK_{
        glabel->SetContent("请输入课程代号");
        glabel->Show();
    });
    input1->SetExceedLimitCallback(_UI_CALLBACK_{
        limit->SetContent("课程代号只能是由字母和数字组成的六个字符");
        limit->Show();
    });
    input2->SetInputCallback(_UI_CALLBACK_{
        courseinfo.courseName = input2->GetText();
    });
    input2->SetBeginCallback(_UI_CALLBACK_{
        glabel->SetContent("请输入课程名称");
        glabel->Show();
    });
    input3->SetInputCallback(_UI_CALLBACK_{
        courseinfo.teacher = input3->GetText();
    });
    input3->SetBeginCallback(_UI_CALLBACK_{
        glabel->SetContent("请输入上课老师");
        glabel->Show();
    });
    input4->SetInputCallback(_UI_CALLBACK_{
        courseinfo.location = input4->GetText();
    });
    input4->SetBeginCallback(_UI_CALLBACK_{
        glabel->SetContent("请输入上课地点");
        glabel->Show();
    });
    for(auto i:weeklist)
    {
        i->SetToggleCallback(_UI_CALLBACK_{
            courseinfo.weeks.push_back(i->GetCaption());
        });
    }
    wbtn->SetClickCallback(_UI_CALLBACK_{
        hsbox->ShowAll();
    });
    cfbtn->SetClickCallback(_UI_CALLBACK_{
        if(coursename==""||courseinfo.courseName==""||courseinfo.teacher==""||courseinfo.location==""||courseinfo.weeks.empty()) {
            glabel->SetContent("请填写完整信息");
            glabel->Show();
        }
        else if(coursename.length()!=6) {
            limit->SetContent("课程代号只能是由字母和数字组成的六个字符");
            limit->Show();
        }
        else {
            Listen(new trm::Sender({trm::rqs::ADM_ADD_COUR,username,password,coursename,courseinfo}),_SD_CALLBACK_{
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
                    glabel->SetContent("开课成功");
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
                    input->SetLengthLimit(6);
                    input->SetContentLimit(ui::InputBox::ContentLimit::ALLOW_SPECIAL_CHARACTERS_ONLY);
                    input->SetSpecialCharacters(ui::InputBox::NUMBER+ui::InputBox::LOWER_LETTER+ui::InputBox::UPPER_LETTER);

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
    backbtn->SetClickCallback(_UI_CALLBACK_{
        SwitchTo(new lab::EnterCourse);
    });
    input->SetInputCallback(_UI_CALLBACK_{
        coursename = input->GetText();
        
    });
    input->SetBeginCallback(_UI_CALLBACK_{
        glabel->SetContent("请输入课程代号");
        glabel->Show();
    });
    input->SetExceedLimitCallback(_UI_CALLBACK_{
        limit->SetContent("课程代号只能是由字母和数字组成的六个字符");
        limit->Show();
    });
    btn1->SetClickCallback(_UI_CALLBACK_{
        btn1->Enable(false);
        if(coursename=="") 
        {
            glabel->SetContent("课程代号不能为空");
            glabel->Show();
        }
        else if(coursename.length()!=6) {
            limit->SetContent("课程代号只能是由字母和数字组成的六个字符");
            limit->Show();
        }
        else
        {
        Listen(new trm::Sender({trm::rqs::ADM_DELETE_COUR,username,password,coursename}),
        _SD_CALLBACK_{ // debug
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
        }
        btn1->Enable();
    }); // 这里的debtn其实是伪debtn
    debtn->SetClickCallback(_UI_CALLBACK_{
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
                                for(int i=1;i<=MAX_MONTHS;i++) {
                                    auto mbtn = new ui::Button;{
                                        mbtn->AddTo(vsbox1);
                                        mbtn->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                                        mbtn->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                                        mbtn->SetName(ToStr(i)); // 这里的名字是为了方便后续获取月份
                                    }
                                    switch(i) {
                                        case 1:
                                            mbtn->SetCaption("一月");
                                            break;
                                        case 2:
                                            mbtn->SetCaption("二月");
                                            break;
                                        case 3:
                                            mbtn->SetCaption("三月");
                                            break;
                                        case 4:
                                            mbtn->SetCaption("四月");
                                            break;
                                        case 5:
                                            mbtn->SetCaption("五月");
                                            break;
                                        case 6:
                                            mbtn->SetCaption("六月");
                                            break;
                                        case 7:
                                            mbtn->SetCaption("七月");
                                            break;
                                        case 8:
                                            mbtn->SetCaption("八月");
                                            break;
                                        case 9:
                                            mbtn->SetCaption("九月");
                                            break;
                                        case 10:
                                            mbtn->SetCaption("十月");
                                            break;
                                        case 11:
                                            mbtn->SetCaption("十一月");
                                            break;
                                        case 12:
                                            mbtn->SetCaption("十二月");
                                            break;
                                        default:
                                            break;
                                    }
                                    months.push_back(mbtn);
                                }
                                clbtn1 =new ui::Button;{
                                    clbtn1->AddTo(vsbox1);
                                    clbtn1->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                                    clbtn1->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                                    clbtn1->SetCaption("清除");
                                    clbtn1->SetName("cancel");
                                }
                                months.push_back(clbtn1);
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
                                for(int i=1;i<=MAX_WEEKS;i++) {
                                    auto weekbtn=new ui::Button;{
                                        weekbtn->AddTo(vsbox2);
                                        weekbtn->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                                        weekbtn->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                                        weekbtn->SetName(ToStr(i)); // 这里的名字是为了方便后续获取周数
                                    }
                                    switch(i) {
                                        case 1:
                                            weekbtn->SetCaption("第一周");
                                            break;
                                        case 2:
                                            weekbtn->SetCaption("第二周");
                                            break;
                                        case 3:
                                            weekbtn->SetCaption("第三周");
                                            break;
                                        case 4:
                                            weekbtn->SetCaption("第四周");
                                            break;
                                        default:
                                            break;
                                    }
                                    weeks.push_back(weekbtn);
                                }
                                clbtn2 =new ui::Button;{
                                    clbtn2->AddTo(vsbox2);
                                    clbtn2->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                                    clbtn2->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER); 
                                    clbtn2->SetCaption("清除");
                                    clbtn2->SetName("cancel");
                                }
                                weeks.push_back(clbtn2);
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
                                for(int i=1;i<=MAX_DAYS;i++) {
                                    auto daybtn = new ui::Button;{
                                        daybtn->AddTo(vsbox3);
                                        daybtn->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                                        daybtn->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                                        daybtn->SetName(ToStr(i)); // 这里的名字是为了方便后续获取星期几
                                    }
                                    switch (i)
                                    {
                                    case 1:
                                        daybtn->SetCaption("星期一");
                                        break;
                                    case 2:
                                        daybtn->SetCaption("星期二");
                                        break;
                                    case 3:
                                        daybtn->SetCaption("星期三");
                                        break;                                        
                                    case 4:
                                        daybtn->SetCaption("星期四");
                                        break;
                                    case 5:
                                        daybtn->SetCaption("星期五");
                                        break;
                                    case 6:
                                        daybtn->SetCaption("星期六");
                                        break;
                                    case 7:
                                        daybtn->SetCaption("星期日");
                                        break;
                                    default:
                                        break;
                                    }
                                    days.push_back(daybtn);
                                }
                                clbtn3 =new ui::Button;{
                                    clbtn3->AddTo(vsbox3);
                                    clbtn3->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                                    clbtn3->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                                    clbtn3->SetCaption("清除");
                                    clbtn3->SetName("cancel");
                                }
                                days.push_back(clbtn3);
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
                btn2->SetHAnchor(10);
            } //private
            admaddbtn = new ui::Button;{
                admaddbtn->AddTo(flat);
                admaddbtn->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                admaddbtn->SetVAnchor(55);
                admaddbtn->SetCaption("添设预约"); // private
                admaddbtn->SetHAnchor(10);
            }
            admdebtn = new ui::Button;{
                admdebtn->AddTo(flat);
                admdebtn->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                admdebtn->SetVAnchor(65);
                admdebtn->SetCaption("撤销预约"); // private
                admdebtn->SetHAnchor(10);
            }
            modifybtn1 = new ui::Button;{
                modifybtn1->AddTo(flat);
                modifybtn1->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                modifybtn1->SetVAnchor(75);
                modifybtn1->SetCaption("修改预约信息"); // private
                modifybtn1->SetHAnchor(10);
            }
            modifybtn2 = new ui::Button;{
                modifybtn2->AddTo(flat);
                modifybtn2->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                modifybtn2->SetVAnchor(85);
                modifybtn2->SetCaption("修改用户预约"); // private
                modifybtn2->SetHAnchor(10);
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
                        idinput->SetLengthLimit(18);
                        idinput->SetContentLimit(ui::InputBox::ContentLimit::ALLOW_SPECIAL_CHARACTERS_ONLY);
                        idinput->SetSpecialCharacters(ui::InputBox::NUMBER+'X');
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
                        phinput->SetLengthLimit(11);
                        phinput->SetContentLimit(ui::InputBox::ContentLimit::ALLOW_SPECIAL_CHARACTERS_ONLY);
                        phinput->SetSpecialCharacters(ui::InputBox::NUMBER);
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
    backbtn->SetClickCallback(_UI_CALLBACK_{
        SwitchTo(new eea::MainPage);
    });
    btn2->SetClickCallback(_UI_CALLBACK_{
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
    dbtn1->SetClickCallback(_UI_CALLBACK_{
        vsbox1->ShowAll();
    });
    dbtn2->SetClickCallback(_UI_CALLBACK_{
        vsbox2->ShowAll();
    });
    dbtn3->SetClickCallback(_UI_CALLBACK_{
        vsbox3->ShowAll();
    });
    tbtn->SetClickCallback(_UI_CALLBACK_{
        hsbox->ShowAll();
    });
    for(auto i:times)
    {
        i->SetClickCallback(_UI_CALLBACK_{
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
    idinput->SetInputCallback(_UI_CALLBACK_{
        idandphone.id=idinput->GetText();
        
    });
    idinput->SetBeginCallback(_UI_CALLBACK_{
        glabel->SetContent("请输入身份证号");
        glabel->Show();
    });
    idinput->SetExceedLimitCallback(_UI_CALLBACK_{
        limit2->SetContent("身份证号只能是18位数字或17位数字加字母X");
        limit2->Show();
    });
    phinput->SetInputCallback(_UI_CALLBACK_{
        idandphone.phone=phinput->GetText();
        
    });
    phinput->SetBeginCallback(_UI_CALLBACK_{
        glabel->SetContent("请输入手机号");
        glabel->Show();
    });
    phinput->SetExceedLimitCallback(_UI_CALLBACK_{
        limit2->SetContent("手机号只能是11位数字");
        limit2->Show();
    });
    btn1->SetClickCallback(_UI_CALLBACK_{
        if(ToStr(rdate)=="")
        {
            glabel->SetContent("日期不能为空");
            glabel->Show();
        }
        else if(rtime=="")
        {
            SwitchTo(new lab::ReserveTimeList);
        }
        else if(idandphone.id.length() !=18)
        {
            limit2->SetContent("身份证号只能是18位数字或17位数字加字母X");
            limit2->Show();
        }
        else if(idandphone.phone.length() !=11)
        {
            limit2->SetContent("手机号只能是11位数字");
            limit2->Show();
        }
        else
        {
            SwitchTo(new lab::Request);
        }
    });
    btn3->SetClickCallback(_UI_CALLBACK_{
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
    cfbtn1->SetClickCallback(_UI_CALLBACK_{
        if(ToStr(rdate)=="")
        {
            glabel->SetContent("日期不能为空");
        }
        else if(rtime=="")
        {
            SwitchTo(new lab::ReserveStatusList);
        }
        else if(idandphone.id.length() !=18)
        {
            limit2->SetContent("身份证号只能是18位数字或17位数字加字母X");
            limit2->Show();
        }
        else if(idandphone.phone.length() !=11)
        {
            limit2->SetContent("手机号只能是11位数字");
            limit2->Show();
        }
        else
        {
            SwitchTo(new lab::Cancel);
        }
    });
    cfbtn2->SetClickCallback(_UI_CALLBACK_{
        if(idandphone.id.length() !=18)
        {
            limit2->SetContent("身份证号只能是18位数字或17位数字加字母X");
            limit2->Show();
        }
        else if(idandphone.phone.length() !=11)
        {
            limit2->SetContent("手机号只能是11位数字");
            limit2->Show();
        }
        else
        {
            SwitchTo(new lab::ReserveStatusList);
        }
    });
    relbtn->SetClickCallback(_UI_CALLBACK_{
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
    admaddbtn->SetClickCallback(_UI_CALLBACK_{
        SwitchTo(new lab::AdmAddReserve);
    });
    admdebtn->SetClickCallback(_UI_CALLBACK_{
        SwitchTo(new lab::AdmCancelReserve);
    });
    modifybtn1->SetClickCallback(_UI_CALLBACK_{
        SwitchTo(new lab::AdmCancelReserve(true));
    });
    modifybtn2->SetClickCallback(_UI_CALLBACK_{
        SwitchTo(new lab::AdmModifyReserve);
    });
    for(auto i:months)
    {
        i->SetClickCallback(_UI_CALLBACK_{
            if(i->GetName()=="cancel")
            {
                rdate.month="";
                vsbox1->HideAll();
                dbtn1->SetCaption("月份");
            }
            else
            {
                rdate.month=i->GetName();
                vsbox1->HideAll();
                dbtn1->SetCaption("月份："+i->GetCaption());
            }
        });
    }
    for(auto i:weeks)
    {
        i->SetClickCallback(_UI_CALLBACK_{
            if(i->GetName()=="cancel")
            {
                rdate.week="";
                vsbox2->HideAll();
                dbtn2->SetCaption("周数");
            }
            else
            {
                rdate.week=i->GetName();
                vsbox2->HideAll();
                dbtn2->SetCaption("周数："+i->GetCaption());
            }
        });
    }
    for(auto i:days)
    {
        i->SetClickCallback(_UI_CALLBACK_{
            if(i->GetName()=="cancel")
            {
                rdate.date="";
                vsbox3->HideAll();
                dbtn3->SetCaption("星期");
            }
            else
            {
                rdate.date=i->GetName();
                vsbox3->HideAll();
                dbtn3->SetCaption("星期："+i->GetCaption());
            }
        });
    }
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
    if(password!=""&&username!="")
    {
    Listen(new trm::Sender({trm::rqs::CHECK_ACCESS,username,password,trm::AccessBox{trm::acc::ADM_ADD_RESERVE_TIME}}),_SD_CALLBACK_{
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
    Listen(new trm::Sender({trm::rqs::CHECK_ACCESS,username,password,trm::AccessBox{trm::acc::ADM_DELETE_RESERVE_TIME}}),_SD_CALLBACK_{
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
    Listen(new trm::Sender({trm::rqs::CHECK_ACCESS,username,password,trm::AccessBox{trm::acc::ADM_MODIFTY_RESERVE_NUMBER}}),_SD_CALLBACK_{
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
    Listen(new trm::Sender({trm::rqs::CHECK_ACCESS,username,password,trm::AccessBox{trm::acc::ADM_MODIFY_RESERVE_STATUS}}),_SD_CALLBACK_{
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
                backbtn->SetCaption("返回"); // private
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
    backbtn->SetClickCallback(_UI_CALLBACK_{
        SwitchTo(new lab::EnterReserve);
    });
}

void lab::ReserveTimeList::Ready(ui::Screen *screen) noexcept
{
    Listen(new trm::Sender({trm::rqs::CHECK_TIME,rdate}),_SD_CALLBACK_{
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
                glabel->SetContent("没有可预约的时间存在");
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
    backbtn->SetClickCallback(_UI_CALLBACK_{
        SwitchTo(new lab::EnterReserve);
    });
}

void lab::ReserveStatusList::Ready(ui::Screen *screen)noexcept
{
    Listen(new trm::Sender({trm::rqs::CHECK_RESERVE_STATUS_LIST,idandphone}),_SD_CALLBACK_{
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
                auto reservereply=trm::Split(reply[i],'+');
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
                        idinput->SetLengthLimit(18);
                        idinput->SetContentLimit(ui::InputBox::ContentLimit::ALLOW_SPECIAL_CHARACTERS_ONLY);
                        idinput->SetSpecialCharacters(ui::InputBox::NUMBER+'X');
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
                        phinput->SetPreset(ui::Control::Preset::FILL_FROM_CENTER); // private
                        phinput->SetLengthLimit(11);
                        phinput->SetContentLimit(ui::InputBox::ContentLimit::ALLOW_SPECIAL_CHARACTERS_ONLY);
                        phinput->SetSpecialCharacters(ui::InputBox::NUMBER);
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
                    limit->SetHSize(70); // private
                }
            }
            rpllabel = new ui::Label; {
                rpllabel->AddTo(flat);
                rpllabel->SetPreset(ui::Control::Preset::PLACE_AT_END); // maybe
                rpllabel->SetHSize(600);
                rpllabel->SetVSize(100);
                rpllabel->SetHAnchor(95);
                rpllabel->SetVAnchor(95);
            }//private
            backbtn = new ui::Button; {
                backbtn->AddTo(flat);
                backbtn->SetPreset(ui::Control::Preset::WRAP_AT_FRONT);
                backbtn->SetCaption("返回"); // private
            }
            glabel = new ui::Label; {
                glabel->AddTo(flat);
                glabel->SetHPreset(ui::Control::Preset::WRAP_AT_CENTER);
                glabel->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                glabel->SetVAnchor(25);
                glabel->SetSizeWrap(ui::Control::Direction::HORIZONTAL, false);
                glabel->SetHSize(700); // private
            }
        }
    }
}

void lab::Request::Logic(ui::Screen *screen) noexcept
{
    backbtn->SetClickCallback(_UI_CALLBACK_{
        SwitchTo(new lab::EnterReserve);
    });
    idinput->SetInputCallback(_UI_CALLBACK_{
        idandphone.id = idinput->GetText();
        
    });
    idinput->SetBeginCallback(_UI_CALLBACK_{
        label->SetContent("请输入身份证号");
        label->Show();
    });
    idinput->SetExceedLimitCallback(_UI_CALLBACK_{
        limit->SetContent("身份证号只能是18位数字或17位数字加字母X");
        limit->Show();
    });
    phinput->SetInputCallback(_UI_CALLBACK_{
        idandphone.phone = phinput->GetText();
        
    });
    phinput->SetBeginCallback(_UI_CALLBACK_{
        label->SetContent("请输入手机号");
        label->Show();
    });
    phinput->SetExceedLimitCallback(_UI_CALLBACK_{
        limit->SetContent("手机号只能是11位数字");
        limit->Show();
    });
    addbtn->SetClickCallback(_UI_CALLBACK_{
        vbox->ShowAll();
        cfbtn->Enable();
        clbtn->Enable();
        hbox->HideAll();
    });
    cfbtn->SetClickCallback(_UI_CALLBACK_{
        if(idandphone.id.length() !=18)
        {
            limit->SetContent("身份证号只能是18位数字或17位数字加字母X");
            limit->Show();
        }
        else if(idandphone.phone.length() !=11)
        {
            limit->SetContent("手机号只能是11位数字");
            limit->Show();
        }
        else
        {
        cfbtn->Enable(false);
        vbox->HideAll();
        hbox->ShowAll();
        glabel->Show();
        rpllabel->Show(); 
        Listen(new trm::Sender({trm::rqs::REQUEST_RESERVE, rdate, rtime,idandphone}), _SD_CALLBACK_{
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
        }
    });
    clbtn->SetClickCallback(_UI_CALLBACK_{
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
    Listen(new trm::Sender({trm::rqs::CHECK_RESERVE_TIME,rdate,rtime}),_SD_CALLBACK_{
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
            label2->SetContent("剩余名额:"+reply[3]);//?
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
                    debtn->SetCaption("取消预约"); // private
                }
            } // private
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
                        idinput->SetPreset(ui::Control::Preset::FILL_FROM_CENTER); // private
                        idinput->SetLengthLimit(18);
                        idinput->SetContentLimit(ui::InputBox::ContentLimit::ALLOW_SPECIAL_CHARACTERS_ONLY);
                        idinput->SetSpecialCharacters(ui::InputBox::NUMBER+'X');
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
                        phinput->SetPreset(ui::Control::Preset::FILL_FROM_CENTER); // private
                        phinput->SetLengthLimit(11);
                        phinput->SetContentLimit(ui::InputBox::ContentLimit::ALLOW_SPECIAL_CHARACTERS_ONLY);
                        phinput->SetSpecialCharacters(ui::InputBox::NUMBER);
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
                    limit->SetHSize(70); // private
                }
            }
            rpllabel = new ui::Label; {
                rpllabel->AddTo(flat);
                rpllabel->SetPreset(ui::Control::Preset::PLACE_AT_END); // maybe
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
    backbtn->SetClickCallback(_UI_CALLBACK_{
        SwitchTo(new lab::EnterReserve);
    });
    idinput->SetInputCallback(_UI_CALLBACK_{
        idandphone.id = idinput->GetText();
        
    });
    idinput->SetBeginCallback(_UI_CALLBACK_{
        label->SetContent("请输入身份证号");
        label->Show();
    });
    idinput->SetExceedLimitCallback(_UI_CALLBACK_{
        limit->SetContent("身份证号只能是18位数字或17位数字加字母X");
        limit->Show();
    });
    phinput->SetInputCallback(_UI_CALLBACK_{
        idandphone.phone = phinput->GetText();
        
    });
    phinput->SetBeginCallback(_UI_CALLBACK_{
        label->SetContent("请输入手机号");
        label->Show();
    });
    phinput->SetExceedLimitCallback(_UI_CALLBACK_{
        limit->SetContent("手机号只能是11位数字");
        limit->Show();
    });
    debtn->SetClickCallback(_UI_CALLBACK_{
        vbox->ShowAll();
        cfbtn->Enable();
        clbtn->Enable();
        hbox->HideAll();
    });
    cfbtn->SetClickCallback(_UI_CALLBACK_{
        if(idandphone.id.length()!=18)
        {
            limit->SetContent("身份证号只能是18位数字或17位数字加字母X");
        }
        else if(idandphone.phone.length() != 11) {
            limit->SetContent("手机号只能是11位数字");
            limit->Show();
        }
        else if(idandphone.id==""||idandphone.phone=="")
        {
            glabel->SetContent("身份证号或者手机号不能为空");
        }
        else
        {
        cfbtn->Enable(false);
        vbox->HideAll();
        hbox->ShowAll();
        glabel->Show();
        rpllabel->Show(); 
        Listen(new trm::Sender({trm::rqs::CANCEL_RESERVE, rdate, rtime,idandphone}), _SD_CALLBACK_{
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
                rpllabel->SetContent("身份证或者手机号不匹配，无取消预约权限");
            }
            else
            {
               rpllabel->SetContent("取消成功"); 
            }
        });
        }
    });
}

void lab::Cancel::Ready(ui::Screen *screen) noexcept
{
    vbox->HideAll();
    cfbtn->Enable(false);
    clbtn->Enable(false);
    Listen(new trm::Sender({trm::rqs::CHECK_RESERVE_STATUS,rdate,rtime,idandphone}),_SD_CALLBACK_{
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
                        input1->SetContentLimit(ui::InputBox::ContentLimit::ALLOW_SPECIAL_CHARACTERS_ONLY);
                        input1->SetSpecialCharacters("1234567890");
                        input1->SetLengthLimit(2); // 只允许输入一个或两个字符
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
                        input2->SetContentLimit(ui::InputBox::ContentLimit::ALLOW_SPECIAL_CHARACTERS_ONLY);
                        input2->SetSpecialCharacters("1234");
                        input2->SetLengthLimit(1); // 只允许输入一个字符
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
                        input3->SetContentLimit(ui::InputBox::ContentLimit::ALLOW_SPECIAL_CHARACTERS_ONLY);
                        input3->SetSpecialCharacters("1234567");
                        input3->SetLengthLimit(1); // 只允许输入一个字符
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
                        input4->SetContentLimit(ui::InputBox::ContentLimit::ALLOW_SPECIAL_CHARACTERS_ONLY);
                        input4->SetSpecialCharacters(ui::InputBox::NUMBER+ui::InputBox::LOWER_LETTER+ui::InputBox::UPPER_LETTER+':');
                        input4->SetLengthLimit(5); 
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
                        input5->SetContentLimit(ui::InputBox::ContentLimit::ALLOW_SPECIAL_CHARACTERS_ONLY);
                        input5->SetSpecialCharacters(ui::InputBox::NUMBER);
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
    backbtn->SetClickCallback(_UI_CALLBACK_{
        SwitchTo(new lab::EnterReserve);
    });
    input1->SetInputCallback(_UI_CALLBACK_{
        rdate.month = input1->GetText();
    });
    input1->SetBeginCallback(_UI_CALLBACK_{
        glabel->SetContent("请输入月份");
        glabel->Show();
    });
    input1->SetExceedLimitCallback(_UI_CALLBACK_{
        glabel->SetContent("月份只能是1-12");
        glabel->Show();
    });
    input2->SetInputCallback(_UI_CALLBACK_{
        rdate.week = input2->GetText();
    });
    input2->SetBeginCallback(_UI_CALLBACK_{
        glabel->SetContent("请输入周数");
        glabel->Show();
    });
    input2->SetExceedLimitCallback(_UI_CALLBACK_{
        glabel->SetContent("周数只能是1-4");
        glabel->Show();
    });
    input3->SetInputCallback(_UI_CALLBACK_{
        rdate.date = input3->GetText();
    });
    input3->SetBeginCallback(_UI_CALLBACK_{
        glabel->SetContent("请输入星期几");
        glabel->Show();
    });
    input3->SetExceedLimitCallback(_UI_CALLBACK_{
        glabel->SetContent("星期只能是1-7");
        glabel->Show();
    });
    input4->SetInputCallback(_UI_CALLBACK_{
        auto temp = input4->GetText();
        std::replace(temp.begin(), temp.end(), ':', '_');
        rtime = temp;
    });
    input4->SetBeginCallback(_UI_CALLBACK_{
        glabel->SetContent("请输入时间");
        glabel->Show();
    });
    input4->SetExceedLimitCallback(_UI_CALLBACK_{
        glabel->SetContent("时间格式错误");
        glabel->Show();
    });
    input5->SetInputCallback(_UI_CALLBACK_{
        rnum = input5->GetText();
    });
    input5->SetBeginCallback(_UI_CALLBACK_{
        glabel->SetContent("请输入可预约人数");
        glabel->Show();
    });
    input5->SetExceedLimitCallback(_UI_CALLBACK_{
        glabel->SetContent("可预约人数只能是数字");
        glabel->Show();
    });
    cfbtn->SetClickCallback(_UI_CALLBACK_{
        if(ToStr(rdate)==""||rtime==""||rnum=="") {
            glabel->SetContent("请填写完整信息");
            glabel->Show();
        }
        else {
            Listen(new trm::Sender({trm::rqs::ADM_ADD_RESERVE_TIME,username,password,rdate,rtime,rnum}),_SD_CALLBACK_{
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
                    glabel->SetContent("开设成功");
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
            limit=new ui::Label;{
                limit->AddTo(flat);
                limit->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                limit->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                limit->SetVAnchor(5);
                limit->SetHSize(70);//private
            }//private
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
                                dinput1->SetContentLimit(ui::InputBox::ContentLimit::ALLOW_SPECIAL_CHARACTERS_ONLY);
                                dinput1->SetSpecialCharacters("1234567890");
                                dinput1->SetLengthLimit(2); // 只允许输入一个或两个字符
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
                                dlabel2->SetContent("周数");
                            }
                            dinput2 = new ui::InputBox;{
                                dinput2->AddTo(vdbox2);
                                dinput2->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);//private
                                dinput2->SetContentLimit(ui::InputBox::ContentLimit::ALLOW_SPECIAL_CHARACTERS_ONLY);
                                dinput2->SetSpecialCharacters("1234");
                                dinput2->SetLengthLimit(1); // 只允许输入一个字符
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
                                dlabel3->SetContent("星期几");
                            }
                            dinput3 = new ui::InputBox;{
                                dinput3->AddTo(vdbox3);
                                dinput3->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);//private
                                dinput3->SetContentLimit(ui::InputBox::ContentLimit::ALLOW_SPECIAL_CHARACTERS_ONLY);
                                dinput3->SetSpecialCharacters("1234567");
                                dinput3->SetLengthLimit(1); // 只允许输入一个字符
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
                            input2->SetContentLimit(ui::InputBox::ContentLimit::ALLOW_SPECIAL_CHARACTERS_ONLY);
                            input2->SetSpecialCharacters(ui::InputBox::NUMBER+ui::InputBox::LOWER_LETTER+ui::InputBox::UPPER_LETTER+':');
                            input2->SetLengthLimit(5); // 
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
    backbtn->SetClickCallback(_UI_CALLBACK_{
        SwitchTo(new lab::EnterReserve);
    });
    dinput1->SetInputCallback(_UI_CALLBACK_{
        rdate.month = dinput1->GetText();
    });
    dinput1->SetBeginCallback(_UI_CALLBACK_{
        glabel->SetContent("请输入月份");
        glabel->Show();
    });
    dinput1->SetExceedLimitCallback(_UI_CALLBACK_{
        limit->SetContent("月份只能是1-12");
        limit->Show();
    });
    dinput2->SetInputCallback(_UI_CALLBACK_{
        rdate.week = dinput2->GetText();
    });
    dinput2->SetBeginCallback(_UI_CALLBACK_{
        glabel->SetContent("请输入周数");
        glabel->Show();
    });
    dinput2->SetExceedLimitCallback(_UI_CALLBACK_{
        limit->SetContent("周数只能是1-4");
        limit->Show();
    });
    dinput3->SetInputCallback(_UI_CALLBACK_{
        rdate.date = dinput3->GetText();
    });
    dinput3->SetBeginCallback(_UI_CALLBACK_{
        glabel->SetContent("请输入星期几");
        glabel->Show();
    });
    dinput3->SetExceedLimitCallback(_UI_CALLBACK_{
        limit->SetContent("星期只能是1-7");
        limit->Show();
    });
    input2->SetInputCallback(_UI_CALLBACK_{
        auto temp = input2->GetText();
        std::replace(temp.begin(), temp.end(), ':', '_');
        rtime= temp;
    });
    input2->SetBeginCallback(_UI_CALLBACK_{
        glabel->SetContent("请输入时间");
        glabel->Show();
    });
    input2->SetExceedLimitCallback(_UI_CALLBACK_{
        limit->SetContent("时间格式错误");
        limit->Show();
    });
    btn1->SetClickCallback(_UI_CALLBACK_{
        if(ToStr(rdate)==""||rtime=="") {
            glabel->SetContent("请填写完整信息");
            glabel->Show();
        }
        else {
            Listen(new trm::Sender({trm::rqs::ADM_SEARCH_RESERVE,username,password,rdate,rtime}),_SD_CALLBACK_{
            if(reply[0] == trm::rpl::TIME_OUT) {
                glabel->SetContent("服务端未响应，请检查后重试");
            }
            else if(reply[0] == trm::rpl::NO ) {
                if(fromModify)
                {
                    glabel->SetContent("待修改的预约不存在");
                }
                else
                {
                    glabel->SetContent("待撤销的预约不存在");
                }
            }
            else if(reply[0] == trm::rpl::ACCESS_DENIED) {
                if(fromModify)
                {
                    glabel->SetContent("无修改预约权限");
                }
                else
                {
                    glabel->SetContent("无撤消预约权限"); 
                }
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
    debtn->SetClickCallback(_UI_CALLBACK_{
        Listen(new trm::Sender({trm::rqs::ADM_DELETE_RESERVE_TIME,username,password,rdate,rtime}),_SD_CALLBACK_{
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
    modifybtn->SetClickCallback(_UI_CALLBACK_{
       vbox2->ShowAll();
       cfbtn->Enable();
       clbtn->Enable();
       hbox2->HideAll();
   });
   input->SetInputCallback(_UI_CALLBACK_{
         rnum = input->GetText();
   });
   cfbtn->SetClickCallback(_UI_CALLBACK_{
       if(rnum == "") {
           glabel->SetContent("请输入预约人数");
           glabel->Show();
       }
       else {
           Listen(new trm::Sender({trm::rqs::ADM_MODIFY_RESERVE_NUMBER,username,password,rdate,rtime,rnum}),_SD_CALLBACK_{
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
   clbtn->SetClickCallback(_UI_CALLBACK_{
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
                limit = new ui::Label; {
                    limit->AddTo(vbox1);
                    limit->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    limit->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                    limit->SetVAnchor(5);
                    limit->SetHSize(70);//private
                }//private
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
                        input1->SetContentLimit(ui::InputBox::ContentLimit::ALLOW_SPECIAL_CHARACTERS_ONLY);
                        input1->SetSpecialCharacters("1234567890");
                        input1->SetLengthLimit(2); // 只允许输入一个或两个字符
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
                        input2->SetContentLimit(ui::InputBox::ContentLimit::ALLOW_SPECIAL_CHARACTERS_ONLY);
                        input2->SetSpecialCharacters("1234");
                        input2->SetLengthLimit(1); // 只允许输入一个字符
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
                        input3->SetContentLimit(ui::InputBox::ContentLimit::ALLOW_SPECIAL_CHARACTERS_ONLY);
                        input3->SetSpecialCharacters("1234567");
                        input3->SetLengthLimit(1); // 只允许输入一个字符
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
                        input4->SetContentLimit(ui::InputBox::ContentLimit::ALLOW_SPECIAL_CHARACTERS_ONLY);
                        input4->SetSpecialCharacters(ui::InputBox::NUMBER+ui::InputBox::LOWER_LETTER+ui::InputBox::UPPER_LETTER+':');
                        input4->SetLengthLimit(5); // 只允许输入一个或两个字符
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
                        input5->SetContentLimit(ui::InputBox::ContentLimit::ALLOW_SPECIAL_CHARACTERS_ONLY);
                        input5->SetSpecialCharacters(ui::InputBox::NUMBER+'X');
                        input5->SetLengthLimit(18); // 只允许输入一个或两个字符
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
                        input6->SetContentLimit(ui::InputBox::ContentLimit::ALLOW_SPECIAL_CHARACTERS_ONLY);
                        input6->SetSpecialCharacters(ui::InputBox::NUMBER);
                        input6->SetLengthLimit(11); // 只允许输入一个或两个字符
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
    input1->SetInputCallback(_UI_CALLBACK_{
        rdate.month = input1->GetText();
    });
    input1->SetBeginCallback(_UI_CALLBACK_{
        glabel->SetContent("请输入月份");
        glabel->Show();
    });
    input2->SetInputCallback(_UI_CALLBACK_{
        rdate.week = input2->GetText();
    });
    input2->SetBeginCallback(_UI_CALLBACK_{
        glabel->SetContent("请输入周数");
        glabel->Show();
    });
    input3->SetInputCallback(_UI_CALLBACK_{
        rdate.date = input3->GetText();
    });
    input3->SetBeginCallback(_UI_CALLBACK_{
        glabel->SetContent("请输入星期几");
        glabel->Show();
    });
    input4->SetInputCallback(_UI_CALLBACK_{
        auto temp = input4->GetText();
        std::replace(temp.begin(), temp.end(), ':', '_');
        rtime = temp;
    });
    input4->SetBeginCallback(_UI_CALLBACK_{
        glabel->SetContent("请输入时间");
        glabel->Show();
    });
    input5->SetInputCallback(_UI_CALLBACK_{
        idandphone.id = input5->GetText();
        
    });
    input5->SetBeginCallback(_UI_CALLBACK_{
        glabel->SetContent("请输入身份证号");
        glabel->Show();
    });
    input5->SetExceedLimitCallback(_UI_CALLBACK_{
        limit->SetContent("身份证号必须为18位数字或17位的数字加X");
        limit->Show();
    });
    input6->SetInputCallback(_UI_CALLBACK_{
        idandphone.phone = input6->GetText();
        
    });
    input6->SetBeginCallback(_UI_CALLBACK_{
        glabel->SetContent("请输入手机号");
        glabel->Show();
    });
    input6->SetExceedLimitCallback(_UI_CALLBACK_{
        limit->SetContent("手机号只能是11位数字");
        limit->Show();
    });
    backbtn->SetClickCallback(_UI_CALLBACK_{
        SwitchTo(new lab::EnterReserve);
    });
    cfbtn->SetClickCallback(_UI_CALLBACK_{
        if(ToStr(rdate) == "" || rtime == "" || idandphone.id == "" || idandphone.phone == "") {
            glabel->SetContent("请填写完整信息");
            glabel->Show();
        }
        else if(idandphone.id.length()!=18)
        {
            limit->SetContent("身份证号必须为18位的数字或者17位的数字加X");
            limit->Show();
        }
        else if(idandphone.phone.length()!=11)
        {
            limit->SetContent("手机号长度必须为11位");
            limit->Show();
        }
        else {
            Listen(new trm::Sender({trm::rqs::ADM_MODIFY_RESERVE_STATUS,username,password,idandphone,rdate,rtime}), _SD_CALLBACK_{
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