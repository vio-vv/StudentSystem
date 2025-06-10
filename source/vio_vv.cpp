#include "client_pages.hpp"

int vio::EnterLibrary::select = 0;
std::string vio::EnterLibrary::optStr = "";
std::string vio::EnterLibrary::userInput = "";
trm::Book vio::EnterLibrary::selectedBook;
std::vector<trm::Book> vio::EnterLibrary::books = {};
std::vector<trm::BorrowLog> vio::EnterLibrary::borrowLogs = {};

std::vector<std::string> vio::BookManage::room302 = {"数理科学与化学", "天文学、地球科学", "环境科学"};
std::vector<std::string> vio::BookManage::room303 = {"自动化技术", "计算机技术", "建筑设计"};
std::vector<std::string> vio::BookManage::room401 = {"法律", "经济"};
std::vector<std::string> vio::BookManage::room402 = {"马克思主义、列宁主义、毛泽东思想、邓小平理论", "社会科学", "哲学", "军事", "语言"};
std::vector<std::string> vio::BookManage::room403 = {"文学", "艺术", "历史"};
std::vector<std::string> vio::BookManage::room621 = {"医药、卫生"};

std::vector<std::string> vio::EnterLibrary::searchOption = {"ISBN", "图书名称", "作者", "出版日期", "馆藏位置", "分类"};

void vio::EnterLibrary::Load(ui::Screen *screen) noexcept
{
    ui::Margin *mar = new ui::Margin;{
        mar->AddTo(screen);
        mar->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
        mar->SetMargin(120, 150, 250, 250);
    }
    {
        vbox = new ui::VerticalBox;{
            vbox->AddTo(mar);
            vbox->SetGap(5);
        }
        {   
            returnBtn = new ui::Button;{
                returnBtn->AddTo(vbox);
                returnBtn->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                returnBtn->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                returnBtn->SetFontSize(50);
                returnBtn->SetCaption("←返回");
            }
            ui::HorizontalBox *topBox = new ui::HorizontalBox;{
                topBox->AddTo(vbox);
                topBox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                topBox->SetVSize(30);
                topBox->SetGap(5);
            }
            {
                searchBox = new ui::InputBox;{
                    searchBox->AddTo(topBox);
                    searchBox->SetSize(1000, 30);
                    searchBox->SetText("在此输入搜索内容");
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
                optBox = new ui::HorizontalBox;{
                    optBox->AddTo(midBox);
                    optBox->SetGap(5);
                    optBox->HideAll();
                    optBox->SetHAnchor(60);
                    optBox->SetVisible(false);
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
                {
                    bookManageBtn = new ui::Button;{
                        bookManageBtn->AddTo(flat);
                        bookManageBtn->SetHPreset(ui::Control::Preset::WRAP_AT_END);
                        bookManageBtn->SetVPosition(5);
                        bookManageBtn->SetVSize(40);
                        bookManageBtn->SetCaption("图书管理");
                        bookManageBtn->SetVisible(false);
                    }
                    resetLibraryBtn = new ui::Button;{
                        resetLibraryBtn->AddTo(flat);
                        resetLibraryBtn->SetHPreset(ui::Control::Preset::WRAP_AT_END);
                        resetLibraryBtn->SetVSize(40);
                        resetLibraryBtn->SetVPosition(90);
                        resetLibraryBtn->SetCaption("重置图书馆");
                        resetLibraryBtn->SetVisible(false);
                    }
                }
            }
        }
    };
}

void vio::EnterLibrary::Logic(ui::Screen *screen) noexcept
{   
    searchBox->SetInputCallback(_UI_CALLBACK_{
        userInput = searchBox->GetText();
    });

    searchBox->SetEndCallback(_UI_CALLBACK_{
        if (searchBox->GetText() == "") searchBox->SetText("在此输入搜索内容");
    });

    searchBox->SetBeginCallback(_UI_CALLBACK_{
        if (searchBox->GetText() == "在此输入搜索内容") searchBox->SetText("");
    });

    returnBtn->SetClickCallback(_UI_CALLBACK_{
        SwitchTo(new eea::MainPage);
    });

    bookManageBtn->SetClickCallback(_UI_CALLBACK_{
        SwitchTo(new BookManage);
    });

    borrowManageBtn->SetClickCallback(_UI_CALLBACK_{
        SwitchTo(new BorrowManage);
    });

    basicNolifyBtn->SetClickCallback(_UI_CALLBACK_{
        SwitchTo(new BookPartitions);
    });

    resetLibraryBtn->SetClickCallback(_UI_CALLBACK_{
        screen->HideAll();
        int ret = MessageBox(screen, "确认重置图书馆？", {"确认", "取消"});
        if (ret == 0) {
            Listen(new trm::Sender({trm::rqs::RESET_LIBRARY}), _SD_CALLBACK_{
                screen->FreeAllVisible();
                if (reply.empty()) {
                    MessageBox(screen, "重置图书馆失败，请稍后再试", {"确认"});
                }
                else if (reply[0] == trm::rpl::TIME_OUT) {
                    MessageBox(screen, "服务端未响应，请稍后再试", {"确认"});
                }
                else if (reply[0] == trm::rpl::SUCC) {
                    MessageBox(screen, "图书馆重置成功", {"确认"});
                }
                else if (reply[0] == trm::rpl::ACCESS_DENIED) {
                    MessageBox(screen, "您没有权限重置图书馆", {"确认"});
                }
                else assert(false);
                screen->FreeAllVisible();
                screen->ShowAll();
            });
        }
        else {
            screen->FreeAllVisible();
            screen->ShowAll();
        }
    });

    searchOptBtn->SetClickCallback(_UI_CALLBACK_{
        if (!isClicked) {
            isClicked ^= 1;
            searchOptBtn->SetCaption(optStr + "﹀");
            optBox->SetVisible(true);
            ui::Button *btn = nullptr;
            ui::VerticalBox *optvBox1 = nullptr;
            for (long long unsigned int i = 0; i < searchOption.size(); i++) {
                if (i % 3 == 0) {
                    optvBox1 = new ui::VerticalBox;{
                        optvBox1->AddTo(optBox);
                        optvBox1->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        optvBox1->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                        optvBox1->SetGap(5);
                    }
                }
                btn = new ui::Button;{
                    btn->AddTo(optvBox1);
                    btn->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    btn->SetCaption(searchOption[i]);
                    btn->SetFontSize(30);
                    btn->SetClickCallback(_UI_CALLBACK_{
                        optStr = btn->GetCaption();
                        searchOptBtn->SetCaption(optStr + "﹀");
                    });
                }
            }
        }
        else {
            isClicked ^= 1;
            optBox->FreeAll();
            if (optStr == "") searchOptBtn->SetCaption("筛选>");
        }
    });

    searchBtn->SetClickCallback(_UI_CALLBACK_{
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
            else searchType = trm::rqs::BOOK_NAME;

            Listen(new trm::Sender({trm::rqs::SEARCH_BOOK, userInput, ToStr(searchType), "false", "false"}), _SD_CALLBACK_{
                hinderBox->FreeAll();
                books.clear();
                if (!reply.empty()) {
                    if (reply[0] == trm::rpl::FAIL) {
                        hinderBox->Add(new ui::Label("查询失败，请检查输入"));
                        return;
                    }
                    else if (reply[0] == trm::rpl::TIME_OUT) {
                        hinderBox->Add(new ui::Label("服务端未响应，请稍后再试"));
                        return;
                    }
                    else {
                        for (auto bookInfo : reply) {
                            books.push_back(trm::Book(bookInfo));
                        }
                    }
                }
                SwitchTo(new BookList);
            });
        }
        searchBtn->Enable();
    });
}

void vio::EnterLibrary::Ready(ui::Screen *screen) noexcept
{
    books = {};
    borrowLogs = {};
    selectedBook = trm::Book();
    userInput = "";

    for (const auto &access : account.access) {
        if (access == trm::Access::ADM) {
            bookManageBtn->SetVisible(true);
            resetLibraryBtn->SetVisible(true);
        }
        else if (access == trm::Access::BOOK_MANAGE) {
            bookManageBtn->SetVisible(true);
        }
        else if (access == trm::Access::RESET_LIBRARY) {
            resetLibraryBtn->SetVisible(true);
        }
    }
}

void vio::BookPartitions::Load(ui::Screen *screen) noexcept
{
    ui::Margin *mar = new ui::Margin;{
        mar->AddTo(screen);
        mar->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
        mar->SetMargin(100, 100, 200, 200);
    }
    {
        ui::VerticalBox *wholeBox = new ui::VerticalBox;{
            wholeBox->AddTo(mar);
            wholeBox->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
        }
        {
            backBtn = new ui::Button;{
                backBtn->AddTo(wholeBox);
                backBtn->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                backBtn->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                backBtn->SetFontSize(50);
                backBtn->SetCaption("←返回");
            }
            ui::VerticalScrollingBox *scrollBox = new ui::VerticalScrollingBox;{
                scrollBox->AddTo(wholeBox);
                scrollBox->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                scrollBox->SetInsideBoxScrollable(true);
            }
            {
                ui::HorizontalBox *topBox = new ui::HorizontalBox;{
                    topBox->AddTo(scrollBox);
                    topBox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    topBox->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                }
                {
                    ui::HorizontalBox *hor = new ui::HorizontalBox;{
                        hor->AddTo(topBox);
                        hor->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                        hor->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                    }
                    {
                        ui::Label *label = new ui::Label;{
                            label->AddTo(hor);
                            label->SetHPreset(ui::Control::Preset::PLACE_AT_CENTER);
                            label->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                            label->SetFontSize(50);
                            label->SetContent("图书分区");
                        }
                    }
                    hor = new ui::HorizontalBox;{
                        hor->AddTo(topBox);
                        hor->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        hor->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                    }
                    {
                        ui::Label *label = new ui::Label;{
                            label->AddTo(hor);
                            label->SetHPreset(ui::Control::Preset::PLACE_AT_CENTER);
                            label->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                            label->SetFontSize(50);
                            label->SetContent("藏书种类");
                        }
                    }
                }
                for (auto room : {"302", "303", "401", "402", "403", "621"}) {
                    std::string roomName = std::string("图书馆") + room;
                    std::string catagory = "";
                    if (room == std::string("302")) {
                        for (unsigned long long i = 0; i < vio::BookManage::room302.size(); ++i) {
                            if (i != vio::BookManage::room302.size() - 1) {
                                catagory += vio::BookManage::room302[i] + ",";
                                if (i % 2) catagory += "\n";
                            }
                            else catagory += vio::BookManage::room302[i];
                        }
                    }
                    else if (room == std::string("303")) {
                        for (unsigned long long i = 0; i < vio::BookManage::room303.size(); ++i) {
                            if (i != vio::BookManage::room303.size() - 1) {
                                catagory += vio::BookManage::room303[i] + ",";
                                if (i % 2) catagory += "\n";
                            }
                            else catagory += vio::BookManage::room303[i];
                        }
                    }
                    else if (room == std::string("401")) {
                        for (unsigned long long i = 0; i < vio::BookManage::room401.size(); ++i) {
                            if (i != vio::BookManage::room401.size() - 1) {
                                catagory += vio::BookManage::room401[i] + ",";
                                if (i % 2) catagory += "\n";
                            }
                            else catagory += vio::BookManage::room401[i];
                        }
                    }
                    else if (room == std::string("402")) {
                        for (unsigned long long i = 0; i < vio::BookManage::room402.size(); ++i) {
                            if (i != vio::BookManage::room402.size() - 1) {
                                catagory += vio::BookManage::room402[i] + ",";
                                if (i % 2) catagory += "\n";
                            }
                            else catagory += vio::BookManage::room402[i];

                        }
                    }
                    else if (room == std::string("403")) {
                        for (unsigned long long i = 0; i < vio::BookManage::room403.size(); ++i) {
                            if (i != vio::BookManage::room403.size() - 1) {
                                catagory += vio::BookManage::room403[i] + ",";
                                if (i % 2) catagory += "\n";
                            }
                            else catagory += vio::BookManage::room403[i];
                        }
                    }
                    else if (room == std::string("621")) {
                        for (unsigned long long i = 0; i < vio::BookManage::room621.size(); ++i) {
                            if (i != vio::BookManage::room621.size() - 1) {
                                catagory += vio::BookManage::room621[i] + ",";
                                if (i % 2) catagory += "\n";
                            }
                            else catagory += vio::BookManage::room621[i];
                        }
                    }

                    topBox = new ui::HorizontalBox;{
                        topBox->AddTo(scrollBox);
                        topBox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        topBox->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                    }
                    {
                        ui::HorizontalBox *hor = new ui::HorizontalBox;{
                            hor->AddTo(topBox);
                            hor->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                            hor->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                        }
                        {
                            ui::Label *label = new ui::Label;{
                                label->AddTo(hor);
                                label->SetHPreset(ui::Control::Preset::PLACE_AT_CENTER);
                                label->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                                label->SetFontSize(40);
                                label->SetContent(roomName);
                            }
                        }
                        hor = new ui::HorizontalBox;{
                            hor->AddTo(topBox);
                            hor->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                            hor->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                        }
                        {
                            ui::Label *label = new ui::Label;{
                                label->AddTo(hor);
                                label->SetHPreset(ui::Control::Preset::PLACE_AT_CENTER);
                                label->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                                label->SetFontSize(40);
                                label->SetContent(catagory);
                            }
                        }
                    }
                }
            }
        }
    }
}

void vio::BookPartitions::Logic(ui::Screen *screen) noexcept
{
    backBtn->SetClickCallback(_UI_CALLBACK_{
        SwitchTo(new EnterLibrary);
    });
}

void vio::BookPartitions::Ready(ui::Screen *screen) noexcept
{
    ;
}

void vio::BookList::Load(ui::Screen *screen) noexcept
{
    ui::Margin *mar = new ui::Margin;{
        mar->AddTo(screen);
        mar->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
        mar->SetMargin(100, 100, 150, 150);
    }
    {
        ui::VerticalBox *wholeBox = new ui::VerticalBox;{
            wholeBox->AddTo(mar);
            wholeBox->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
            wholeBox->SetGap(5);
        }
        {
            backBtn = new ui::Button;{
                backBtn->AddTo(wholeBox);
                backBtn->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                backBtn->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                backBtn->SetFontSize(50);
                backBtn->SetCaption("←返回");
            }
            ui::HorizontalBox *topBox = new ui::HorizontalBox;{
                topBox->AddTo(wholeBox);
                topBox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                topBox->SetVSize(30);
                topBox->SetGap(5);
            }
            {
                searchBox = new ui::InputBox;{
                    searchBox->AddTo(topBox);
                    searchBox->SetSize(1000, 30);
                    searchBox->SetText(userInput);
                }
                searchOptBtn = new ui::Button;{
                    searchOptBtn->AddTo(topBox);
                    searchOptBtn->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    if (optStr == "") optStr = "图书名称";
                    searchOptBtn->SetCaption(optStr + ">");
                }
                searchBtn = new ui::Button;{
                    searchBtn->AddTo(topBox);
                    searchBtn->SetHPreset(ui::Control::Preset::WRAP_AT_END);
                    searchBtn->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    searchBtn->SetCaption("搜索");
                }
            }
            optBox = new ui::HorizontalBox;{
                optBox->AddTo(wholeBox);
                optBox->SetGap(5);
                optBox->HideAll();
                optBox->SetHPosition(1000);
                optBox->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                optBox->SetSize(120, 320);
            }
            listBox = new ui::VerticalScrollingBox;{
                listBox->AddTo(wholeBox);
                listBox->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                listBox->SetInsideBoxScrollable(true);
            }
            ui::VerticalBox *footBox = new ui::VerticalBox;{
                footBox->AddTo(wholeBox);
                footBox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                footBox->SetVPreset(ui::Control::Preset::WRAP_AT_END);
                footBox->SetGap(5);
                footBox->SetVSize(60);
            }
            {
                ui::HorizontalBox *pageBox = new ui::HorizontalBox;{
                    pageBox->AddTo(footBox);
                    pageBox->SetHPreset(ui::Control::Preset::WRAP_AT_CENTER);
                    pageBox->SetVSize(30);
                }
                {
                    lastBtn = new ui::Button;{
                        lastBtn->AddTo(pageBox);
                        lastBtn->SetVSize(30);
                        lastBtn->SetHPreset(ui::Control::Preset::WRAP_AT_CENTER);
                        lastBtn->SetCaption("上一页");
                        lastBtn->SetFontSize(35);
                    }
                    pageLabel = new ui::Label;{
                        pageLabel->AddTo(pageBox);
                        pageLabel->SetVSize(30);
                        pageLabel->SetHPreset(ui::Control::Preset::WRAP_AT_CENTER);
                        pageLabel->SetFontSize(35);
                        pageLabel->SetContent(ToStr(page) + '/' + ToStr(totPage));
                    }
                    nextBtn = new ui::Button;{
                        nextBtn->AddTo(pageBox);
                        nextBtn->SetVSize(30);
                        nextBtn->SetHPreset(ui::Control::Preset::WRAP_AT_CENTER);
                        nextBtn->SetCaption("下一页");
                        nextBtn->SetFontSize(35);
                    }
                }
                ui::HorizontalBox *turnToBox = new ui::HorizontalBox;{
                    turnToBox->AddTo(footBox);
                    turnToBox->SetHPreset(ui::Control::Preset::WRAP_AT_CENTER);
                    turnToBox->SetVSize(30);
                }
                {
                    turnToBtn = new ui::Button;{
                        turnToBtn->AddTo(turnToBox);
                        turnToBtn->SetHSize(30);
                        turnToBtn->SetHPreset(ui::Control::Preset::WRAP_AT_CENTER);
                        turnToBtn->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        turnToBtn->SetCaption("跳转到");
                        turnToBtn->SetFontSize(35);
                        turnToBtn->SetVSize(30);
                    }
                    pageInput = new ui::InputBox;{
                        pageInput->AddTo(turnToBox);
                        pageInput->SetSize(100, 30);
                    }
                    tip = new ui::Label;{
                        tip->AddTo(turnToBox);
                        tip->SetHSize(30);
                        tip->SetHPreset(ui::Control::Preset::WRAP_AT_CENTER);
                        tip->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        tip->SetFontSize(35);
                        tip->SetContent("页面非法");
                        tip->SetVisible(false);
                    }
                }
            }
        }
    }
}

void vio::BookList::Logic(ui::Screen *screen) noexcept
{
    resetBookList = [=, this]() {
        listBox->FreeAll();
        ui::Button *btn = nullptr;
        pageLabel->SetContent(ToStr(page) + '/' + ToStr(totPage));
        if (len == 0) {
            ui::Label *tip = new ui::Label;{
                tip->AddTo(listBox);
                tip->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                tip->SetContent("没有匹配的书籍");
            }
            return;
        }
        for (int i = (page - 1) * 10; i < page * 10 && i < len; i++) {
            btn = new ui::Button;{
                btn->AddTo(listBox);
                btn->SetHPreset(ui::Control::Preset::WRAP_AT_CENTER);
                btn->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                std::string bookInfo = books[i].bookName + '\n' + books[i].bookIsbn + "   " + books[i].bookPublicationDate + "   " + books[i].bookAuthor[0] + "...";
                if (books[i].bookTot - books[i].bookBorrowed > 0) bookInfo += "\n可借  " + ToStr(books[i].bookTot - books[i].bookBorrowed);
                btn->SetCaption(bookInfo);
                btn->SetClickCallback(_UI_CALLBACK_{
                    btn->Disable();
                    selectedBook = books[i];
                    select = i;
                    SwitchTo(new BookDetail);
                });
            }
        }
    };

    lastBtn->SetClickCallback(_UI_CALLBACK_{
        lastBtn->Disable();
        nextBtn->Disable();
        if (page > 1) {
            page--;
            resetBookList();
        }
        if (page != 1) lastBtn->Enable();
        if (page != totPage) nextBtn->Enable(); 
    });

    nextBtn->SetClickCallback(_UI_CALLBACK_{
        lastBtn->Disable();
        nextBtn->Disable();
        if (page < totPage) {
            page++;
            resetBookList();
        }
        if (page != 1) lastBtn->Enable();
        if (page != totPage) nextBtn->Enable(); 
    });

    turnToBtn->SetClickCallback(_UI_CALLBACK_{
        std::string pageStr = pageInput->GetText();
        tip->SetVisible(false);
        if (pageStr.empty()) {
            return;
        }
        else {
            for (auto c : pageStr) {
                if (c < '0' || c > '9') {
                    tip->SetVisible(true);
                    return;
                }
            }
            int pageNum = ToNum<int>(pageStr);
            if (pageNum < 1) page = 1;
            else if (pageNum > totPage) page = totPage;
            else page = pageNum;
            pageLabel->SetContent(ToStr(page) + '/' + ToStr(totPage));
            lastBtn->Enable();
            nextBtn->Enable();
            if (page == 1) lastBtn->Disable();
            if (page == totPage) nextBtn->Disable();  
            resetBookList();
        }
    });

    backBtn->SetClickCallback(_UI_CALLBACK_{
        SwitchTo(new EnterLibrary);
    });

    searchOptBtn->SetClickCallback(_UI_CALLBACK_{
        if (!isClicked) {
            isClicked ^= 1;
            searchOptBtn->SetCaption(optStr + "﹀");
            optBox->SetVisible(true);
            ui::Button *btn = nullptr;
            ui::VerticalBox *optvBox1 = nullptr;
            for (long long unsigned int i = 0; i < searchOption.size(); i++) {
                if (i % 3 == 0) {
                    optvBox1 = new ui::VerticalBox;{
                        optvBox1->AddTo(optBox);
                        optvBox1->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        optvBox1->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                        optvBox1->SetGap(5);
                    }
                }
                btn = new ui::Button;{
                    btn->AddTo(optvBox1);
                    btn->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    btn->SetCaption(searchOption[i]);
                    btn->SetFontSize(30);
                    btn->SetClickCallback(_UI_CALLBACK_{
                        optStr = btn->GetCaption();
                        searchOptBtn->SetCaption(optStr + "﹀");
                    });
                }
            }
        }
        else {
            isClicked ^= 1;
            optBox->FreeAll();
            if (optStr == "") searchOptBtn->SetCaption("筛选>");
        }
    });

    searchBtn->SetClickCallback(_UI_CALLBACK_{
        searchBtn->Disable();
        listBox->FreeAll();
        if (userInput == "") {
            ui::Label *tip = new ui::Label;{
                tip->AddTo(listBox);
                tip->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                tip->SetContent("没有匹配的书籍");
            }
            return;
        }
        else {
            listBox->FreeAll();
            ui::LoadingRing *loading = new ui::LoadingRing;{
                loading->AddTo(listBox);
                loading->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                loading->SetSize(80, 80);
                loading->Start();
            }

            int searchType;
            if (optStr == "ISBN") searchType = trm::rqs::BOOK_ISBN;
            else if (optStr == "图书名称") searchType = trm::rqs::BOOK_NAME;
            else if (optStr == "作者") searchType = trm::rqs::BOOK_AUTHOR;
            else if (optStr == "出版日期") searchType = trm::rqs::BOOK_PUBLISHDATE;
            else if (optStr == "馆藏位置") searchType = trm::rqs::BOOK_STROEPOSTION;
            else if (optStr == "分类") searchType = trm::rqs::BOOK_CATAGORY;
            else searchType = trm::rqs::BOOK_NAME;

            Listen(new trm::Sender({trm::rqs::SEARCH_BOOK, userInput, ToStr(searchType), "false", "false"}), _SD_CALLBACK_{
                listBox->FreeAll();
                books.clear();
                if (!reply.empty()) {
                    if (reply[0] == trm::rpl::FAIL) {
                        listBox->Add(new ui::Label("查询失败，请检查输入"));
                        return;
                    }
                    else if (reply[0] == trm::rpl::TIME_OUT) {
                        listBox->Add(new ui::Label("服务端未响应，请稍后再试"));
                        return;
                    }
                    else {
                        for (auto bookInfo : reply) {
                            books.push_back(trm::Book(bookInfo));
                        }
                    }
                }
                len = books.size();
                page = 1;
                totPage = std::max((len + 9) / 10, 1);
                lastBtn->Disable();
                nextBtn->Enable();
                if (page == totPage) nextBtn->Disable(); 
                resetBookList();
            });
        }
        searchBtn->Enable();
    });
}

void vio::BookList::Ready(ui::Screen *screen) noexcept
{
    isClicked = false;
    len = books.size();
    page = 1;
    totPage = std::max((len + 9) / 10, 1);
    if (page == 1) lastBtn->Disable();
    if (page == totPage) nextBtn->Disable();
    selectedBook = trm::Book();
    resetBookList();
}

void vio::BookDetail::Load(ui::Screen *screen) noexcept
{
    ui::Margin *mar = new ui::Margin;{
        mar->AddTo(screen);
        mar->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
        mar->SetMargin(150, 200, 300, 300);
    }
    {   
        ui::VerticalBox *wholeBox = new ui::VerticalBox;{
            wholeBox->AddTo(mar);
            wholeBox->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
        }
        {
            backBtn = new ui::Button;{
                backBtn->AddTo(wholeBox);
                backBtn->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                backBtn->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                backBtn->SetFontSize(40);
                backBtn->SetCaption("←返回");
            }
            ui::VerticalBox *bookDetial = new ui::VerticalBox;{
                bookDetial->AddTo(wholeBox);
                bookDetial->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                bookDetial->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                bookDetial->SetGap(10);
            }
            {
                ui::Label *bookName = new ui::Label;{
                    bookName->AddTo(bookDetial);
                    bookName->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                    bookName->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                    bookName->SetContent(selectedBook.bookName);
                }
                ui::Label *bookIsbn = new ui::Label;{
                    bookIsbn->AddTo(bookDetial);
                    bookIsbn->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                    bookIsbn->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                    bookIsbn->SetContent("ISBN号" + selectedBook.bookIsbn);
                    bookIsbn->SetFontSize(40);
                }
                ui::Label *bookAuthor = new ui::Label;{
                    bookAuthor->AddTo(bookDetial);
                    bookAuthor->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                    bookAuthor->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                    std::string authorStr = "";
                    for (unsigned long long int i = 0; i < selectedBook.bookAuthor.size(); i++) {
                        if (i == selectedBook.bookAuthor.size() - 1) authorStr += selectedBook.bookAuthor[i];
                        else authorStr += selectedBook.bookAuthor[i] + ",";
                    }
                    bookAuthor->SetContent("作者" + authorStr);
                    bookAuthor->SetFontSize(40);
                }
                ui::Label *bookPubDate = new ui::Label;{
                    bookPubDate->AddTo(bookDetial);
                    bookPubDate->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                    bookPubDate->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                    bookPubDate->SetContent("出版时间" + selectedBook.bookPublicationDate);
                    bookPubDate->SetFontSize(40);
                }
                ui::Label *bookStorePos = new ui::Label;{
                    bookStorePos->AddTo(bookDetial);
                    bookStorePos->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                    bookStorePos->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                    bookStorePos->SetContent("藏书位置" + selectedBook.storePosition);
                    bookStorePos->SetFontSize(40);
                }
                ui::Label *bookCatagory = new ui::Label;{
                    bookCatagory->AddTo(bookDetial);
                    bookCatagory->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                    bookCatagory->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                    bookCatagory->SetContent("书籍分类" + selectedBook.bookCatagory);
                    bookCatagory->SetFontSize(40);
                }
                ui::Label *bookTot = new ui::Label;{
                    bookTot->AddTo(bookDetial);
                    bookTot->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                    bookTot->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                    bookTot->SetContent("藏书数量" + ToStr(selectedBook.bookTot));
                    bookTot->SetFontSize(40);
                }
            }
            borrowBox = new ui::VerticalBox;{
                borrowBox->AddTo(wholeBox);
                borrowBox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                borrowBox->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                borrowBox->SetGap(10);
            }
            {
                ui::HorizontalBox *borrowTopBox = new ui::HorizontalBox;{
                    borrowTopBox->AddTo(borrowBox);
                    borrowTopBox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    borrowTopBox->SetVSize(40);
                }
                {
                    borrowTip = new ui::Label;{
                        borrowTip->AddTo(borrowTopBox);
                        borrowTip->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                        borrowTip->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                        borrowTip->SetContent("可借" + ToStr(selectedBook.bookTot - selectedBook.bookBorrowed));
                        borrowTip->SetFontSize(40);
                    }
                    borrowBtn = new ui::Button;{
                        borrowBtn->AddTo(borrowTopBox);
                        borrowBtn->SetCaption("借阅>");
                        borrowBtn->SetHPreset(ui::Control::Preset::WRAP_AT_END);
                        borrowBtn->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                        borrowBtn->SetFontSize(40);
                    }
                }
                borrowBottomBox = new ui::HorizontalBox;{
                    borrowBottomBox->AddTo(borrowBox);
                    borrowBottomBox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    borrowBottomBox->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                    borrowBottomBox->SetVisible(false);
                    borrowBottomBox->HideAll();
                }
                {
                    borrowLast = new ui::Label;{
                        borrowLast->AddTo(borrowBottomBox);
                        borrowLast->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                        borrowLast->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                        borrowLast->SetContent("借阅时间");
                        borrowLast->SetFontSize(40);
                    }
                    confirmBtn = new ui::Button;{
                        confirmBtn->AddTo(borrowBottomBox);
                        confirmBtn->SetHPreset(ui::Container::Preset::WRAP_AT_FRONT);
                        confirmBtn->SetVPreset(ui::Container::Preset::WRAP_AT_FRONT);
                        confirmBtn->SetCaption("确认");
                    }

                    for (int i = 10; i <= 60; i += 10) {
                        ui::Button *btn = new ui::Button;{
                            btn->AddTo(borrowBottomBox);
                            btn->SetHPreset(ui::Container::Preset::WRAP_AT_FRONT);
                            btn->SetVPreset(ui::Container::Preset::WRAP_AT_FRONT);
                            btn->SetCaption(ToStr(i) + "天");
                            btn->SetFontSize(40);
                        }
                        btn->SetClickCallback(_UI_CALLBACK_{
                            day = i;
                            borrowLast->SetContent("借阅时间 " + ToStr(day) + " 天");
                        });
                    }
                }
            }
        }   
    }
}

void vio::BookDetail::Logic(ui::Screen *screen) noexcept
{
    backBtn->SetClickCallback(_UI_CALLBACK_{
        SwitchTo(new BookList);
    });

    borrowBtn->SetClickCallback(_UI_CALLBACK_{
        if (!isClicked) {
            isClicked ^= 1;
            borrowBottomBox->ShowAll();
            borrowBottomBox->SetVisible(true);
            borrowBtn->SetCaption(std::string("借阅") + "﹀");
        }
        else {
            isClicked ^= 1;
            borrowBottomBox->HideAll();
            borrowBottomBox->SetVisible(false);
            borrowBtn->SetCaption("借阅>");
        }
    });

    confirmBtn->SetClickCallback(_UI_CALLBACK_{
        if (day == 0) {
            borrowLast->SetContent("借阅时间非法");
            return;
        }
        else {
            screen->HideAll();
            std::string tip = "是否确认借阅\n" + trm::Book::GetInfo(selectedBook);
            tip += "\n借阅时间 " + ToStr(day) + " 天";
            int ret = MessageBox(screen, tip, {"确认", "取消"});
            if (ret == 1) {
                screen->ShowAll();
                return;
            }
            else {
                Listen(new trm::Sender({trm::rqs::BORROW_BOOK, account.code, password, selectedBook.bookIsbn, ToStr(day)}), _SD_CALLBACK_{
                    screen->FreeAllVisible();
                    if (reply.empty()) {
                        int ret = MessageBox(screen, "借阅失败，请稍后再试", {"确认"});
                        if (ret == 0) {
                            screen->FreeAllVisible();
                            screen->ShowAll();
                        }
                        return;
                    }
                    else if (reply[0] == trm::rpl::TIME_OUT) {
                        int ret = MessageBox(screen, "服务端未响应，请稍后再试", {"确认"});
                        if (ret == 0) {
                            screen->FreeAllVisible();
                            screen->ShowAll();
                        }
                    }
                    else if (reply[0] == trm::rpl::SUCC) {
                        selectedBook.bookBorrowed++;
                        books[select].bookBorrowed++;
                        time_t time = std::time(nullptr) + day * 24 * 3600;
                        tm *lt = new tm;
                        localtime_s(lt, &time);
                        std::string borrowTime = std::to_string(lt->tm_year + 1900) + "-" + std::to_string(lt->tm_mon + 1) + "-" + std::to_string(lt->tm_mday);
                        borrowTip->SetContent("可借" + ToStr(selectedBook.bookTot - selectedBook.bookBorrowed));
                        int ret = MessageBox(screen, "借阅成功\n将在" + borrowTime + "到期", {"确认"});
                        if (ret == 0) {
                            screen->FreeAllVisible();
                            screen->ShowAll();
                        }
                        return;
                    }
                    else if (reply[0] == trm::rpl::NO_BOOK) {
                        int ret = MessageBox(screen, "借阅的图书不存在", {"确认"});
                        if (ret == 0) {
                            screen->FreeAllVisible();
                            screen->ShowAll();
                        }
                        return;
                    }
                    else if (reply[0] == trm::rpl::NO_SPARE_BOOK) {
                        int ret = MessageBox(screen, "剩余可借阅图书不足", {"确认"});
                        if (ret == 0) {
                            screen->FreeAllVisible();
                            screen->ShowAll();
                        }
                        return;
                    }
                    else {
                        assert(false);
                    }
                });
            }
        }
    });
}

void vio::BookDetail::Ready(ui::Screen *screen) noexcept
{
    isClicked = false;
}

void vio::BorrowManage::Load(ui::Screen *screen) noexcept
{
    ui::Margin *mar = new ui::Margin;{
        mar->AddTo(screen);
        mar->SetMargin(150, 200, 400, 400);
        mar->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
    }
    {
        ui::VerticalBox *wholeBox = new ui::VerticalBox;{
            wholeBox->AddTo(mar);
            wholeBox->SetHSizeValueType(ui::Control::ValueType::PERCENTAGE);
            wholeBox->SetHSize(50);
            wholeBox->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
        }
        {
            ui::HorizontalBox *topBox = new ui::HorizontalBox;{
                topBox->AddTo(wholeBox);
                topBox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                topBox->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
            }
            {
                backBtn = new ui::Button;{
                    backBtn->AddTo(topBox);
                    backBtn->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                    backBtn->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                    backBtn->SetFontSize(40);
                    backBtn->SetCaption("←返回");
                }
                ui::Flat *flat = new ui::Flat;{
                    flat->AddTo(topBox);
                    flat->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    flat->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                }
                refleshBtn = new ui::Button;{
                    refleshBtn->AddTo(topBox);
                    refleshBtn->SetHPreset(ui::Control::Preset::PLACE_AT_END);
                    refleshBtn->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                    refleshBtn->SetFontSize(40);
                    refleshBtn->SetCaption("刷新");
                }
            }
            ui::HorizontalBox *mainBox = new ui::HorizontalBox;{
                mainBox->AddTo(wholeBox);
                mainBox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                mainBox->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
            }
            {
                ui::VerticalBox *leftBox = new ui::VerticalBox;{
                    leftBox->AddTo(mainBox);
                    leftBox->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                    leftBox->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                }
                {
                    ui::Label *lfTip = new ui::Label;{
                        lfTip->AddTo(leftBox);
                        lfTip->SetHPreset(ui::Control::Preset::WRAP_AT_CENTER);
                        lfTip->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                        lfTip->SetContent("借阅记录");
                        lfTip->SetFontSize(40);
                    }
                    borrowLogBox = new ui::VerticalScrollingBox;{
                        borrowLogBox->AddTo(leftBox);
                        borrowLogBox->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        borrowLogBox->SetInsideBoxScrollable(true);
                        borrowLogBox->SetVMinSize(300);
                    }
                    ui::HorizontalBox *pageBox = new ui::HorizontalBox;{
                        pageBox->AddTo(leftBox);
                        pageBox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        pageBox->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                    }
                    {
                        lastBtn = new ui::Button;{
                            lastBtn->AddTo(pageBox);
                            lastBtn->SetHPreset(ui::Control::Preset::WRAP_AT_CENTER);
                            lastBtn->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                            lastBtn->SetCaption("上一页");
                            lastBtn->SetFontSize(40);
                        }
                        pageLabel = new ui::Label;{
                            pageLabel->AddTo(pageBox);
                            pageLabel->SetHPreset(ui::Control::Preset::WRAP_AT_CENTER);
                            pageLabel->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                            pageLabel->SetFontSize(40);
                            pageLabel->SetContent(ToStr(page) + '/' + ToStr(totPage));
                        }
                        nextBtn = new ui::Button;{
                            nextBtn->AddTo(pageBox);
                            nextBtn->SetHPreset(ui::Control::Preset::WRAP_AT_CENTER);
                            nextBtn->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                            nextBtn->SetCaption("下一页");
                            nextBtn->SetFontSize(40);
                        }
                    }
                    ui::HorizontalBox *turnTobox = new ui::HorizontalBox;{
                        turnTobox->AddTo(leftBox);
                        turnTobox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        turnTobox->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                    }
                    {
                        confirmTurnBtn = new ui::Button;{
                            confirmTurnBtn->AddTo(turnTobox);
                            confirmTurnBtn->SetHPreset(ui::Control::Preset::WRAP_AT_CENTER);
                            confirmTurnBtn->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                            confirmTurnBtn->SetFontSize(40);
                            confirmTurnBtn->SetCaption("跳转到");
                        }
                        pageInput = new ui::InputBox;{
                            pageInput->AddTo(turnTobox);
                            pageInput->SetHSize(200);
                            pageInput->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        }
                        tip = new ui::Label;{
                            tip->AddTo(turnTobox);
                            tip->SetHPreset(ui::Control::Preset::WRAP_AT_END);
                            tip->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                            tip->SetFontSize(40);
                            tip->SetContent("页码需为非0正整数");
                            tip->SetVisible(false);
                        }
                    }
                }
                ui::VerticalBox *rightBox = new ui::VerticalBox;{
                    rightBox->AddTo(mainBox);
                    rightBox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    rightBox->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                }
                {
                    borrowDetailBox = new ui::VerticalScrollingBox;{
                        borrowDetailBox->AddTo(rightBox);
                        borrowDetailBox->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        borrowDetailBox->SetInsideBoxScrollable(true);
                    }
                    returnBtn = new ui::Button;{
                        returnBtn->AddTo(rightBox);
                        returnBtn->SetHPreset(ui::Control::Preset::WRAP_AT_END);
                        returnBtn->SetVPreset(ui::Control::Preset::WRAP_AT_END);
                        returnBtn->SetFontSize(40);
                        returnBtn->SetCaption("确认归还");
                    }
                }
            }
        }
    }
}

void vio::BorrowManage::Logic(ui::Screen *screen) noexcept
{
    backBtn->SetClickCallback(_UI_CALLBACK_{
        SwitchTo(new EnterLibrary);
    });

    auto resetBorrowDetail = [=, this]() -> void {
        borrowDetailBox->FreeAll();
        ui::Label *borrowTip = new ui::Label;{
            borrowTip->AddTo(borrowDetailBox);
            borrowTip->SetHPreset(ui::Control::Preset::WRAP_AT_CENTER);
            borrowTip->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
            borrowTip->SetFontSize(40);
            borrowTip->SetContent("====借阅详情====");
        }
        ui::Label *borrowName = new ui::Label;{
            borrowName->AddTo(borrowDetailBox);
            borrowName->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
            borrowName->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
            borrowName->SetFontSize(40);
            borrowName->SetContent("图书名称" + bookName[select]);
        }
        ui::Label *borrowIsbn = new ui::Label;{
            borrowIsbn->AddTo(borrowDetailBox);
            borrowIsbn->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
            borrowIsbn->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
            borrowIsbn->SetFontSize(40);
            borrowIsbn->SetContent("ISBN号" + borrowLogs[select].bookIsbn);
        }
        ui::Label *borrowTime = new ui::Label;{
            borrowTime->AddTo(borrowDetailBox);
            borrowTime->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
            borrowTime->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
            borrowTime->SetFontSize(40);
            borrowTime->SetContent("借阅时间" + borrowLogs[select].start.GetDate());
        }
        ui::Label *borrowEndTime = new ui::Label;{
            borrowEndTime->AddTo(borrowDetailBox);
            borrowEndTime->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
            borrowEndTime->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
            borrowEndTime->SetFontSize(40);
            borrowEndTime->SetContent("到期时间" + borrowLogs[select].end.GetDate());
        }
    };

    resetBorrowList = [=, this]() -> void {
        borrowLogBox->FreeAll();
        borrowDetailBox->FreeAll();
        
        ui::Label *listTip = nullptr;
        ui::Button *btn = nullptr;
        if (len == 0) {
            listTip = new ui::Label;{
                listTip->AddTo(borrowLogBox);
                listTip->SetHPreset(ui::Control::Preset::PLACE_AT_CENTER);
                listTip->SetVPreset(ui::Control::Preset::PLACE_AT_CENTER);
                listTip->SetContent("暂无借阅记录");
                listTip->SetFontSize(40);
            }
            return;
        }
        for (int i = (page - 1) * 10; i < page * 10 + 10 && i < len; i++) {
            btn = new ui::Button;{
                btn->AddTo(borrowLogBox);
                btn->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                btn->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                btn->SetFontSize(40);
                btn->SetCaption(bookName[i] + '\n' + "截止" + borrowLogs[i].end.GetDate());
                btn->SetClickCallback(_UI_CALLBACK_{
                    select = i;
                    returnBtn->Enable();
                    resetBorrowDetail();
                });
            }
        }
    };

    lastBtn->SetClickCallback(_UI_CALLBACK_{
        lastBtn->Enable();
        nextBtn->Enable();
        if (page > 1) page--;
        resetBorrowList();
        pageLabel->SetContent(ToStr(page) + '/' + ToStr(totPage));
        if (page == 1) lastBtn->Disable();
        if (page == totPage) nextBtn->Disable();
    });

    nextBtn->SetClickCallback(_UI_CALLBACK_{
        lastBtn->Enable();
        nextBtn->Enable();
        if (page < totPage) page++;
        resetBorrowList();
        pageLabel->SetContent(ToStr(page) + '/' + ToStr(totPage));
        if (page == 1) lastBtn->Disable();
        if (page == totPage) nextBtn->Disable();
    });

    confirmTurnBtn->SetClickCallback(_UI_CALLBACK_{
        std::string input = pageInput->GetText();
        tip->SetVisible(false);
        if (input.empty()) {
            return;
        }
        else {
            for (auto c : input) {
                if (c < '0' || c > '9') {
                    tip->SetVisible(true);
                    return;
                }
            }
            int inputPage = ToNum<int>(input);
            if (inputPage < 1) page = 1;
            else if (inputPage > totPage) page = totPage;
            else page = inputPage;
            pageLabel->SetContent(ToStr(page) + '/' + ToStr(totPage));
            resetBorrowList();
        }
    });

    refleshBtn->SetClickCallback(_UI_CALLBACK_{
        borrowLogBox->FreeAll();
        borrowDetailBox->FreeAll();
        ui::LoadingRing *ld = new ui::LoadingRing;{
            ld->AddTo(borrowLogBox);
            ld->SetHSize(100);
            ld->SetVSize(100);
            ld->Start();
        }
        Listen(new trm::Sender({trm::rqs::GET_ACCOUNT_BORROW_LIST, account.code, password}), _SD_CALLBACK_{
            borrowLogBox->FreeAll();
            borrowLogs.clear();
            bookName.clear();
            screen->HideAll();
            if (reply.empty()) {
                screen->ShowAll();
            }
            else if (reply[0] == trm::rpl::TIME_OUT) {
                int ret = MessageBox(screen, "服务端请求超时，请稍后再试", {"确认"});
                if (ret == 0) {
                    screen->FreeAllVisible();
                    screen->ShowAll();
                }
                return;
            }
            else if (reply[0] == trm::rpl::NO_ACCOUNT) {
                screen->ShowAll();
                screen->FreeAllVisible();
                int reply = MessageBox(screen, "该账号不存在", {"确认"});
                if (reply == 0) {
                    SwitchTo(new EnterLibrary);
                }
            }
            else {
                screen->ShowAll();
                int size = reply.size();
                for (int i = 0; i < size; i += 2) {
                    borrowLogs.emplace_back(reply[i]);
                    bookName.emplace_back(reply[i + 1]);
                }
            }
            len = borrowLogs.size();
            totPage = std::max((len + 9) / 10, 1);
            page = 1;
            resetBorrowList();
        });
    });

    returnBtn->SetClickCallback(_UI_CALLBACK_{
        screen->HideAll();
        std::string tip = "是否确认归还\n" + bookName[select] + '\n' + borrowLogs[select].end.GetDate();
        int ret = MessageBox(screen, tip, {"确认", "取消"});
        if (ret == 1) {
            screen->ShowAll();
            return;
        }
        else {
            Listen(new trm::Sender({trm::rqs::RETURN_BOOK, account.code, password, borrowLogs[select].bookIsbn, ToStr(borrowLogs[select].start.currantTime)}), _SD_CALLBACK_{
                screen->FreeAllVisible();
                if (reply.empty()) {
                    int ret = MessageBox(screen, "归还失败，请稍后再试", {"确认"});
                    if (ret == 0) {
                        screen->FreeAllVisible();
                        screen->ShowAll();
                    }
                    return;
                }
                else if (reply[0] == trm::rpl::FAIL) {
                    int ret = MessageBox(screen, "归还失败，请稍后再试", {"确认"});
                    if (ret == 0) {
                        screen->FreeAllVisible();
                        screen->ShowAll();
                    }
                    return;
                }
                else if (reply[0] == trm::rpl::SUCC) {
                    int ret = MessageBox(screen, "归还成功", {"确认"});
                    if (ret == 0) {
                        screen->FreeAllVisible();
                        screen->ShowAll();
                    }
                    return;
                }
                else if (reply[0] == trm::rpl::NO_BORROW_RECORD) {
                    int ret = MessageBox(screen, "您无借阅记录", {"确认"});
                    if (ret == 0) {
                        screen->FreeAllVisible();
                        screen->ShowAll();
                    }
                    return;
                }
                else if (reply[0] == trm::rpl::TIME_OUT) {
                    int ret = MessageBox(screen, "服务端请求超时，请稍后再试", {"确认"});
                    if (ret == 0) {
                        screen->FreeAllVisible();
                        screen->ShowAll();
                    }
                    return;
                }
            });
        }
    });
}

void vio::BorrowManage::Ready(ui::Screen *screen) noexcept
{
    ui::LoadingRing *ld = new ui::LoadingRing;{
        ld->AddTo(borrowLogBox);
        ld->SetHSize(100);
        ld->SetVSize(100);
        ld->Start();
    }
    Listen(new trm::Sender({trm::rqs::GET_ACCOUNT_BORROW_LIST, account.code, password}), _SD_CALLBACK_{
        borrowLogBox->FreeAll();
        borrowLogs.clear();
        bookName.clear();
        screen->HideAll();
        if (reply.empty()) {
            screen->ShowAll();
        }
        else if (reply[0] == trm::rpl::TIME_OUT) {
            int ret = MessageBox(screen, "服务端请求超时，请稍后再试", {"确认"});
            if (ret == 0) {
                screen->FreeAllVisible();
                screen->ShowAll();
            }
            return;
        }
        else if (reply[0] == trm::rpl::NO_ACCOUNT) {
            screen->ShowAll();
            screen->FreeAllVisible();
            int reply = MessageBox(screen, "该账号不存在", {"确认"});
            if (reply == 0) {
                SwitchTo(new EnterLibrary);
            }
        }
        else {
            screen->ShowAll();
            int size = reply.size();
            for (int i = 0; i < size; i += 2) {
                borrowLogs.emplace_back(reply[i]);
                bookName.emplace_back(reply[i + 1]);
            }
        }
        len = borrowLogs.size();
        totPage = std::max((len + 9) / 10, 1);
        page = 1;
        resetBorrowList();
    });

    if (page == 1) lastBtn->Disable();
    if (page == totPage) nextBtn->Disable();
    returnBtn->Disable();
}

void vio::BookManage::Load(ui::Screen *screen) noexcept
{
    ui::Margin *mar = new ui::Margin;{
        mar->AddTo(screen);
        mar->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
        mar->SetMargin(100, 100, 150, 150);
    }
    {
        ui::HorizontalBox *wholeBox = new ui::HorizontalBox;{
            wholeBox->AddTo(mar);
            wholeBox->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
        }
        {
            ui::VerticalBox *leftMainBox = new ui::VerticalBox;{
                leftMainBox->AddTo(wholeBox);
                leftMainBox->SetHSizeValueType(ui::Control::ValueType::PERCENTAGE);
                leftMainBox->SetHSize(50);
                leftMainBox->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
            }
            {
                backBtn = new ui::Button;{
                    backBtn->AddTo(leftMainBox);
                    backBtn->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                    backBtn->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                    backBtn->SetFontSize(40);
                    backBtn->SetCaption("←返回");
                }
                ui::HorizontalBox *lfTopBox = new ui::HorizontalBox;{
                    lfTopBox->AddTo(leftMainBox);
                    lfTopBox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    lfTopBox->SetVSize(40);
                }
                {
                    restoreBookBtn = new ui::Button;{
                        restoreBookBtn->AddTo(lfTopBox);
                        restoreBookBtn->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        restoreBookBtn->SetCaption("新增图书");
                        restoreBookBtn->SetFontSize(40);
                    }
                    modifyBookBtn = new ui::Button;{
                        modifyBookBtn->AddTo(lfTopBox);
                        modifyBookBtn->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        modifyBookBtn->SetCaption("修改图书");
                        modifyBookBtn->SetFontSize(40);
                    }
                    removeBookBtn = new ui::Button;{
                        removeBookBtn->AddTo(lfTopBox);
                        removeBookBtn->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        removeBookBtn->SetCaption("删除图书");
                        removeBookBtn->SetFontSize(40);
                    }
                }
                lfMidBox = new ui::VerticalBox;{
                    lfMidBox->AddTo(leftMainBox);
                    lfMidBox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    lfMidBox->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    lfMidBox->SetGap(10);
                }
                {   
                    ui::Center *center = new ui::Center;{
                        center->AddTo(lfMidBox);
                        center->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    }
                    {
                        ui::Label *lfmdTip = new ui::Label("请选择你的操作");{
                            lfmdTip->AddTo(center);
                            lfmdTip->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                            lfmdTip->SetHPreset(ui::Control::Preset::WRAP_AT_CENTER);
                        }
                    }
                }
            }
            ui::VerticalBox *rightMainBox = new ui::VerticalBox;{
                rightMainBox->AddTo(wholeBox);
                rightMainBox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                rightMainBox->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
            }
            {
                detailBox = new ui::VerticalScrollingBox;{
                    detailBox->AddTo(rightMainBox);
                    detailBox->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    detailBox->SetInsideBoxScrollable(true);
                }
                {   
                    ui::Center *center = new ui::Center;{
                        center->AddTo(detailBox);
                        center->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    }
                    {
                        ui::Label *rtmdTip = new ui::Label("请选择你的操作");{
                            rtmdTip->AddTo(center);
                            rtmdTip->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
                        }
                    }
                }
                ui::HorizontalBox *rtfootBox = new ui::HorizontalBox;{
                    rtfootBox->AddTo(rightMainBox);
                    rtfootBox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    rtfootBox->SetVSize(80);
                }
                {   
                    rtFootFlat = new ui::Flat;{
                        rtFootFlat->AddTo(rtfootBox);
                        rtFootFlat->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        rtFootFlat->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    }
                    confirmBtn = new ui::Button;{
                        confirmBtn->AddTo(rtfootBox);
                        confirmBtn->SetHPreset(ui::Control::Preset::PLACE_AT_END);
                        confirmBtn->SetSize(30, 30);
                        confirmBtn->SetCaption("确认");
                    }
                }
            }
        }
    }
}

void vio::BookManage::Logic(ui::Screen *screen) noexcept
{
    auto restoreprework = [=, this]() -> void {
        ui::Label *label = new ui::Label;{
            label->AddTo(lfMidBox);
            label->SetFontSize(40);
            label->SetContent(opt);
            label->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
        }
        ui::VerticalBox *vbox = new ui::VerticalBox;{
            vbox->AddTo(wholeBox);
            vbox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
            vbox->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
        }
        {
            ui::HorizontalBox *hbox = new ui::HorizontalBox;{
                hbox->AddTo(vbox);
                hbox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                hbox->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
            }
            {
                ui::Label *storenum = new ui::Label;{
                    storenum->AddTo(hbox);
                    storenum->SetContent("存放数量");
                    storenum->SetHSize(100);
                }
                ui::InputBox *numInput = new ui::InputBox;{
                    numInput->AddTo(hbox);
                    numInput->SetHSize(100);
                    numInput->SetText(bookNum);
                    numInput->SetInputCallback(_UI_CALLBACK_{
                        bookNum = numInput->GetText();
                    });
                }
            }
            numLimitTip = new ui::Label;{
                numLimitTip->AddTo(vbox);
                numLimitTip->SetContent("输入需为大于0的整数");
                numLimitTip->SetFontSize(35);
                numLimitTip->SetFontColor(sf::Color::Red);
                numLimitTip->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                numLimitTip->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                numLimitTip->SetVisible(false);
            }
        }
    };
    auto removeprework = [=, this]() -> void {
        ui::VerticalBox *vbox = new ui::VerticalBox;{
            vbox->AddTo(wholeBox);
            vbox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
            vbox->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
        }
        {
            ui::HorizontalBox *hbox = new ui::HorizontalBox;{
                hbox->AddTo(vbox);
                hbox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                hbox->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
            }
            {
                ui::Label *storenum = new ui::Label;{
                    storenum->AddTo(hbox);
                    storenum->SetContent("删除数量");
                    storenum->SetHSize(100);
                }
                ui::InputBox *numInput = new ui::InputBox;{
                    numInput->AddTo(hbox);
                    numInput->SetHSize(100);
                    if (selectedBook.bookTot != 0) numInput->SetText(std::to_string(selectedBook.bookTot));
                    numInput->SetInputCallback(_UI_CALLBACK_{
                        bookNum = numInput->GetText();
                    });
                }
                ui::Button *allBtn = new ui::Button;{
                    allBtn->AddTo(hbox);
                    allBtn->SetCaption("all");
                    allBtn->SetHSize(80);
                    allBtn->SetClickCallback(_UI_CALLBACK_{
                        bookNum = "all";
                        numInput->SetText(bookNum);
                    });
                }
            }
            numLimitTip = new ui::Label;{
                numLimitTip->AddTo(vbox);
                numLimitTip->SetContent("输入需为大于0的整数, 或者all");
                numLimitTip->SetFontSize(35);
                numLimitTip->SetFontColor(sf::Color::Red);
                numLimitTip->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                numLimitTip->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                numLimitTip->SetVisible(false);
            }
        }
    };
#pragma region right page logic
   auto drawCatergoryBox = [=, this](std::vector<std::string> &catergories) -> void {
        int slen = 0;
        int cnt = 0;
        catergoryLabel = new ui::Label("请选择分类");{
            catergoryLabel->SetFontSize(40);
            catergoryLabel->AddTo(catergoryBox);
            if (selectedBook.bookCatagory != "") catergoryLabel->SetContent(selectedBook.bookCatagory);
            catergoryLabel->SetHPreset(ui::Control::Preset::WRAP_AT_CENTER);
            catergoryLabel->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
        }
        ui::HorizontalBox *hbox = nullptr;
        ui::Button *catergoryBtn = nullptr;
        for (auto catergory : catergories) {
            slen += catergory.length();
            if ((slen >= 30 || catergory.length() >= 15) && cnt) {
                slen = 0;
                hbox = new ui::HorizontalBox;{
                    hbox->AddTo(catergoryBox);
                    hbox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    hbox->SetVSize(40);
                }
                cnt = 0;
            }
            if (hbox == nullptr) {
                hbox = new ui::HorizontalBox;{
                    hbox->AddTo(catergoryBox);
                    hbox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    hbox->SetVSize(40);
                }
            }
            catergoryBtn = new ui::Button;{
                catergoryBtn->AddTo(hbox);
                catergoryBtn->SetFontSize(40);
                catergoryBtn->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                catergoryBtn->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                catergoryBtn->SetCaption(catergory);
                catergoryBtn->SetClickCallback(_UI_CALLBACK_{
                    selectedBook.bookCatagory = catergoryBtn->GetCaption();
                    catergoryLabel->SetContent(selectedBook.bookCatagory);
                });
            }
            cnt++;
        }
    };

    reSetCatergoryBox = [=, this]() -> void {
        if (!isChanged) return;
        isChanged ^= 1;
        catergoryBox->FreeAll();
        if (selectedBook.storePosition == "302") {
            drawCatergoryBox(room302);
        } else if (selectedBook.storePosition == "303") {
            drawCatergoryBox(room303);
        } else if (selectedBook.storePosition == "401") {
            drawCatergoryBox(room401);
        } else if (selectedBook.storePosition == "402") {
            drawCatergoryBox(room402);
        } else if (selectedBook.storePosition == "403") {
            drawCatergoryBox(room403);
        } else if (selectedBook.storePosition == "621") {
            drawCatergoryBox(room621);
        }
    };

    auto setStorePositon = [=, this]() -> void {
        for (auto btn : {room302Btn, room303Btn, room401Btn, room402Btn, room403Btn, room621Btn}) {
            btn->SetClickCallback(_UI_CALLBACK_{
                selectedBook.storePosition = btn->GetCaption();
                storePosition->SetContent("图书位置" + selectedBook.storePosition);
                isChanged ^= 1;
                reSetCatergoryBox();
            });
        }
    };

    auto printBookDetail = [=, this]() -> void {
        ui::VerticalBox *rtMidBox = new ui::VerticalBox;{
            rtMidBox->AddTo(wholeBox);
            rtMidBox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
            rtMidBox->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
        }
        {   
            ui::HorizontalBox *hbox = new ui::HorizontalBox;{
                hbox->AddTo(rtMidBox);
                hbox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
            }
            {
                ui::Label *author = new ui::Label("作者");{
                    author->AddTo(hbox);
                    author->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                    author->SetHSize(100);
                }
                ui::InputBox *authorInput = new ui::InputBox;{
                    authorInput->AddTo(hbox);
                    authorInput->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                    authorInput->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    if (!selectedBook.bookAuthor.empty()) {
                        std::string text = "";
                        int size = selectedBook.bookAuthor.size();
                        for (int i = 0; i < size; i++) {
                            if (i == size - 1) {
                                text += selectedBook.bookAuthor[i];
                            }
                            else text += selectedBook.bookAuthor[i] + ",";
                        }
                        authorInput->SetText(text);
                        bookAuthor = text;
                    }
                }
                authorInput->SetInputCallback(_UI_CALLBACK_{
                    bookAuthor= authorInput->GetText();
                });
            }
            ui::Label *tip = new ui::Label;{
                tip->AddTo(rtMidBox);
                tip->SetContent("多个作者请用\",\"隔开");
                tip->SetFontSize(35);
                tip->SetFontColor(sf::Color::Red);
                tip->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                tip->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
            }
        }
        rtMidBox = new ui::VerticalBox;{
            rtMidBox->AddTo(wholeBox);
            rtMidBox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
            rtMidBox->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
        }
        {
            ui::HorizontalBox *hbox = new ui::HorizontalBox;{
                hbox->AddTo(rtMidBox);
                hbox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
            }
            {
                ui::Label *publishDate = new ui::Label("出版日期");{
                    publishDate->AddTo(hbox);
                    publishDate->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                    publishDate->SetHSize(100);
                }
                ui::InputBox *publishDateInput = new ui::InputBox;{
                    publishDateInput->AddTo(hbox);
                    publishDateInput->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                    publishDateInput->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    if (selectedBook.bookPublicationDate != "") publishDateInput->SetText(selectedBook.bookPublicationDate);    
                }
                publishDateInput->SetInputCallback(_UI_CALLBACK_{
                    selectedBook.bookPublicationDate = publishDateInput->GetText();
                });
            }
            bookpublishDateLimitTip = new ui::Label;{
                bookpublishDateLimitTip->AddTo(rtMidBox);
                bookpublishDateLimitTip->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                bookpublishDateLimitTip->SetHSize(300);
                bookpublishDateLimitTip->SetFontSize(35);
                bookpublishDateLimitTip->SetFontColor(sf::Color::Red);
                bookpublishDateLimitTip->SetContent("需要输入合法日期，同时满足xxxx-xx-xx格式");
                bookpublishDateLimitTip->SetVisible(false);
            }
        }
        ui::HorizontalBox *hbox1 = new ui::HorizontalBox;{
            hbox1->AddTo(wholeBox);
            hbox1->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
            hbox1->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
        }
        {
            storePosition = new ui::Label;{
                storePosition->AddTo(hbox1);
                storePosition->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                storePosition->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                storePosition->SetContent("图书位置");
                if (selectedBook.storePosition != "") storePosition->SetContent("图书位置" + selectedBook.storePosition);
            }
            room302Btn = new ui::Button;{
                room302Btn->AddTo(hbox1);
                room302Btn->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                room302Btn->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                room302Btn->SetCaption("302");
            }
            room303Btn = new ui::Button;{
                room303Btn->AddTo(hbox1);
                room303Btn->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                room303Btn->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                room303Btn->SetCaption("303");
            }
            room401Btn = new ui::Button;{
                room401Btn->AddTo(hbox1);
                room401Btn->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                room401Btn->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                room401Btn->SetCaption("401");
            }
            room402Btn = new ui::Button;{
                room402Btn->AddTo(hbox1);
                room402Btn->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                room402Btn->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                room402Btn->SetCaption("402");
            }
            room403Btn = new ui::Button;{
                room403Btn->AddTo(hbox1);
                room403Btn->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                room403Btn->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                room403Btn->SetCaption("403");
            }
            room621Btn = new ui::Button;{
                room621Btn->AddTo(hbox1);
                room621Btn->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                room621Btn->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                room621Btn->SetCaption("621");
            }
        }
        catergoryBox = new ui::VerticalBox;{
            catergoryBox->AddTo(wholeBox);
            catergoryBox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
            catergoryBox->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
        }
        {
            ui::Label *catergory = new ui::Label;{
                catergory->AddTo(catergoryBox);
                catergory->SetHPreset(ui::Control::Preset::WRAP_AT_CENTER);
                catergory->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                catergory->SetContent("图书类别:  请选择图书位置");
            }
        }
    };

    auto printBasicDetail = [=, this]() -> void {
        ui::Margin *mar = new ui::Margin;{
            mar->AddTo(detailBox);
            mar->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
            mar->SetMargin(50, 50, 50, 50);
        }
        {
            wholeBox = new ui::VerticalBox;{
                wholeBox->AddTo(mar);
                wholeBox->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                wholeBox->SetGap(80);
            }
            {
                ui::VerticalBox *rtMidBox = new ui::VerticalBox;{
                    rtMidBox->AddTo(wholeBox);
                    rtMidBox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    rtMidBox->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                }
                {
                    ui::HorizontalBox *hbox = new ui::HorizontalBox;{
                        hbox->AddTo(rtMidBox);
                        hbox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    }
                    {
                        ui::Label *isbn = new ui::Label("ISBN");{
                            isbn->AddTo(hbox);
                            isbn->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                            isbn->SetHSize(100);
                        }
                        if (opt != "删除图书") {
                            ui::InputBox *isbnInput = new ui::InputBox;{
                                isbnInput->AddTo(hbox);
                                isbnInput->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                                isbnInput->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                                if (selectedBook.bookIsbn != "") isbnInput->SetText(selectedBook.bookIsbn);
                            }
                            isbnInput->SetInputCallback(_UI_CALLBACK_{
                                selectedBook.bookIsbn = isbnInput->GetText();
                            });
                            bookisbnLimitTip = new ui::Label;{
                                bookisbnLimitTip->AddTo(rtMidBox);
                                bookisbnLimitTip->SetHPreset(ui::Control::Preset::WRAP_AT_CENTER);
                                bookisbnLimitTip->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                                bookisbnLimitTip->SetFontSize(35);
                                bookisbnLimitTip->SetFontColor(sf::Color::Red);
                                bookisbnLimitTip->SetContent("ISBN的输入形式需为xxx-x-x-xxxxxx-x, 其中x为数字");
                                bookisbnLimitTip->SetVisible(false);
                            }

                        }
                        else {
                            ui::Label *isbnLabel = new ui::Label;{
                                isbnLabel->AddTo(hbox);
                                isbnLabel->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                                isbnLabel->SetHSize(200);
                                isbnLabel->SetContent(selectedBook.bookIsbn);
                            }
                        }
                    }
                }
                ui::HorizontalBox *hbox1 = new ui::HorizontalBox;{
                    hbox1->AddTo(wholeBox);
                    hbox1->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    hbox1->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                }
                {
                    ui::Label *name = new ui::Label("图书名称");{
                        name->AddTo(hbox1);
                        name->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                        name->SetHSize(100);
                    }
                    if (opt != "删除图书") {
                        ui::InputBox *nameInput = new ui::InputBox;{
                            nameInput->AddTo(hbox1);
                            nameInput->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                            nameInput->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                            if (selectedBook.bookName != "") nameInput->SetText(selectedBook.bookName);
                        }
                        nameInput->SetInputCallback(_UI_CALLBACK_{
                            selectedBook.bookName = nameInput->GetText();
                        });
                    }
                    else {
                        ui::Label *nameLabel = new ui::Label;{
                            nameLabel->AddTo(hbox1);
                            nameLabel->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                            nameLabel->SetHSize(200);
                            nameLabel->SetContent(selectedBook.bookName);
                        }
                    }
                
                }
            }
        }
    };

#pragma region left page logic
    auto optEnable = [=, this]() -> void {
        if (opt == "新增图书") {
            restoreBookBtn->Disable();
            modifyBookBtn->Enable();
            removeBookBtn->Enable();
        } else if (opt == "修改图书") {
            restoreBookBtn->Enable();
            modifyBookBtn->Disable();
            removeBookBtn->Enable();
        } else if (opt == "删除图书") {
            restoreBookBtn->Enable();
            modifyBookBtn->Enable();
            removeBookBtn->Disable();
        }
    };

    auto resetLeftDetail = [=, this]() -> void {
        bookList->FreeAllVisible();
        ui::Button *btn;
        for (int i = (page - 1) * 10; i < len && i < page * 10; i++) {
            btn = new ui::Button;{
                btn->AddTo(bookList);
                btn->SetFontSize(35);
                btn->SetHPreset(ui::Control::Preset::WRAP_AT_CENTER);
                btn->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                btn->SetCaption(books[i].bookName + "\n" + books[i].bookIsbn + "  存量" + ToStr(books[i].bookTot));
                btn->SetCaption(books[i].bookName + "\n" + books[i].bookIsbn + "  存量" + ToStr(books[i].bookTot));
            }
            btn->SetClickCallback(_UI_CALLBACK_{
                selectedBook = books[i];
                bookAuthor = "";
                int len = selectedBook.bookAuthor.size();
                for (int i = 0; i < len; i++) {
                    if (i == len - 1) bookAuthor += selectedBook.bookAuthor[i];
                    else bookAuthor += selectedBook.bookAuthor[i] + ",";
                }
                bookNum = ToStr(selectedBook.bookTot);
                detailBox->FreeAll();
                printBasicDetail();
                if (opt == "删除图书") removeprework();
                else {
                    printBookDetail();
                    setStorePositon();
                }
            });
        }
        if (len == 0) {
            ui::Label *label = new ui::Label;{
                label->AddTo(bookList);
                label->SetContent("暂无图书");
                label->SetPreset(ui::Control::Preset::WRAP_AT_CENTER);
            }
        }
    };

    auto printLeftDetail = [=, this]() -> void {
        lfMidBox->FreeAll();
        ui::Label *label = new ui::Label;{
            label->AddTo(lfMidBox);
            label->SetContent(opt);
            label->SetFontSize(40);
            label->SetHPreset(ui::Control::Preset::WRAP_AT_CENTER);
            label->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
        }
        ui::HorizontalBox *hbox = new ui::HorizontalBox;{
            hbox->AddTo(lfMidBox);
            hbox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
            hbox->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
            hbox->SetGap(5);
        }
        {
            ui::InputBox *searchBox = new ui::InputBox;{
                searchBox->AddTo(hbox);
                searchBox->SetHSize(350);
                searchBox->SetVSize(30);
                searchBox->SetInputCallback(_UI_CALLBACK_{
                    searchInput = searchBox->GetText();
                });
            }
            searchOpt = new ui::Button;{
                searchOpt->AddTo(hbox);
                searchOpt->SetCaption("图书名称>");
                searchOpt->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                searchOpt->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                searchOpt->SetFontSize(40);
                searchOpt->SetClickCallback(_UI_CALLBACK_{
                    isClicked ^= 1;
                    if (isClicked) {
                        optBox->SetVisible(true);
                        optBox->ShowAll();
                    }
                    else {
                        optBox->SetVisible(false);
                        optBox->HideAll();
                    }
                });
            }
            searchBtn = new ui::Button;{
                searchBtn->AddTo(hbox);
                searchBtn->SetCaption("搜索");
                searchBtn->SetHSize(100);
                searchBtn->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                searchBtn->SetFontSize(40);
            }
            searchBtn->SetClickCallback(_UI_CALLBACK_{
                searchBtn->Disable();
                int searchType;
                if (searchOpt->GetCaption() == "ISBN") searchType = trm::rqs::BOOK_ISBN;
                else if (searchOpt->GetCaption() == "图书名称") searchType = trm::rqs::BOOK_NAME;
                bookList->FreeAllVisible();
                bookListLoading = new ui::LoadingRing;{
                    bookListLoading->AddTo(bookList);
                    bookListLoading->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    bookListLoading->SetSize(30, 30);
                    bookListLoading->Start();
                }
                Listen(new trm::Sender({trm::rqs::SEARCH_BOOK, searchInput, ToStr(searchType), "false", "false"}), _SD_CALLBACK_{
                    if (reply.empty()) {
                        books.clear();
                        for (auto bookInfo : reply) {
                            books.push_back(trm::Book(bookInfo));
                        }
                        len = books.size();
                        totPage = std::max((len + 10 - 1) / 10, 1);
                        page = 1;
                        nextBtn->Enable();
                        if (page == totPage) nextBtn->Disable();
                        resetLeftDetail();
                    }
                    else if (reply[0] == trm::rpl::FAIL) {
                        bookList->Add(new ui::Label("查询失败，请检查输入"));
                    }
                    else if (reply[0] == trm::rpl::TIME_OUT) {
                        bookList->Add(new ui::Label("服务端未响应，请稍后再试"));
                    }
                    else {
                        books.clear();
                        for (auto bookInfo : reply) {
                            books.push_back(trm::Book(bookInfo));
                        }
                        len = books.size();
                        totPage = std::max((len + 10 - 1) / 10, 1);
                        page = 1;
                        lastBtn->Disable();
                        nextBtn->Enable();
                        if (page == totPage) nextBtn->Disable();
                        resetLeftDetail();
                    }
                });
                searchBtn->Enable();
            });
        }
        optBox = new ui::HorizontalBox;{
            optBox->AddTo(lfMidBox);
            optBox->SetHPosition(350);
            optBox->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
            optBox->SetGap(5);
            optBox->SetVisible(false);
        }
        {
            ui::Button *btn = new ui::Button;{
                btn->AddTo(optBox);
                btn->SetCaption("isbn");
                btn->SetHSize(50);
                btn->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                btn->SetFontSize(30);
                btn->SetVisible(false);
                btn->SetClickCallback(_UI_CALLBACK_{
                    searchOpt->SetCaption("ISBN");
                });
            }
            btn = new ui::Button;{
                btn->AddTo(optBox);
                btn->SetCaption("图书名称");
                btn->SetHSize(50);
                btn->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                btn->SetFontSize(30);
                btn->SetVisible(false);
                btn->SetClickCallback(_UI_CALLBACK_{
                    searchOpt->SetCaption("图书名称");
                });
            }
        }
        bookList = new ui::VerticalScrollingBox;{
            bookList->AddTo(lfMidBox);
            bookList->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
            bookList->SetInsideBoxScrollable(true);
        }
        ui::HorizontalBox *pageBox = new ui::HorizontalBox;{
            pageBox->AddTo(lfMidBox);
            pageBox->SetHPreset(ui::Control::Preset::WRAP_AT_CENTER);
            pageBox->SetVSize(40);
        }
        {
            lastBtn = new ui::Button;{
                lastBtn->AddTo(pageBox);
                lastBtn->SetCaption("上一页");
                lastBtn->SetHSize(80);
                lastBtn->SetFontSize(35);
                lastBtn->SetHPreset(ui::Control::Preset::PLACE_AT_CENTER);
                lastBtn->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                if(page == 1) lastBtn->Disable();
                lastBtn->SetClickCallback(_UI_CALLBACK_{
                    nextBtn->Enable();
                    lastBtn->Enable();
                    if (page > 1) {
                        page--;
                        resetLeftDetail();
                    }
                    if (page == 1) lastBtn->Disable();
                    if (page == totPage) nextBtn->Disable();
                });
            }
            pageLabel = new ui::Label;{
                pageLabel->AddTo(pageBox);
                pageLabel->SetHSize(40);
                pageLabel->SetFontSize(35);
                pageLabel->SetHPreset(ui::Control::Preset::PLACE_AT_CENTER);
                pageLabel->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                pageLabel->SetContent(ToStr(page) + "/" + ToStr(totPage));
            }
            nextBtn = new ui::Button;{
                nextBtn->AddTo(pageBox);
                nextBtn->SetCaption("下一页");
                nextBtn->SetHSize(80);
                nextBtn->SetFontSize(35);
                nextBtn->SetHPreset(ui::Control::Preset::PLACE_AT_CENTER);
                nextBtn->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                if (page == totPage) nextBtn->Disable();
                nextBtn->SetClickCallback(_UI_CALLBACK_{
                    lastBtn->Enable();
                    nextBtn->Enable();
                    if (page < totPage) {
                        page++;
                        resetLeftDetail();
                    }
                    if (page == totPage) nextBtn->Disable();
                    if (page == 1) nextBtn->Disable();
                });
            }
        }
        ui::HorizontalBox *turnToBox = new ui::HorizontalBox;{
            turnToBox->AddTo(lfMidBox);
            turnToBox->SetHPreset(ui::Control::Preset::WRAP_AT_CENTER);
            turnToBox->SetVSize(40);
        }
        {
            ui::Label *tip = new ui::Label("非法页码");{
                tip->AddTo(turnToBox);
                tip->SetFontSize(35);
                tip->SetHPreset(ui::Control::Preset::WRAP_AT_CENTER);
                tip->SetVPreset(ui::Control::Preset::WRAP_AT_CENTER);
                tip->SetVisible(false);
            }
            ui::InputBox *inputBox = new ui::InputBox;{
                inputBox->AddTo(turnToBox);
                inputBox->SetHSize(200);
                inputBox->SetVSize(30);
                inputBox->SetHPreset(ui::Control::Preset::PLACE_AT_CENTER);
            }
            ui::Button *btn = new ui::Button;{
                btn->AddTo(turnToBox);
                btn->SetCaption("跳转");
                btn->SetFontSize(35);
                btn->SetHPreset(ui::Control::Preset::WRAP_AT_CENTER);
                btn->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                btn->SetClickCallback(_UI_CALLBACK_{
                    std::string input = inputBox->GetText();
                    tip->SetVisible(false);
                    for (auto c : input) {
                        if (c < '0' || c > '9') {
                            tip->SetVisible(true);
                            return;
                        }
                    }
                    int inputPage = ToNum<int>(input);
                    if (inputPage == page) {
                        return;
                    }
                    else if (inputPage < 1) {
                        page = 1;
                    }
                    else if (inputPage > totPage) {
                        page = totPage;
                    }
                    else {
                        page = inputPage;
                    }
                    lastBtn->Enable();
                    nextBtn->Enable();
                    if (page == 1) lastBtn->Disable();
                    if (page == totPage) nextBtn->Disable();
                    pageLabel->SetContent(ToStr(page) + "/" + ToStr(totPage));
                    resetLeftDetail();
                });
            }
        }
    };

#pragma region keybutton logic
    backBtn->SetClickCallback(_UI_CALLBACK_{
        SwitchTo(new EnterLibrary);
    });

    restoreBookBtn->SetClickCallback(_UI_CALLBACK_{
        opt = "新增图书";
        optEnable();
        bookNum = "0";
        selectedBook = trm::Book();
        detailBox->FreeAll();
        lfMidBox->FreeAll();
        printBasicDetail();
        printBookDetail();
        restoreprework();
        setStorePositon();
    });

    modifyBookBtn->SetClickCallback(_UI_CALLBACK_{
        opt = "修改图书";
        optEnable();
        selectedBook = trm::Book();
        detailBox->FreeAll();
        printLeftDetail();
        printBasicDetail();
        printBookDetail();
        setStorePositon();
    });

    removeBookBtn->SetClickCallback(_UI_CALLBACK_{
        opt = "删除图书";
        optEnable();
        selectedBook = trm::Book();
        detailBox->FreeAll();
        printLeftDetail();
        printBasicDetail();
        removeprework();
    });

    confirmBtn->SetClickCallback(_UI_CALLBACK_{
        std::vector<std::string> invalid = CheckInput();
        if (invalid.empty()) {
            screen->HideAll();
            std::string author = "";
            selectedBook.bookAuthor.clear();
            for (auto c : bookAuthor) {
                if (c == ',') {
                    selectedBook.bookAuthor.push_back(author);
                    author = "";
                } else {
                    author += c;
                }
            }
            selectedBook.bookAuthor.push_back(author);
            std::string tip = opt + '\n' + trm::Book::GetInfo(selectedBook);
                    
            if (opt == "新增图书" || opt == "删除图书") tip += "\n    数量 " + bookNum;
            int ret = MessageBox(screen, tip, {"取消", "确认信息无误"});
            if (ret == 0) {
                screen->FreeAllVisible();
                screen->ShowAll();
            }
            else {
                if (opt == "新增图书") {
                    screen->FreeAllVisible();
                    auto [success, reply] = WaitServer(screen, {trm::rqs::RESTORE_BOOK, account.code, password, selectedBook.bookIsbn, bookNum, selectedBook}, "等待服务端响应");
                    screen->FreeAllVisible();
                    if (success == 1) {
                        if (reply[0] == trm::rpl::SUCC) {
                            int succret =MessageBox(screen, "图书添加成功", {"确认"});
                            if (succret == 0) {
                                SwitchTo(new BookManage);
                            }
                        } 
                        else if (reply[0] == trm::rpl::ACCESS_DENIED) {
                            int denyret = MessageBox(screen, "权限不足，请联系管理员", {"确认"});
                            if (denyret == 0) {
                                SwitchTo(new EnterLibrary);
                            }
                        }
                        else if (reply[0] == trm::rpl::BOOK_INFO_CONFLICT) {
                            trm::Book storedBook(reply[1]);
                            int existret = MessageBox(screen, "存在的图书信息与您添加的相冲突\n你是否想添加\n" + trm::Book::GetInfo(storedBook), {"确认", "取消"});
                            if (existret == 0) {
                                selectedBook = storedBook;
                                screen->FreeAllVisible();
                                screen->ShowAll();
                                detailBox->FreeAll();
                                printBasicDetail();
                                printBookDetail();
                                restoreprework();
                                isChanged ^= 1;
                                setStorePositon();
                                reSetCatergoryBox();
                            }
                            else {
                                screen->FreeAllVisible();
                                screen->ShowAll();
                            }
                            return;
                        }
                        else {
                            assert(false);
                        }
                    } 
                    else if (success == 0) {
                        int failret = MessageBox(screen, "服务端未响应，请稍后再试", {"确认"});
                        if (failret == 0) {
                            SwitchTo(new BookManage);
                        }
                    }
                }
                else if (opt == "修改图书") {
                    screen->FreeAllVisible();
                    auto [success, reply] = WaitServer(screen, {trm::rqs::MODIFY_BOOK_INFO, account.code, password, selectedBook.bookIsbn, selectedBook}, "等待服务端响应");
                    screen->FreeAllVisible();
                    if (success == 1) {
                        if (reply[0] == trm::rpl::SUCC) {
                            int succret =MessageBox(screen, "图书修改成功", {"确认"});
                            if (succret == 0) {
                                SwitchTo(new BookManage);
                            }
                        } 
                        else if (reply[0] == trm::rpl::ACCESS_DENIED) {
                            int denyret = MessageBox(screen, "权限不足，请联系管理员", {"确认"});
                            if (denyret == 0) {
                                SwitchTo(new EnterLibrary);
                            }
                        }
                        else if (reply[0] == trm::rpl::NO_BOOK) {
                            int noret = MessageBox(screen, "该图书不存在", {"确认"});
                            if (noret == 0) {
                                SwitchTo(new BookManage);
                            }
                        }
                        else if (reply[0] == trm::rpl::EXIST_BOOK) {
                            int existret = MessageBox(screen, "修改后的图书与馆藏图书冲突", {"确认"});
                            if (existret == 0) {
                                SwitchTo(new BookManage);
                            }
                        }
                        else {
                            assert(false);
                        }
                    } 
                    else if (success == 0) {
                        int failret = MessageBox(screen, "服务端未响应，请稍后再试", {"确认"});
                        if (failret == 0) {
                            SwitchTo(new BookManage);
                        }
                    }
                }
                else if (opt == "删除图书") {
                    screen->FreeAllVisible();
                    auto [success, reply] = WaitServer(screen, {trm::rqs::REMOVE_BOOK, account.code, password, selectedBook.bookIsbn, bookNum}, "等待服务端响应");
                    screen->FreeAllVisible();
                    if (success == 1) {
                        if (reply[0] == trm::rpl::SUCC) {
                            int succret =MessageBox(screen, "图书删除成功", {"确认"});
                            if (succret == 0) {
                                SwitchTo(new BookManage);
                            }
                        } 
                        else if (reply[0] == trm::rpl::ACCESS_DENIED) {
                            int denyret = MessageBox(screen, "权限不足，请联系管理员", {"确认"});
                            if (denyret == 0) {
                                SwitchTo(new EnterLibrary);
                            }
                        }
                        else if (reply[0] == trm::rpl::NO_BOOK) {
                            int noret = MessageBox(screen, "该图书不存在", {"确认"});
                            if (noret == 0) {
                                SwitchTo(new BookManage);
                            }
                        }
                        else if (reply[0] == trm::rpl::EXCEED_BOOK_NUM) {
                            int exceedret = MessageBox(screen, "图书数量不足", {"确认"});
                            if (exceedret == 0) {
                                SwitchTo(new BookManage);
                            }
                        }
                        else {
                            assert(false);
                        }
                    } 
                    else if (success == 0) {
                        int failret = MessageBox(screen, "服务端未响应，请稍后再试", {"确认"});
                        if (failret == 0) {
                            SwitchTo(new BookManage);
                        }
                    }
                }
            }
        }
        else {
            if (opt == "新增图书" || opt == "删除图书") numLimitTip->SetVisible(false);
            if (opt == "新增图书") {
                bookisbnLimitTip->SetVisible(false);
                bookpublishDateLimitTip->SetVisible(false);
            }
            for (auto s : invalid) {
                if (s == "isbn" && opt != "删除图书") {
                    bookisbnLimitTip->SetVisible(true);
                }
                else if (s == "date" && opt != "删除图书") {
                    bookpublishDateLimitTip->SetVisible(true);
                }
                else if (s == "num" && (opt == "新增图书" || opt == "删除图书")) {
                    numLimitTip->SetVisible(true);
                }
            }
        }
    });

}

void vio::BookManage::Ready(ui::Screen *screen) noexcept
{
    bookNum = "";
    isChanged = 0;
    isClicked = false;
}

std::vector<std::string> vio::BookManage::CheckInput() const noexcept
{   
    std::vector<std::string> invalid;
    if (selectedBook.bookIsbn.empty()) invalid.emplace_back("isbn");
    else {
        if (selectedBook.bookIsbn.length() != 16) invalid.emplace_back("isbn");
        else {
            for (int i = 0; i < 16; i++) {
                if (i == 3 || i == 5 || i == 7 || i == 14) {
                    if (selectedBook.bookIsbn[i] != '-') {
                        invalid.emplace_back("isbn");
                        break;
                    }
                }
                else if (selectedBook.bookIsbn[i] < '0' || selectedBook.bookIsbn[i] > '9') {
                    invalid.emplace_back("isbn");
                    break;
                }
            }
        }
    }
    if (selectedBook.bookPublicationDate.empty()) invalid.emplace_back("date");
    else {
        if (selectedBook.bookPublicationDate.length() != 10) invalid.emplace_back("date");
        else {
            for (int i = 0; i < 10; i++) {
                if (i == 4 || i == 7) {
                    if (selectedBook.bookPublicationDate[i] != '-') {
                        invalid.emplace_back("date");
                        break;
                    }
                }
                else if (selectedBook.bookPublicationDate[i] < '0' || selectedBook.bookPublicationDate[i] > '9') {
                    invalid.emplace_back("date");
                    break;
                }
            }
            if (!CheckBookDate()) invalid.emplace_back("date");
        }
    }
    if (opt == "删除图书" || opt == "新增图书") {
        if (bookNum == "" || bookNum == "0") invalid.emplace_back("num");
        else if (bookNum != "all") {
            for (auto c : bookNum) {
                if (c < '0' || c > '9') {
                    invalid.emplace_back("num");
                    break;
                }
            }
        }
        else if (opt != "删除图书") invalid.emplace_back("num");
    }
    return invalid;
}

bool vio::BookManage::CheckBookDate() const noexcept
{
    std::string _date = selectedBook.bookPublicationDate;
    std::string _year = _date.substr(0, 4);
    std::string _month = _date.substr(5, 2);
    std::string _day = _date.substr(8, 2);

    int year = ToNum<int>(_year);
    int month = ToNum<int>(_month);
    int day = ToNum<int>(_day);

    time_t now = time(nullptr);
    tm* timeinfo = new tm;
    localtime_s(timeinfo, &now);

    if (year > timeinfo->tm_year + 1900) {
        return false;  
    }
    else if (year == timeinfo->tm_year + 1900 && month > timeinfo->tm_mon + 1) {
        return false;
    }
    else if (year == timeinfo->tm_year + 1900 && month == timeinfo->tm_mon + 1 && day > timeinfo->tm_mday) {
        return false;
    }

    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
        if (day > 31 || day < 1) return false;
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day > 30 || day < 1) return false;
    }
    else if (month == 2) {
        if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
            if (day > 29 || day < 1) return false;
        }
        else {
            if (day > 28 || day < 1) return false;
        }
    }
    else return false;
    return true;
}


void vio::EnterNolify::Load(ui::Screen *screen) noexcept
{
    ui::Margin *mar = new ui::Margin;{
        mar->AddTo(screen);
        mar->SetMargin(180, 200, 300, 300);
        mar->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
    }
    {
        ui::VerticalBox *wholeBox = new ui::VerticalBox;{
            wholeBox->AddTo(mar);
            wholeBox->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
            wholeBox->SetGap(5);
        }
        {
            backBtn = new ui::Button;{
                backBtn->AddTo(wholeBox);
                backBtn->SetCaption("←返回");
                backBtn->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                backBtn->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                backBtn->SetFontSize(40);
            }
            ui::HorizontalBox *bodyBox = new ui::HorizontalBox;{
                bodyBox->AddTo(wholeBox);
                bodyBox->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
            }
            {
                ui::VerticalBox *leftBox = new ui::VerticalBox;{
                    leftBox->AddTo(bodyBox);
                    leftBox->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                }
                {
                    mode = new ui::Label;{
                        mode->AddTo(leftBox);
                        mode->SetHPreset(ui::Control::Preset::WRAP_AT_CENTER);
                        mode->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                        mode->SetContent("请选择您的操作");
                        mode->SetFontSize(40);
                    }
                    ui::HorizontalBox *optionBox = new ui::HorizontalBox;{
                        optionBox->AddTo(leftBox);
                        optionBox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        optionBox->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                    }
                    {
                        publishBtn = new ui::Button;{
                            publishBtn->AddTo(optionBox);
                            publishBtn->SetCaption("发布通知");
                            publishBtn->SetHPreset(ui::Control::Preset::WRAP_AT_CENTER);
                            publishBtn->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                            publishBtn->SetFontSize(40);
                        }
                        deleteBtn = new ui::Button;{
                            deleteBtn->AddTo(optionBox);
                            deleteBtn->SetCaption("删除通知");
                            deleteBtn->SetHPreset(ui::Control::Preset::WRAP_AT_CENTER);
                            deleteBtn->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                            deleteBtn->SetFontSize(40);
                        }
                    }
                    partitionLabel = new ui::Label;{
                        partitionLabel->AddTo(leftBox);
                        partitionLabel->SetHPreset(ui::Control::Preset::WRAP_AT_CENTER);
                        partitionLabel->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                        partitionLabel->SetContent("请选择通知板块");
                        partitionLabel->SetFontSize(40);
                    }
                    ui::VerticalBox *partitionBox = new ui::VerticalBox;{
                        partitionBox->AddTo(leftBox);
                        partitionBox->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                        partitionBox->SetGap(10);
                        partitionBox->SetHPreset(ui::Control::Preset::WRAP_AT_CENTER);
                    }
                    {
                        headlineBtn = new ui::Button;{
                            headlineBtn->AddTo(partitionBox);
                            headlineBtn->SetCaption("头条");
                            headlineBtn->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                            headlineBtn->SetFontSize(40);
                        }
                        newsBtn = new ui::Button;{
                            newsBtn->AddTo(partitionBox);
                            newsBtn->SetCaption("新闻");
                            newsBtn->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                            newsBtn->SetFontSize(40);
                        }
                        noticeBtn = new ui::Button;{
                            noticeBtn->AddTo(partitionBox);
                            noticeBtn->SetCaption("通知");
                            noticeBtn->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                            noticeBtn->SetFontSize(40);
                        }   
                    }
                    partitionTip = new ui::Label;{
                        partitionTip->AddTo(leftBox);
                        partitionTip->SetHPreset(ui::Control::Preset::WRAP_AT_CENTER);
                        partitionTip->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                        partitionTip->SetContent("通知类型不能为空");
                        partitionTip->SetFontSize(40);
                        partitionTip->SetVisible(false);
                    }
                }
                ui::VerticalBox *rightBox = new ui::VerticalBox;{
                    rightBox->AddTo(bodyBox);
                    rightBox->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                }
                {
                    nolifyDetailBox = new ui::VerticalScrollingBox;{
                        nolifyDetailBox->AddTo(rightBox);
                        nolifyDetailBox->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        nolifyDetailBox->SetInsideBoxScrollable(true);
                    }
                    {
                        ui::Label *tip = new ui::Label;{
                            tip->AddTo(nolifyDetailBox);
                            tip->SetHPreset(ui::Control::Preset::WRAP_AT_CENTER);
                            tip->SetContent("请选择您的操作");
                            tip->SetFontSize(40);
                        }
                    }
                }
            }
        }
    }
}

void vio::EnterNolify::Logic(ui::Screen *screen) noexcept
{
    auto printPublishDetail = [=, this]() {
        nolifyDetailBox->FreeAll();
        ui::Label *titleLabel = new ui::Label;{
            titleLabel->AddTo(nolifyDetailBox);
            titleLabel->SetHPreset(ui::Control::Preset::WRAP_AT_CENTER);
            titleLabel->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
            titleLabel->SetContent("标题");
            titleLabel->SetFontSize(40);
        }
        titleInputBox = new ui::InputBox;{
            titleInputBox->AddTo(nolifyDetailBox);
            titleInputBox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
            titleInputBox->SetMaxCount(20);
            titleInputBox->SetInputCallback(_UI_CALLBACK_{
                nolifyTitle = titleInputBox->GetText();
            });
        }
        ui::Label *contentLabel = new ui::Label;{
            contentLabel->AddTo(nolifyDetailBox);
            contentLabel->SetHPreset(ui::Control::Preset::WRAP_AT_CENTER);
            contentLabel->SetContent("内容");
            contentLabel->SetFontSize(40);
            contentLabel->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
        }
        contentInputBox = new ui::InputBox;{
            contentInputBox->AddTo(nolifyDetailBox);
            contentInputBox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
            contentInputBox->SetFontSize(20);
            contentInputBox->SetMaxCount(50);
            contentInputBox->SetInputCallback(_UI_CALLBACK_{
                nolifyContent = contentInputBox->GetText();
            });
        }
        ui::HorizontalBox *btnBox = new ui::HorizontalBox;{
            btnBox->AddTo(nolifyDetailBox);
            btnBox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
            btnBox->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
        }
        {
            ui::Label *inputTip = new ui::Label;{
                inputTip->AddTo(btnBox);
                inputTip->SetHPreset(ui::Control::Preset::WRAP_AT_CENTER);
                inputTip->SetContent("标题和内容不能为空");
                inputTip->SetFontSize(40);
                inputTip->SetVisible(false);
            }
            confirmBtn = new ui::Button;{
                confirmBtn->AddTo(btnBox);
                confirmBtn->SetCaption("确认");
                confirmBtn->SetHPreset(ui::Control::Preset::WRAP_AT_END);
                confirmBtn->SetVPreset(ui::Control::Preset::WRAP_AT_END);
                confirmBtn->SetFontSize(40);
                confirmBtn->SetClickCallback(_UI_CALLBACK_{
                    partitionTip->SetVisible(false);
                    if (partitionOpt == nullptr) {
                        partitionTip->SetVisible(true);
                        return;
                    }
                    if (partitionOpt->GetCaption() == "头条") type = "headline";
                    else if (partitionOpt->GetCaption() == "新闻") type = "news";
                    else if (partitionOpt->GetCaption() == "通知") type = "notice";
                    else {
                        partitionTip->SetVisible(true);
                        return;
                    }
                    inputTip->SetVisible(false);
                    if (nolifyTitle == "" || nolifyContent == "") {
                        inputTip->SetVisible(true);
                        return;
                    }

                    screen->HideAll();
                    int ret = MessageBox(screen, "确认发布通知？", {"确认", "取消"});
                    if (ret == 0) {
                        screen->FreeAllVisible();
                        auto [success, reply] = WaitServer(screen, {trm::rqs::PUBLISH_NOLIFY, account.code, password, nolifyTitle, nolifyContent, type}, "等待服务端响应");
                        screen->FreeAllVisible();
                        if (success == 1) {
                            if (reply[0] == trm::rpl::SUCC) {
                                int succret = MessageBox(screen, "通知发布成功", {"确认"});
                                if (succret == 0) {
                                    screen->FreeAllVisible();
                                    screen->ShowAll();
                                    titleInputBox->SetText("");
                                    contentInputBox->SetText("");
                                }
                            }
                            else if (reply[0] == trm::rpl::ACCESS_DENIED) {
                                int denyret = MessageBox(screen, "权限不足，请联系管理员", {"确认"});
                                if (denyret == 0) {
                                    SwitchTo(new EnterLibrary);
                                }
                            }
                            else if (reply[0] == trm::rpl::TIME_OUT) {
                                int timeoutret = MessageBox(screen, "连接超时，请重试", {"确认"});
                                if (timeoutret == 0) {
                                    screen->FreeAllVisible();
                                    screen->ShowAll();
                                }
                            }
                            else {
                                assert(false);
                            }
                        }
                    }
                    else if (ret == 1) {
                        screen->FreeAllVisible();
                        screen->ShowAll();
                    }
                });
            }
        }
    };

    auto searchNolify = [=, this]() {
        nolifyDetailBox->FreeAll();
        ui::LoadingRing *loading = new ui::LoadingRing;{
            loading->AddTo(nolifyDetailBox);
            loading->SetPreset(ui::Control::Preset::PLACE_AT_CENTER);
            loading->Start();
        }
        if (isChanged) {
            page = 1;
            Listen(new trm::Sender({trm::rqs::GET_NOLIFY_NUMBER, type}), _SD_CALLBACK_{
                if (reply.empty()) {
                    assert(false);
                }
                else if (reply[0] == trm::rpl::TIME_OUT) {
                    screen->HideAll();
                    int timeoutret = MessageBox(screen, "连接超时，请重试", {"确认"});
                    if (timeoutret == 0) {
                        screen->FreeAllVisible();
                        screen->ShowAll();
                    }
                }
                else {
                    totPage = ToNum<unsigned long long>(reply[0]);
                    totPage = (totPage + 9) / 10;
                }
            });
        }
        isChanged = false;
        notices.clear();
        Listen(new trm::Sender({trm::rqs::GET_NOLIFY_LIST, ToStr((page - 1) * 10), ToStr(page * 10), type}), _SD_CALLBACK_{
            nolifyDetailBox->FreeAll();
            if (reply.empty()) {
                printDeleteDetail();
            }
            else {
                for (auto nolify : reply) {
                    notices.emplace_back(nolify);
                }
                printDeleteDetail();
            }

        });
    };

    printDeleteDetail = [=, this]() {
        nolifyDetailBox->FreeAll();
        ui::HorizontalBox *hBox = nullptr;
        ui::Label *titleLbl = nullptr;
        ui::Button *btn = nullptr;
        if (!notices.empty()) {
            for (unsigned long long int i = 0; i < notices.size(); i++) {
                hBox = new ui::HorizontalBox;{
                    hBox->AddTo(nolifyDetailBox);
                    hBox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    hBox->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                }
                {
                    titleLbl = new ui::Label;{
                        titleLbl->AddTo(hBox);
                        titleLbl->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                        titleLbl->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);

                        titleLbl->SetContent(notices[i].title + "  " + notices[i].date.GetDate());
                        titleLbl->SetFontSize(40);
                    }
                    ui::Flat *flat = new ui::Flat;{
                        flat->AddTo(hBox);
                        flat->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        flat->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    }
                    btn = new ui::Button;{
                        btn->AddTo(hBox);
                        btn->SetCaption("查看");
                        btn->SetHPreset(ui::Control::Preset::PLACE_AT_END);
                        btn->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        btn->SetFontSize(40);
                        btn->SetClickCallback(_UI_CALLBACK_{
                            selectedNotice = notices[i];
                            screen->HideAll();
                            auto[success, reply] = WaitServer(screen, {trm::rqs::GET_NOLIFY, ToStr((page - 1) * 10 + i), type}, "等待服务端响应");
                            screen->FreeAllVisible();
                            if (success == 1) {
                                if (reply.empty()) assert(false);
                                else if (reply[0] == trm::rpl::TIME_OUT) {
                                    int timeoutret = MessageBox(screen, "连接超时，请重试", {"确认"});
                                    if (timeoutret == 0) {
                                        screen->FreeAllVisible();
                                        screen->ShowAll();
                                    }
                                }
                                else {
                                    selectedNotice = reply[0];
                                    std::string content = "标题：\n" + selectedNotice.title + "\n\n" + "内容：\n" + selectedNotice.content + "\n\n";
                                    int ret = MessageBox(screen, content, {"返回"});
                                    if (ret == 0) {
                                        screen->FreeAllVisible();
                                        screen->ShowAll();
                                    }
                                }
                            }
                            else {
                                int ret = MessageBox(screen, "获取通知失败", {"确认"});
                                if (ret == 0) {
                                    screen->FreeAllVisible();
                                    screen->ShowAll();
                                }
                            }
                        });
                    }
                    btn = new ui::Button;{
                        btn->AddTo(hBox);
                        btn->SetCaption("删除");
                        btn->SetHPreset(ui::Control::Preset::PLACE_AT_END);
                        btn->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                        btn->SetFontSize(40);
                        btn->SetClickCallback(_UI_CALLBACK_{
                            screen->HideAll();
                            int ret = MessageBox(screen, "确认删除通知？", {"确认", "取消"});
                            if (ret == 0) {
                                Listen(new trm::Sender({trm::rqs::DELETE_NOLIFY, account.code, password, ToStr((page - 1) * 10 + i), type}), _SD_CALLBACK_{
                                    screen->FreeAllVisible();
                                    if (reply[0] == trm::rpl::SUCC) {
                                        int succret = MessageBox(screen, "通知删除成功", {"确认"});
                                        if (succret == 0) {
                                            screen->FreeAllVisible();
                                            screen->ShowAll();
                                            isChanged = true;
                                            searchNolify();
                                        }
                                    }
                                    else if (reply[0] == trm::rpl::TIME_OUT) {
                                        int timeoutret = MessageBox(screen, "连接超时，请重试", {"确认"});
                                        if (timeoutret == 0) {
                                            screen->FreeAllVisible();
                                            screen->ShowAll();
                                        }
                                    } 
                                    else {
                                        assert(false);
                                    }
                                });
                            }
                            else if (ret == 1) {
                                screen->FreeAllVisible();
                                screen->ShowAll();
                            }
                        });
                    }
                }
            }
    
            hBox = new ui::HorizontalBox;{
                hBox->AddTo(nolifyDetailBox);
                hBox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                hBox->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
            }
            {
                lastBtn = new ui::Button;{
                    lastBtn->AddTo(hBox);
                    lastBtn->SetCaption("上一页");
                    lastBtn->SetHPreset(ui::Control::Preset::PLACE_AT_CENTER);
                    lastBtn->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    lastBtn->SetFontSize(40);
                    if (page == 1) lastBtn->Disable();
                    lastBtn->SetClickCallback(_UI_CALLBACK_{
                        if (page > 1) {
                            page--;
                            searchNolify();
                        }
                    });
                }
                pageLbl = new ui::Label;{
                    pageLbl->AddTo(hBox);
                    pageLbl->SetHPreset(ui::Control::Preset::WRAP_AT_CENTER);
                    pageLbl->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    pageLbl->SetContent(ToStr(page) + "/" + ToStr(totPage));
                    pageLbl->SetFontSize(40);
                }
                nextBtn = new ui::Button;{
                    nextBtn->AddTo(hBox);
                    nextBtn->SetCaption("下一页");
                    nextBtn->SetHPreset(ui::Control::Preset::PLACE_AT_CENTER);
                    nextBtn->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    nextBtn->SetFontSize(40);
                    if (page == totPage) nextBtn->Disable();
                    nextBtn->SetClickCallback(_UI_CALLBACK_{
                        if (page < totPage) {
                            page++;
                            searchNolify();
                        }
                    });
                }
            }
        }
        else {
            ui::Label *titleLbl = new ui::Label;{
                titleLbl->AddTo(nolifyDetailBox);
                titleLbl->SetPreset(ui::Control::Preset::PLACE_AT_CENTER);
                titleLbl->SetContent("暂无通知");
                titleLbl->SetFontSize(40);
            }
        }
    };
    auto resetRightBox = [=, this]() {
        if (opt->GetCaption() == "发布通知") {
            printPublishDetail();
        }
        if (opt->GetCaption() == "删除通知") {
            partitionTip->SetVisible(false);
            if (partitionOpt == nullptr) {
                partitionTip->SetVisible(true);
                deleteBtn->Enable();
                return;
            }
            if (partitionOpt->GetCaption() == "头条") type = "headline";
            else if (partitionOpt->GetCaption() == "新闻") type = "news";
            else if (partitionOpt->GetCaption() == "通知") type = "notice";
            else {
                partitionTip->SetVisible(true);
                deleteBtn->Enable();
                return;
            }
            searchNolify();
        }
    };

    backBtn->SetClickCallback(_UI_CALLBACK_{
        SwitchTo(new eea::MainPage);
    });

    for (auto btn : {publishBtn, deleteBtn}) {
        btn->SetClickCallback(_UI_CALLBACK_{
            if (opt != nullptr) opt->Enable();
            opt = btn;
            opt->Disable();
            mode->SetContent(opt->GetCaption());
            isChanged = true;
            resetRightBox();
        });
    }


    for (auto btn : {headlineBtn, newsBtn, noticeBtn}) {
        btn->SetClickCallback(_UI_CALLBACK_{
            if (partitionOpt != nullptr) partitionOpt->Enable();
            partitionOpt = btn;
            partitionOpt->Disable();
            partitionLabel->SetContent(partitionOpt->GetCaption());
            isChanged = true;
            if (opt != nullptr) {
                if (opt->GetCaption() == "删除通知") {
                    resetRightBox();
                }
            }
        });
    }
}

void vio::EnterNolify::Ready(ui::Screen *screen) noexcept
{   
    bool pass = false;
    for (const auto &access : account.access) {
        if (access == trm::Access::MANAGE_NOLIFY) {
            pass = true;
            break;
        }
        else if (access == trm::Access::ADM) {
            pass = true;
            break;
        }
    };

    if (!pass) {
        screen->FreeAll();
        int ret = MessageBox(screen, "权限不足，无法进入", {"确认"});
        if (ret == 0) {
            screen->FreeAll();
            SwitchTo(new eea::MainPage);
        }
    }
}

void vio::ViewNolify::Load(ui::Screen *screen) noexcept
{
    ui::Margin *mar = new ui::Margin;{
        mar->AddTo(screen);
        mar->SetMargin(150, 150, 320, 320);
        mar->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
    }
    {
        bodyBox = new ui::VerticalBox;{
            bodyBox->AddTo(mar);
            bodyBox->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
            bodyBox->SetGap(10);
        }
        {
            backBtn = new ui::Button;{
                backBtn->AddTo(bodyBox);
                backBtn->SetCaption("←返回");
                backBtn->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                backBtn->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
            }
            ui::Label *lbl = new ui::Label;{
                lbl->AddTo(bodyBox);
                lbl->SetHPreset(ui::Control::Preset::WRAP_AT_CENTER);
                lbl->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                lbl->SetContent("通知详情");
            }
            ui::VerticalScrollingBox *noticeBox = new ui::VerticalScrollingBox;{
                noticeBox->AddTo(bodyBox);
                noticeBox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                noticeBox->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                noticeBox->SetInsideBoxScrollable(true);
                noticeBox->SetBarSize(20);
            }
            {
                titleLabel = new ui::Label;{
                    titleLabel->AddTo(noticeBox);
                    titleLabel->SetHPreset(ui::Control::Preset::WRAP_AT_CENTER);
                    titleLabel->SetVSize(80);
                }
                contentLabel = new ui::Label;{
                    contentLabel->AddTo(noticeBox);
                    contentLabel->SetHPreset(ui::Control::Preset::WRAP_AT_CENTER);
                    contentLabel->SetFontSize(35);
                }
            }
        }
    }
}

void vio::ViewNolify::Logic(ui::Screen *screen) noexcept
{
    backBtn->SetClickCallback(_UI_CALLBACK_{
        if (from == "ViewNolifyList") SwitchTo(new vio::ViewNolifyList(len, type, std::string("ViewNolify")));
        else SwitchTo(new eea::MainPage);
    });

    screen->HideAll();
    ui::LoadingRing *loading = new ui::LoadingRing;{
        loading->AddTo(bodyBox);
        loading->SetPreset(ui::Control::Preset::PLACE_AT_CENTER);
        loading->Start();
    }
    Listen(new trm::Sender({trm::rqs::GET_NOLIFY, ToStr(selectedNoticeNum), type}), _SD_CALLBACK_{
        screen->FreeAllVisible();
        if (reply.empty()) {
            int ret = MessageBox(screen, "该通知不存在", {"确认"});
            if (ret == 0) {
                screen->FreeAllVisible();
                SwitchTo(new eea::MainPage);
            }
        }
        else if (reply[0] == trm::rpl::TIME_OUT) {
            int ret = MessageBox(screen, "连接超时，请重试", {"确认"});
            if (ret == 0) {
                screen->FreeAllVisible();
                SwitchTo(new eea::MainPage);
            }
        }
        else {
            loading->Hide();
            screen->FreeAllVisible();
            screen->ShowAll();
            notice = reply[0];
            titleLabel->SetContent(notice.title);
            contentLabel->SetContent(notice.content);
        }
    });
}

void vio::ViewNolify::Ready(ui::Screen *screen) noexcept
{
    ;
}

void vio::ViewNolifyList::Load(ui::Screen *screen) noexcept
{
    ui::Margin *mar = new ui::Margin;{
        mar->AddTo(screen);
        mar->SetMargin(150, 150, 200, 200);
        mar->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
    }
    {
        ui::VerticalBox *bodyBox = new ui::VerticalBox;{
            bodyBox->AddTo(mar);
            bodyBox->SetPreset(ui::Control::Preset::FILL_FROM_CENTER);
            bodyBox->SetGap(10);
        }
        {
            backBtn = new ui::Button;{
                backBtn->AddTo(bodyBox);
                backBtn->SetCaption("←返回");
                backBtn->SetHPreset(ui::Control::Preset::WRAP_AT_FRONT);
                backBtn->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
            }
            listDetailBox = new ui::VerticalScrollingBox;{
                listDetailBox->AddTo(bodyBox);
                listDetailBox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                listDetailBox->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                listDetailBox->SetInsideBoxScrollable(true);
            }
            ui::HorizontalBox *pageBox = new ui::HorizontalBox;{
                pageBox->AddTo(bodyBox);
                pageBox->SetHPreset(ui::Control::Preset::WRAP_AT_CENTER);
                pageBox->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
            }
            {
                lastBtn = new ui::Button;{
                    lastBtn->AddTo(pageBox);
                    lastBtn->SetCaption("上一页");
                    lastBtn->SetHPreset(ui::Control::Preset::PLACE_AT_CENTER);
                    lastBtn->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    lastBtn->SetFontSize(40);
                }
                pageLbl = new ui::Label;{
                    pageLbl->AddTo(pageBox);
                    pageLbl->SetHPreset(ui::Control::Preset::WRAP_AT_CENTER);
                    pageLbl->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    pageLbl->SetContent(ToStr(page) + "/" + ToStr(totPage));
                    pageLbl->SetFontSize(40);
                }
                nextBtn = new ui::Button;{
                    nextBtn->AddTo(pageBox);
                    nextBtn->SetCaption("下一页");
                    nextBtn->SetHPreset(ui::Control::Preset::PLACE_AT_CENTER);
                    nextBtn->SetVPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    nextBtn->SetFontSize(40);
                }
            }
        }
    }
}

void vio::ViewNolifyList::Logic(ui::Screen *screen) noexcept
{
    backBtn->SetClickCallback(_UI_CALLBACK_{ 
        SwitchTo(new eea::MainPage);
    });
    
    auto printListDetail = [=, this]() {
        listDetailBox->FreeAll();
        pageLbl->SetContent(ToStr(page) + "/" + ToStr(totPage));
        if (len == 0) {
            ui::Label *tip = new ui::Label;{
                tip->AddTo(listDetailBox);
                tip->SetPreset(ui::Control::Preset::PLACE_AT_CENTER);
                tip->SetContent("暂无通知");
            }
        }
        for (unsigned long long i = 0; i < nolifyList.size(); ++i) {
            ui::HorizontalBox *hBox = new ui::HorizontalBox;{
                hBox->AddTo(listDetailBox);
                hBox->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                hBox->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
            }
            {
                ui::Button *btn = new ui::Button;{
                    btn->AddTo(hBox);
                    btn->SetCaption(nolifyList[i].title);
                    btn->SetHPreset(ui::Control::Preset::FILL_FROM_CENTER);
                    btn->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                    btn->SetClickCallback(_UI_CALLBACK_{
                        selectedNoticeNum = i + (page - 1) * 10;
                        SwitchTo(new vio::ViewNolify(len, type, "ViewNolifyList"));
                    });
                }
                ui::Label *dateLabel = new ui::Label;{
                    dateLabel->AddTo(hBox);
                    dateLabel->SetHPreset(ui::Control::Preset::WRAP_AT_END);
                    dateLabel->SetVPreset(ui::Control::Preset::WRAP_AT_FRONT);
                    dateLabel->SetContent(nolifyList[i].date.GetDate());
                }
            }
        }
    };

    getNolifyList = [=, this]() {
        Listen(new trm::Sender({trm::rqs::GET_NOLIFY_LIST, ToStr((page - 1) * 10), ToStr(page * 10), type}), _SD_CALLBACK_{
            if (!reply.empty()) {
                if (reply[0] == trm::rpl::TIME_OUT) {
                    screen->HideAll();
                    int ret = MessageBox(screen, "连接超时，请重试", {"确认"});
                    if (ret == 0) {
                        screen->FreeAllVisible();
                        screen->ShowAll();
                    }
                }
            }
            nolifyList.clear();
            for (auto &notice : reply) {
                nolifyList.emplace_back(notice);
            }
            printListDetail();
        });
    };


    lastBtn->SetClickCallback(_UI_CALLBACK_{
        nextBtn->Enable();
        if (page > 1) {
            page--;
        }
        if (page == 1) lastBtn->Disable();
        getNolifyList();
    });

    nextBtn->SetClickCallback(_UI_CALLBACK_{
        lastBtn->Enable();
        if (page < totPage) {
            page++;
        }
        if (page == totPage) nextBtn->Disable();
        getNolifyList();
    });
}

void vio::ViewNolifyList::Ready(ui::Screen *screen) noexcept
{
    totPage = std::max((len + 9) / 10, 1);
    page = 1;
    if (page == 1) lastBtn->Disable();
    if (page == totPage) nextBtn->Disable();
    getNolifyList();
}
