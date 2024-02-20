#include "abpch.h"
#include "IBuffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace abcd 
{
    IVertexBuffer* IVertexBuffer::Create(float* vertices, uint32_t size)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::None:    AB_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
        case RendererAPI::OpenGL:  return new OpenGLVertexBuffer(vertices, size);
        }

        AB_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    IIndexBuffer* IIndexBuffer::Create(uint32_t* indices, uint32_t size)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::None:    AB_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
        case RendererAPI::OpenGL:  return new OpenGLIndexBuffer(indices, size);
        }

        AB_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}