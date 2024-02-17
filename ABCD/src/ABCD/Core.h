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

#ifdef AB_ENABLE_ASSERTS
    #define AB_ASSERT(x, ...) { if(!(x)) { AB_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
    #define AB_CORE_ASSERT(x, ...) { if(!(x)) { AB_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
    #define AB_ASSERT(x, ...)
    #define AB_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)