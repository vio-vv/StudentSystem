#ifndef __EEA_HPP__
#define __EEA_HPP__

#include "page_header.hpp"

namespace clpg{

ID Retry(ui::Screen &screen) noexcept;
ID Login(ui::Screen &screen) noexcept;
ID Forget(ui::Screen &screen) noexcept;
ID MainPage(ui::Screen &screen) noexcept;

ID EnterAccManage(ui::Screen &screen) noexcept;

ID EnterCanteen(ui::Screen &screen) noexcept;
ID EnterMailSystem(ui::Screen &screen) noexcept;

}

#endif
