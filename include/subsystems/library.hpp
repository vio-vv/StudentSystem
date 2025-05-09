#ifndef __SUBSYSTEMS_LIBRARY_HPP__
#define __SUBSYSTEMS_LIBRARY_HPP__

/**
 * @brief 图书馆系统。
 * @namespace ssys
 * 
 * @par REQUIRES
 * TO_COMPLETE
 * 
 * @par PROVIDES
 * TO_COMPLETE
 */

#include "system_header.hpp"

namespace ssys{

class Library{
public:
    trm::Information RestoreNewBook(const trm::Information&) noexcept;
    trm::Information BorrowBook(const trm::Information&) noexcept;
    trm::Information ReturnBook(const trm::Information&) noexcept;
    trm::Information RemoveBook(const trm::Information&) noexcept;
    trm::Information ModifyBookInfo(const trm::Information&) noexcept;
    trm::Information ResetLibrary(const trm::Information&) noexcept;
    trm::Information SendReturnReminder(const trm::Information&) noexcept;
    trm::Information SearchBook(const trm::Information&) noexcept;
    trm::Information GetAccountBorrowList(const trm::Information&) noexcept;

    //extra 

    trm::Information AddFavourate(const trm::Information&) noexcept;
    trm::Information RemoveFavourate(const trm::Information&) noexcept;
    trm::Information ShowFavourateList(const trm::Information&) noexcept;
    trm::Information ShowFavourateList(const trm::Information&, const unsigned int&) noexcept;
    trm::Information SearchFavourate(const trm::Information&) noexcept;

protected:
    Library() noexcept;
    ~Library() noexcept;
    Library(const Library&) = delete;
    Library& operator=(const Library&) = delete;
private:
    const std::string LIBRARY = "library";
    dat::DataBase books = DATA_BASE[LIBRARY]["books"];
    dat::DataBase borrowLogList = DATA_BASE[LIBRARY]["borrowLogList"];
    dat::DataBase bookBorrowLog = borrowLogList["bookBorrowLog"];
    dat::DataBase accountBorrowLog = borrowLogList["accountBorrowLog"];

    std::vector<trm::Book> activebookseries;
    std::vector<trm::BorrowLog> timeout;
    trm::Information CrossBorrowInfo() noexcept;
    trm::Information SortMatchBook(const trm::Information &content, std::function<bool(const trm::Book &a, const trm::Book &b)> &f) noexcept;
};

}

#endif