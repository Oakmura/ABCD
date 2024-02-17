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
        AB_INFO("ExampleLayer::Update");
    }

    void OnEvent(abcd::Event& event) override
    {
        AB_TRACE("{0}", event);
    }
};

class Sandbox : public abcd::Application
{
public:
    Sandbox()
    {
        PushLayer(new ExampleLayer());
    }

    ~Sandbox()
    {
        
    }
};

abcd::Application* abcd::CreateApplication()
{
    return new Sandbox();
}