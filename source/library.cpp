#include "subsystems/library.hpp"
#include "student_system.hpp"

ssys::Library::Library() noexcept
{
    //books.Push({"978-7-04-059902-2", trm::Book{"978-7-04-059902-2", "思想道德与法治", "2023-02", "政治、法律", "图书馆社会科学综合书库402", {"《思想道德与法治（2023年版）》"}}});
}

ssys::Library::~Library() noexcept
{
}

trm::Information ssys::Library::RestoreNewBook(const trm::Information &content) noexcept
{
    assert(content[0] == trm::rqs::RESTORE_BOOK);

    auto reply = SSys::Get().CheckAccess({trm::rqs::CHECK_ACCESS, content[1], content[2], trm::Access::BOOK_MANAGE});
    if (reply[0] == trm::rpl::NO) return {trm::rpl::ACCESS_DENIED};

    if (!books.Exists(content[3])) {
        auto book = trm::Book(content[5]);
        book.bookTot = ToNum(content[4]);
        books[content[3]] = book;
    }
    else {
        trm::Book book = trm::Book(books[content[3]]);
        book.bookTot += ToNum(content[4]);
        books[content[3]] = book;
    }
    return {trm::rpl::SUCC};
}

trm::Information ssys::Library::BorrowBook(const trm::Information &content) noexcept
{
    return{};
}

trm::Information ssys::Library::ReturnBook(const trm::Information &content) noexcept
{
    return{};
}

trm::Information ssys::Library::RemoveBook(const trm::Information &content) noexcept
{   
    assert(content[0] == trm::rqs::REMOVE_BOOK);

    auto reply = SSys::Get().CheckAccess({trm::rqs::CHECK_ACCESS, content[1], content[2], trm::Access::BOOK_MANAGE});
    if (reply[0] == trm::rpl::NO) return {trm::rpl::ACCESS_DENIED};

    if (!books.Exists(content[3])) return {trm::rpl::FAIL};
    else {
        trm::Book book = trm::Book(books[content[3]]);
        if (content[4] == "all") {
            books[content[3]].Clear();
        }
        else {
            if (book.bookTot - book.bookBorrowed >= ToNum(content[4])) {
                book.bookTot -= ToNum(content[4]);
                books[content[3]] = book;
            }
            else {
                return {trm::rpl::FAIL};
            }
            if (book.bookTot == 0) books[content[3]].Clear();
        }
    }

    return{trm::rpl::SUCC};
}

trm::Information ssys::Library::ModifyBookInfo(const trm::Information &content) noexcept
{   
    assert(content[0] == trm::rqs::MODIFY_BOOK_INFO);

    auto reply = SSys::Get().CheckAccess({trm::rqs::CHECK_ACCESS, content[1], content[2], trm::Access::BOOK_MANAGE});

    if (reply[0] == trm::rpl::NO) return {trm::rpl::ACCESS_DENIED};

    if (!books.Exists(content[3])) return {trm::rpl::FAIL};
    else {
        trm::Book book = content[4];
        trm::Book oldBook = trm::Book(books[content[3]]);
        book.bookBorrowed = oldBook.bookBorrowed;
        book.bookTot = oldBook.bookTot;
        book.borrowLog = oldBook.borrowLog;
        books[book.bookIsbn] = book;
        books[content[3]].Clear();
    }

    return{trm::rpl::SUCC};
}

trm::Information ssys::Library::SortMatchBook(const trm::Information &content, std::function<bool(const trm::Book &a, const trm::Book &b)> &f) noexcept {
    assert(content[0] == trm::rqs::SORT_BOOK);
    std::sort(activebookseries.begin(), activebookseries.end(), f);
    return{trm::rpl::SUCC};
}


std::pair<trm::Information, std::vector<trm::Book>> ssys::Library::SearchBook(const trm::Information &content, std::function<bool(const trm::Book &a, const trm::Book &b)> &&f) noexcept
{   
    assert(content[0] == trm::rqs::SEARCH_BOOK);
    int type = ToNum<int>(content[2]);
    bool replace = false;
    if (content[3] == "true" || ToNum<int>(content[3]) == 1) {
        replace = true;
    }
    if (replace) {
        const double standard = 0.1;

        activebookseries.clear();
        std::vector<std::pair<double, trm::Book>> match;
        double matchRate = 0;
        for (auto [name, bookInfo] : books) {
            trm::Book tmp = trm::Book(bookInfo);
            switch (type) {
                case trm::rqs::bk::BOOK_ISBN:
                    matchRate = trm::FuzzyMatch(content[1], tmp.bookIsbn);
                    if (matchRate > standard) {
                        match.push_back({matchRate, tmp});
                    }
                    break;
                case trm::rqs::bk::BOOK_AUTHOR:
                    for (auto author : tmp.bookAuthor) {
                        matchRate = std::max(trm::FuzzyMatch(content[1], author), matchRate);
                    }
                    if (matchRate > standard) {
                        match.push_back({matchRate, tmp});
                    }
                    break;
                case trm::rqs::bk::BOOK_CATAGORY:
                    matchRate = trm::FuzzyMatch(content[1], tmp.bookCatagory);
                    if (matchRate > standard) {
                        match.push_back({matchRate, tmp});
                    }
                    break;
                case trm::rqs::bk::BOOK_PUBLISHDATE:
                    matchRate = trm::FuzzyMatch(content[1], tmp.bookPublicationDate);
                    if (matchRate > standard) {
                        match.push_back({matchRate, tmp});
                    }    
                    break;
                default:
                    matchRate = trm::FuzzyMatch(content[1], tmp.bookName);
                    if (matchRate > standard) {
                        match.push_back({matchRate, tmp});
                    }
                    break;
            }
        }
        std::sort(match.begin(), match.end(), [](const std::pair<double, trm::Book>& a, const std::pair<double, trm::Book>& b) -> bool { return a.first > b.first; });
        for (auto [a, book] : match) {
            activebookseries.push_back(book);
        }
    }

    SortMatchBook({trm::rqs::SORT_BOOK}, f);
    return{{trm::rpl::SUCC}, activebookseries};
}

trm::Information ssys::Library::SendReturnReminder(const trm::Information &content) noexcept
{   
    auto reply = CrossBorrowInfo();
    return{};
}

trm::Information ssys::Library::CrossBorrowInfo() noexcept
{   
    for (auto begin = borrowLogList.begin(); begin != borrowLogList.end(); begin++) {
        // = (borrowLogList[(*begin).first]);
    }
    
    return{};
}
