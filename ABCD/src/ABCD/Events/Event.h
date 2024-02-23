#pragma once

#include "abpch.h"

#include "ABCD/Core/Core.h"

namespace abcd
{
    enum class eEventType
    {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased, KeyTyped,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    enum eEventCategory
    {
        None = 0,
        EventCategoryApplication = BIT(0),
        EventCategoryInput = BIT(1),
        EventCategoryKeyboard = BIT(2),
        EventCategoryMouse = BIT(3),
        EventCategoryMouseButton = BIT(4)
    };

#define EVENT_CLASS_TYPE(type) static eEventType GetStaticType() { return eEventType::type; }\
                            virtual eEventType GetEventType() const override { return GetStaticType(); }\
                            virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

    class Event
    {
    public:
        virtual eEventType GetEventType() const = 0;
        virtual const char* GetName() const = 0;
        virtual int GetCategoryFlags() const = 0;
        virtual std::string ToString() const { return GetName(); }

        inline bool IsInCategory(eEventCategory category)
        {
            return GetCategoryFlags() & category;
        }

        bool mbHandled = false;
    };

    class EventDispatcher
    {
    public:
        EventDispatcher(Event& event)
            : mEvent(event)
        {
        }

        // F will be deduced by the compiler
        template<typename T, typename F>
        bool Dispatch(const F& func)
        {
            if (mEvent.GetEventType() == T::GetStaticType())
            {
                mEvent.mbHandled = func(static_cast<T&>(mEvent));
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