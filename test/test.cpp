#include <iostream>
#include "ui.hpp"

int main()
{
    std::vector v{1, 2, 3};

    v.erase(v.begin() + 1);
    std::cout << v.size() << std::endl;

    return 0;
}


