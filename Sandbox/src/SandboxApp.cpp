#include "ABCD.h"
#include <ABCD/Core/EntryPoint.h>

#include "Sandbox2D.h"
#include "ExampleLayer.h"

class Sandbox : public abcd::Application
{
public:
    Sandbox()
    {
        PushLayer(new ExampleLayer());
        PushLayer(new Sandbox2D());
    }

    ~Sandbox()
    {
        
    }
};

abcd::Application* abcd::CreateApplication()
{
    return new Sandbox();
}