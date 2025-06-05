#ifndef __CLIENTS_HPP__
#define __CLIENTS_HPP__

/**
 * @brief 客户端页面。
 * @namespace clpg
 * 
 * @par REQUIRES
 * - @ref ui.hpp
 * - @ref transmitter.hpp
 * 
 * @par PROVIDES
 * 各种客户端页面的实现。
 */

#include "subpages/eea.hpp"
#include "subpages/vio_vv.hpp"
#include "subpages/lab.hpp"

namespace clpg {

class EnterSystem : public PageBase {
private:
    ui::Button *btn;
protected:
    void Load(ui::Screen *screen) noexcept override;
    void Logic(ui::Screen *screen) noexcept override;
    void Ready(ui::Screen *screen) noexcept override;
};

}

#endif
