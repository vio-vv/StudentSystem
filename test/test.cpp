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

    auto f = [](const Infomation &info) {
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

    f(ssys.SendMessage({rqs::SEND_MESSAGE, "adm", "12", "1", "hello"}));
    f(ssys.SendMessage({rqs::SEND_MESSAGE, "adm", "123", "1", "hello"}));
    f(ssys.SendMessage({rqs::SEND_MESSAGE, "adm", "123", "2", "hello"}));
    f(ssys.GetMessageNumber({rqs::GET_MESSAGE_NUMBER, "adm"}));
    f(ssys.GetMessageNumber({rqs::GET_MESSAGE_NUMBER, "admin"}));
    f(ssys.GetMessageNumber({rqs::GET_MESSAGE_NUMBER, "1"}));

#endif
#endif

    while (1) ;

    return 0;
}


