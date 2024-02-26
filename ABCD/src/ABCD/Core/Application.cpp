#include "abpch.h"
#include "ABCD/Core/Application.h"

#include "ABCD/Core/Log.h"

#include "ABCD/Renderer/Renderer.h"

#include "ABCD/Core/Input.h"

#include <GLFW/glfw3.h>

namespace abcd
{
    Application* Application::sInstance = nullptr;

    Application::Application()
    {
        AB_PROFILE_FUNCTION();

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
        AB_PROFILE_FUNCTION();

        Renderer::Shutdown();
    }

    void Application::OnEvent(Event& e)
    {
        AB_PROFILE_FUNCTION();

        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(AB_BIND_EVENT_FN(Application::onWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(AB_BIND_EVENT_FN(Application::onWindowResize));

        for (auto it = mLayerStack.rbegin(); it != mLayerStack.rend(); ++it)
        {
            if (e.mbHandled)
            {
                break;
            }
            (*it)->OnEvent(e);
        }
    }

    void Application::PushLayer(Layer* layer)
    {
        AB_PROFILE_FUNCTION();

        mLayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* layer)
    {
        AB_PROFILE_FUNCTION();

        mLayerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    bool Application::onWindowClose(WindowCloseEvent& e)
    {
        mbRunning = false;

        return true;
    }

    bool Application::onWindowResize(WindowResizeEvent& e)
    {
        AB_PROFILE_FUNCTION();

        if (e.GetWidth() == 0 || e.GetHeight() == 0)
        {
            mbMinimized = true;
            return false;
        }

        mbMinimized = false;
        Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

        return false;
    }

    void Application::run()
    {
        AB_PROFILE_FUNCTION();

        while (mbRunning)
        {
            AB_PROFILE_SCOPE("RunLoop");

            float time = (float)glfwGetTime();
            Timestep timestep = time - mLastFrameTime;
            mLastFrameTime = time;

            if (!mbMinimized)
            {
                {
                    AB_PROFILE_SCOPE("LayerStack OnUpdate");

                    for (Layer* layer : mLayerStack)
                    {
                        layer->OnUpdate(timestep);
                    }
                }
            }

            mImGuiLayer->Begin();
            {
                AB_PROFILE_SCOPE("LayerStack OnImGuiRender");
                for (Layer* layer : mLayerStack)
                {
                    layer->OnImGuiRender();
                }
            }
            mImGuiLayer->End();

            mWindow->OnUpdate();
        }
    }
}