#define SELF ".\\space"

#define REGISTER(ENUM, FUNC)                                               \
    else if (request.content[0] == ENUM) {                                 \
        trm::SendReply(request.sender, request.id, FUNC(request.content)); \
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
    auto log = dat::DataBase(DATA_PATH)["log"];

    std::cout << "Server started." << std::endl;
    sf::Clock interval;
    auto &ssys = SSys::Get();
    while (true) {
        if (interval.getElapsedTime().asMilliseconds() > 1000) {
            interval.restart();
            auto ok_requests = trm::GetRequests(SELF);
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
                assert(request.content.size() > 0); // Abnormal request information size.
                if (request.content[0] == trm::rqs::CHECK_ONLINE) {
                    trm::SendReply(request.sender, request.id, {trm::rpl::YES});
                } 

                /*******************************
                 * @attention EEA 请在此处添加。*
                 * *****************************
                 */
                REGISTER(trm::rqs::CHECK_ACCOUNT_EXISTS, ssys.CheckAccountExist)
                REGISTER(trm::rqs::QUERY_TAG, ssys.QueryTag)
                REGISTER(trm::rqs::CHECK_ACCOUNT, ssys.CheckAccount)
                REGISTER(trm::rqs::CHECK_ACCESS, ssys.CheckAccess)
                REGISTER(trm::rqs::CREATE_ACCOUNT, ssys.CreateAccount)
                REGISTER(trm::rqs::DELETE_ACCOUNT, ssys.DeleteAccount)
                REGISTER(trm::rqs::GRANT_ACCESS, ssys.GrantAccess)
                REGISTER(trm::rqs::REVOKE_ACCESS, ssys.RevokeAccess)
                REGISTER(trm::rqs::REVOKE_ALL_ACCESS, ssys.RevokeAllAccess)
                REGISTER(trm::rqs::ADD_TAG, ssys.AddTag)
                REGISTER(trm::rqs::REMOVE_TAG, ssys.RemoveTag)
                REGISTER(trm::rqs::CLEAR_TAG, ssys.ClearTag)
                REGISTER(trm::rqs::RESET_ACCOUNT_AND_ACCESS, ssys.ResetAccountAndAccess)

                /*******************************
                 * @attention LAB 请在此处添加。*
                 * *****************************
                 */
                REGISTER(trm::rqs::ADD_COURSE, ssys.AddCourse)
                REGISTER(trm::rqs::DELETE_COURSE, ssys.DeleteCourse)
                REGISTER(trm::rqs::ADM_ADD_COUR,ssys.AdmAddCour)
                REGISTER(trm::rqs::ADM_DELETE_COUR,ssys.AdmDeleteCour)
                REGISTER(trm::rqs::CHECK_ALL_COURSE, ssys.CheckAllCourse)
                REGISTER(trm::rqs::SEARCH_COURSE_INFORMATION, ssys.SearchCourseInformation)
                REGISTER(trm::rqs::REQUEST_RESERVE, ssys.RequestReserve)
                REGISTER(trm::rqs::CANCEL_RESERVE, ssys.CancelReserve)
                REGISTER(trm::rqs::CHECK_TIME, ssys.CheckTime)
                REGISTER(trm::rqs::CHECK_RESERVE_TIME, ssys.CheckReserveTime)
                REGISTER(trm::rqs::CHECK_RESERVE_STATUS, ssys.CheckReserveStatus)
                REGISTER(trm::rqs::CHECK_RESERVE_STATUS_LIST, ssys.CheckReserveStatusList)
                REGISTER(trm::rqs::ADM_ADD_RESERVE_TIME, ssys.AdmAddReserveTime)
                REGISTER(trm::rqs::ADM_DELETE_RESERVE_TIME, ssys.AdmDeleteReserveTime)
                REGISTER(trm::rqs::ADM_MODIFY_RESERVE_NUMBER, ssys.AdmModifyReserveNumber)
                /**********************************
                 * @attention VIO_VV 请在此处添加。*
                 * ********************************
                 */
                REGISTER(trm::rqs::BORROW_BOOK, ssys.BorrowBook)
                REGISTER(trm::rqs::RETURN_BOOK, ssys.ReturnBook)
                REGISTER(trm::rqs::MODIFY_BOOK_INFO, ssys.ModifyBookInfo)
                REGISTER(trm::rqs::REMOVE_BOOK, ssys.RemoveBook)
                REGISTER(trm::rqs::RESTORE_BOOK, ssys.RestoreNewBook)
                REGISTER(trm::rqs::SEARCH_BOOK, ssys.SearchBook)
                REGISTER(trm::rqs::GET_ACCOUNT_BORROW_LIST, ssys.GetAccountBorrowList)
                REGISTER(trm::rqs::SEND_RETURN_REMINDER, ssys.SendReturnReminder)
                // REGISTER(trm::rqs::???, ssys.???)

                else {
                    assert(false); // Unknown request.
                    std::cout << "Unknown request: " << request.content[0] << std::endl;
                }
            }
        }
    }
    return 0;
}

