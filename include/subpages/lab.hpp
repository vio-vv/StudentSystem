#ifndef __LAB_HPP__
#define __LAB_HPP__

#include "page_header.hpp"

namespace lab{
using namespace clpg;

class EnterCourse : public PageBase {
private:
    ;
public:
    void Load(ui::Screen *screen) noexcept;
    void Logic(ui::Screen *screen) noexcept;
    void Ready(ui::Screen *screen) noexcept;
};
class EnterReserve : public PageBase {
    ;
private:
    void Load(ui::Screen *screen) noexcept;
    void Logic(ui::Screen *screen) noexcept;
    void Ready(ui::Screen *screen) noexcept;
};

}
    
#endif
