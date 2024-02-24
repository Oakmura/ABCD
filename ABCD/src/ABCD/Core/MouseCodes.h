#pragma once

namespace abcd
{
    typedef enum class MouseCode : uint16_t
    {
        // From glfw3.h
        Button0 = 0,
        Button1 = 1,
        Button2 = 2,
        Button3 = 3,
        Button4 = 4,
        Button5 = 5,
        Button6 = 6,
        Button7 = 7,

        ButtonLast = Button7,
        ButtonLeft = Button0,
        ButtonRight = Button1,
        ButtonMiddle = Button2
    } Mouse;

    inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode)
    {
        os << static_cast<int32_t>(mouseCode);
        return os;
    }
}

#define AB_MOUSE_BUTTON_0      ::abcd::Mouse::Button0
#define AB_MOUSE_BUTTON_1      ::abcd::Mouse::Button1
#define AB_MOUSE_BUTTON_2      ::abcd::Mouse::Button2
#define AB_MOUSE_BUTTON_3      ::abcd::Mouse::Button3
#define AB_MOUSE_BUTTON_4      ::abcd::Mouse::Button4
#define AB_MOUSE_BUTTON_5      ::abcd::Mouse::Button5
#define AB_MOUSE_BUTTON_6      ::abcd::Mouse::Button6
#define AB_MOUSE_BUTTON_7      ::abcd::Mouse::Button7
#define AB_MOUSE_BUTTON_LAST   ::abcd::Mouse::ButtonLast
#define AB_MOUSE_BUTTON_LEFT   ::abcd::Mouse::ButtonLeft
#define AB_MOUSE_BUTTON_RIGHT  ::abcd::Mouse::ButtonRight
#define AB_MOUSE_BUTTON_MIDDLE ::abcd::Mouse::ButtonMiddle