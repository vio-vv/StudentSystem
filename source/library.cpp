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

trm::Infomation ssys::Library::RestoreNewBook(const trm::Infomation &content) noexcept
{
    assert(content[0] == trm::rqs::RESTORE_BOOK);

    // auto reply = SSys::Get().CheckAccess({trm::rqs::CHECK_ACCESS, content[1], content[2], trm::Access::RESTORE_BOOK});
    // if (reply[0] == trm::rpl::NO) return {trm::rpl::ACCESS_DENIED};

    auto books = dat::DataBase(DATA_PATH)["library"]["books"];
    if (!file::CheckFileExists(books.GetSpace() + content[3])) {
        auto bk = trm::Book(content[5]);
        bk.book_tot = ToNum(content[4]);
        books.Push({content[3], bk});
    }
    else {
        trm::Book bk = std::string(books[content[1]]);
        bk.book_tot += ToNum(content[4]);
        books[content[1]] = bk;
    }
    return {trm::rpl::SUCC};
}

trm::Infomation ssys::Library::BorrowBook(const trm::Infomation &content) noexcept
{
    return{};
}

trm::Infomation ssys::Library::ReturnBook(const trm::Infomation &content) noexcept
{
    return{};
}

trm::Infomation ssys::Library::RemoveBook(const trm::Infomation &content) noexcept
{
    return{};
}

trm::Infomation ssys::Library::ModifyBookInfo(const trm::Infomation &content) noexcept
{
    return{};
}

trm::Infomation ssys::Library::ShowBookList(const trm::Infomation &content) noexcept
{
    return{};
}

trm::Book::Book(const std::string &content) noexcept
{
    auto data = trm::Split(content);
    *this = {
        data[0],
        data[1],
        data[2],
        data[3],
        data[4],
        trm::Split(data[5]),
        ToNum<unsigned int>(data[6]),
        ToNum<unsigned int>(data[7]),
        trm::Split(data[8])
    };
}

trm::Book::~Book() noexcept
{
}

trm::Book::operator std::string() noexcept
{
    return trm::Combine({
        book_isbn, book_name,
        book_publication_date,
        book_catagory,
        store_position,
        trm::Combine(book_author),
        ToStr(book_tot),
        ToStr(book_borrowed),
        trm::Combine(borrow_log)
    });
}
