#include <iostream>
#include "ui.hpp"

int main()
{
    ui::Screen screen(800, 600, "Test");
    
    

    while (screen.IsOpen()) {
        screen.Tick();
    }

    return 0;
}


