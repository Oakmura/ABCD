#pragma once

#include "Core.h"
#include "IWindow.h"

#include "ABCD/LayerStack.h"
#include "ABCD/Events/Event.h"
#include "ABCD/Events/ApplicationEvent.h"

#include "ABCD/ImGui/ImGuiLayer.h"
#include "ABCD/Renderer/Shader.h"

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

        inline IWindow& GetWindow() { return *mWindow; }

        inline static Application& Get() { return *sInstance; }

    private:
        bool onWindowClose(WindowCloseEvent& e);

    private:
        std::unique_ptr<IWindow> mWindow;
        ImGuiLayer* mImGuiLayer;
        LayerStack mLayerStack;
        std::unique_ptr<Shader> mShader;

        bool mbRunning = true;
        unsigned int mVertexArray;
        unsigned int mVertexBuffer;
        unsigned int mIndexBuffer;

    private:
        static Application* sInstance;
    };

    Application* CreateApplication();
}