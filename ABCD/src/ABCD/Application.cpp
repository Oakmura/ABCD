#include "abpch.h"
#include "Application.h"

#include "ABCD/Log.h"

#include "ABCD/Renderer/Renderer.h"

#include "Input.h"

#include <glfw/glfw3.h>

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

        Renderer::Init();

        mImGuiLayer = new ImGuiLayer();
        PushOverlay(mImGuiLayer);
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(onWindowResize));

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
    }

    void Application::PushOverlay(Layer* layer)
    {
        mLayerStack.PushOverlay(layer);
    }

    bool Application::onWindowClose(WindowCloseEvent& e)
    {
        mbRunning = false;

        return true;
    }

    bool Application::onWindowResize(WindowResizeEvent& e)
    {
        if (e.GetWidth() == 0 || e.GetHeight() == 0)
        {
            mbMinimized = true;
            return false;
        }

        mbMinimized = false;
        Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

        return false;
    }

    void Application::Run()
    {
        while (mbRunning)
        {
            float time = (float)glfwGetTime();
            Timestep timestep = time - mLastFrameTime;
            mLastFrameTime = time;

            if (!mbMinimized)
            {
                for (Layer* layer : mLayerStack)
                {
                    layer->OnUpdate(timestep);
                }
            }

            mImGuiLayer->Begin();
            for (Layer* layer : mLayerStack)
            {
                layer->OnImGuiRender();
            }
            mImGuiLayer->End();

            mWindow->OnUpdate();
        }
    }
}