#pragma once

#include "ABCD/Layer.h"

#include "ABCD/Events/ApplicationEvent.h"
#include "ABCD/Events/KeyEvent.h"
#include "ABCD/Events/MouseEvent.h"

namespace abcd 
{
    class AB_API ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate() override;
        void OnEvent(Event& event) override;

    private:
        bool onMouseButtonPressedEvent(MouseButtonPressedEvent& e);
        bool onMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
        bool onMouseMovedEvent(MouseMovedEvent& e);
        bool onMouseScrolledEvent(MouseScrolledEvent& e);
        bool onKeyPressedEvent(KeyPressedEvent& e);
        bool onKeyReleasedEvent(KeyReleasedEvent& e);
        bool onKeyTypedEvent(KeyTypedEvent& e);
        bool onWindowResizeEvent(WindowResizeEvent& e);
    private:
        float mTime = 0.0f;
    };
}