#ifndef __VIO_VV_HPP__
#define __VIO_VV_HPP__

#include "page_header.hpp"

namespace vio{
using namespace clpg;

class EnterLibrary : public PageBase {
private:
    ;
protected:
    void Load(ui::Screen *screen) noexcept;
    void Logic(ui::Screen *screen) noexcept;
    void Ready(ui::Screen *screen) noexcept;
};
class EnterNolify : public PageBase {
private:
    ;
protected:
    void Load(ui::Screen *screen) noexcept;
    void Logic(ui::Screen *screen) noexcept;
    void Ready(ui::Screen *screen) noexcept;
};

}
        
#endif
