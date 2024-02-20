#include "abpch.h"
#include "Application.h"

#include "ABCD/Log.h"

#include <glad/glad.h>

#include "Input.h"

namespace abcd
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application* Application::sInstance = nullptr;

    Application::Application()
    {
        AB_CORE_ASSERT(!sInstance, "Application already exists!");
        sInstance = this;

        mWindow = std::unique_ptr<IWindow>(IWindow::Create());
        mWindow->SetEventCallback(BIND_EVENT_FN(OnEvent));
    }

    Application::~Application()
    {
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));

        for (auto it = mLayerStack.end(); it != mLayerStack.begin(); )
        {
            (*--it)->OnEvent(e);
            if (e.mbHandled)
            {
                break;
            }
        }
    }

    void Application::PushLayer(Layer* layer)
    {
        mLayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* layer)
    {
        mLayerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    bool Application::onWindowClose(WindowCloseEvent& e)
    {
        mbRunning = false;

        return true;
    }

    void Application::Run()
    {
        while (mbRunning)
        {
            glClearColor(1, 0, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            for (Layer* layer : mLayerStack)
            {
                layer->OnUpdate();
            }

            mWindow->OnUpdate();
        }
    }
}