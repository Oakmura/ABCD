#include "abpch.h"
#include "IShader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace abcd 
{
    IShader* IShader::Create(const std::string& filepath)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:    AB_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
        case RendererAPI::API::OpenGL:  return new OpenGLShader(filepath);
        }

        AB_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    IShader* IShader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:    AB_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
        case RendererAPI::API::OpenGL:  return new OpenGLShader(vertexSrc, fragmentSrc);
        }

        AB_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}