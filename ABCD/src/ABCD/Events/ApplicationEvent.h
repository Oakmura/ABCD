#pragma once

#include "Event.h"

namespace abcd {

    class AB_API WindowResizeEvent : public Event
    {
    public:
        WindowResizeEvent(unsigned int width, unsigned int height)
            : mWidth(width), mHeight(height) {}

        inline unsigned int GetWidth() const { return mWidth; }
        inline unsigned int GetHeight() const { return mHeight; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "WindowResizeEvent: " << mWidth << ", " << mHeight;
            return ss.str();
        }

        EVENT_CLASS_TYPE(WINDOW_RESIZE)
            EVENT_CLASS_CATEGORY(EVENT_CATEGORY_APPLICATION)
    private:
        unsigned int mWidth, mHeight;
    };

    class AB_API WindowCloseEvent : public Event
    {
    public:
        WindowCloseEvent() {}

        EVENT_CLASS_TYPE(WINDOW_CLOSE)
            EVENT_CLASS_CATEGORY(EVENT_CATEGORY_APPLICATION)
    };

    class AB_API AppTickEvent : public Event
    {
    public:
        AppTickEvent() {}

        EVENT_CLASS_TYPE(APP_TICK)
            EVENT_CLASS_CATEGORY(EVENT_CATEGORY_APPLICATION)
    };

    class AB_API AppUpdateEvent : public Event
    {
    public:
        AppUpdateEvent() {}

        EVENT_CLASS_TYPE(APP_UPDATE)
            EVENT_CLASS_CATEGORY(EVENT_CATEGORY_APPLICATION)
    };

    class AB_API AppRenderEvent : public Event
    {
    public:
        AppRenderEvent() {}

        EVENT_CLASS_TYPE(APP_RENDER)
            EVENT_CLASS_CATEGORY(EVENT_CATEGORY_APPLICATION)
    };
}