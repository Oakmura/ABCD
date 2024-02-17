#pragma once

#ifdef AB_PLATFORM_WINDOWS

extern abcd::Application* abcd::CreateApplication();

int main(int argc, char** argv)
{
    auto app = abcd::CreateApplication();
    app->Run();
    delete app;
}

#endif