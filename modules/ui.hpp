#ifndef __UI_HPP__
#define __UI_HPP__

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
    class Label;

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
    void SetPosition (Direction directrion, int absolute)   noexcept;

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

    virtual ~Control() noexcept;
protected:
    template<typename T>
    class Around{
    public: 
        T horizontal; 
        T vertical; 
        T       &operator[](Direction direction)       noexcept 
        {
            switch (direction) {
                case Direction::HORIZONTAL: return horizontal;
                case Direction::VERTICAL:   return vertical;
            }
            return horizontal;
        }
        const T &operator[](Direction direction) const noexcept 
        {
            switch (direction) {
                case Direction::HORIZONTAL: return horizontal;
                case Direction::VERTICAL:   return vertical;
            }
            return horizontal;
        }
    };

    Around<ValueType>    sizeValueType = {ValueType::ABSOLUTE, ValueType::ABSOLUTE};
    Around<bool>         sizeWrap      = {false, false};
    Around<unsigned int> size          = {200, 100};
    Around<unsigned int> minSize       = {200, 100};
    Around<int> center   = {0, 0};
    Around<int> anchor   = {0, 0};
    Around<int> position = {0, 0};

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
    void Update(bool resetMinSize = true) noexcept;
};

class LinearBox : public Container{
public:
    void SetGap(int absolute) noexcept;
    void Update(bool resetMinSize = true) noexcept = 0;
protected:
    void UpdateLinear(Direction direction, bool resetMinSize = true) noexcept;
    int gap = 5;
};

class Horizontal : public LinearBox{
public:
    void Update(bool resetMinSize = true) noexcept;
};

class Vertical : public LinearBox{
public:
    void Update(bool resetMinSize = true) noexcept;
};

class Label : public Control{
    static const std::string FONT_FILE_PATH;
public:
    Label() noexcept
    {
        SetFont(FONT_FILE_PATH);
    }
    void SetContent(const std::wstring &newContent) noexcept;
    void SetFontSize(unsigned int size)             noexcept;
    void SetFont(const std::string &fontFile)       noexcept;
    void Update (bool resetMinSize = true) noexcept;
    void Process(const sf::Event &event)   noexcept {}
    void Draw   (sf::RenderWindow &screen) noexcept;
protected:
    std::wstring content = L"";
    unsigned int fontSize = 50;
    sf::Font font;
    bool error = false;
    sf::Text text;
};

}

#endif
