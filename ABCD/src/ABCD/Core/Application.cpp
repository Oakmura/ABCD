#include "abpch.h"
#include "ABCD/Core/Application.h"

#include "ABCD/Core/Log.h"

#include "ABCD/Renderer/Renderer.h"

#include "ABCD/Core/Input.h"

#include <glfw/glfw3.h>

namespace abcd
{
    Application* Application::sInstance = nullptr;

    Application::Application()
    {
        AB_CORE_ASSERT(!sInstance, "Application already exists!");
        sInstance = this;

        mWindow = IWindow::Create();
        mWindow->SetEventCallback(AB_BIND_EVENT_FN(Application::OnEvent));

        Renderer::Init();

        mImGuiLayer = new ImGuiLayer();
        PushOverlay(mImGuiLayer);
    }

    Application::~Application()
    {
        Renderer::Shutdown();
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(AB_BIND_EVENT_FN(Application::onWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(AB_BIND_EVENT_FN(Application::onWindowResize));

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