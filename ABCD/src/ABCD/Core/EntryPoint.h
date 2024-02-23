#pragma once

#include "ABCD/Core/Core.h"

#ifdef AB_PLATFORM_WINDOWS

extern abcd::Application* abcd::CreateApplication();

int main(int argc, char** argv)
{
    abcd::Log::Init();
    AB_CORE_TRACE("Initialized Log!");

    int a = 5;
    AB_INFO("Hello! Var={0}", a);

    auto app = abcd::CreateApplication();
    app->Run();
    delete app;
}

#endif