#include "client_pages.hpp"

clpg::ID clpg::EnterLibrary(ui::Screen &screen) noexcept
{
    ;

    while (screen.IsOpen()) {
        screen.Tick();
    }
    return ID::BREAK;
}

clpg::ID clpg::EnterNolify(ui::Screen &screen) noexcept
{
    ;

    while (screen.IsOpen()) {
        screen.Tick();
    }
    return ID::BREAK;
}
