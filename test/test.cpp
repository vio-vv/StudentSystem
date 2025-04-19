#include <iostream>
#include "ui.hpp"
#include <string>
#include "student_system.hpp"
#include "transmitter.hpp"

using namespace std;
using namespace trm;

int main()
{
    file::DataBase base(".\\data");
    base.Cut();

    base.Count();

    return 0;

    auto &ssys = SSys::Get();

    auto f = [](const Infomation &info) {
        for (const auto &each : info) {
            cout << each << endl;
        }
        cout << endl;
    };
    
    f(ssys.CreateAccount({trm::rqs::CREATE_ACCOUNT, "adm", "123", Account{"1", "1", {trm::Access::ADM}, {{"name", "张三"}, {"age", "20"}}}}));
    f(ssys.GetMessageNumber({trm::rqs::GET_MESSAGE_NUMBER, "1"}));
    f(ssys.SendMessage({trm::rqs::SEND_MESSAGE, "adm", "123", "1", "hello"}));
    f(ssys.GetMessageNumber({trm::rqs::GET_MESSAGE_NUMBER, "1"}));
    f(ssys.SendMessage({trm::rqs::SEND_MESSAGE, "1", "1", "adm", "world"}));

    while (1) ;

    return 0;
}


