#include "ui.hpp"

using namespace ui;

int main()
{
    ui::Screen screen(1500, 1000, L"调试页面");

    auto label = new Label;
    screen.Add(label);
    label->SetContent("Hello, world!"); // DEBUG YOUR CODE HERE LIKE THIS

    while (screen.IsOpen()) {
        screen.Tick();
    }
    return 0;
}


