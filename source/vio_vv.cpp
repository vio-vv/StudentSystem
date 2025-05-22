#include "client_pages.hpp"

std::vector<trm::Book> vio::EnterLibrary::books = {};
std::vector<trm::BorrowLog> vio::EnterLibrary::borrowLogs = {};

void vio::EnterLibrary::Load(ui::Screen *screen) noexcept
{
    ui::Margin *mar = new ui::Margin;{
        mar->AddTo(screen);
        mar->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
        mar->SetMargin(150, 150, 250, 250);
    }
    {
        vbox = new ui::VerticalBox;{
            vbox->AddTo(mar);
            vbox->SetGap(5);
        }
        {
            ui::HorizontalBox *topBox = new ui::HorizontalBox;{
                topBox->AddTo(vbox);
                topBox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                topBox->SetVSize(30);
                topBox->SetGap(5);
            }
            {
                searchBox = new ui::InputBox;{
                    searchBox->AddTo(topBox);
                    searchBox->SetText("在此输入搜索内容");
                    searchBox->SetSize(1000, 30);
                }
                searchOptBtn = new ui::Button;{
                    searchOptBtn->AddTo(topBox);
                    searchOptBtn->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    searchOptBtn->SetCaption("筛选>");
                }
                searchBtn = new ui::Button;{
                    searchBtn->AddTo(topBox);
                    searchBtn->SetHPreset(ui::Control::Preset::WRAP_AT_END);
                    searchBtn->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    searchBtn->SetCaption("搜索");
                }
            }
            midBox = new ui::HorizontalBox;{
                midBox->AddTo(vbox);
                midBox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                midBox->SetVSize(320);
                midBox->SetGap(5);
            }
            {
                ui::Flat *midBoxFlat = new ui::Flat;{
                    midBoxFlat->AddTo(midBox);
                    midBoxFlat->SetHPreset(ui::Control::Preset::PLACE_AT_FRONT);
                    midBoxFlat->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    midBoxFlat->SetHSize(searchBox->GetSize(ui::Control::Direction::HORIZONTAL));
                }
                {
                    hinderBox = new ui::HorizontalBox;{
                        hinderBox->AddTo(midBoxFlat);
                        hinderBox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        hinderBox->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                        hinderBox->SetVSize(100);
                    }
                }
                optBox = new ui::VerticalBox;{
                    optBox->AddTo(midBox);
                    optBox->SetGap(5);
                    optBox->HideAll();
                    optBox->SetHAnchor(60);
                    optBox->SetSize(120, 320);
                }
                {
                    chooseIsbn = new ui::Button;{
                        chooseIsbn->AddTo(optBox);
                        chooseIsbn->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        chooseIsbn->SetCaption("ISBN");
                        chooseIsbn->SetFontSize(30);
                        chooseIsbn->SetVisible(false);
                    }
                    chooseBookName = new ui::Button;{
                        chooseBookName->AddTo(optBox);
                        chooseBookName->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        chooseBookName->SetCaption("图书名称");
                        chooseBookName->SetFontSize(30);
                        chooseBookName->SetVisible(false);
                    }
                    chooseAuthor = new ui::Button;{
                        chooseAuthor->AddTo(optBox);
                        chooseAuthor->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        chooseAuthor->SetCaption("作者");
                        chooseAuthor->SetFontSize(30);
                        chooseAuthor->SetVisible(false);
                    }
                    choosePublishDate = new ui::Button;{
                        choosePublishDate->AddTo(optBox);
                        choosePublishDate->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);    
                        choosePublishDate->SetCaption("出版日期");
                        choosePublishDate->SetFontSize(30);
                        choosePublishDate->SetVisible(false);
                    }
                    chooseStorePosion = new ui::Button;{
                        chooseStorePosion->AddTo(optBox);
                        chooseStorePosion->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        chooseStorePosion->SetCaption("馆藏位置");
                        chooseStorePosion->SetFontSize(30);
                        chooseStorePosion->SetVisible(false);
                    }
                    chooseCategory = new ui::Button;{
                        chooseCategory->AddTo(optBox);
                        chooseCategory->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        chooseCategory->SetCaption("分类");
                        chooseCategory->SetFontSize(30);
                        chooseCategory->SetVisible(false);
                    }
                }
            }
            ui::HorizontalBox *bottomBox = new ui::HorizontalBox;{
                bottomBox->AddTo(vbox);
                bottomBox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                bottomBox->SetVPreset(ui::Control::Preset::FILL_FROM_END);
                bottomBox->SetGap(5);
            }
            {
                ui::VerticalBox *leftSideBox = new ui::VerticalBox;{
                    leftSideBox->AddTo(bottomBox);
                    leftSideBox->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                    leftSideBox->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                    leftSideBox->SetSize(120, 100);
                }
                {
                    borrowManageBtn = new ui::Button;{
                        borrowManageBtn->AddTo(leftSideBox);
                        borrowManageBtn->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        borrowManageBtn->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                        borrowManageBtn->SetCaption("借阅管理");
                    }
                    basicNolifyBtn = new ui::Button;{
                        basicNolifyBtn->AddTo(leftSideBox);
                        basicNolifyBtn->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        basicNolifyBtn->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                        basicNolifyBtn->SetCaption("图书馆概况");
                    }
                }
                ui::Flat *flat = new ui::Flat;{
                    flat->AddTo(bottomBox);
                    flat->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    flat->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                }
                ui::VerticalBox *rightSideBox = new ui::VerticalBox;{
                    rightSideBox->AddTo(bottomBox);
                    rightSideBox->SetHPreset(ui::Control::Preset::PLACE_AT_END);
                    rightSideBox->SetVPreset(ui::Control::Preset::PLACE_AT_END);
                    rightSideBox->SetSize(50, 50);
                }
                {
                    returnBtn = new ui::Button;{
                        returnBtn->AddTo(rightSideBox);
                        returnBtn->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        returnBtn->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                        returnBtn->SetFontSize(50);
                        returnBtn->SetCaption("←返回");
                    }
                }
            }
        }
    };
}

void vio::EnterLibrary::Logic(ui::Screen *screen) noexcept
{   
    searchBox->SetInputCallback(UI_CALLBACK{
        userInput = searchBox->GetText();
    });

    returnBtn->SetClickCallback(UI_CALLBACK{
        SwitchTo(new eea::MainPage);
    });

    searchOptBtn->SetClickCallback(UI_CALLBACK{
        if (!isClicked) {
            isClicked ^= 1;
            searchOptBtn->SetCaption(optStr + "﹀");
            optBox->SetVisible(true);
            optBox->ShowAll();
            for (auto btn : {chooseIsbn, chooseBookName, chooseAuthor, choosePublishDate, chooseStorePosion, chooseCategory}) {
                btn->SetClickCallback(UI_CALLBACK{
                    optStr = btn->GetCaption();
                    searchOptBtn->SetCaption(optStr + "﹀");
                });
            }
        }
        else {
            isClicked ^= 1;
            optBox->HideAll();
            if (optStr == "") searchOptBtn->SetCaption("筛选>");
        }
    });

    searchBtn->SetClickCallback(UI_CALLBACK{
        searchBtn->Disable();
        
        if (userInput == "") {
            hinderBox->FreeAll();
            hinderBox->Add(new ui::Label("注意，查询内容不能为空，请检查输入"));
        }
        else {
            hinderBox->FreeAll();
            ui::LoadingRing *loading = new ui::LoadingRing;{
                loading->AddTo(hinderBox);
                loading->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                loading->SetSize(30, 30);
                loading->Start();
            }

            int searchType;
            if (optStr == "ISBN") searchType = trm::rqs::BOOK_ISBN;
            else if (optStr == "图书名称") searchType = trm::rqs::BOOK_NAME;
            else if (optStr == "作者") searchType = trm::rqs::BOOK_AUTHOR;
            else if (optStr == "出版日期") searchType = trm::rqs::BOOK_PUBLISHDATE;
            else if (optStr == "馆藏位置") searchType = trm::rqs::BOOK_STROEPOSTION;
            else if (optStr == "分类") searchType = trm::rqs::BOOK_CATAGORY;

            Listen(new trm::Sender({trm::rqs::SEARCH_BOOK, userInput, ToStr(searchType), "false", "false"}), SD_CALLBACK{
                hinderBox->FreeAll();
                if (reply.empty()) {
                    SwitchTo(new BookList);
                }
                else if (reply[0] == trm::rpl::FAIL) {
                    hinderBox->Add(new ui::Label("查询失败，请检查输入"));
                }
                else if (reply[0] == trm::rpl::TIME_OUT) {
                    hinderBox->Add(new ui::Label("服务端未响应，请稍后再试"));
                }
                else {
                    for (auto bookInfo : reply) {
                        books.push_back(trm::Book(bookInfo));
                    }
                    SwitchTo(new BookList);
                }
            });
        }
        searchBtn->Enable();
    });
}

void vio::EnterLibrary::Ready(ui::Screen *screen) noexcept
{
    books = {};
    borrowLogs = {};
}

void vio::BookList::Load(ui::Screen *screen) noexcept
{
    ui::Margin *mar = new ui::Margin;{
        mar->AddTo(screen);
        mar->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
        mar->SetMargin(100, 100, 150, 150);
    }
    {
        backBtn = new ui::Button;{
            backBtn->AddTo(mar);
            backBtn->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
            backBtn->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
            backBtn->SetFontSize(50);
            backBtn->SetCaption("←返回");
        }
    }
}

void vio::BookList::Logic(ui::Screen *screen) noexcept
{
    backBtn->SetClickCallback(UI_CALLBACK{
        SwitchTo(new EnterLibrary);
    });
}

void vio::BookList::Ready(ui::Screen *screen) noexcept
{
    ;
}

void vio::EnterNolify::Load(ui::Screen *screen) noexcept
{
    ;
}

void vio::EnterNolify::Logic(ui::Screen *screen) noexcept
{
    ;
}

void vio::EnterNolify::Ready(ui::Screen *screen) noexcept
{
    ;
}
