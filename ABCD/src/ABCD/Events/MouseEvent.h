#pragma once

#include <sstream>

#include "Event.h"

namespace abcd {

    class AB_API MouseMovedEvent : public Event
    {
    public:
        MouseMovedEvent(float x, float y)
            : mMouseX(x), mMouseY(y) {}

        inline float GetX() const { return mMouseX; }
        inline float GetY() const { return mMouseY; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << mMouseX << ", " << mMouseY;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MOUSE_MOVED)
            EVENT_CLASS_CATEGORY(EVENT_CATEGORY_MOUSE | EVENT_CATEGORY_INPUT)
    private:
        float mMouseX, mMouseY;
    };

    class AB_API MouseScrolledEvent : public Event
    {
    public:
        MouseScrolledEvent(float xOffset, float yOffset)
            : mXOffset(xOffset), mYOffset(yOffset) {}

        inline float GetXOffset() const { return mXOffset; }
        inline float GetYOffset() const { return mYOffset; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
            return ss.str();
        }

        EVENT_CLASS_TYPE(MOUSE_SCROLLED)
            EVENT_CLASS_CATEGORY(EVENT_CATEGORY_MOSUE | EVENT_CATEGORY_INPUT)
    private:
        float mXOffset, mYOffset;
    };

    class AB_API MouseButtonEvent : public Event
    {
    public:
        inline int GetMouseButton() const { return mButton; }

        EVENT_CLASS_CATEGORY(EVENT_CATEGORY_MOUSE | EVENT_CATEGORY_INPUT)
    protected:
        MouseButtonEvent(int button)
            : mButton(button) {}

        int mButton;
    };

    class AB_API MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonPressedEvent(int button)
            : MouseButtonEvent(button) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << mButton;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MOUSE_BUTTON_PRESSED)
    };

    class AB_API MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(int button)
            : MouseButtonEvent(button) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: " << mButton;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MOUSE_BUTTON_RELEASED)
    };
}