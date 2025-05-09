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
    assert(content[0] == trm::rqs::BORROW_BOOK);

    auto reply = SSys::Get().CheckAccess({trm::rqs::CHECK_ACCESS, content[1], content[2], trm::Access::BORROW_BOOK});
    if (reply[0] == trm::rpl::NO) return {trm::rpl::ACCESS_DENIED};

    auto book = trm::Book(books[content[3]]);
    if (book.bookTot - book.bookBorrowed < 1) return {trm::rpl::NO_SPARE_BOOK};
    else {
        book.bookBorrowed++;
        books[content[3]] = book;
        time_t currantTime = time(nullptr);
        bookBorrowLog[content[3]].Push(trm::BorrowLog{ToNum<int>(content[4]), trm::Date(currantTime), content[1], content[3]});
        accountBorrowLog[content[1]].Push(trm::BorrowLog{ToNum<int>(content[4]), trm::Date(currantTime), content[1], content[3]});
    }
    return{trm::rpl::SUCC};
}

trm::Information ssys::Library::ReturnBook(const trm::Information &content) noexcept
{
    assert(content[0] == trm::rqs::RETURN_BOOK);

    auto reply = SSys::Get().CheckAccountExist({trm::rqs::CHECK_ACCOUNT_EXISTS, content[1]});
    if (reply[0] == trm::rpl::NO) return {trm::rpl::FAIL};

    auto logs = accountBorrowLog[content[1]];
    for (auto [name, log] : logs) {
        auto logInfo = trm::BorrowLog(log);
        if (logInfo.bookIsbn == content[3] && logInfo.start.currantTime == ToNum<time_t>(content[4])) {
            auto book = trm::Book(books[content[3]]);
            book.bookBorrowed--;
            books[content[3]] = book;
            accountBorrowLog[content[1]][name].Clear();
            for (auto [name1, log1] : bookBorrowLog[content[3]]) {
                auto logInfo1 = trm::BorrowLog(log1);
                if (logInfo1.borrower == content[1] && logInfo1.start.currantTime == ToNum<time_t>(content[4])) {
                    bookBorrowLog[content[3]][name1].Clear();
                    break;
                }
            }
            return {trm::rpl::SUCC};
        }
    }
    return{trm::rpl::NO_BORROW_RECORD};
}

trm::Information ssys::Library::RemoveBook(const trm::Information &content) noexcept
{   
    assert(content[0] == trm::rqs::REMOVE_BOOK);

    auto reply = SSys::Get().CheckAccess({trm::rqs::CHECK_ACCESS, content[1], content[2], trm::Access::BOOK_MANAGE});
    if (reply[0] == trm::rpl::NO) return {trm::rpl::ACCESS_DENIED};

    if (!books.Exists(content[3])) return {trm::rpl::NO_BOOK};
    else {
        trm::Book book = trm::Book(books[content[3]]);
        if (content[4] == "all") {
            books[content[3]].Clear();
            for (auto [name, log] : bookBorrowLog[content[3]]) {
                auto logInfo = trm::BorrowLog(log);
                for (auto [name1, log1] : accountBorrowLog[logInfo.borrower]) {
                    auto logInfo1 = trm::BorrowLog(log1);
                    if (logInfo1.bookIsbn == content[3]) {
                        accountBorrowLog[logInfo1.borrower][name1].Clear();
                    }
                }
                bookBorrowLog[content[3]][name].Clear();
            }
            bookBorrowLog[content[3]].Remove();
        }
        else {
            if (book.bookTot - book.bookBorrowed >= ToNum(content[4])) {
                book.bookTot -= ToNum(content[4]);
                books[content[3]] = book;
            }
            else {
                return {trm::rpl::EXCEED_BOOK_NUM};
            }
            if (book.bookTot == 0)  {
                books[content[3]].Clear();
                for (auto [name, log] : bookBorrowLog[content[3]]) {
                    auto logInfo = trm::BorrowLog(log);
                    for (auto [name1, log1] : accountBorrowLog[logInfo.borrower]) {
                        auto logInfo1 = trm::BorrowLog(log1);
                        if (logInfo1.bookIsbn == content[3]) {
                            accountBorrowLog[logInfo1.borrower][name1].Clear();
                        }
                    }
                    bookBorrowLog[content[3]][name].Clear();
                }
                bookBorrowLog[content[3]].Remove();
            }
        }
    }

    return{trm::rpl::SUCC};
}

trm::Information ssys::Library::ModifyBookInfo(const trm::Information &content) noexcept
{   
    assert(content[0] == trm::rqs::MODIFY_BOOK_INFO);

    auto reply = SSys::Get().CheckAccess({trm::rqs::CHECK_ACCESS, content[1], content[2], trm::Access::BOOK_MANAGE});

    if (reply[0] == trm::rpl::NO) return {trm::rpl::ACCESS_DENIED};

    if (!books.Exists(content[3])) return {trm::rpl::NO_BOOK};
    else {
        trm::Book book = content[4];
        if (books.Exists(book.bookIsbn) && book.bookIsbn != content[3]) return {trm::rpl::EXIST_BOOK}; 
        auto oldBook = trm::Book(books[content[3]]);
        book.bookBorrowed = oldBook.bookBorrowed;
        book.bookTot = oldBook.bookTot;
        if (book.bookIsbn != oldBook.bookIsbn) {
            auto newLogs = bookBorrowLog[book.bookIsbn];
            auto oldLogs = bookBorrowLog[content[3]];
            for (auto [name, log] : oldLogs) {
                auto logInfo = trm::BorrowLog(log);
                logInfo.bookIsbn = book.bookIsbn;
                newLogs.Push(logInfo);
                for (auto [name1, log1] : accountBorrowLog[logInfo.borrower]) {
                    auto logInfo1 = trm::BorrowLog(log1);
                    if (logInfo1.bookIsbn == content[3]) {
                        accountBorrowLog[logInfo1.borrower][name1] = logInfo;
                    }
                }
            }
            bookBorrowLog[content[3]].Remove();
            books[content[3]].Clear();
        }
        books[book.bookIsbn] = book;
    }

    return{trm::rpl::SUCC};
}

trm::Information ssys::Library::SortMatchBook(const trm::Information &content, std::function<bool(const trm::Book &a, const trm::Book &b)> &f) noexcept {
    assert(content[0] == trm::rqs::SORT_BOOK);
    std::sort(activebookseries.begin(), activebookseries.end(), f);
    return{trm::rpl::SUCC};
}

trm::Information ssys::Library::GetAccountBorrowList(const trm::Information &content) noexcept
{
    assert(content[0] == trm::rqs::GET_ACCOUNT_BORROW_LIST);

    auto reply = SSys::Get().CheckAccountExist({trm::rqs::CHECK_ACCOUNT_EXISTS, content[1]});
    if (reply[0] == trm::rpl::NO) return {{trm::rpl::NO_ACCOUNT}};

    trm::Information ret;

    auto logs = accountBorrowLog[content[1]];
    for (auto [name, log] : logs) {
        auto logInfo = trm::BorrowLog(log);
        ret.push_back(logInfo);
    }
    return ret;
}


trm::Information ssys::Library::SearchBook(const trm::Information &content) noexcept
{   
    assert(content[0] == trm::rqs::SEARCH_BOOK);
    int type = ToNum<int>(content[2]);
    bool ascending = true;
    if (content[4] == "false") {
        ascending = false;
    }
    std::function<bool(const trm::Book &a, const trm::Book &b)> f;
    const double standard = 0.10;

    trm::Information ret;
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
                if (ascending) f = [](const trm::Book &a, const trm::Book &b) -> bool { return a.bookIsbn < b.bookIsbn; };
                else f = [](const trm::Book &a, const trm::Book &b) -> bool { return a.bookIsbn > b.bookIsbn; };
                break;
            case trm::rqs::bk::BOOK_AUTHOR:
                for (auto author : tmp.bookAuthor) {
                    matchRate = std::max(trm::FuzzyMatch(content[1], author), matchRate);
                }
                if (matchRate > standard) {
                    match.push_back({matchRate, tmp});
                }
                if (ascending) f = [](const trm::Book &a, const trm::Book &b) -> bool { return a.bookAuthor[0] < b.bookAuthor[0]; };
                else f = [](const trm::Book &a, const trm::Book &b) -> bool { return a.bookAuthor[0] > b.bookAuthor[0]; };
                break;
            case trm::rqs::bk::BOOK_CATAGORY:
                matchRate = trm::FuzzyMatch(content[1], tmp.bookCatagory);
                if (matchRate > standard) {
                    match.push_back({matchRate, tmp});
                }
                if (ascending) f = [](const trm::Book &a, const trm::Book &b) -> bool { return a.bookCatagory < b.bookCatagory; };
                else f = [](const trm::Book &a, const trm::Book &b) -> bool { return a.bookCatagory > b.bookCatagory; };
                break;
            case trm::rqs::bk::BOOK_PUBLISHDATE:
                matchRate = trm::FuzzyMatch(content[1], tmp.bookPublicationDate);
                if (matchRate > standard) {
                    match.push_back({matchRate, tmp});
                }
                if (ascending) f = [](const trm::Book &a, const trm::Book &b) -> bool { return a.bookPublicationDate < b.bookPublicationDate; };
                else f = [](const trm::Book &a, const trm::Book &b) -> bool { return a.bookPublicationDate > b.bookPublicationDate; };
                break;
            default:
                matchRate = trm::FuzzyMatch(content[1], tmp.bookName);
                if (matchRate > standard) {
                    match.push_back({matchRate, tmp});
                }
                if (ascending) f = [](const trm::Book &a, const trm::Book &b) -> bool { return a.bookName < b.bookName; };
                else f = [](const trm::Book &a, const trm::Book &b) -> bool { return a.bookName > b.bookName; };
                break;
        }
    
        std::sort(match.begin(), match.end(), [](const std::pair<double, trm::Book>& a, const std::pair<double, trm::Book>& b) -> bool { return a.first > b.first; });
        for (auto [rate, book] : match) {
            activebookseries.push_back(book);
        }
        match.clear();
    }

    if (content[3] == "true") SortMatchBook({trm::rqs::SORT_BOOK}, f);
    for (auto book : activebookseries) {
        ret.push_back(book);
    }
    activebookseries.clear();
    return ret;
}

trm::Information ssys::Library::SendReturnReminder(const trm::Information &content) noexcept
{   
    assert(content[0] == trm::rqs::SEND_RETURN_REMINDER);

    auto reply = CrossBorrowInfo();
    if (reply[0] != trm::rpl::SUCC) return {trm::rpl::FAIL};

    for (auto log : timeout) {
        auto time = log.end.timeInfo;
        auto book = trm::Book(books[log.bookIsbn]);
        SSys::Get().SendMessage({trm::rqs::SEND_MESSAGE, "adm", "123", log.borrower, "图书归还提醒", "您好，您的图书《" + book.bookName + "》在" + std::to_string(time->tm_year + 1900) + "年" + std::to_string(time->tm_mon + 1) + "月" + std::to_string(time->tm_mday) + "到期，请及时归还。"});
    }
    timeout.clear();
    return{trm::rpl::SUCC};
}

trm::Information ssys::Library::CrossBorrowInfo() noexcept
{   
    timeout.clear();
    for (auto [name, account] : accountBorrowLog) {
        for (auto [name1, log] : account) {
            auto logInfo = trm::BorrowLog(log);
            time_t now = time(nullptr);
            if (logInfo.end.currantTime - 5 * 24 * 60 * 60 <= now ) {
                timeout.push_back(logInfo);
            }
        }
    }
    return{trm::rpl::SUCC};
}
