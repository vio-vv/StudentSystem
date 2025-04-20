#include <iostream>
#include "ui.hpp"
#include <string>
#include "student_system.hpp"
#include "transmitter.hpp"
#include "data_base.hpp"

using namespace std;
using namespace trm;

int main()
{
    auto base = dat::DataBase(DATA_PATH);

    auto lis = base["list"];

    lis.Push("456");
    lis.Push("454654");
    lis.Push(Account{"1", "1", {trm::Access::ADM}, {{"name", "张三"}, {"age", "20"}}});

    for (auto [i, con] : lis) {
        cout << i << " " << (string) con << endl;
    }

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


