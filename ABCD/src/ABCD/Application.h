#pragma once

#include "Core.h"
#include "IWindow.h"

#include "ABCD/LayerStack.h"
#include "ABCD/Events/Event.h"
#include "ABCD/Events/ApplicationEvent.h"

namespace abcd
{
    class AB_API Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();
        void OnEvent(Event& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);

    private:
        bool onWindowClose(WindowCloseEvent& e);

    private:
        std::unique_ptr<IWindow> mWindow;
        LayerStack mLayerStack;

        bool mbRunning = true;
    };

    Application* CreateApplication();
}