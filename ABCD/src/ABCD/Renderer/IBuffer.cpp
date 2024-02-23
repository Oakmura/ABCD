#include "abpch.h"
#include "ABCD/Renderer/IBuffer.h"

#include "ABCD/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace abcd 
{
    Ref<IVertexBuffer> IVertexBuffer::Create(float* vertices, uint32_t size)
    {
        switch (Renderer::GetAPI())
        {
        case IRendererAPI::API::None:    AB_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
        case IRendererAPI::API::OpenGL:  return CreateRef<OpenGLVertexBuffer>(vertices, size);
        }

        AB_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    Ref<IIndexBuffer> IIndexBuffer::Create(uint32_t* indices, uint32_t size)
    {
        switch (Renderer::GetAPI())
        {
        case IRendererAPI::API::None:    AB_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
        case IRendererAPI::API::OpenGL:  return CreateRef<OpenGLIndexBuffer>(indices, size);
        }

        AB_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}