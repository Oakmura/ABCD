#include "ABCD.h"

class ExampleLayer : public abcd::Layer
{
public:
    ExampleLayer()
        : Layer("Example")
    {
    }

    void OnUpdate() override
    {
        if (abcd::Input::IsKeyPressed(AB_KEY_TAB))
        {
            AB_TRACE("Tab key is pressed (poll)!");
        }
    }

    void OnEvent(abcd::Event& event) override
    {
        if (event.GetEventType() == abcd::EventType::KeyPressed)
        {
            abcd::KeyPressedEvent& e = (abcd::KeyPressedEvent&)event;
            if (e.GetKeyCode() == AB_KEY_TAB)
            {
                AB_TRACE("Tab key is pressed (event)!");
            }
            AB_TRACE("{0}", (char)e.GetKeyCode());
        }
    }
};

class Sandbox : public abcd::Application
{
public:
    Sandbox()
    {
        PushLayer(new ExampleLayer());
        PushOverlay(new abcd::ImGuiLayer());
    }

    ~Sandbox()
    {
        
    }
};

abcd::Application* abcd::CreateApplication()
{
    return new Sandbox();
}