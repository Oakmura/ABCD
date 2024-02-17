#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "ABCD/Events/ApplicationEvent.h"

#include "IWindow.h"

namespace abcd
{
    class AB_API Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();
        void OnEvent(Event& e);

    private:
        bool onWindowClose(WindowCloseEvent& e);

    private:
        std::unique_ptr<IWindow> mWindow;
        bool mbRunning = true;
    };

    Application* CreateApplication();
}