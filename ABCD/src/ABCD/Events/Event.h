#pragma once

#include <string>
#include <functional>

#include "ABCD/Core.h"

namespace abcd
{
    enum class eEventType
    {
        NONE = 0,
        WINDOW_CLOSE, WINDOW_RESIZE, WINDOW_FOCUS, WINDOW_LOST_FOCUS, WINDOW_MOVED,
        APP_TICK, APP_UPDATE, APP_RENDER,
        KEY_PRESSED, KEY_RELEASED,
        MOUSE_BUTTON_PRESSED, MOUSE_BUTTON_RELEASED, MOUSE_MOVED, MOUSE_SCROLLED
    };

    enum eEventCategory
    {
        NONE = 0,
        EVENT_CATEGORY_APPLICATION = BIT(0),
        EVENT_CATEGORY_INPUT = BIT(1),
        EVENT_CATEGORY_KEYBOARD = BIT(2),
        EVENT_CATEGORY_MOUSE = BIT(3),
        EVENT_CATEGORY_MOUSE_BUTTON = BIT(4)
    };

#define EVENT_CLASS_TYPE(type) static eEventType GetStaticType() { return eEventType::##type; }\
                            virtual eEventType GetEventType() const override { return GetStaticType(); }\
                            virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

    class AB_API Event
    {
        friend class EventDispatcher;
    public:
        virtual eEventType GetEventType() const = 0;
        virtual const char* GetName() const = 0;
        virtual int GetCategoryFlags() const = 0;
        virtual std::string ToString() const { return GetName(); }

        inline bool IsInCategory(eEventCategory category)
        {
            return GetCategoryFlags() & category;
        }
    protected:
        bool mbHandled = false;
    };

    class EventDispatcher
    {
        template<typename T>
        using EventFn = std::function<bool(T&)>;
    public:
        EventDispatcher(Event& event)
            : mEvent(event)
        {
        }

        template<typename T>
        bool Dispatch(EventFn<T> func)
        {
            if (mEvent.GetEventType() == T::GetStaticType())
            {
                mEvent.mbHandled = func(*(T*)&mEvent);
                return true;
            }
            return false;
        }
    private:
        Event& mEvent;
    };

    inline std::ostream& operator<<(std::ostream& os, const Event& e)
    {
        return os << e.ToString();
    }
    
}