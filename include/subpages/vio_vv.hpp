#ifndef __VIO_VV_HPP__
#define __VIO_VV_HPP__

#include "page_header.hpp"

namespace vio{
using namespace clpg;

class EnterLibrary : public PageBase {
private:
    bool isClicked = false;
    
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
    ui::Button *bookManageBtn = nullptr;
    ui::Button *resetLibraryBtn = nullptr;
    ui::HorizontalBox *optBox = nullptr;
    ui::VerticalBox *vbox = nullptr;
    ui::HorizontalBox *midBox = nullptr;
    ui::HorizontalBox *hinderBox = nullptr;
protected:
    static int select;
    static std::string optStr;
    static std::string userInput;
    static trm::Book selectedBook;
    static std::vector<trm::Book> books;
    static std::vector<trm::BorrowLog> borrowLogs;
    static std::vector<std::string> searchOption;

    void Load(ui::Screen *screen) noexcept;
    void Logic(ui::Screen *screen) noexcept;
    void Ready(ui::Screen *screen) noexcept;
};

class BookList : public EnterLibrary {
private:
    bool isClicked = false;
    int page = 1;
    int totPage = 1;
    int len = 0;

    ui::HorizontalBox *optBox = nullptr;
//{
    ui::Button *chooseIsbn = nullptr;
    ui::Button *chooseBookName = nullptr;
    ui::Button *chooseAuthor = nullptr;
    ui::Button *choosePublishDate = nullptr;
    ui::Button *chooseStorePosion = nullptr;
    ui::Button *chooseCategory = nullptr;
//}

    ui::Button *backBtn = nullptr;
    ui::InputBox *searchBox = nullptr;
    ui::Button *searchBtn = nullptr;
    ui::Button *searchOptBtn = nullptr;
    ui::Button *lastBtn = nullptr;
    ui::Button *nextBtn = nullptr;
    ui::Label *pageLabel = nullptr;
    ui::InputBox *pageInput = nullptr;
    ui::Button *turnToBtn = nullptr;
    ui::Label *tip = nullptr;
    ui::VerticalScrollingBox *listBox = nullptr;

    std::function<void()> resetBookList = [](){};
protected:
    void Load(ui::Screen *screen) noexcept;
    void Logic(ui::Screen *screen) noexcept;
    void Ready(ui::Screen *screen) noexcept;
};

class BorrowManage : public EnterLibrary {
private:
    int page = 1;
    int totPage = 1;
    int len = 0;
    int select = 0;
    
    std::vector<std::string> bookName = {};

    ui::Button *backBtn = nullptr;
    ui::Button *lastBtn = nullptr;
    ui::Button *nextBtn = nullptr;
    ui::Label *pageLabel = nullptr;
    ui::InputBox *pageInput = nullptr;
    ui::Label *tip = nullptr;
    ui::Button *confirmTurnBtn = nullptr;
    ui::Button *confirmBtn = nullptr;
    ui::Button *returnBtn = nullptr;
    ui::Button *refleshBtn = nullptr;
    ui::VerticalScrollingBox *borrowDetailBox = nullptr;
    ui::VerticalScrollingBox *borrowLogBox = nullptr;

    std::function<void()> resetBorrowList = [](){};
protected:
    void Load(ui::Screen *screen) noexcept;
    void Logic(ui::Screen *screen) noexcept;
    void Ready(ui::Screen *screen) noexcept;
};

class BookManage : public EnterLibrary {
private:
    bool isChanged = false;
    bool isClicked = false;
    int page = 1;
    int totPage = 1;
    int len = 0;
    std::string searchInput = "";
    std::string bookAuthor = "";
    std::string bookNum = "";
    std::string opt = "";
    
    //rightBox{
    ui::Label *catergoryLabel = nullptr;
    ui::Label *storePosition = nullptr;
    ui::Label *numLimitTip = nullptr;
    ui::Label *bookisbnLimitTip = nullptr;
    ui::Label *bookpublishDateLimitTip = nullptr;
    ui::VerticalBox *wholeBox = nullptr;
    ui::VerticalBox *catergoryBox = nullptr;
    ui::VerticalScrollingBox *detailBox = nullptr;
    ui::Flat *rtFootFlat = nullptr;
    ui::Button *confirmBtn = nullptr;
        ui::Button *room302Btn = nullptr;
        ui::Button *room303Btn = nullptr;
        ui::Button *room401Btn = nullptr;
        ui::Button *room402Btn = nullptr;
        ui::Button *room403Btn = nullptr;
        ui::Button *room621Btn = nullptr;
    //}
    //leftBox{
    ui::Button *backBtn = nullptr;
    ui::Button *restoreBookBtn = nullptr;
    ui::Button *modifyBookBtn = nullptr;
    ui::Button *removeBookBtn = nullptr;
    ui::VerticalBox *lfMidBox = nullptr;
    ui::HorizontalBox*optBox = nullptr;
    ui::VerticalScrollingBox *bookList = nullptr;
    ui::Button *searchOpt = nullptr;
    ui::Button *searchBtn = nullptr;
    ui::Button *nextBtn = nullptr;
    ui::Button *lastBtn = nullptr;
    ui::Label *pageLabel = nullptr;
    ui::LoadingRing *bookListLoading = nullptr;
    //}

    std::function<void()> reSetCatergoryBox = [](){};

    static std::vector<std::string> room302;
    static std::vector<std::string> room303;
    static std::vector<std::string> room401;
    static std::vector<std::string> room402;
    static std::vector<std::string> room403;
    static std::vector<std::string> room621;

    std::vector<std::string> CheckInput() const noexcept;
protected:
    void Load(ui::Screen *screen) noexcept;
    void Logic(ui::Screen *screen) noexcept;
    void Ready(ui::Screen *screen) noexcept;
};

class BookDetail : public EnterLibrary {
private:
    bool isClicked = false;
    int day = 0;

    ui::Button *backBtn = nullptr;
    ui::Button *borrowBtn = nullptr;
    ui::Button *confirmBtn = nullptr;
    ui::Label *borrowLast = nullptr;
    ui::Label *borrowTip = nullptr;
    ui::HorizontalBox *borrowBottomBox = nullptr;
    ui::VerticalBox *borrowBox = nullptr;
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
