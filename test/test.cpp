#include <iostream>
#include "ui.hpp"
#include <string>
#include "student_system.hpp"
#include "transmitter.hpp"
#include "data_base.hpp"

using namespace std;
using namespace trm;

void f(const Information &info)
{
    for (const auto &each : info) {
        cout << each << " :: ";
    }
    cout << endl;
}

int main()
{
    freopen("out.txt", "w", stdout);
    auto &ssys = SSys::Get();

#ifdef EEA

    f(ssys.CheckAccountExist({rqs::CHECK_ACCOUNT_EXISTS, "admin"}));
    f(ssys.CheckAccountExist({rqs::CHECK_ACCOUNT_EXISTS, "adm"}));

    f(ssys.CreateAccount({rqs::CREATE_ACCOUNT, "adm", "123", Account{"1", "1", {}, {{"name", "张三"}, {"age", "20"}}}}));
    f(ssys.CheckAccount({rqs::CHECK_ACCOUNT, "adm", "123456"}));
    f(ssys.CheckAccount({rqs::CHECK_ACCOUNT, "adm", "123"}));
    f(ssys.CheckAccount({rqs::CHECK_ACCOUNT, "1", "1"}));
    f(ssys.CheckAccount({rqs::CHECK_ACCOUNT, "2", "1"}));

    f(ssys.CheckAccess({rqs::CHECK_ACCESS, "adm", "123456", Access::CREATE_ACCOUNT}));
    f(ssys.CheckAccess({rqs::CHECK_ACCESS, "1", "123", Access::CREATE_ACCOUNT}));
    f(ssys.CheckAccess({rqs::CHECK_ACCESS, "1", "1", Access::CREATE_ACCOUNT}));

    f(ssys.CreateAccount({rqs::CREATE_ACCOUNT, "adm", "123", Account{"2", "2", {Access::SEND_MESSAGE, Access::CREATE_ACCOUNT}}}));
    f(ssys.CreateAccount({rqs::CREATE_ACCOUNT, "adm", "123", Account{"2", "2", {Access::SEND_MESSAGE, Access::CREATE_ACCOUNT}}}));
    f(ssys.CreateAccount({rqs::CREATE_ACCOUNT, "1", "1", Account{"3", "3"}}));
    f(ssys.CreateAccount({rqs::CREATE_ACCOUNT, "2", "2", Account{"3", "3", {Access::SEND_MESSAGE, Access::DELETE_ACCOUNT}}}));
    f(ssys.CreateAccount({rqs::CREATE_ACCOUNT, "2", "2", Account{"3", "3", {Access::SEND_MESSAGE}}}));
    
    f(ssys.DeleteAccount({rqs::DELETE_ACCOUNT, "2", "2", "3"}));
    f(ssys.DeleteAccount({rqs::DELETE_ACCOUNT, "adm", "123", "3"}));
    f(ssys.DeleteAccount({rqs::DELETE_ACCOUNT, "adm", "123", "2"}));
    f(ssys.DeleteAccount({rqs::DELETE_ACCOUNT, "adm", "123", "2"}));

    f(ssys.SendMessage({rqs::SEND_MESSAGE, "adm", "12", "1", "Title", "hello"}));
    f(ssys.SendMessage({rqs::SEND_MESSAGE, "adm", "123", "1", "Title", "hello"}));
    f(ssys.SendMessage({rqs::SEND_MESSAGE, "adm", "123", "2", "Title", "hello"}));
    f(ssys.GetMessageNumber({rqs::GET_MESSAGE_NUMBER, "adm", "123"}));
    f(ssys.GetMessageNumber({rqs::GET_MESSAGE_NUMBER, "admin", "123"}));
    f(ssys.GetMessageNumber({rqs::GET_MESSAGE_NUMBER, "1", "2"}));
    f(ssys.GetMessageNumber({rqs::GET_MESSAGE_NUMBER, "1", "1"}));

    f(ssys.GetMessageProfile({rqs::GET_MESSAGE_PROFILE, "1", "1", "0", "5"}));
    f(ssys.GetMessageProfile({rqs::GET_MESSAGE_PROFILE, "1", "1", "1", "5"}));
    f(ssys.SendMessage({rqs::SEND_MESSAGE, "adm", "123", "1", "Title111", "hello111"}));
    f(ssys.SendMessage({rqs::SEND_MESSAGE, "adm", "123", "1", "Title222", "hello222"}));
    f(ssys.GetMessageProfile({rqs::GET_MESSAGE_PROFILE, "1", "1", "1", "5"}));

    f(ssys.GetMessageNumber({rqs::GET_MESSAGE_NUMBER, "1", "1"}));
    f(ssys.GetUnreadMessageNumber({rqs::GET_UNREAD_MESSAGE_NUMBER, "1", "1"}));
    f(ssys.GetMessage({rqs::GET_MESSAGE, "1", "1", "0"}));
    f(ssys.GetMessageNumber({rqs::GET_MESSAGE_NUMBER, "1", "1"}));
    f(ssys.GetUnreadMessageNumber({rqs::GET_UNREAD_MESSAGE_NUMBER, "1", "1"}));
    f(ssys.MarkAsRead({rqs::MARK_AS_READ, "1", "1", "1"}));
    f(ssys.GetMessageNumber({rqs::GET_MESSAGE_NUMBER, "1", "1"}));
    f(ssys.GetUnreadMessageNumber({rqs::GET_UNREAD_MESSAGE_NUMBER, "1", "1"}));
    f(ssys.MarkAsUnread({rqs::MARK_AS_UNREAD, "1", "1", "0"}));
    f(ssys.GetMessageNumber({rqs::GET_MESSAGE_NUMBER, "1", "1"}));
    f(ssys.GetUnreadMessageNumber({rqs::GET_UNREAD_MESSAGE_NUMBER, "1", "1"}));
    f(ssys.MarkAsUnread({rqs::MARK_AS_UNREAD, "1", "1", "0"}));
    f(ssys.GetMessageNumber({rqs::GET_MESSAGE_NUMBER, "1", "1"}));
    f(ssys.GetUnreadMessageNumber({rqs::GET_UNREAD_MESSAGE_NUMBER, "1", "1"}));
    f(ssys.MarkAsRead({rqs::MARK_AS_READ, "1", "1", "1"}));
    f(ssys.GetMessageNumber({rqs::GET_MESSAGE_NUMBER, "1", "1"}));
    f(ssys.GetUnreadMessageNumber({rqs::GET_UNREAD_MESSAGE_NUMBER, "1", "1"}));
    f(ssys.GetMessage({rqs::GET_MESSAGE, "1", "1", "1"}));
    f(ssys.GetMessageNumber({rqs::GET_MESSAGE_NUMBER, "1", "1"}));
    f(ssys.GetUnreadMessageNumber({rqs::GET_UNREAD_MESSAGE_NUMBER, "1", "1"}));

    f(ssys.DeleteMessage({rqs::DELETE_MESSAGE, "1", "1", "1"}));
    f(ssys.GrantAccess({rqs::GRANT_ACCESS, "adm", "12", "1", Access::DELETE_MESSAGE}));
    f(ssys.GrantAccess({rqs::GRANT_ACCESS, "adm", "123", "1", Access::DELETE_MESSAGE}));
    f(ssys.DeleteMessage({rqs::DELETE_MESSAGE, "1", "1", "1"}));
    f(ssys.GetMessageNumber({rqs::GET_MESSAGE_NUMBER, "1", "1"}));
    f(ssys.GetUnreadMessageNumber({rqs::GET_UNREAD_MESSAGE_NUMBER, "1", "1"}));
    f(ssys.DeleteMessage({rqs::DELETE_MESSAGE, "1", "1", "1"}));
    f(ssys.GetMessageNumber({rqs::GET_MESSAGE_NUMBER, "1", "1"}));
    f(ssys.GetUnreadMessageNumber({rqs::GET_UNREAD_MESSAGE_NUMBER, "1", "1"}));

    f(ssys.RevokeAccess({rqs::REVOKE_ACCESS, "adm", "123", "1", Access::DELETE_MESSAGE}));
    f(ssys.DeleteMessage({rqs::DELETE_MESSAGE, "1", "1", "0"}));
    f(ssys.GetMessageNumber({rqs::GET_MESSAGE_NUMBER, "1", "1"}));
    f(ssys.GetUnreadMessageNumber({rqs::GET_UNREAD_MESSAGE_NUMBER, "1", "1"}));
    f(ssys.GrantAccess({rqs::GRANT_ACCESS, "adm", "123", "1", Access::GRANT_ACCESS}));
    f(ssys.GrantAccess({rqs::GRANT_ACCESS, "adm", "123", "1", Access::REVOKE_ACCESS}));
    f(ssys.GrantAccess({rqs::GRANT_ACCESS, "1", "1", "adm", Access::DELETE_MESSAGE}));
    f(ssys.GrantAccess({rqs::GRANT_ACCESS, "1", "1", "admin", Access::GRANT_ACCESS}));
    f(ssys.GrantAccess({rqs::GRANT_ACCESS, "1", "1", "adm", Access::GRANT_ACCESS}));
    f(ssys.GrantAccess({rqs::GRANT_ACCESS, "1", "1", "adm", Access::GRANT_ACCESS}));
    f(ssys.RevokeAccess({rqs::REVOKE_ACCESS, "1", "1", "adm", Access::GRANT_ACCESS}));
    f(ssys.RevokeAccess({rqs::REVOKE_ACCESS, "1", "1", "adm", Access::GRANT_ACCESS}));
    f(ssys.RevokeAccess({rqs::REVOKE_ACCESS, "1", "1", "adm", Access::ADM}));
    f(ssys.RevokeAccess({rqs::REVOKE_ACCESS, "adm", "123", "1", Access::GRANT_ACCESS}));
    f(ssys.RevokeAccess({rqs::REVOKE_ACCESS, "adm", "123", "1", Access::REVOKE_ACCESS}));

    f(ssys.DeleteMessageOfOthers({rqs::DELETE_MESSAGE_OF_OTHERS, "adm", "123", "1", "2"}));
    f(ssys.GetMessageNumber({rqs::GET_MESSAGE_NUMBER, "1", "1"}));
    f(ssys.GetUnreadMessageNumber({rqs::GET_UNREAD_MESSAGE_NUMBER, "1", "1"}));
    f(ssys.DeleteMessageOfOthers({rqs::DELETE_MESSAGE_OF_OTHERS, "adm", "123", "1", "0"}));
    f(ssys.GetMessageNumber({rqs::GET_MESSAGE_NUMBER, "1", "1"}));
    f(ssys.GetUnreadMessageNumber({rqs::GET_UNREAD_MESSAGE_NUMBER, "1", "1"}));
    f(ssys.ClearMessageOfOthers({rqs::CLEAR_MESSAGE_OF_OTHERS, "adm", "123", "1"}));
    f(ssys.GetMessageNumber({rqs::GET_MESSAGE_NUMBER, "1", "1"}));
    f(ssys.GetUnreadMessageNumber({rqs::GET_UNREAD_MESSAGE_NUMBER, "1", "1"}));

    f(ssys.CreateAccount({rqs::CREATE_ACCOUNT, "adm", "123", Account{"2", "2"}}));
    f(ssys.DeleteMessageOfOthers({rqs::DELETE_MESSAGE_OF_OTHERS, "adm", "123", "2", "0"}));
    f(ssys.ClearMessageOfOthers({rqs::CLEAR_MESSAGE_OF_OTHERS, "adm", "123", "2"}));
    f(ssys.DeleteAccount({rqs::DELETE_ACCOUNT, "adm", "123", "2"}));
    f(ssys.DeleteMessageOfOthers({rqs::DELETE_MESSAGE_OF_OTHERS, "adm", "123", "2", "0"}));
    f(ssys.ClearMessageOfOthers({rqs::CLEAR_MESSAGE_OF_OTHERS, "adm", "123", "2"}));

    f(ssys.ResetMailSystem({rqs::RESET_MAIL_SYSTEM, "2", "2"}));
    f(ssys.ResetMailSystem({rqs::RESET_MAIL_SYSTEM, "1", "1"}));
    f(ssys.ResetMailSystem({rqs::RESET_MAIL_SYSTEM, "adm", "1"}));
    f(ssys.ResetMailSystem({rqs::RESET_MAIL_SYSTEM, "adm", "123"}));

    f(ssys.AddTag({rqs::ADD_TAG, "adm", "1233", "2", "t", "v"}));
    f(ssys.AddTag({rqs::ADD_TAG, "adm", "123", "2", "t", "v"}));
    f(ssys.AddTag({rqs::ADD_TAG, "adm", "123", "1", "t", "v"}));
    f(ssys.AddTag({rqs::ADD_TAG, "adm", "123", "1", "name", "李四"}));

    f(ssys.QueryTag({rqs::QUERY_TAG, "adm", "123"}));
    f(ssys.QueryTag({rqs::QUERY_TAG, "1", "t"}));
    f(ssys.QueryTag({rqs::QUERY_TAG, "1", "name"}));
    f(ssys.QueryTag({rqs::QUERY_TAG, "1", "1"}));
    f(ssys.QueryTag({rqs::QUERY_TAG, "2", "2"}));

    f(ssys.RemoveTag({rqs::REMOVE_TAG, "adm", "123", "2", "t"}));
    f(ssys.RemoveTag({rqs::REMOVE_TAG, "adm", "123", "1", "t"}));
    f(ssys.RemoveTag({rqs::REMOVE_TAG, "1", "1", "1", "name"}));
    f(ssys.ClearTag({rqs::CLEAR_TAG, "1", "1", "1"}));
    f(ssys.ClearTag({rqs::CLEAR_TAG, "adm", "1", "1"}));
    f(ssys.ClearTag({rqs::CLEAR_TAG, "adm", "123", "1"}));

    f(ssys.GrantAccess({rqs::GRANT_ACCESS, "adm", "123", "1", Access::SEND_MESSAGE}));
    f(ssys.GrantAccess({rqs::GRANT_ACCESS, "adm", "123", "1", Access::CREATE_ACCOUNT}));
    f(ssys.GrantAccess({rqs::GRANT_ACCESS, "adm", "123", "1", Access::REVOKE_ACCESS}));
    f(ssys.CreateAccount({rqs::CREATE_ACCOUNT, "1", "1", Account{"2", "2", {Access::SEND_MESSAGE, Access::CREATE_ACCOUNT, trm::Access::DELETE_ACCOUNT}}}));
    f(ssys.GrantAccess({rqs::GRANT_ACCESS, "adm", "123", "2", Access::DELETE_ACCOUNT}));
    f(ssys.RevokeAllAccess({rqs::REVOKE_ALL_ACCESS, "1", "2", "2"}));
    f(ssys.RevokeAllAccess({rqs::REVOKE_ALL_ACCESS, "1", "1", "2"}));
    f(ssys.RevokeAllAccess({rqs::REVOKE_ALL_ACCESS, "adm", "123", "2"}));
    f(ssys.RevokeAllAccess({rqs::REVOKE_ALL_ACCESS, "adm", "123", "1"}));

    f(ssys.ResetAccountAndAccess({rqs::RESET_ACCOUNT_AND_ACCESS, "adm", "123"}));

#endif

#ifdef LIBRARY
    f(ssys.RestoreNewBook({trm::rqs::RESTORE_BOOK, "adm", "123", "999-9-99-999999-1", "15", Book{"999-9-99-999999-1", "++--", "2025-04", "科学技术", "图书馆208", {"张某某"}}}));
    f(ssys.RestoreNewBook({trm::rqs::RESTORE_BOOK, "adm", "123", "784-8-15-941394-1", "5", Book{"784-8-15-941394-1", "aabb", "2024-10", "科学技术", "图书馆208", {"李某某"}}}));
    f(ssys.RestoreNewBook({trm::rqs::RESTORE_BOOK, "adm", "123", "189-9-39-998899-2", "5", Book{"189-9-39-998899-2", "ccad45", "1925-12", "科学技术", "图书馆208", {"李某"}}}));
    f(ssys.RemoveBook({trm::rqs::REMOVE_BOOK, "adm", "123", "999-9-99-999999-1", "10"}));
    f(ssys.ModifyBookInfo({trm::rqs::MODIFY_BOOK_INFO, "adm", "123", "999-9-99-999999-1", Book{"123-4-56-789101-1", "++--", "2025-04", "科学技术", "图书馆208", {"张某某"}}}));
    auto reply = ssys.SearchBook({trm::rqs::SEARCH_BOOK, "abc", "", "true"}, [](const trm::Book &a, const trm::Book &b) -> bool { return a.storePosition < b.storePosition; });
    for (auto &book : reply.second) {
        std::cout << book.bookIsbn << " " << book.bookName << " ";
        for (auto &author : book.bookAuthor) {
            std::cout << author << ',';
        }
        std::cout << " " << book.bookPublicationDate << " " << book.bookCatagory << " " << book.storePosition << std::endl;
    }

    f(ssys.RestoreNewBook({trm::rqs::RESTORE_BOOK, "adm", "123", "123-4-56-789101-1", "15", Book{"123-4-56-789101-1", "8416++--", "1945-04", "自然哲学", "图书馆108", {"廖某"}}}));
    f(ssys.RestoreNewBook({trm::rqs::RESTORE_BOOK, "adm", "123", "123-4-56-784875-2", "100", Book{"123-4-56-784875-2", "jasjiw", "1885-04", "信息技术", "图书馆103", {"欧锦"}}}));
    f(ssys.RestoreNewBook({trm::rqs::RESTORE_BOOK, "adm", "123", "443-4-56-784875-2", "100", Book{"443-4-56-784875-2", "百科大全", "1885-04", "信息技术", "图书馆106", {"王"}}}));
    f(ssys.RestoreNewBook({trm::rqs::RESTORE_BOOK, "adm", "123", "333-4-56-784875-2", "100", Book{"333-4-56-784875-2", "深度学习下计算机视觉", "2019-04", "信息技术", "图书馆106", {"阿达"}}}));
    f(ssys.RestoreNewBook({trm::rqs::RESTORE_BOOK, "adm", "123", "553-4-56-784875-2", "100", Book{"553-4-56-784875-2", "数学分析", "2015-04", "数学", "图书馆104", {"莫"}}}));
    f(ssys.RestoreNewBook({trm::rqs::RESTORE_BOOK, "adm", "123", "123-4-96-784875-2", "100", Book{"123-4-96-784875-2", "材料", "1995-04", "自然科学", "图书馆203", {"孙少平"}}}));
    f(ssys.RestoreNewBook({trm::rqs::RESTORE_BOOK, "adm", "123", "123-4-55-784875-2", "100", Book{"123-4-55-784875-2", "经济与文化演变", "2005-04", "社会学", "图书馆302", {"kk"}}}));
    f(ssys.RestoreNewBook({trm::rqs::RESTORE_BOOK, "adm", "123", "123-5-56-784875-2", "100", Book{"123-5-56-784875-2", "民法典探讨", "1885-04", "法学", "图书馆203", {"康"}}}));
    f(ssys.RestoreNewBook({trm::rqs::RESTORE_BOOK, "adm", "123", "123-8-56-784875-2", "100", Book{"123-8-56-784875-2", "神曲", "1485-04", "文学", "图书馆101", {"但丁"}}}));
    f(ssys.RestoreNewBook({trm::rqs::RESTORE_BOOK, "adm", "123", "123-3-56-784875-2", "100", Book{"123-2-56-784875-2", "中国近现代史", "2019-04", "历史", "图书馆104", {"白"}}}));

    f(ssys.RemoveBook({trm::rqs::REMOVE_BOOK, "adm", "123", "123-4-56-789101-1", "20"}));
    f(ssys.RemoveBook({trm::rqs::REMOVE_BOOK, "adm", "123", "123-4-56-784875-2", "105"}));
    f(ssys.RemoveBook({trm::rqs::REMOVE_BOOK, "adm", "123", "443-4-56-784875-2", "80"}));
    f(ssys.RemoveBook({trm::rqs::REMOVE_BOOK, "adm", "123", "333-4-56-784875-2", "90"}));
    f(ssys.RemoveBook({trm::rqs::REMOVE_BOOK, "adm", "123", "553-4-56-784875-2", "10"}));
    f(ssys.RemoveBook({trm::rqs::REMOVE_BOOK, "adm", "123", "123-4-96-784875-2", "120"}));
    f(ssys.RemoveBook({trm::rqs::REMOVE_BOOK, "adm", "123", "123-4-55-784875-2", "10"}));
    f(ssys.RemoveBook({trm::rqs::REMOVE_BOOK, "adm", "123", "123-5-56-784875-2", "900"}));
    f(ssys.RemoveBook({trm::rqs::REMOVE_BOOK, "adm", "123", "123-8-56-784875-2", "all"}));
    f(ssys.RemoveBook({trm::rqs::REMOVE_BOOK, "adm", "123", "123-3-56-784875-2", "1"}));

    f(ssys.BorrowBook({trm::rqs::BORROW_BOOK, "adm", "123", "443-4-56-784875-2", "20"}));
    f(ssys.BorrowBook({trm::rqs::BORROW_BOOK, "adm", "123", "333-4-56-784875-2", "10"}));
    f(ssys.BorrowBook({trm::rqs::BORROW_BOOK, "adm", "123", "553-4-56-784875-2", "5"}));
    f(ssys.BorrowBook({trm::rqs::BORROW_BOOK, "adm", "123", "123-4-96-784875-2", "10"}));
    f(ssys.BorrowBook({trm::rqs::BORROW_BOOK, "adm", "123", "123-4-55-784875-2", "-10"}));
    auto reply_ = ssys.GetAccountBorrowList({trm::rqs::GET_ACCOUNT_BORROW_LIST, "adm", "123"});
    for (auto &borrow : reply_.second) {
        std::cout << borrow.borrowLast << " " << borrow.start.currantTime << " " << borrow.end.currantTime << " " << borrow.bookIsbn << " " << borrow.borrower << std::endl;
    }

    f(ssys.SendReturnReminder({trm::rqs::SEND_RETURN_REMINDER}));

    auto reply_4 = ssys.SearchBook({trm::rqs::SEARCH_BOOK, "经济", "", "true"}, [](const trm::Book &a, const trm::Book &b) -> bool { return a.bookPublicationDate < b.bookPublicationDate; });
    for (auto &book : reply_4.second) {
        std::cout << book.bookIsbn << " "; 
        std::cout << book.bookName << " ";
        for (auto &author : book.bookAuthor) {
            std::cout << author << ',';
        }
        std::cout << " " << book.bookPublicationDate << " " << book.bookCatagory << " " << book.storePosition << std::endl;
    }

    f(ssys.ModifyBookInfo({trm::rqs::MODIFY_BOOK_INFO, "adm", "123", "443-4-56-784875-2", Book{"111-1-11-111111-1", "asdi-", "2015-04", "科学技术", "图书馆207", {"张某某"}}}));
    f(ssys.ModifyBookInfo({trm::rqs::MODIFY_BOOK_INFO, "adm", "123", "333-4-56-784875-2", Book{"222-2-22-222222-2", "+ojo-", "2019-04", "信息技术", "图书馆106", {"阿达"}}}));
    f(ssys.ModifyBookInfo({trm::rqs::MODIFY_BOOK_INFO, "adm", "123", "553-4-56-784875-2", Book{"553-4-56-784875-2", "oooj-", "2015-04", "数学", "图书馆104", {"莫"}}}));

    std::vector<std::pair<std::string, std::string>> date;
    auto reply_2 = ssys.GetAccountBorrowList({trm::rqs::GET_ACCOUNT_BORROW_LIST, "adm", "123"});
    for (auto &borrow : reply_2.second) {
        std::cout << borrow.borrowLast << " " << borrow.start.currantTime << " " << borrow.end.currantTime << " " << borrow.bookIsbn << " " << borrow.borrower << std::endl;
        date.push_back({ToStr(borrow.start.currantTime), borrow.bookIsbn});
    }

    auto reply_3 = ssys.SearchBook({trm::rqs::SEARCH_BOOK, "计算机", "", "true"}, [](const trm::Book &a, const trm::Book &b) -> bool { return a.bookPublicationDate < b.bookPublicationDate; });
    for (auto &book : reply_3.second) {
        std::cout << book.bookIsbn << " " << book.bookName << " ";
        for (auto &author : book.bookAuthor) {
            std::cout << author << ',';
        }
        std::cout << " " << book.bookPublicationDate << " " << book.bookCatagory << " " << book.storePosition << std::endl;
    }

    f(ssys.ReturnBook({trm::rqs::RETURN_BOOK, "adm", "123", date[0].second, date[0].first}));
    f(ssys.ReturnBook({trm::rqs::RETURN_BOOK, "adm", "123", date[2].second, date[2].first}));
    f(ssys.ReturnBook({trm::rqs::RETURN_BOOK, "adm", "123", date[1].second, date[1].first}));

    auto reply__ = ssys.GetAccountBorrowList({trm::rqs::GET_ACCOUNT_BORROW_LIST, "adm", "123"});
    for (auto& borrow : reply__.second) {
        std::cout << borrow.borrowLast << " " << borrow.start.currantTime << " " << borrow.end.currantTime << " " << borrow.bookIsbn << " " << borrow.borrower << std::endl;
    }


#endif
#ifdef COURSE
    f(ssys.AddCourse({trm::rqs::ADD_COURSE,"adm","123","10086"})); // succ
    f(ssys.AddCourse({trm::rqs::ADD_COURSE,"adm","123","10086"})); // fail course exist
    f(ssys.AddCourse({trm::rqs::ADD_COURSE,"adm","123","12345"})); // fail no match course
    f(ssys.AdmAddCour({trm::rqs::ADM_ADD_COUR,"adm","123","10086"})); // fail course exist
    f(ssys.SearchCourseInformation({trm::rqs::SEARCH_COURSE_INFORMATION,"adm","10086"})); // yes courseinformation
    f(ssys.SearchCourseInformation({trm::rqs::SEARCH_COURSE_INFORMATION,"adm","12345"})); // no no match course
    f(ssys.AdmAddCour({trm::rqs::ADM_ADD_COUR,"adm","123","12345",trm::CourseInformation{"离散数学","李四","A1 203",{"1","2","3","4","5"}}})); // succ
    f(ssys.SearchCourseInformation({trm::rqs::SEARCH_COURSE_INFORMATION,"adm","12345"})); // succ 
    f(ssys.CheckAllCourse({trm::rqs::CHECK_ALL_COURSE,"adm"})); // succ course list
    f(ssys.DeleteCourse({trm::rqs::DELETE_COURSE,"adm","123","10086"})); // succ
    f(ssys.DeleteCourse({trm::rqs::DELETE_COURSE,"adm","123","10086"})); // no match course
    f(ssys.SearchCourseInformation({trm::rqs::SEARCH_COURSE_INFORMATION,"adm","10086"})); // no match course
    f(ssys.AdmDeleteCour({trm::rqs::ADM_DELETE_COUR,"adm","123","12345"})); // succ
    f(ssys.AdmDeleteCour({trm::rqs::ADM_DELETE_COUR,"adm","123","12345"})); // no match course
    f(ssys.AddCourse({trm::rqs::ADD_COURSE,"adm","123","12345"})); // no match course
    f(ssys.DeleteCourse({trm::rqs::DELETE_COURSE,"adm","123","12345"})); // succ
    f(ssys.CheckAllCourse({trm::rqs::CHECK_ALL_COURSE,"adm"})); // no course exist
#endif
#ifdef RESERVE
    f(ssys.RequestReserve({trm::rqs::REQUEST_RESERVE,"10::1::20","15:00","123","321"})); // succ
    f(ssys.RequestReserve({trm::rqs::REQUEST_RESERVE,"10::1::20","15:30","123","321"})); // fail no match reserve
    f(ssys.RequestReserve({trm::rqs::REQUEST_RESERVE,"10::1::20","15:00","123","321"})); // fail already reserved
    f(ssys.AdmAddReserveTime({trm::rqs::ADM_ADD_RESERVE_TIME,"adm","123","10::1::20","15:30","10"}));//succ 
    f(ssys.AdmAddReserveTime({trm::rqs::ADM_ADD_RESERVE_TIME,"adm","123","10::1::20","15:00","10"}));//fail time have set
    f(ssys.RequestReserve({trm::rqs::REQUEST_RESERVE,"10::1::20","15:30","123","321"})); // succ
    f(ssys.CheckTime({trm::rqs::CHECK_TIME,"10::1::20"}));
    f(ssys.CheckReserveTime({trm::rqs::CHECK_RESERVE_TIME,"10::1::20","15:30"})); //yes
    f(ssys.CheckReserveTime({trm::rqs::CHECK_RESERVE_TIME,"10::1::20","16:00"})); //no no match time
    f(ssys.CheckReserveStatus({trm::rqs::CHECK_RESERVE_STATUS,"10::1::20","15:30","123","321"})); //yes
    f(ssys.CheckReserveStatus({trm::rqs::CHECK_RESERVE_STATUS,"10::1::20","16:00","123","321"})); //no no match reserve
    f(ssys.CheckReserveStatusList({trm::rqs::CHECK_RESERVE_STATUS_LIST,"123","321"})); //yes
    f(ssys.CancelReserve({trm::rqs::CANCEL_RESERVE,"10::1::20","15:30","123","321"})); //yes
    f(ssys.CancelReserve({trm::rqs::CANCEL_RESERVE,"10::1::20","15:00","123","321"})); //yes
    f(ssys.CancelReserve({trm::rqs::CANCEL_RESERVE,"10::1::20","16:30","123","321"})); //no no match reserve
    f(ssys.CancelReserve({trm::rqs::CANCEL_RESERVE,"10::1::20","15:30","123","123"})); //reserve accesee denied
    f(ssys.CheckReserveStatusList({trm::rqs::CHECK_RESERVE_STATUS_LIST,"123","321"})); //no no reserve exist
    f(ssys.CheckReserveStatus({trm::rqs::CHECK_RESERVE_STATUS,"10::1::20","15:30","123","321"})); //no no match reserve
    f(ssys.AdmDeleteReserveTime({trm::rqs::ADM_DELETE_RESERVE_TIME,"adm","123","10::1::20","15:30"})); //succ
    f(ssys.AdmDeleteReserveTime({trm::rqs::ADM_DELETE_RESERVE_TIME,"adm","123","10::1::20","15:00"})); //no no match reserve
    f(ssys.AdmAddReserveTime({trm::rqs::ADM_ADD_RESERVE_TIME,"adm","123","10::1::20","15:30","10"}));//succ 
    f(ssys.AdmModifyReserveNumber({trm::rqs::ADM_MODIFY_RESERVE_NUMBER,"adm","123","10::1::20","15:30","0"})); //succ
    f(ssys.AdmModifyReserveNumber({trm::rqs::ADM_MODIFY_RESERVE_NUMBER,"adm","123","10::1::20","16:30","0"})); //fail no match reserve
    f(ssys.CheckReserveTime({trm::rqs::CHECK_RESERVE_TIME,"10::1::20","15:30"})); // no no left reserve 
    f(ssys.CheckReserveStatusList({trm::rqs::CHECK_RESERVE_STATUS_LIST,"123","321"})); //yes
#endif
    while (1) ;

    return 0;
}


