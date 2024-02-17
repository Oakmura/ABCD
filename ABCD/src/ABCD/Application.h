#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace abcd
{
    class AB_API Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();
    };

    Application* CreateApplication();
}