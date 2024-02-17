#pragma once

#include "abpch.h"
#include "ABCD/Core.h"

namespace abcd
{
    enum class eEventType
    {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased,
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