#include <iostream>
#include "ui.hpp"
#include <string>
#include "student_system.hpp"
#include "transmitter.hpp"
#include "data_base.hpp"

#define MAIL

using namespace std;
using namespace trm;

int main()
{
    auto &ssys = SSys::Get();

    auto f = [](const Information &info) {
        for (const auto &each : info) {
            cout << each << endl;
        }
        cout << endl;
    };
    
#ifdef ACC_ACC

    f(ssys.CheckAccountExist({rqs::CHECK_ACCOUNT_EXISTS, "admin"}));
    f(ssys.CheckAccountExist({rqs::CHECK_ACCOUNT_EXISTS, "adm"}));

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

#else
#ifdef MAIL

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

#endif
#endif

    while (1) ;

    return 0;
}


