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
    trm::Information RestoreNewBook(const trm::Information&) noexcept;
    trm::Information BorrowBook(const trm::Information&) noexcept;
    trm::Information ReturnBook(const trm::Information&) noexcept;
    trm::Information RemoveBook(const trm::Information&) noexcept;
    trm::Information SearchBook(const trm::Information&) noexcept;
    trm::Information ModifyBookInfo(const trm::Information&) noexcept;
    trm::Information ShowBookList(const trm::Information&) noexcept;
    trm::Information ShowBookList(const trm::Information&, const unsigned int&) noexcept;
    trm::Information SendReturnReminder(const trm::Information&) noexcept;
    template<typename SortType>
    trm::Information SortMatchBook(const trm::Information &content, std::function<bool(const SortType &a, const SortType &b)> &f) noexcept;

protected:
    Library() noexcept;
    ~Library() noexcept;
    Library(const Library&) = delete;
    Library& operator=(const Library&) = delete;
};

template<typename SortType>
trm::Information Library::SortMatchBook(const trm::Information &content, std::function<bool(const SortType &a, const SortType &b)> &f) noexcept {
    assert(content[0] == trm::rqs::SORT_BOOK);
    std::sort(activebookseries.begin(), activebookseries.end(), f);
    return{trm::rpl::SUCC};
}

}

#endif
