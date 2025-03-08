#ifndef __UI_HPP__
#define __UI_HPP__

#define DEBUG

#ifdef DEBUG
#define DRAW_DEBUG_RECT \
    sf::RectangleShape ____(sf::Vector2f(globalSize[Direction::HORIZONTAL], globalSize[Direction::VERTICAL])); \
    ____.setPosition(sf::Vector2f(globalPosition[Direction::HORIZONTAL], (float)globalPosition[Direction::VERTICAL])); \
    ____.setOutlineColor(sf::Color::Yellow); \
    ____.setOutlineThickness(1); \
    ____.setFillColor(sf::Color(0, 0, 0, 0)); \
    screen.draw(____)
#else
#define DRAW_DEBUG_RECT
#endif

/**
 * @brief 实现 UI 界面的布局和绘制。
 * 
 * @par REQUIRES
 * NONE
 * 
 * @par PROVIDES
 * 
 * @author 梁祖章
 */

#include <string>
#include <list>
#include <functional>
#include "SFML/Graphics.hpp"

namespace ui{
    
class Control;
    class Container;
        class Flat;
            class Screen;
        class Center;
        class LinearBox;
            class Horizontal;
            class Vertical;
        class Margen;
    class Label;
    class Button;
    class InputBox;

class Control{
public:
    enum class Direction{
        HORIZONTAL, VERTICAL
    };
    enum class ValueType{
        PERCENTAGE, ABSOLUTE
    };
    enum class Preset{
        PLACR_AT_FRONT,  PLACR_AT_END,  PLACR_AT_CENTER,
        WRAP_AT_FRONT,   WRAP_AT_END,   WRAP_AT_CENTER,
        FILL_FROM_FRONT, FILL_FROM_END, FILL_FROM_CENTER
    };

    void SetSizeValueType(Direction direction, ValueType valueType)    noexcept;
    void SetSizeWrap     (Direction directrion, bool flag)             noexcept;
    void SetSize         (Direction directrion, unsigned int value)    noexcept;
    void SetMinSize      (Direction directrion, unsigned int absolute) noexcept;
    void SetCenter    (Direction directrion, int percentage) noexcept;
    void SetAnchor    (Direction directrion, int percentage) noexcept;
    void SetPosition  (Direction directrion, int absolute)   noexcept;
    void SetVisible (bool flag) noexcept;

    void AddTo    (Container *container)               noexcept;
    void SetPreset(Direction direction, Preset preset) noexcept;
    void SetHSizeValueType(ValueType valueType)   noexcept { SetSizeValueType(Direction::HORIZONTAL, valueType); }
    void SetVSizeValueType(ValueType valueType)   noexcept { SetSizeValueType(Direction::VERTICAL,   valueType); }
    void SetHSizeWrap     (bool flag)             noexcept { SetSizeWrap(Direction::HORIZONTAL, flag); }
    void SetVSizeWrap     (bool flag)             noexcept { SetSizeWrap(Direction::VERTICAL,   flag); }
    void SetHSize         (unsigned int value)    noexcept { SetSize(Direction::HORIZONTAL, value); }
    void SetVSize         (unsigned int value)    noexcept { SetSize(Direction::VERTICAL,   value); }
    void SetHMinSize      (unsigned int absolute) noexcept { SetMinSize(Direction::HORIZONTAL, absolute); }
    void SetVMinSize      (unsigned int absolute) noexcept { SetMinSize(Direction::VERTICAL,   absolute); }
    void SetHCenter       (int percentage)        noexcept { SetCenter(Direction::HORIZONTAL, percentage); }
    void SetVCenter       (int percentage)        noexcept { SetCenter(Direction::VERTICAL,   percentage); }
    void SetHAnchor       (int percentage)        noexcept { SetAnchor(Direction::HORIZONTAL, percentage); }
    void SetVAnchor       (int percentage)        noexcept { SetAnchor(Direction::VERTICAL,   percentage); }
    void SetHPosition     (int absolute)          noexcept { SetPosition(Direction::HORIZONTAL, absolute); }
    void SetVPosition     (int absolute)          noexcept { SetPosition(Direction::VERTICAL,   absolute); }
    void SetHPreset       (Preset preset)         noexcept { SetPreset(Direction::HORIZONTAL, preset); }
    void SetVPreset       (Preset preset)         noexcept { SetPreset(Direction::VERTICAL,   preset); }
    void SetSizeValueType (ValueType valueType)                            noexcept { SetHSizeValueType(valueType);   SetVSizeValueType(valueType); }
    void SetSizeWrap      (bool flag)                                      noexcept { SetHSizeWrap     (flag);        SetVSizeWrap     (flag); }
    void SetSize          (unsigned int valueH, unsigned int valueV)       noexcept { SetHSize         (valueH);      SetVSize         (valueV); }
    void SetMinSize       (unsigned int absoluteH, unsigned int absoluteV) noexcept { SetHMinSize      (absoluteH);   SetVMinSize      (absoluteV); }
    void SetCenter        (int percentageH, int percentageV)               noexcept { SetHCenter       (percentageH); SetVCenter       (percentageV); }
    void SetAnchor        (int percentageH, int percentageV)               noexcept { SetHAnchor       (percentageH); SetVAnchor       (percentageV); }
    void SetPosition      (int absoluteH, int absoluteV)                   noexcept { SetHPosition     (absoluteH);   SetVPosition     (absoluteV); }
    void SetPreset        (Preset preset)                                  noexcept { SetHPreset       (preset);      SetVPreset       (preset); }

    virtual void Update  (bool resetMinSize = true) noexcept = 0;
    virtual void Process (const sf::Event &event)   noexcept = 0;
    virtual void Draw    (sf::RenderWindow &screen) noexcept = 0;

    void SetParent        (Container *container)                        noexcept;
    void SetGlobalSize    (Direction directrion, unsigned int absolute) noexcept;
    void SetGlobalPosition(Direction directrion, int absolute)          noexcept;
    unsigned int GetGlobalSize    (Direction direction) const noexcept { return globalSize[direction]; }
    int          GetGlobalPosition(Direction direction) const noexcept { return globalPosition[direction]; }

    ValueType    GetSizeValueType(Direction direction) const noexcept { return sizeValueType[direction]; }
    bool         GetSizeWrap     (Direction direction) const noexcept { return sizeWrap[direction]; }
    unsigned int GetSize         (Direction direction) const noexcept { return size[direction]; }
    unsigned int GetMinSize      (Direction direction) const noexcept { return minSize[direction]; }
    int  GetCenter  (Direction direction) const noexcept { return center[direction]; }
    int  GetAnchor  (Direction direction) const noexcept { return anchor[direction]; }
    int  GetPosition(Direction direction) const noexcept { return position[direction]; }
    bool GetVisible() const noexcept { return visible; }

    virtual ~Control() noexcept;
protected:
    bool IsInside(int x, int y) const noexcept;

    template<typename DataType>
    class Around{
    public: 
        DataType horizontal; 
        DataType vertical; 
        DataType       &operator[](Direction direction)       noexcept 
        {
            switch (direction) {
                case Direction::HORIZONTAL: return horizontal;
                case Direction::VERTICAL:   return vertical;
            }
            return horizontal;
        }
        const DataType &operator[](Direction direction) const noexcept 
        {
            switch (direction) {
                case Direction::HORIZONTAL: return horizontal;
                case Direction::VERTICAL:   return vertical;
            }
            return horizontal;
        }
    };
    using Callback = std::function<void (std::wstring, const sf::Event &)>;

    Around<ValueType>    sizeValueType = {ValueType::ABSOLUTE, ValueType::ABSOLUTE};
    Around<bool>         sizeWrap      = {false, false};
    Around<unsigned int> size          = {200, 100};
    Around<unsigned int> minSize       = {0, 0};
    Around<int> center   = {0, 0};
    Around<int> anchor   = {0, 0};
    Around<int> position = {0, 0};
    bool        visible = true;

    Container           *parent         = nullptr;
    Around<unsigned int> globalSize     = {200, 100};
    Around<int>          globalPosition = {0, 0};
};

class Container : public Control{
public:
    void Add     (Control *control) noexcept;
    void Remove  (Control *control) noexcept;
    void FreeAll ()                 noexcept;

    void Update (bool resetMinSize = true) noexcept = 0;
    void Process(const sf::Event &event)   noexcept;
    void Draw   (sf::RenderWindow &screen) noexcept;

    ~Container() noexcept;
protected:
    void UpdateByDefault(Direction direction, Control *child) noexcept;
    void UpdateSizeByDefault    (Direction direction, Control *child) noexcept;
    void UpdatePositionByDefault(Direction direction, Control *child) noexcept;
    static unsigned int ObtainDefaultGlobalSize    (Direction direction, const Control *child, unsigned int parentSize)                                                              noexcept;
    static int          ObtainDefaultGlobalPosition(Direction direction, const Control *child, unsigned int parentSize, int parentPosition)                                          noexcept;
    static unsigned int ObtainDefaultGlobalSize    (ValueType sizeValueType, bool wrap,   unsigned int size,     unsigned int minSize,  unsigned int parentSize)                     noexcept;
    static int          ObtainDefaultGlobalPosition(int       center,        int  anchor, int          position, unsigned int thisSize, unsigned int parentSize, int parentPosition) noexcept;
    std::list<Control *> children = {};
};

class Flat : public Container{
public:
    void Update(bool resetMinSize = true) noexcept;
};

class Screen : public Flat{
public:
    sf::RenderWindow &Get() noexcept { return screen; }
    Screen() noexcept
    {
        unsigned int width = globalSize[Direction::HORIZONTAL];
        unsigned int height = globalSize[Direction::VERTICAL];
        screen.create(sf::VideoMode({width, height}), "Caption");
        screen.setVerticalSyncEnabled(true);
    }
    Screen(unsigned int width, unsigned int height, const std::wstring &caption) noexcept
    {
        screen.create(sf::VideoMode({width, height}), caption);
        screen.setVerticalSyncEnabled(true);
        SetGlobalSize(Direction::HORIZONTAL, width);
        SetGlobalSize(Direction::VERTICAL, height);
    }
    void SetRange  (unsigned int width, unsigned int height) noexcept;
    void SetCaption(const std::wstring &caption)             noexcept;
    bool IsOpen    ()                                  const noexcept;
    void Tick      ()                                        noexcept;
protected:
    sf::RenderWindow screen;
};

class Center : public Container{
public:
    Center() noexcept
    {
        Update(true);
    }
    void Update(bool resetMinSize = true) noexcept;
};

class LinearBox : public Container{
public:
    void SetGap(int absolute) noexcept;
    void Update(bool resetMinSize = true) noexcept = 0;
protected:
    void UpdateLinear(Direction direction, bool resetMinSize) noexcept;
    int gap = 25;
};

class Horizontal : public LinearBox{
public:
    Horizontal() noexcept
    {
        Update(true);
    }
    void Update(bool resetMinSize = true) noexcept;
};

class Vertical : public LinearBox{
public:
    Vertical() noexcept
    {
        Update(true);
    }
    void Update(bool resetMinSize = true) noexcept;
};

class Margen : public Container{
public:
    Margen() noexcept
    {
        Update(true);
    }
    void SetMargin(unsigned int top, unsigned int bottom, unsigned int left, unsigned int right) noexcept;
    void SetMarginTop   (unsigned int top)    noexcept;
    void SetMarginBottom(unsigned int bottom) noexcept;
    void SetMarginLeft  (unsigned int left)   noexcept;
    void SetMarginRight (unsigned int right)  noexcept;
    void Update(bool resetMinSize = true) noexcept;
private:
    struct{
        unsigned int top = 25;
        unsigned int bottom = 25;
        unsigned int left = 25;
        unsigned int right = 25;
    }margin;
};

class Label : public Control{
    static const std::string FONT_FILE_PATH;
public:
    Label() noexcept
    {
        SetFont(FONT_FILE_PATH);
        Update(true);
    }
    void SetContent(const std::wstring &newContent) noexcept;
    void SetFontSize(unsigned int size)             noexcept;
    void SetFontColor(const sf::Color &color)       noexcept;
    void SetFont(const std::string &fontFile)       noexcept;
    std::wstring GetContent() const noexcept { return content; }
    bool         GetError()   const noexcept { return error; }
    void Update (bool resetMinSize = true) noexcept;
    void Process(const sf::Event &event)   noexcept {}
    void Draw   (sf::RenderWindow &screen) noexcept;
protected:
    static const unsigned int REVISION_X = 15;
    static const unsigned int REVISION_Y = 20;
    std::wstring content = L"";
    unsigned int fontSize = 50;
    sf::Color fontColor = sf::Color::White;
    sf::Font font;
    bool error = false;
    sf::Text text;
};

class Button : public Control{
public:
    Button() noexcept
    {
        label->SetPreset(Preset::WRAP_AT_CENTER);
        layer.Add(label);
        Update(true);
    }
    void SetCaption(const std::wstring &caption)   noexcept;
    void SetFontSize(unsigned int size)            noexcept;
    void SetFontColor(const sf::Color &color)      noexcept;
    void SetFont(const std::string &fontFile)      noexcept;
    void SetName(const std::wstring &newName)    noexcept { name = newName; }
    void SetEnterCallback(Callback function)     noexcept { enterCallback = function; }
    void SetLeaveCallback(Callback function)     noexcept { leaveCallback = function; }
    void SetPressDownCallback(Callback function) noexcept { pressDownCallback = function; }
    void SetPressUpCallback(Callback function)   noexcept { pressUpCallback = function; }
    void SetClickCallback(Callback function)     noexcept { clickCallback = function; }
    std::wstring GetCaption() const noexcept { return label->GetContent(); }
    bool         GetEntered() const noexcept { return entered; }
    bool         GetPressed() const noexcept { return pressed; }
    bool         GetError()   const noexcept { return label->GetError(); }
    void Update (bool resetMinSize = true) noexcept;
    void Process(const sf::Event &event)   noexcept;
    void Draw   (sf::RenderWindow &screen) noexcept;
protected:
    void SetEntered(bool flag) noexcept;
    void SetPressed(bool flag) noexcept;
    Label *label = new Label;
    bool entered = false;
    bool pressed = false;
    std::wstring name = L"default";
    Callback enterCallback = [](std::wstring name, const sf::Event &event){};
    Callback leaveCallback = [](std::wstring name, const sf::Event &event){};
    Callback pressDownCallback = [](std::wstring name, const sf::Event &event){};
    Callback pressUpCallback = [](std::wstring name, const sf::Event &event){};
    Callback clickCallback = [](std::wstring name, const sf::Event &event){};
    Flat layer;
};

class InputBox : public Control{
public:
    InputBox() noexcept
    {
        button->SetPreset(Preset::FILL_FROM_CENTER);
        button->SetClickCallback([this](std::wstring name, const sf::Event &event){
            this->SetInputting(true);
        });
        label->SetPreset(Preset::FILL_FROM_CENTER);
        layer.Add(button);
        layer.Add(label);
        Update(true);
    }
    void SetText(std::wstring text)                noexcept;
    void SetFontSize(unsigned int size)            noexcept;
    void SetFontColor(const sf::Color &color)      noexcept;
    void SetFont(const std::string &fontFile)      noexcept;
    void SetSensitivity(unsigned int value)        noexcept { sensitivity = value; }
    void SetContinuousInterval(unsigned int value) noexcept { continuousInterval = value; }
    void SetName(const std::wstring &newName) noexcept { name = newName; }
    void SetBeginCallback(Callback function)  noexcept { beginCallback = function; }
    void SetInputCallback(Callback function)  noexcept { inputCallback = function; }
    void SetEndCallback(Callback function)    noexcept { endCallback = function; }
    std::wstring GetText() const noexcept { return label->GetContent(); }
    bool GetInputting()    const noexcept { return inputting; }
    bool GetError()        const noexcept { return button->GetError() || label->GetError(); }
    void Update (bool resetMinSize = true) noexcept;
    void Process(const sf::Event &event)   noexcept;
    void Draw   (sf::RenderWindow &screen) noexcept;
protected:
    void SetInputting(bool flag) noexcept;
    Button *button = new Button;
    Label *label = new Label;
    unsigned int sensitivity = 800;
    unsigned int continuousInterval = 50;
    bool inputting = false;
    std::wstring name = L"default";
    Callback beginCallback = [](std::wstring name, const sf::Event &event){};
    Callback inputCallback = [](std::wstring name, const sf::Event &event){};
    Callback endCallback = [](std::wstring name, const sf::Event &event){};
    Flat layer;
};

}

#endif
