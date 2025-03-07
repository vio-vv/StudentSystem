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

void ui::Control::SetPosition(Direction directrion, int absolute) noexcept
{
    position[directrion] = absolute;
    if (parent) parent->Update();
}

void ui::Control::AddTo(Container *container) noexcept
{
    container->Add(this);
}

void ui::Control::SetPreset(Direction direction, Preset preset) noexcept
{
    switch (preset) {
        case Preset::WRAP_AT_FRONT:
        case Preset::WRAP_AT_END:
        case Preset::WRAP_AT_CENTER:
            SetSizeValueType(direction, ValueType::ABSOLUTE);
            SetSizeWrap(direction, true);
            break;
        case Preset::FILL_FROM_FRONT:
        case Preset::FILL_FROM_END:
        case Preset::FILL_FROM_CENTER:
            SetSizeValueType(direction, ValueType::PERCENTAGE);
            SetSize(direction, 100);
            break;
    }

    switch (preset) {
        case Preset::PLACR_AT_FRONT:
        case Preset::WRAP_AT_FRONT:
        case Preset::FILL_FROM_FRONT:
            SetCenter(direction, 0);
            SetAnchor(direction, 0);
            break;
        case Preset::PLACR_AT_END:
        case Preset::WRAP_AT_END:
        case Preset::FILL_FROM_END:
            SetCenter(direction, 100);
            SetAnchor(direction, 100);
            break;
        case Preset::PLACR_AT_CENTER:
        case Preset::WRAP_AT_CENTER:
        case Preset::FILL_FROM_CENTER:
            SetCenter(direction, 50);
            SetAnchor(direction, 50);
            break;
    }
    SetPosition(direction, 0);
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
    Update(false);
}

void ui::Control::SetGlobalSize(Direction directrion, unsigned int absolute) noexcept
{
    globalSize[directrion] = absolute;
    Update(false);
}

ui::Control::~Control() noexcept
{
    if (parent) parent->Remove(this);
}

void ui::Container::Add(Control *control) noexcept
{
    children.push_back(control);
    control->SetParent(this);
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

void ui::Container::Draw(sf::RenderWindow &screen) noexcept
{
    for (auto child : children) {
        child->Draw(screen);
    }

    DRAW_DEBUG_RECT;
}

ui::Container::~Container() noexcept
{
    FreeAll();
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
            sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
            screen.setView(sf::View(visibleArea));
        } else {
            Process(event);
        }
        screen.clear();
        Draw(screen);
        screen.display();
    }
}

void ui::Flat::Update(bool resetMinSize) noexcept
{
    for (auto direction : {Direction::HORIZONTAL, Direction::VERTICAL}) {
        for (auto child : children) {
            UpdateByDefault(direction, child);
        }
    }
}

void ui::Container::UpdateByDefault(Direction direction, Control *child) noexcept
{
    UpdateSizeByDefault(direction, child);
    UpdatePositionByDefault(direction, child);
}

void ui::Container::UpdateSizeByDefault(Direction direction, Control *child) noexcept
{
    child->SetGlobalSize(direction, ObtainDefaultGlobalSize(direction, child, globalSize[direction]));
}

void ui::Container::UpdatePositionByDefault(Direction direction, Control *child) noexcept
{
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
    unsigned int tmpSize;
    switch (sizeValueType) {
        case ValueType::ABSOLUTE:
            if (wrap) tmpSize = minSize;
            else      tmpSize = size;
            break;
        case ValueType::PERCENTAGE:
            tmpSize = size * parentSize / 100;
            break;
    }
    return std::max(minSize, tmpSize);
}

int ui::Container::ObtainDefaultGlobalPosition(int center, int anchor, int position, unsigned int thisSize, unsigned int parentSize, int parentPosition) noexcept
{
    int thisPosition = parentPosition;
    thisPosition -= center * thisSize / 100;
    thisPosition += anchor * parentSize / 100;
    thisPosition += position;
    return thisPosition;
}

void ui::Center::Update(bool resetMinSize) noexcept
{
    for (auto direction : {Direction::HORIZONTAL, Direction::VERTICAL}) {
        unsigned int myMinSize = 0;
        for (auto child : children) {
            UpdateSizeByDefault(direction, child);
            child->SetGlobalPosition(direction, globalPosition[direction] + (globalSize[direction] - child->GetGlobalSize(direction)) / 2);
            myMinSize = std::max(myMinSize, child->GetGlobalSize(direction));
        }
        if (resetMinSize) SetMinSize(direction, myMinSize);
    }
}

void ui::LinearBox::SetGap(int absolute) noexcept
{
    gap = absolute;
    Update();
}

void ui::LinearBox::UpdateLinear(Direction direction, bool resetMinSize) noexcept
{
    Direction another;
    switch (direction) {
        case Direction::HORIZONTAL:
            another = Direction::VERTICAL;
            break;
        case Direction::VERTICAL:
            another = Direction::HORIZONTAL;
            break;
    }

    unsigned int anotherMinSize = 0;
    for (auto child : children) {
        UpdateByDefault(another, child);
        anotherMinSize = std::max(anotherMinSize, child->GetGlobalSize(another));
    }
    if (resetMinSize) SetMinSize(another, anotherMinSize);

    unsigned int directionMinSize = 0;
    unsigned int sizeOccupied     = 0;
    unsigned int ratioSum         = 0;
    for (auto child : children) {
        switch (child->GetSizeValueType(direction)) {
            case ValueType::ABSOLUTE:
                UpdateSizeByDefault(direction, child);
                directionMinSize += child->GetGlobalSize(direction);
                sizeOccupied     += child->GetGlobalSize(direction);
                break;
            case ValueType::PERCENTAGE:
                directionMinSize += child->GetMinSize(direction);
                ratioSum         += child->GetSize(direction);
                break;
        }
    }
    if (resetMinSize) SetMinSize(direction, directionMinSize + std::max(0ull, children.size() - 1) * gap);
    unsigned int sizeLeft    = globalSize[direction] - std::max(0ull, children.size() - 1) * gap - sizeOccupied;
    unsigned int tmpPosition = 0;
    for (auto child : children) {
        if (child->GetSizeValueType(direction) == ValueType::PERCENTAGE) {
            child->SetGlobalSize(direction, child->GetSize(direction) * sizeLeft / ratioSum);
        }
        child->SetGlobalPosition(direction, globalPosition[direction] + tmpPosition);
        tmpPosition += child->GetGlobalSize(direction) + gap;
    }
}

void ui::Horizontal::Update(bool resetMinSize) noexcept
{
    UpdateLinear(Direction::HORIZONTAL, resetMinSize);
}

void ui::Vertical::Update(bool resetMinSize) noexcept
{
    UpdateLinear(Direction::VERTICAL, resetMinSize);
}

const std::string ui::Label::FONT_FILE_PATH = "../assets/simfang.ttf";

void ui::Label::SetContent(const std::wstring &newContent) noexcept
{
    content = newContent;
    Update();
}

void ui::Label::SetFont(const std::string &fontFile) noexcept
{
    if (!font.loadFromFile(fontFile)) {
        error = true;
    }
    Update();
}

void ui::Label::Update(bool resetMinSize) noexcept
{
    text.setString(content);
    text.setCharacterSize(fontSize);
    text.setFont(font);
    text.setPosition({(float)globalPosition[Direction::HORIZONTAL], (float)globalPosition[Direction::VERTICAL]});
    if (resetMinSize) {
        SetMinSize(Direction::HORIZONTAL, text.getGlobalBounds().getSize().x + REVISION_X);
        SetMinSize(Direction::VERTICAL, text.getGlobalBounds().getSize().y + REVISION_Y);
    }
}

void ui::Label::SetFontSize(unsigned int size) noexcept
{
    fontSize = size;
    Update();
}

void ui::Label::Draw(sf::RenderWindow &screen) noexcept
{
    if (!error) {
        screen.draw(text);
    }

    DRAW_DEBUG_RECT;
}

void ui::Button::SetCaption(const std::wstring &caption) noexcept
{
    label->SetContent(caption);
    Update();
}

void ui::Button::SetFontSize(unsigned int size) noexcept
{
    label->SetFontSize(size);
    Update();
}

void ui::Button::SetFont(const std::string &fontFile) noexcept
{
    label->SetFont(fontFile);
    Update();
}

void ui::Button::SetName(const std::wstring &newName) noexcept
{
    name = newName;
}

void ui::Button::SetEnterCallback(Callback function) noexcept
{
    enterCallback = function;
}

void ui::Button::SetLeaveCallback(Callback function) noexcept
{
    leaveCallback = function;
}

void ui::Button::SetPressDownCallback(Callback function) noexcept
{
    pressDownCallback = function;
}

void ui::Button::SetPressUpCallback(Callback function) noexcept
{
    pressUpCallback = function;
}

void ui::Button::SetClickCallback(Callback function) noexcept
{
    clickCallback = function;
}

void ui::Button::Update(bool resetMinSize) noexcept
{
    layer.SetGlobalSize(Direction::HORIZONTAL, globalSize[Direction::HORIZONTAL]);
    layer.SetGlobalSize(Direction::VERTICAL, globalSize[Direction::VERTICAL]);
    layer.SetGlobalPosition(Direction::HORIZONTAL, globalPosition[Direction::HORIZONTAL]);
    layer.SetGlobalPosition(Direction::VERTICAL, globalPosition[Direction::VERTICAL]);
    if (resetMinSize) {
        SetMinSize(Direction::HORIZONTAL, label->GetMinSize(Direction::HORIZONTAL));
        SetMinSize(Direction::VERTICAL, label->GetMinSize(Direction::VERTICAL));
    }
}

bool ui::Control::IsInside(int x, int y) const noexcept
{
    auto x0 = globalPosition[Direction::HORIZONTAL];
    auto xx = x0 + globalSize[Direction::HORIZONTAL];
    auto y0 = globalPosition[Direction::VERTICAL];
    auto yy = y0 + globalSize[Direction::VERTICAL];
    if (x0 <= x && x <= xx && y0 <= y && y <= yy) {
        return true;
    }
    return false;
}

void ui::Button::Process(const sf::Event &event) noexcept
{
    if (event.type == sf::Event::MouseMoved) {
        if (IsInside(event.mouseMove.x, event.mouseMove.y)) {
            if (!entered) {
                SetEntered(true);
                enterCallback(name, event);
            }
        } else {
            if (entered) {
                SetEntered(false);
                leaveCallback(name, event);
            }
        }
    } else if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (IsInside(event.mouseButton.x, event.mouseButton.y)) {
                if (!pressed) {
                    SetPressed(true);
                    pressDownCallback(name, event);
                }
            }
        }
    } else if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (pressed) {
                SetPressed(false);
                pressUpCallback(name, event);
                if (IsInside(event.mouseButton.x, event.mouseButton.y)) {
                    clickCallback(name, event);
                }
            }
        }
    }
}

void ui::Button::Draw(sf::RenderWindow &screen) noexcept
{
    sf::RectangleShape rect(sf::Vector2f(globalSize[Direction::HORIZONTAL], globalSize[Direction::VERTICAL]));
    rect.setPosition({(float)globalPosition[Direction::HORIZONTAL], (float)globalPosition[Direction::VERTICAL]});
    rect.setOutlineThickness(5);
    if (entered) {
        rect.setOutlineColor(sf::Color::Blue);
    } else {
        rect.setOutlineColor(sf::Color::White);
    }
    if (pressed) {
        rect.setFillColor(sf::Color::Blue);
    } else {
        rect.setFillColor(sf::Color(0, 0, 0, 0));
    }
    screen.draw(rect);
    layer.Draw(screen);

    DRAW_DEBUG_RECT;
}

void ui::Button::SetEntered(bool flag) noexcept
{
    entered = flag;
    Update();
}

void ui::Button::SetPressed(bool flag) noexcept
{
    pressed = flag;
    Update();
}

void ui::Margen::SetMargin(unsigned int top, unsigned int bottom, unsigned int left, unsigned int right) noexcept
{
    margin = {top, bottom, left, right};
    Update();
}

void ui::Margen::SetMarginTop(unsigned int top) noexcept
{
    margin.top = top;
    Update();
}

void ui::Margen::SetMarginBottom(unsigned int bottom) noexcept
{
    margin.bottom = bottom;
    Update();
}

void ui::Margen::SetMarginLeft(unsigned int left) noexcept
{
    margin.left = left;
    Update();
}

void ui::Margen::SetMarginRight(unsigned int right) noexcept
{
    margin.right = right;
    Update();
}

void ui::Margen::Update(bool resetMinSize) noexcept
{
    for (auto child : children) {
        child->SetGlobalSize(Direction::HORIZONTAL, globalSize[Direction::HORIZONTAL] - margin.left - margin.right);
        child->SetGlobalSize(Direction::VERTICAL, globalSize[Direction::VERTICAL] - margin.top - margin.bottom);
        child->SetGlobalPosition(Direction::HORIZONTAL, globalPosition[Direction::HORIZONTAL] + margin.left);
        child->SetGlobalPosition(Direction::VERTICAL, globalPosition[Direction::VERTICAL] + margin.top);
        if (resetMinSize) {
            SetMinSize(Direction::HORIZONTAL, child->GetMinSize(Direction::HORIZONTAL) + margin.left + margin.right);
            SetMinSize(Direction::VERTICAL, child->GetMinSize(Direction::VERTICAL) + margin.top + margin.bottom);
        }
    }
}
