#include "transmitter.hpp"
#include <iostream>

int main()
{
    using namespace std;
    for (auto t : trm::Split(trm::Split(trm::Combine({"Hello", "World", "Hello", trm::Combine({"415", "45646"})}))[3])) {
        cout << t << endl;
    }

    return 0;
}