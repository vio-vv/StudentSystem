#define _SELF_ ".\\space"

#define _REGISTER_(ENUM, FUNC)                                                         \
    else if (request.content[0] == ENUM) {                                             \
        std::cout << trm::TimestampToString(ToStr(trm::GetTimestamp())) << "GET:\n\t"; \
        for (auto each : request.content) {                                            \
            std::cout << each << ", ";                                                 \
        }                                                                              \
        std::cout << std::endl;                                                        \
        auto ____ = FUNC(request.content);                                             \
        trm::SendReply(request.sender, request.id, ____);                              \
        std::cout << "SEND:\n\t";                                                      \
        for (auto each : ____) {                                                       \
            std::cout << each << ", ";                                                 \
        }                                                                              \
        std::cout << std::endl;                                                        \
    }

/**
 * @brief 服务端主程序。
 * 
 * @par REQUIRES
 * NONE
 * 
 * @par PROVIDES
 * - @fn main 主程序入口
 */

#include <iostream>
#include "SFML/System.hpp"
#include "student_system.hpp"

int main() noexcept
{
    freopen("log.txt", "at", stdout);
    if (!trm::Initialize(_SELF_)) {
        assert(false); // Unexpected failure.
        std::cout << "Init failed." << std::endl;
    }
    std::cout << "Server started." << std::endl;
    sf::Clock interval;
    auto &ssys = SSys::Get();
    while (true) {
        if (interval.getElapsedTime().asMilliseconds() > 1000) {
            interval.restart();
            auto ok_requests = trm::GetRequests(_SELF_);
            if (!ok_requests.first) {
                std::cout << "Get requests failed." << std::endl;
                sf::Clock wait;
                while (true) {
                    if (wait.getElapsedTime().asMilliseconds() > 10000) {
                        break;
                    }
                }
                continue;
            }
            for (const auto &request : ok_requests.second) {
                assert(request.content.size() > 0); // Unexpected information size.
                if (request.content[0] == trm::rqs::CHECK_ONLINE) {
                    std::cout << trm::TimestampToString(ToStr(trm::GetTimestamp())) << " GET:\n\t";
                    for (auto each : request.content) {
                        std::cout << each << ", ";
                    }
                    std::cout << std::endl;
                    trm::SendReply(request.sender, request.id, {trm::rpl::YES});
                    std::cout << "SEND:\n\t" << trm::rpl::YES << std::endl;
                } 

                /*******************************
                 * @attention EEA 请在此处添加。*
                 * *****************************
                 */
                _REGISTER_(trm::rqs::CHECK_ACCOUNT_EXISTS, ssys.CheckAccountExist)
                _REGISTER_(trm::rqs::QUERY_TAG, ssys.QueryTag)
                _REGISTER_(trm::rqs::CHECK_ACCOUNT, ssys.CheckAccount)
                _REGISTER_(trm::rqs::CHECK_ACCESS, ssys.CheckAccess)
                _REGISTER_(trm::rqs::CREATE_ACCOUNT, ssys.CreateAccount)
                _REGISTER_(trm::rqs::DELETE_ACCOUNT, ssys.DeleteAccount)
                _REGISTER_(trm::rqs::GRANT_ACCESS, ssys.GrantAccess)
                _REGISTER_(trm::rqs::REVOKE_ACCESS, ssys.RevokeAccess)
                _REGISTER_(trm::rqs::REVOKE_ALL_ACCESS, ssys.RevokeAllAccess)
                _REGISTER_(trm::rqs::ADD_TAG, ssys.AddTag)
                _REGISTER_(trm::rqs::REMOVE_TAG, ssys.RemoveTag)
                _REGISTER_(trm::rqs::CLEAR_TAG, ssys.ClearTag)
                _REGISTER_(trm::rqs::RESET_ACCOUNT_AND_ACCESS, ssys.ResetAccountAndAccess)
                _REGISTER_(trm::rqs::LIST_ACCOUNT, ssys.ListAccount)
                _REGISTER_(trm::rqs::GET_ACCOUNT_DETAIL, ssys.GetAccountDetail)

                _REGISTER_(trm::rqs::SEND_MESSAGE, ssys.SendMessage)
                _REGISTER_(trm::rqs::GET_MESSAGE_NUMBER, ssys.GetMessageNumber)
                _REGISTER_(trm::rqs::GET_MESSAGE_PROFILE, ssys.GetMessageProfile)
                _REGISTER_(trm::rqs::GET_MESSAGE, ssys.GetMessage)
                _REGISTER_(trm::rqs::MARK_AS_READ, ssys.MarkAsRead)
                _REGISTER_(trm::rqs::MARK_AS_UNREAD, ssys.MarkAsUnread)
                _REGISTER_(trm::rqs::GET_UNREAD_MESSAGE_NUMBER, ssys.GetUnreadMessageNumber)
                _REGISTER_(trm::rqs::DELETE_MESSAGE, ssys.DeleteMessage)
                _REGISTER_(trm::rqs::CLEAR_MESSAGE, ssys.ClearMessage)
                _REGISTER_(trm::rqs::DELETE_MESSAGE_OF_OTHERS, ssys.DeleteMessageOfOthers)
                _REGISTER_(trm::rqs::CLEAR_MESSAGE_OF_OTHERS, ssys.ClearMessageOfOthers)
                _REGISTER_(trm::rqs::RESET_MAIL_SYSTEM, ssys.ResetMailSystem)

                /*******************************
                 * @attention LAB 请在此处添加。*
                 * *****************************
                 */
                _REGISTER_(trm::rqs::ADD_COURSE, ssys.AddCourse)
                _REGISTER_(trm::rqs::DELETE_COURSE, ssys.DeleteCourse)
                _REGISTER_(trm::rqs::ADM_ADD_COUR,ssys.AdmAddCour)
                _REGISTER_(trm::rqs::ADM_DELETE_COUR,ssys.AdmDeleteCour)
                _REGISTER_(trm::rqs::CHECK_ALL_COURSE, ssys.CheckAllCourse)
                _REGISTER_(trm::rqs::SEARCH_COURSE_INFORMATION, ssys.SearchCourseInformation)
                _REGISTER_(trm::rqs::REQUEST_RESERVE, ssys.RequestReserve)
                _REGISTER_(trm::rqs::CANCEL_RESERVE, ssys.CancelReserve)
                _REGISTER_(trm::rqs::CHECK_TIME, ssys.CheckTime)
                _REGISTER_(trm::rqs::CHECK_RESERVE_TIME, ssys.CheckReserveTime)
                _REGISTER_(trm::rqs::CHECK_RESERVE_STATUS, ssys.CheckReserveStatus)
                _REGISTER_(trm::rqs::CHECK_RESERVE_STATUS_LIST, ssys.CheckReserveStatusList)
                _REGISTER_(trm::rqs::ADM_ADD_RESERVE_TIME, ssys.AdmAddReserveTime)
                _REGISTER_(trm::rqs::ADM_DELETE_RESERVE_TIME, ssys.AdmDeleteReserveTime)
                _REGISTER_(trm::rqs::ADM_MODIFY_RESERVE_NUMBER, ssys.AdmModifyReserveNumber)
                _REGISTER_(trm::rqs::ADM_MODIFY_RESERVE_STATUS, ssys.AdmModifyReserveStatus)
                _REGISTER_(trm::rqs::ADM_SEARCH_RESERVE, ssys.AdmSearchReserve)
                /**********************************
                 * @attention VIO_VV 请在此处添加。*
                 * ********************************
                 */
                _REGISTER_(trm::rqs::BORROW_BOOK, ssys.BorrowBook)
                _REGISTER_(trm::rqs::RETURN_BOOK, ssys.ReturnBook)
                _REGISTER_(trm::rqs::MODIFY_BOOK_INFO, ssys.ModifyBookInfo)
                _REGISTER_(trm::rqs::REMOVE_BOOK, ssys.RemoveBook)
                _REGISTER_(trm::rqs::RESTORE_BOOK, ssys.RestoreNewBook)
                _REGISTER_(trm::rqs::SEARCH_BOOK, ssys.SearchBook)
                _REGISTER_(trm::rqs::GET_ACCOUNT_BORROW_LIST, ssys.GetAccountBorrowList)
                _REGISTER_(trm::rqs::SEND_RETURN_REMINDER, ssys.SendReturnReminder)

                _REGISTER_(trm::rqs::PUBLISH_NOLIFY, ssys.PublishNolify)
                _REGISTER_(trm::rqs::GET_NOLIFY, ssys.GetNolifyContent)
                _REGISTER_(trm::rqs::GET_NOLIFY_LIST, ssys.GetNolifyTitle)
                _REGISTER_(trm::rqs::DELETE_NOLIFY, ssys.DeleteNolify)
                _REGISTER_(trm::rqs::GET_NOLIFY_NUMBER, ssys.GetNolifyNumber)

                // _REGISTER_(trm::rqs::???, ssys.???)

                else {
                    assert(false); // Deny.
                    std::cout << "Unknown request: " << request.content[0] << std::endl;
                }
            }
        }
    }
    return 0;
}

