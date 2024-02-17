#pragma once

#include <sstream>

#include "Event.h"

namespace abcd {

    class AB_API KeyEvent : public Event
    {
    public:
        inline int GetKeyCode() const { return mKeyCode; }

        EVENT_CLASS_CATEGORY(EVENT_CATEGORY_KEYBOARD| EVENT_CATEGORY_INPUT)
    protected:
        KeyEvent(int keycode)
            : mKeyCode(keycode) {}

        int mKeyCode;
    };

    class AB_API KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(int keycode, int repeatCount)
            : KeyEvent(keycode), mRepeatCount(repeatCount) {}

        inline int GetRepeatCount() const { return mRepeatCount; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << mKeyCode << " (" << mRepeatCount << " repeats)";
            return ss.str();
        }

        EVENT_CLASS_TYPE(KEY_PRESSED)
    private:
        int mRepeatCount;
    };

    class AB_API KeyReleasedEvent : public KeyEvent
    {
    public:
        KeyReleasedEvent(int keycode)
            : KeyEvent(keycode) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << mKeyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KEY_RELEASED)
    };
}