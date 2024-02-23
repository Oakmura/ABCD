#include "abpch.h"
#include "ABCD/Renderer/IGraphicsContext.h"

#include "ABCD/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace abcd
{
    Scope<IGraphicsContext> IGraphicsContext::Create(void* window)
    {
        switch (Renderer::GetAPI())
        {
        case IRendererAPI::API::None:    AB_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
        case IRendererAPI::API::OpenGL:  return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
        }

        AB_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}