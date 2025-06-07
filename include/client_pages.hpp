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
    ui::InputBox *link;
    ui::InputBox *self;
    ui::InputBox *selfAsSender;
    const std::string LINK;
    const std::string SELF;
    const std::string SELF_AS_SENDER;
protected:
    void Load(ui::Screen *screen) noexcept override;
    void Logic(ui::Screen *screen) noexcept override;
    void Ready(ui::Screen *screen) noexcept override;
public:
    EnterSystem(const std::string &link, const std::string &self, const std::string &selfAsSender) noexcept : 
        LINK(link), SELF(self), SELF_AS_SENDER(selfAsSender) {}
};

}

#endif
