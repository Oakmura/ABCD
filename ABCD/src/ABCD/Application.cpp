#include "Application.h"

#include "ABCD/Events/ApplicationEvent.h"
#include "ABCD/Log.h"

namespace abcd
{
    Application::Application()
    {
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        WindowResizeEvent e(1280, 720);
        if (e.IsInCategory(EVENT_CATEGORY_APPLICATION))
        {
            AB_TRACE(e);
        }
        if (e.IsInCategory(EVENT_CATEGORY_INPUT))
        {
            AB_TRACE(e);
        }

        while (true);
    }
}