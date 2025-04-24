#include "subsystems/library.hpp"
#include "student_system.hpp"

ssys::Library::Library() noexcept
{
    auto base = dat::DataBase(DATA_PATH);
    auto library = base["library"];
    auto books = library["books"];
    books.Push({"978-7-04-059902-2", trm::Book{"978-7-04-059902-2", "思想道德与法治", "2023-02", "政治、法律", "图书馆社会科学综合书库402", {"《思想道德与法治（2023年版）》"}}});

}

ssys::Library::~Library() noexcept
{
}

trm::Information ssys::Library::RestoreNewBook(const trm::Information &content) noexcept
{
    assert(content[0] == trm::rqs::RESTORE_BOOK);

    auto reply = SSys::Get().CheckAccess({trm::rqs::CHECK_ACCESS, content[1], content[2], trm::Access::BOOK_MANAGE});
    if (reply[0] == trm::rpl::NO) return {trm::rpl::ACCESS_DENIED};

    if (books.Exists(content[3])) {
        auto book = trm::Book(content[5]);
        book.bookTot = ToNum(content[4]);
        books.Push({content[3], book});
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

    if (books.Exists(content[3])) return {trm::rpl::FAIL};
    else {
        trm::Book book = trm::Book(books[content[3]]);
        if (content[4] == "all") {
            books[content[3]].Clear();
        }
        else {
            if (book.bookTot - book.bookBorrowed <= ToNum(content[4])) {
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

    if (books.Exists(content[3])) return {trm::rpl::FAIL};
    else {
        trm::Book book = trm::Book(books[content[3]]);
        book = content[4];
    }

    return{};
}

trm::Information ssys::Library::ShowBookList(const trm::Information &content) noexcept
{
    return{};
}