#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "IWindow.h"

namespace abcd
{
    class AB_API Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();

    private:
        std::unique_ptr<IWindow> mWindow;
        bool mbRunning = true;
    };

    Application* CreateApplication();
}