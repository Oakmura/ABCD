#include "abpch.h"
#include "Application.h"

#include "ABCD/Events/ApplicationEvent.h"
#include "ABCD/Log.h"

#include <GLFW/glfw3.h>

namespace abcd
{
    Application::Application()
    {
        mWindow = std::unique_ptr<IWindow>(IWindow::Create());
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        while (mbRunning)
        {
            glClearColor(1, 0, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            mWindow->OnUpdate();
        }
    }
}