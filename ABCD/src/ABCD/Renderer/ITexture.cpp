#include "abpch.h"
#include "ITexture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace abcd 
{
    Ref<Texture2D> Texture2D::Create(const std::string& path)
    {
        switch (Renderer::GetAPI())
        {
        case IRendererAPI::API::None:    AB_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
        case IRendererAPI::API::OpenGL:  return std::make_shared<OpenGLTexture2D>(path);
        }

        AB_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}