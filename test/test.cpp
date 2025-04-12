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

    auto f = [](const std::vector<Infomation> &series) {
        for (const auto &info : series) {
            for (const auto &each : info) {
                cout << each << endl;
            }
            cout << endl;
        }
    };

    f({
        ssys.CheckAccount({trm::rqs::CHECK_ACCOUNT, "admin", "123456"}), 
        ssys.CheckAccount({trm::rqs::CHECK_ACCOUNT, "adm", "123"}), 
        ssys.CreateAccount({trm::rqs::CREATE_ACCOUNT, Account{"6", "6"}}), 
        ssys.CheckAccount({trm::rqs::CHECK_ACCOUNT, "6", "6"}), 
        ssys.CheckAccount({trm::rqs::CHECK_ACCOUNT, "6", "666"}), 
    });

    while (1) ;

    return 0;
}


