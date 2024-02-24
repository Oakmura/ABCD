#pragma once

namespace abcd
{
    typedef enum class KeyCode : uint16_t
    {
        // From glfw3.h
        Space = 32,
        Apostrophe = 39, /* ' */
        Comma = 44, /* , */
        Minus = 45, /* - */
        Period = 46, /* . */
        Slash = 47, /* / */

        D0 = 48, /* 0 */
        D1 = 49, /* 1 */
        D2 = 50, /* 2 */
        D3 = 51, /* 3 */
        D4 = 52, /* 4 */
        D5 = 53, /* 5 */
        D6 = 54, /* 6 */
        D7 = 55, /* 7 */
        D8 = 56, /* 8 */
        D9 = 57, /* 9 */

        Semicolon = 59, /* ; */
        Equal = 61, /* = */

        A = 65,
        B = 66,
        C = 67,
        D = 68,
        E = 69,
        F = 70,
        G = 71,
        H = 72,
        I = 73,
        J = 74,
        K = 75,
        L = 76,
        M = 77,
        N = 78,
        O = 79,
        P = 80,
        Q = 81,
        R = 82,
        S = 83,
        T = 84,
        U = 85,
        V = 86,
        W = 87,
        X = 88,
        Y = 89,
        Z = 90,

        LeftBracket = 91,  /* [ */
        Backslash = 92,  /* \ */
        RightBracket = 93,  /* ] */
        GraveAccent = 96,  /* ` */

        World1 = 161, /* non-US #1 */
        World2 = 162, /* non-US #2 */

        /* Function keys */
        Escape = 256,
        Enter = 257,
        Tab = 258,
        Backspace = 259,
        Insert = 260,
        Delete = 261,
        Right = 262,
        Left = 263,
        Down = 264,
        Up = 265,
        PageUp = 266,
        PageDown = 267,
        Home = 268,
        End = 269,
        CapsLock = 280,
        ScrollLock = 281,
        NumLock = 282,
        PrintScreen = 283,
        Pause = 284,
        F1 = 290,
        F2 = 291,
        F3 = 292,
        F4 = 293,
        F5 = 294,
        F6 = 295,
        F7 = 296,
        F8 = 297,
        F9 = 298,
        F10 = 299,
        F11 = 300,
        F12 = 301,
        F13 = 302,
        F14 = 303,
        F15 = 304,
        F16 = 305,
        F17 = 306,
        F18 = 307,
        F19 = 308,
        F20 = 309,
        F21 = 310,
        F22 = 311,
        F23 = 312,
        F24 = 313,
        F25 = 314,

        /* Keypad */
        KP0 = 320,
        KP1 = 321,
        KP2 = 322,
        KP3 = 323,
        KP4 = 324,
        KP5 = 325,
        KP6 = 326,
        KP7 = 327,
        KP8 = 328,
        KP9 = 329,
        KPDecimal = 330,
        KPDivide = 331,
        KPMultiply = 332,
        KPSubtract = 333,
        KPAdd = 334,
        KPEnter = 335,
        KPEqual = 336,

        LeftShift = 340,
        LeftControl = 341,
        LeftAlt = 342,
        LeftSuper = 343,
        RightShift = 344,
        RightControl = 345,
        RightAlt = 346,
        RightSuper = 347,
        Menu = 348
    } Key;

    inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
    {
        os << static_cast<int32_t>(keyCode);
        return os;
    }
}

// From glfw3.h
#define AB_KEY_SPACE           ::abcd::Key::Space
#define AB_KEY_APOSTROPHE      ::abcd::Key::Apostrophe    /* ' */
#define AB_KEY_COMMA           ::abcd::Key::Comma         /* , */
#define AB_KEY_MINUS           ::abcd::Key::Minus         /* - */
#define AB_KEY_PERIOD          ::abcd::Key::Period        /* . */
#define AB_KEY_SLASH           ::abcd::Key::Slash         /* / */
#define AB_KEY_0               ::abcd::Key::D0
#define AB_KEY_1               ::abcd::Key::D1
#define AB_KEY_2               ::abcd::Key::D2
#define AB_KEY_3               ::abcd::Key::D3
#define AB_KEY_4               ::abcd::Key::D4
#define AB_KEY_5               ::abcd::Key::D5
#define AB_KEY_6               ::abcd::Key::D6
#define AB_KEY_7               ::abcd::Key::D7
#define AB_KEY_8               ::abcd::Key::D8
#define AB_KEY_9               ::abcd::Key::D9
#define AB_KEY_SEMICOLON       ::abcd::Key::Semicolon     /* ; */
#define AB_KEY_EQUAL           ::abcd::Key::Equal         /* = */
#define AB_KEY_A               ::abcd::Key::A
#define AB_KEY_B               ::abcd::Key::B
#define AB_KEY_C               ::abcd::Key::C
#define AB_KEY_D               ::abcd::Key::D
#define AB_KEY_E               ::abcd::Key::E
#define AB_KEY_F               ::abcd::Key::F
#define AB_KEY_G               ::abcd::Key::G
#define AB_KEY_H               ::abcd::Key::H
#define AB_KEY_I               ::abcd::Key::I
#define AB_KEY_J               ::abcd::Key::J
#define AB_KEY_K               ::abcd::Key::K
#define AB_KEY_L               ::abcd::Key::L
#define AB_KEY_M               ::abcd::Key::M
#define AB_KEY_N               ::abcd::Key::N
#define AB_KEY_O               ::abcd::Key::O
#define AB_KEY_P               ::abcd::Key::P
#define AB_KEY_Q               ::abcd::Key::Q
#define AB_KEY_R               ::abcd::Key::R
#define AB_KEY_S               ::abcd::Key::S
#define AB_KEY_T               ::abcd::Key::T
#define AB_KEY_U               ::abcd::Key::U
#define AB_KEY_V               ::abcd::Key::V
#define AB_KEY_W               ::abcd::Key::W
#define AB_KEY_X               ::abcd::Key::X
#define AB_KEY_Y               ::abcd::Key::Y
#define AB_KEY_Z               ::abcd::Key::Z
#define AB_KEY_LEFT_BRACKET    ::abcd::Key::LeftBracket   /* [ */
#define AB_KEY_BACKSLASH       ::abcd::Key::Backslash     /* \ */
#define AB_KEY_RIGHT_BRACKET   ::abcd::Key::RightBracket  /* ] */
#define AB_KEY_GRAVE_ACCENT    ::abcd::Key::GraveAccent   /* ` */
#define AB_KEY_WORLD_1         ::abcd::Key::World1        /* non-US #1 */
#define AB_KEY_WORLD_2         ::abcd::Key::World2        /* non-US #2 */

/* Function keys */
#define AB_KEY_ESCAPE          ::abcd::Key::Escape
#define AB_KEY_ENTER           ::abcd::Key::Enter
#define AB_KEY_TAB             ::abcd::Key::Tab
#define AB_KEY_BACKSPACE       ::abcd::Key::Backspace
#define AB_KEY_INSERT          ::abcd::Key::Insert
#define AB_KEY_DELETE          ::abcd::Key::Delete
#define AB_KEY_RIGHT           ::abcd::Key::Right
#define AB_KEY_LEFT            ::abcd::Key::Left
#define AB_KEY_DOWN            ::abcd::Key::Down
#define AB_KEY_UP              ::abcd::Key::Up
#define AB_KEY_PAGE_UP         ::abcd::Key::PageUp
#define AB_KEY_PAGE_DOWN       ::abcd::Key::PageDown
#define AB_KEY_HOME            ::abcd::Key::Home
#define AB_KEY_END             ::abcd::Key::End
#define AB_KEY_CAPS_LOCK       ::abcd::Key::CapsLock
#define AB_KEY_SCROLL_LOCK     ::abcd::Key::ScrollLock
#define AB_KEY_NUM_LOCK        ::abcd::Key::NumLock
#define AB_KEY_PRINT_SCREEN    ::abcd::Key::PrintScreen
#define AB_KEY_PAUSE           ::abcd::Key::Pause
#define AB_KEY_F1              ::abcd::Key::F1
#define AB_KEY_F2              ::abcd::Key::F2
#define AB_KEY_F3              ::abcd::Key::F3
#define AB_KEY_F4              ::abcd::Key::F4
#define AB_KEY_F5              ::abcd::Key::F5
#define AB_KEY_F6              ::abcd::Key::F6
#define AB_KEY_F7              ::abcd::Key::F7
#define AB_KEY_F8              ::abcd::Key::F8
#define AB_KEY_F9              ::abcd::Key::F9
#define AB_KEY_F10             ::abcd::Key::F10
#define AB_KEY_F11             ::abcd::Key::F11
#define AB_KEY_F12             ::abcd::Key::F12
#define AB_KEY_F13             ::abcd::Key::F13
#define AB_KEY_F14             ::abcd::Key::F14
#define AB_KEY_F15             ::abcd::Key::F15
#define AB_KEY_F16             ::abcd::Key::F16
#define AB_KEY_F17             ::abcd::Key::F17
#define AB_KEY_F18             ::abcd::Key::F18
#define AB_KEY_F19             ::abcd::Key::F19
#define AB_KEY_F20             ::abcd::Key::F20
#define AB_KEY_F21             ::abcd::Key::F21
#define AB_KEY_F22             ::abcd::Key::F22
#define AB_KEY_F23             ::abcd::Key::F23
#define AB_KEY_F24             ::abcd::Key::F24
#define AB_KEY_F25             ::abcd::Key::F25

/* Keypad */
#define AB_KEY_KP_0            ::abcd::Key::KP0
#define AB_KEY_KP_1            ::abcd::Key::KP1
#define AB_KEY_KP_2            ::abcd::Key::KP2
#define AB_KEY_KP_3            ::abcd::Key::KP3
#define AB_KEY_KP_4            ::abcd::Key::KP4
#define AB_KEY_KP_5            ::abcd::Key::KP5
#define AB_KEY_KP_6            ::abcd::Key::KP6
#define AB_KEY_KP_7            ::abcd::Key::KP7
#define AB_KEY_KP_8            ::abcd::Key::KP8
#define AB_KEY_KP_9            ::abcd::Key::KP9
#define AB_KEY_KP_DECIMAL      ::abcd::Key::KPDecimal
#define AB_KEY_KP_DIVIDE       ::abcd::Key::KPDivide
#define AB_KEY_KP_MULTIPLY     ::abcd::Key::KPMultiply
#define AB_KEY_KP_SUBTRACT     ::abcd::Key::KPSubtract
#define AB_KEY_KP_ADD          ::abcd::Key::KPAdd
#define AB_KEY_KP_ENTER        ::abcd::Key::KPEnter
#define AB_KEY_KP_EQUAL        ::abcd::Key::KPEqual

#define AB_KEY_LEFT_SHIFT      ::abcd::Key::LeftShift
#define AB_KEY_LEFT_CONTROL    ::abcd::Key::LeftControl
#define AB_KEY_LEFT_ALT        ::abcd::Key::LeftAlt
#define AB_KEY_LEFT_SUPER      ::abcd::Key::LeftSuper
#define AB_KEY_RIGHT_SHIFT     ::abcd::Key::RightShift
#define AB_KEY_RIGHT_CONTROL   ::abcd::Key::RightControl
#define AB_KEY_RIGHT_ALT       ::abcd::Key::RightAlt
#define AB_KEY_RIGHT_SUPER     ::abcd::Key::RightSuper
#define AB_KEY_MENU            ::abcd::Key::Menu