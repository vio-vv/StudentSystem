#include <iostream>
#include "ui.hpp"
#include <string>
#include "student_system.hpp"
#include "transmitter.hpp"

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

    f(ssys.CheckAccount({trm::rqs::CHECK_ACCOUNT, "admin", "123456"}));
    f(ssys.CheckAccount({trm::rqs::CHECK_ACCOUNT, "adm", "123"}));
    f(ssys.CreateAccount({trm::rqs::CREATE_ACCOUNT, Account{"66", "6", {"admin", "teacher"}, {{"name", "张三"}, {"age", "20"}}}}));
    f(ssys.CheckAccount({trm::rqs::CHECK_ACCOUNT, "66", "6"}));
    f(ssys.CheckAccount({trm::rqs::CHECK_ACCOUNT, "66", "66"}));
    f(ssys.DeleteAccount({trm::rqs::DELETE_ACCOUNT, "66"}));

    while (1) ;

    return 0;
}


