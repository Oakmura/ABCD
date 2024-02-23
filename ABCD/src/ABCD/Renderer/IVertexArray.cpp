#include "abpch.h"
#include "IVertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace abcd 
{
    Ref<IVertexArray> IVertexArray::Create()
    {
        switch (Renderer::GetAPI())
        {
        case IRendererAPI::API::None:    AB_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
        case IRendererAPI::API::OpenGL:  return std::make_shared<OpenGLVertexArray>();
        }

        AB_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}