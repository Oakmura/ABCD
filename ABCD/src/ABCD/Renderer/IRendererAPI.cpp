#include "abpch.h"

#include "ABCD/Renderer/IRendererAPI.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace abcd 
{
    IRendererAPI::API IRendererAPI::sAPI = IRendererAPI::API::OpenGL;

    Scope<IRendererAPI> IRendererAPI::Create()
    {
        switch (sAPI)
        {
        case IRendererAPI::API::None:    AB_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
        case IRendererAPI::API::OpenGL:  return CreateScope<OpenGLRendererAPI>();
        }

        AB_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}