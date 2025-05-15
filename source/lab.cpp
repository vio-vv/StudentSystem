#include "client_pages.hpp"

void lab::EnterCourse::Load(ui::Screen *screen) noexcept
{
   auto mar = new ui::Margin;{
   screen->Add(mar);
   mar->SetPreset(ui::Control::Preset::FILL_FROM_CENTER); 
   mar->SetMargin(80, 80, 200, 200);}
   auto box = new ui::VerticalBox();
   box->Add(mar);
   auto box = new ui::VerticalBox();
   screen->Add(box);
}
void lab::EnterCourse::Logic(ui::Screen *screen) noexcept
{
    ;
}

void lab::EnterCourse::Ready(ui::Screen *screen) noexcept
{
    ;
}

void lab::EnterReserve::Load(ui::Screen *screen) noexcept
{
    ;
}

void lab::EnterReserve::Logic(ui::Screen *screen) noexcept
{
    ;
}

void lab::EnterReserve::Ready(ui::Screen *screen) noexcept
{
    ;
}
