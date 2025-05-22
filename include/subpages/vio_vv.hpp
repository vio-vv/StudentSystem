#ifndef __VIO_VV_HPP__
#define __VIO_VV_HPP__

#include "page_header.hpp"

namespace vio{
using namespace clpg;

class EnterLibrary : public PageBase {
private:
    bool isClicked = false;
    std::string optStr = "";
    std::string userInput = "";
    
    ui::InputBox *searchBox = nullptr;
    ui::Button *searchOptBtn = nullptr;
    //由optbtn控制的按钮组{
        ui::Button *chooseIsbn = nullptr;
        ui::Button *chooseBookName = nullptr;
        ui::Button *chooseAuthor = nullptr;
        ui::Button *choosePublishDate = nullptr;
        ui::Button *chooseStorePosion = nullptr;
        ui::Button *chooseCategory = nullptr;
    //}
    ui::Button *searchBtn = nullptr;
    ui::Button *returnBtn = nullptr;
    ui::Button *borrowManageBtn = nullptr;
    ui::Button *basicNolifyBtn = nullptr;
    ui::VerticalBox *optBox = nullptr;
    ui::VerticalBox *vbox = nullptr;
    ui::HorizontalBox *midBox = nullptr;
    ui::HorizontalBox *hinderBox = nullptr;
protected:
    static std::vector<trm::Book> books;
    static std::vector<trm::BorrowLog> borrowLogs;

    void Load(ui::Screen *screen) noexcept;
    void Logic(ui::Screen *screen) noexcept;
    void Ready(ui::Screen *screen) noexcept;
};

class BookList : public EnterLibrary {
private:
    ui::Button *backBtn = nullptr;
protected:
    void Load(ui::Screen *screen) noexcept;
    void Logic(ui::Screen *screen) noexcept;
    void Ready(ui::Screen *screen) noexcept;
};

class EnterNolify : public PageBase {
private:
    ;
protected:
    void Load(ui::Screen *screen) noexcept;
    void Logic(ui::Screen *screen) noexcept;
    void Ready(ui::Screen *screen) noexcept;
};

}
        
#endif
