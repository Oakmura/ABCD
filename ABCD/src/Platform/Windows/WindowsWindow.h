#pragma once

#include "ABCD/Core/IWindow.h"
#include "ABCD/Renderer/IGraphicsContext.h"

#include <GLFW/glfw3.h>

namespace abcd 
{
    class WindowsWindow : public IWindow
    {
    public:
        WindowsWindow(const WindowProps& props);
        virtual ~WindowsWindow();

        void OnUpdate() override;

        unsigned int GetWidth() const override { return mData.Width; }
        unsigned int GetHeight() const override { return mData.Height; }

        void SetEventCallback(const EventCallbackFn& callback) override { mData.EventCallback = callback; }
        void SetVSync(bool enabled) override;
        bool IsVSync() const override;

        virtual void* GetNativeWindow() const { return mWindow; }
    private:
        virtual void Init(const WindowProps& props);
        virtual void Shutdown();
    private:
        GLFWwindow* mWindow;
        Scope<IGraphicsContext> mContext;

        struct WindowData
        {
            std::string Title;
            unsigned int Width, Height;
            bool VSync;

            EventCallbackFn EventCallback;
        };

        WindowData mData;
    };

}