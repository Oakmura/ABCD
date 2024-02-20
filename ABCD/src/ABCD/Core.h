#pragma once

#ifdef AB_PLATFORM_WINDOWS
#if AB_DYNAMIC_LINK
    #ifdef AB_BUILD_DLL
        #define AB_API __declspec(dllexport)
    #else
        #define AB_API __declspec(dllimport)
    #endif
#else
    #define AB_API
#endif
#else
    #error ABCD only supports Windows!
#endif

#ifdef AB_DEBUG
    #define AB_ENABLE_ASSERTS
#endif

#ifdef AB_ENABLE_ASSERTS
    #define AB_ASSERT(x, ...) { if(!(x)) { AB_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
    #define AB_CORE_ASSERT(x, ...) { if(!(x)) { AB_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
    #define AB_ASSERT(x, ...)
    #define AB_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define AB_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)