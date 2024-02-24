#pragma once

#include "ABCD/Core/Core.h"

#include "ABCD/Core/IWindow.h"

#include "ABCD/Core/LayerStack.h"
#include "ABCD/Events/Event.h"
#include "ABCD/Events/ApplicationEvent.h"

#include "ABCD/Core/Timestep.h"

#include "ABCD/ImGui/ImGuiLayer.h"

int main(int argc, char** argv);

namespace abcd
{
    class Application
    {
    public:
        Application();
        virtual ~Application();

        void OnEvent(Event& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);

        inline IWindow& GetWindow() { return *mWindow; }

        inline static Application& Get() { return *sInstance; }

    private:
        void run();

        bool onWindowClose(WindowCloseEvent& e);
        bool onWindowResize(WindowResizeEvent& e);

    private:
        std::unique_ptr<IWindow> mWindow;
        ImGuiLayer* mImGuiLayer;
        LayerStack mLayerStack;

        bool mbRunning = true;
        bool mbMinimized = false;
        float mLastFrameTime = 0.0f;

    private:
        static Application* sInstance;
        friend int ::main(int argc, char** argv);
    };

    Application* CreateApplication();
}