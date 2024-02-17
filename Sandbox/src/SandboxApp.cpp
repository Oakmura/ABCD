#include "ABCD.h"

class Sandbox : public abcd::Application
{
public:
    Sandbox()
    {

    }

    ~Sandbox()
    {
        
    }
};

abcd::Application* abcd::CreateApplication()
{
    return new Sandbox();
}