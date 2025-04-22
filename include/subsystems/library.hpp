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
    //std::vector<bk::Book> basebookseries;    
    std::vector<trm::Book> activebookseries;
    std::pair<bool, std::vector<std::string>> CrossBorrowInfo() noexcept;  
public:
    trm::Infomation RestoreNewBook(const trm::Infomation&) noexcept;
    trm::Infomation BorrowBook(const trm::Infomation&) noexcept;
    trm::Infomation ReturnBook(const trm::Infomation&) noexcept;
    trm::Infomation RemoveBook(const trm::Infomation&) noexcept;
    trm::Infomation SearchBook(const trm::Infomation&) noexcept;
    trm::Infomation ModifyBookInfo(const trm::Infomation&) noexcept;
    trm::Infomation ShowBookList(const trm::Infomation&) noexcept;
    trm::Infomation ShowBookList(const trm::Infomation&, const unsigned int&) noexcept;
    trm::Infomation SendReturnReminder(const trm::Infomation&) noexcept;
    template<typename SortType>
    trm::Infomation SortMatchBook(const trm::Infomation &content, std::function<bool(const SortType &a, const SortType &b)> &f) noexcept;

protected:
    Library() noexcept;
    ~Library() noexcept;
    Library(const Library&) = delete;
    Library& operator=(const Library&) = delete;
};

template<typename SortType>
trm::Infomation Library::SortMatchBook(const trm::Infomation &content, std::function<bool(const SortType &a, const SortType &b)> &f) noexcept {
    assert(content[0] == trm::rqs::SORT_BOOK);
    std::sort(activebookseries.begin(), activebookseries.end(), f);
    return{trm::rpl::SUCC};
}

}

#endif
