#pragma once

#ifdef AB_PLATFORM_WINDOWS
    #ifdef AB_BUILD_DLL
        #define AB_API __declspec(dllexport)
    #else
        #define AB_API __declspec(dllimport)
    #endif
#else
    #error ABCD only supports Windows!
#endif