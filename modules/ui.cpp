#include "ui.hpp"

void ui::Control::SetCenter(Direction directrion, int percentage) noexcept
{
    center[directrion] = percentage;
    if (parent) parent->Update();
}

void ui::Control::SetAnchor(Direction directrion, int percentage) noexcept
{
    anchor[directrion] = percentage;
    if (parent) parent->Update();
}

void ui::Control::SetPotistion(Direction directrion, int absolute) noexcept
{
    position[directrion] = absolute;
    if (parent) parent->Update();
}

void ui::Control::SetMinSize(Direction directrion, unsigned int absolute) noexcept
{
    minSize[directrion] = absolute;
    if (parent) parent->Update();
}

void ui::Control::SetSizeWrap(Direction directrion, bool flag) noexcept
{
    sizeWrap[directrion] = flag;
    if (parent) parent->Update();
}

void ui::Control::SetSizeValueType(Direction direction, ValueType valueType) noexcept
{
    sizeValueType[direction] = valueType;
    if (parent) parent->Update();
}

void ui::Control::SetSize(Direction directrion, unsigned int value) noexcept
{
    size[directrion] = value;
    if (parent) parent->Update();
}

void ui::Control::SetParent(Container *container) noexcept
{
    parent = container;
}

void ui::Control::SetGlobalPosition(Direction directrion, int absolute) noexcept
{
    globalPosition[directrion] = absolute;
    Update();
}

void ui::Control::SetGlobalSize(Direction directrion, unsigned int absolute) noexcept
{
    globalSize[directrion] = absolute;
    Update();
}

ui::Control::~Control() noexcept
{
    if (parent) parent->Remove(this);
}

void ui::Container::Add(Control *control) noexcept
{
    children.push_back(control);
    Update();
}

void ui::Container::Remove(Control *control) noexcept
{
    children.remove(control);
    Update();
}

void ui::Container::FreeAll() noexcept
{
    auto tmp = children;
    for (auto each : tmp) {
        delete each;
    }
}

void ui::Container::Process(const sf::Event &event) noexcept
{
    for (auto child : children) {
        child->Process(event);
    }
}

void ui::Container::Draw(const Screen &screen) noexcept
{
    for (auto child : children) {
        child->Draw(screen);
    }
}

ui::Container::~Container() noexcept
{
    for (auto child : children) {
        delete child;
    }
}

void ui::Screen::SetRange(unsigned int width, unsigned int height) noexcept
{
    screen.setSize({width, height});
}

void ui::Screen::SetCaption(const std::wstring &caption) noexcept
{
    screen.setTitle(caption);
}

bool ui::Screen::IsOpen() const noexcept
{
    return screen.isOpen();
}

void ui::Screen::Tick() noexcept
{
    if (IsOpen()) {
        sf::Event event;
        screen.pollEvent(event);
        if (event.type == sf::Event::Closed) {
            screen.close();
        } else if (event.type == sf::Event::Resized) {
            SetGlobalSize(Direction::HORIZONTAL, event.size.width);
            SetGlobalSize(Direction::VERTICAL, event.size.height);
        } else {
            Process(event);
        }
    }
}

void ui::Flat::Update() noexcept
{
    for (auto direction : {Direction::HORIZONTAL, Direction::VERTICAL}) {
        unsigned int myMinSize = 0;
        for (auto child : children) {
            UpdateByDefault(direction, child);
            myMinSize = std::max(myMinSize, child->GetGlobalSize(direction));
        }
        SetMinSize(direction, myMinSize);
    }
}

void ui::Container::UpdateByDefault(Direction direction, Control *child) noexcept
{
    UpdateSizeByDefault(direction, child);
    UpdatePositionByDefault(direction, child);
}

void ui::Container::UpdateSizeByDefault(Direction direction, Control *child) noexcept
{
    unsigned int tmpSize;
    switch (sizeValueType) {
        case ValueType::ABSOLUTE:
            if (wrap) tmpSize =  minSize;
            else      tmpSize = size;
            break;
        case ValueType::PERCENTAGE:
            tmpSize = size * parentSize / 100;
            break;
    }
    return std::max(minSize, tmpSize);
    child->SetGlobalSize(direction, ObtainDefaultGlobalSize(direction, child, globalSize[direction]));
}

void ui::Container::UpdatePositionByDefault(Direction direction, Control *child) noexcept
{
    int thisPosition = parentPosition;
    thisPosition -= center * thisSize / 100;
    thisPosition += anchor * parentSize / 100;
    thisPosition += position;
    return thisPosition;
    child->SetGlobalPosition(direction, ObtainDefaultGlobalPosition(direction, child, globalSize[direction], globalPosition[direction]));
}

unsigned int ui::Container::ObtainDefaultGlobalSize(Direction direction, const Control *child, unsigned int parentSize) noexcept
{
    return ObtainDefaultGlobalSize(child->GetSizeValueType(direction), child->GetSizeWrap(direction), child->GetSize(direction), child->GetMinSize(direction), parentSize);
}

int ui::Container::ObtainDefaultGlobalPosition(Direction direction, const Control *child, unsigned int parentSize, int parentPosition) noexcept
{
    return ObtainDefaultGlobalPosition(child->GetCenter(direction), child->GetAnchor(direction), child->GetPosition(direction), child->GetGlobalSize(direction), parentSize, parentPosition);
}

unsigned int ui::Container::ObtainDefaultGlobalSize(ValueType sizeValueType, bool wrap, unsigned int size, unsigned int minSize, unsigned int parentSize) noexcept
{
}

int ui::Container::ObtainDefaultGlobalPosition(int center, int anchor, int position, unsigned int thisSize, unsigned int parentSize, int parentPosition) noexcept
{
}

void ui::Center::Update() noexcept
{
    for (auto direction : {Direction::HORIZONTAL, Direction::VERTICAL}) {
        unsigned int myMinSize = 0;
        for (auto child : children) {
            UpdateSizeByDefault(direction, child);
            child->SetGlobalPosition(direction, globalPosition[direction] + (globalSize[direction] - child->GetGlobalSize(direction)) / 2);
            myMinSize = std::max(myMinSize, child->GetGlobalSize(direction));
        }
        SetMinSize(direction, myMinSize);
    }
}

void ui::LinearBox::SetGap(int absolute) noexcept
{
    gap = absolute;
    Update();
}

void ui::Vertical::Update() noexcept
{
    unsigned int horizontalMinSize = 0;
    for (auto child : children) {
        UpdateByDefault(Direction::HORIZONTAL, child);
        horizontalMinSize = std::max(horizontalMinSize, child->GetGlobalSize(Direction::HORIZONTAL));
    }
    SetMinSize(Direction::HORIZONTAL, horizontalMinSize);

    unsigned int verticalMinSize = 0;
    unsigned int sizeOccupied    = 0;
    unsigned int ratioSum        = 0;
    for (auto child : children) {
        switch (child->GetSizeValueType(Direction::VERTICAL)) {
            case ValueType::ABSOLUTE:
                UpdateSizeByDefault(Direction::VERTICAL, child);
                verticalMinSize += child->GetGlobalSize(Direction::VERTICAL);
                sizeOccupied    += child->GetGlobalSize(Direction::VERTICAL);
                break;
            case ValueType::PERCENTAGE:
                verticalMinSize += child->GetMinSize(Direction::VERTICAL);
                ratioSum        += child->GetSize(Direction::VERTICAL);
                break;
        }
    }
    SetMinSize(Direction::VERTICAL, verticalMinSize);
    unsigned int sizeLeft    = globalSize[Direction::VERTICAL] - sizeOccupied;
    unsigned int tmpPosition = 0;
    for (auto child : children) {
        if (child->GetSizeValueType(Direction::VERTICAL) == ValueType::PERCENTAGE) {
            child->SetGlobalSize(Direction::VERTICAL, child->GetSize(Direction::VERTICAL) * sizeLeft / ratioSum);
        }
        child->SetGlobalPosition(Direction::VERTICAL, globalPosition[Direction::VERTICAL] + tmpPosition);
        tmpPosition += child->GetGlobalSize(Direction::VERTICAL);
    }
}
