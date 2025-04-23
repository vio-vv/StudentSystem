#include <iostream>
#include "ui.hpp"
#include <string>
#include "student_system.hpp"
#include "transmitter.hpp"
#include "data_base.hpp"

#define EEA

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

    f(ssys.ResetAccountAndAccess({rqs::RESET_ACCOUNT_AND_ACCESS, "adm", "123"}));

#endif

    while (1) ;

    return 0;
}


