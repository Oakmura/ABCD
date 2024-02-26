#pragma once

#include "abpch.h"

#include "ABCD/Core/Base.h"
#include "ABCD/Events/Event.h"

namespace abcd 
{
    struct WindowProps
    {
        std::string Title;
        unsigned int Width;
        unsigned int Height;

        WindowProps(const std::string& title = "ABCD Engine",
            unsigned int width = 1280,
            unsigned int height = 720)
            : Title(title), Width(width), Height(height)
        {
        }
    };

    // Interface representing a desktop system based Window
    class IWindow
    {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        virtual ~IWindow() = default;

        virtual void OnUpdate() = 0;

        virtual unsigned int GetWidth() const = 0;
        virtual unsigned int GetHeight() const = 0;

        virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
        virtual void SetVSync(bool enabled) = 0;
        virtual bool IsVSync() const = 0;

        virtual void* GetNativeWindow() const = 0;

        static Scope<IWindow> Create(const WindowProps& props = WindowProps());
    };

}