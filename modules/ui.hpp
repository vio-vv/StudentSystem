#ifndef __UI_HPP__
#define __UI_HPP__

#define DEBUG

#ifdef DEBUG
#define DRAW_DEBUG_RECT \
    sf::RectangleShape ____(sf::Vector2f(globalSize[Direction::HORIZONTAL], globalSize[Direction::VERTICAL])); \
    ____.setPosition(sf::Vector2f(globalPosition[Direction::HORIZONTAL], (float)globalPosition[Direction::VERTICAL])); \
    ____.setOutlineColor(sf::Color::Yellow); \
    ____.setOutlineThickness(1); \
    ____.setFillColor(sf::Color::Transparent); \
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
 * 各种组件类。
 * 
 * @author 梁祖章
 */

#include <string>
#include <list>
#include <functional>
#include "SFML/Graphics.hpp"

namespace ui{

/*****************************************
 * @brief 所有组件类的声明及它们的继承关系。*
 * ***************************************
 */
/**
 * @class 组件类
 * @brief 所有组件的基类。
 */
class Control;
    /**
     * @class 容器类
     * @brief 所有容器类的基类。
     */
    class Container;
        /**
         * @class 平凡容器类
         * @brief 仅为组件提供尺寸和位置的参考。
         */
        class Flat;
            /**
             * @class 屏幕类
             * @brief 所有组件都要放在屏幕上才能起作用。
             */
            class Screen;
        /**
         * @class 中心布局类
         * @brief 将组件居中。
         * @note 仅能接受一个子组件。
         */
        class Center;
        /**
         * @class 线性布局类
         * @brief 按行或列排列子组件的水平布局类和垂直布局类的基类。
         */
        class LinearBox;
            /**
             * @class 水平布局类
             * @brief 按行排列子组件。
             */
            class HorizontalBox;
            /**
             * @class 垂直布局类
             * @brief 按列排列子组件。
             */
            class VerticalBox;
        /**
         * @class 边距容器类
         * @brief 给组件添加边距。
         */
        class Margen;
    /**
     * @class 间隔类
     * @brief 用于调整组件之间的距离或绘制一个矩形。
     */
    class Spacer;
    /**
     * @class 标签类
     * @brief 显示文本的组件。
     */
    class Label;
    /**
     * @class 按钮类
     * @brief 响应用户按键操作的组件。
     */
    class Button;
    /**
     * @class 输入框类
     * @brief 允许用户输入文本的组件。
     */
    class InputBox;
    /**
     * @class 滚动条类
     * @brief 水平滚动条类和垂直滚动条类的基类。
     */
    class ScrollBar;
        /**
         * @class 水平滚动条类
         * @brief 提供一个水平方向的滚动条。
         */
        class HorizontalBar;
        /**
         * @class 垂直滚动条类
         * @brief 提供一个垂直方向的滚动条。
         */
        class VerticalBar;

/******************************
 * @brief 所有组件类的接口声明。*
 * ****************************
 */

class Control{
public:
    /******************************
     * @brief 约定的常量和数据类型。*
     * ****************************
     */
    /**
     * @enum 方向枚举
     */
    enum class Direction{
        HORIZONTAL, // 水平方向
        VERTICAL    // 垂直方向
    };
    /**
     * @enum 尺寸值类型枚举
     */
    enum class ValueType{
        PERCENTAGE, // 百分值
        ABSOLUTE    // 绝对值
    };
    /**
     * @enum 预设尺寸和位置枚举
     */
    enum class Preset{
        PLACR_AT_FRONT,  PLACR_AT_END,  PLACR_AT_CENTER,  // 置于容器前端、末端、中间
        WRAP_AT_FRONT,   WRAP_AT_END,   WRAP_AT_CENTER,   // 紧缩在容器前端、末端、中间
        FILL_FROM_FRONT, FILL_FROM_END, FILL_FROM_CENTER  // 自容器前端、末端、中间填充
    };

    /**********************************
     * @brief 期望尺寸和位置的设置接口。*
     * ********************************
     */
    /**
     * @fn 设置期望尺寸值类型。
     * @param direction 方向。
     * @param valueType 尺寸值类型。
     * @note 百分值表示相对于父容器的尺寸，绝对值表示像素值。
     */
    void SetSizeValueType(Direction direction, ValueType valueType)    noexcept;
    /**
     * @fn 设置自动紧缩。
     * @param direction 方向。
     * @param flag 是否自动紧缩。
     * @note 仅当期望尺寸值类型为绝对值时有效，当值为 true 时，组件的尺寸会自动缩小到最小尺寸，并使期望尺寸失效。
     */
    void SetSizeWrap     (Direction directrion, bool flag)             noexcept;
    /**
     * @fn 设置期望尺寸。
     * @param direction 方向。
     * @param value 期望尺寸。
     * @note 当期望尺寸值类型为百分值时，其值表示所占父容器的百分比或权重；当期望尺寸值类型为绝对值时，要求自动紧缩为 false 时有效，其值为绝对尺寸。
     */
    void SetSize         (Direction directrion, unsigned int value)    noexcept;
    /**
     * @fn 设置最小尺寸。
     * @param direction 方向。
     * @param absolute 最小绝对尺寸。
     */
    void SetMinSize      (Direction directrion, unsigned int absolute) noexcept;
    /**
     * @fn 设置组件的中心点。
     * @param direction 方向。
     * @param percentage 从前端算起中心点所在位置相对于最终尺寸的百分比。
     */
    void SetCenter    (Direction directrion, int percentage) noexcept;
    /**
     * @fn 设置组件的锚点。
     * @param direction 方向。
     * @param percentage 从父容器前端算起锚点所在位置相对于父容器最终尺寸的百分比。
     */
    void SetAnchor    (Direction directrion, int percentage) noexcept;
    /**
     * @fn 设置组件的位置。
     * @param direction 方向。
     * @param absolute 中心点偏离锚点的绝对位置。
     */
    void SetPosition  (Direction directrion, int absolute)   noexcept;
    /**
     * @fn 设置组件的可见性。
     * @param flag 是否可见。
     */
    void SetVisible (bool flag) noexcept;

    /*****************************************
     * @brief 封装后的设置期望尺寸和位置的接口。*
     * ***************************************
     */
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

    /************************************************
     * @brief 要求派生提供的抽象方法，以实现具体的功能。*
     * **********************************************
     */
    /**
     * @fn 组件的更新接口。
     */
    virtual void Update  (bool resetMinSize = true) noexcept = 0;
    virtual void Process (const sf::Event &event)   noexcept = 0;
    virtual void Draw    (sf::RenderWindow &screen) noexcept = 0;

    /**************************************************
     * @brief 耦合组件与容器的接口，以确定最终尺寸和位置。*
     * ************************************************
     */
    void AddTo            (Container *container)                        noexcept;

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
    /*************************
     * @brief 封装的工具方法。*
     * ***********************
     */
    bool IsInside(int x, int y) const noexcept;

    /*************************
     * @brief 封装的数据类型。*
     * ***********************
     */
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
    using Callback = std::function<void (const sf::String &, const sf::Event &)>;

    /****************************
     * @brief 期望尺寸和位置属性。*
     * **************************
     */
    Around<ValueType>    sizeValueType = {ValueType::ABSOLUTE, ValueType::ABSOLUTE};
    Around<bool>         sizeWrap      = {false, false};
    Around<unsigned int> size          = {200, 100};
    Around<unsigned int> minSize       = {0, 0};
    Around<int> center   = {0, 0};
    Around<int> anchor   = {0, 0};
    Around<int> position = {0, 0};
    bool visible = true;

    /****************************
     * @brief 最终尺寸和位置属性。*
     * **************************
     */
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
    Screen(unsigned int width, unsigned int height, const sf::String &caption) noexcept
    {
        screen.create(sf::VideoMode({width, height}), caption);
        screen.setVerticalSyncEnabled(true);
        SetGlobalSize(Direction::HORIZONTAL, width);
        SetGlobalSize(Direction::VERTICAL, height);
    }
    void SetRange  (unsigned int width, unsigned int height) noexcept;
    void SetCaption(const sf::String &caption)             noexcept;
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

class HorizontalBox : public LinearBox{
public:
    HorizontalBox() noexcept
    {
        Update(true);
    }
    void Update(bool resetMinSize = true) noexcept;
};

class VerticalBox : public LinearBox{
public:
    VerticalBox() noexcept
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
    static const sf::String FONT_FILE_PATH;
public:
    Label() noexcept
    {
        SetFont(FONT_FILE_PATH);
        Update(true);
    }
    void SetContent(const sf::String &newContent) noexcept;
    void SetFontSize(unsigned int size)             noexcept;
    void SetFontColor(const sf::Color &color)       noexcept;
    void SetFont(const sf::String &fontFile)       noexcept;
    const sf::String &GetContent() const noexcept { return content; }
    bool         GetError()   const noexcept { return error; }
    void Update (bool resetMinSize = true) noexcept;
    void Process(const sf::Event &event)   noexcept {}
    void Draw   (sf::RenderWindow &screen) noexcept;
protected:
    static const unsigned int REVISION_X = 15;
    static const unsigned int REVISION_Y = 20;
    sf::String content = "";
    unsigned int fontSize = 50;
    sf::Color fontColor = sf::Color::White;
    sf::Font font;
    bool error = false;
    sf::Text text;
};

class Spacer : public Control{
public:
    Spacer() noexcept
    {
        rect.setOutlineThickness(0);
        rect.setOutlineColor(sf::Color::Transparent);
        rect.setFillColor(sf::Color::Transparent);
    }
    void SetOutlineThickness(float thickness)    noexcept;
    void SetOutlineColor(const sf::Color &color) noexcept;
    void SetFillColor(const sf::Color &color)    noexcept;
    void Update (bool resetMinSize = true) noexcept;
    void Process(const sf::Event &event)   noexcept {}
    void Draw   (sf::RenderWindow &screen) noexcept;
protected:
    sf::RectangleShape rect;
};

class Button : public Control{
public:
    Button() noexcept
    {
        rect->SetPreset(Preset::FILL_FROM_CENTER);
        rect->SetOutlineThickness(5);
        label->SetPreset(Preset::WRAP_AT_CENTER);
        layer.Add(rect);
        layer.Add(label);
        Update(true);
    }
    void SetCaption(const sf::String &caption)   noexcept;
    void SetFontSize(unsigned int size)            noexcept;
    void SetFontColor(const sf::Color &color)      noexcept;
    void SetFont(const sf::String &fontFile)      noexcept;
    void SetName(const sf::String &newName)    noexcept { name = newName; }
    void SetEnterCallback(Callback function)     noexcept { enterCallback = function; }
    void SetLeaveCallback(Callback function)     noexcept { leaveCallback = function; }
    void SetPressDownCallback(Callback function) noexcept { pressDownCallback = function; }
    void SetPressUpCallback(Callback function)   noexcept { pressUpCallback = function; }
    void SetClickCallback(Callback function)     noexcept { clickCallback = function; }
    const sf::String &GetCaption() const noexcept { return label->GetContent(); }
    bool         GetEntered() const noexcept { return entered; }
    bool         GetPressed() const noexcept { return pressed; }
    bool         GetError()   const noexcept { return label->GetError(); }
    void Update (bool resetMinSize = true) noexcept;
    void Process(const sf::Event &event)   noexcept;
    void Draw   (sf::RenderWindow &screen) noexcept;
protected:
    void SetEntered(bool flag) noexcept;
    void SetPressed(bool flag) noexcept;
    Spacer *rect = new Spacer;
    Label *label = new Label;
    bool entered = false;
    bool pressed = false;
    sf::String name = "default";
    Callback enterCallback = [](const sf::String &name, const sf::Event &event){};
    Callback leaveCallback = [](const sf::String &name, const sf::Event &event){};
    Callback pressDownCallback = [](const sf::String &name, const sf::Event &event){};
    Callback pressUpCallback = [](const sf::String &name, const sf::Event &event){};
    Callback clickCallback = [](const sf::String &name, const sf::Event &event){};
    Flat layer;
};

class InputBox : public Control{
public:
    InputBox() noexcept
    {
        button->SetPreset(Preset::FILL_FROM_CENTER);
        button->SetClickCallback([this](const sf::String &name, const sf::Event &event){
            if (!this->inputting) {
                this->SetInputting(true);
                this->beginCallback(this->name, event);
            }
        });
        rect->SetPreset(Preset::FILL_FROM_CENTER);
        label->SetPreset(Preset::FILL_FROM_CENTER);
        layer.Add(button);
        layer.Add(rect);
        layer.Add(label);
        Update(true);
    }
    void SetText(const sf::String &text)                noexcept;
    void SetFontSize(unsigned int size)            noexcept;
    void SetFontColor(const sf::Color &color)      noexcept;
    void SetInputtingFontColor(const sf::Color &color) noexcept;
    void SetBackColor(const sf::Color &color)      noexcept;
    void SetInputtingBackColor(const sf::Color &color) noexcept;
    void SetFont(const sf::String &fontFile)      noexcept;
    void SetName(const sf::String &newName) noexcept { name = newName; }
    void SetBeginCallback(Callback function)  noexcept { beginCallback = function; }
    void SetInputCallback(Callback function)  noexcept { inputCallback = function; }
    void SetEndCallback(Callback function)    noexcept { endCallback = function; }
    const sf::String &GetText() const noexcept { return label->GetContent(); }
    bool GetInputting()    const noexcept { return inputting; }
    bool GetError()        const noexcept { return button->GetError() || label->GetError(); }
    void Update (bool resetMinSize = true) noexcept;
    void Process(const sf::Event &event)   noexcept;
    void Draw   (sf::RenderWindow &screen) noexcept;
protected:
    void SetInputting(bool flag) noexcept;
    Button *button = new Button;
    Spacer *rect = new Spacer;
    Label *label = new Label;
    bool inputting = false;
    sf::String name = "default";
    sf::Color fontColor = sf::Color::White;
    sf::Color inputtingFontColor = sf::Color::Black;
    sf::Color backColor = sf::Color::Transparent;
    sf::Color inputtingBackColor = sf::Color::White;
    Callback beginCallback = [](const sf::String &name, const sf::Event &event){};
    Callback inputCallback = [](const sf::String &name, const sf::Event &event){};
    Callback endCallback = [](const sf::String &name, const sf::Event &event){};
    Flat layer;
};

class ScrollBar : public Control{
public:
    void Update (bool resetMinSize = true) noexcept;
    void Process(const sf::Event &event)   noexcept;
    void Draw   (sf::RenderWindow &screen) noexcept;
protected:
    Button *button = new Button;
    Flat layer;
};

}

#endif
