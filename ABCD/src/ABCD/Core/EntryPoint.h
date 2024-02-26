#pragma once

#include "ABCD/Core/Base.h"

#ifdef AB_PLATFORM_WINDOWS

extern abcd::Application* abcd::CreateApplication();

int main(int argc, char** argv)
{
    abcd::Log::Init();

    AB_PROFILE_BEGIN_SESSION("Startup", "ABCDProfile-Startup.json");
    auto app = abcd::CreateApplication();
    AB_PROFILE_END_SESSION();

    AB_PROFILE_BEGIN_SESSION("Runtime", "ABCDProfile-Runtime.json");
    app->run();
    AB_PROFILE_END_SESSION();

    AB_PROFILE_BEGIN_SESSION("Startup", "ABCDProfile-Shutdown.json");
    delete app;
    AB_PROFILE_END_SESSION();
}

#endif