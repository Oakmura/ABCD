#include "abpch.h"
#include "ABCD/Core/Input.h"

#ifdef AB_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsInput.h"
#endif

namespace abcd 
{
    Scope<Input> Input::sInstance = Input::Create();

    Scope<Input> Input::Create()
    {
#ifdef AB_PLATFORM_WINDOWS
       return CreateScope<WindowsInput>();
#else
       AB_CORE_ASSERT(false, "Unknown platform!");
       return nullptr;
#endif
    }
}