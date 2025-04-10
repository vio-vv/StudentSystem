#include <iostream>
#include "ui.hpp"
#include <string>
#include "student_system.hpp"
#include "transmitter.hpp"

int main()
{
    auto &ssys = SSys::Get();

    auto reply = ssys.CheckAccount(trm::Infomation{trm::rqs::CHECK_ACCOUNT, "adm", "123"});

    for (const auto &each : reply) {
        std::cout << each << std::endl;
    }
 
    return 0;
}


