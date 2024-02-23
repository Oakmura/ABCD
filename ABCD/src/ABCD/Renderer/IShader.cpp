#include "abpch.h"
#include "IShader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace abcd 
{
    Ref<IShader> IShader::Create(const std::string& filepath)
    {
        switch (Renderer::GetAPI())
        {
        case IRendererAPI::API::None:    AB_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
        case IRendererAPI::API::OpenGL:  return std::make_shared<OpenGLShader>(filepath);
        }

        AB_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

	Ref<IShader> IShader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        switch (Renderer::GetAPI())
        {
        case IRendererAPI::API::None:    AB_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
        case IRendererAPI::API::OpenGL:  return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
        }

        AB_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    void ShaderLibrary::Add(const std::string& name, const Ref<IShader>& shader)
    {
        AB_CORE_ASSERT(!Exists(name), "Shader already exists!");
        mShaders[name] = shader;
    }

    void ShaderLibrary::Add(const Ref<IShader>& shader)
    {
        auto& name = shader->GetName();
        Add(name, shader);
    }

    abcd::Ref<abcd::IShader> ShaderLibrary::Load(const std::string& filepath)
    {
        auto shader = IShader::Create(filepath);
        Add(shader);
        return shader;
    }

    abcd::Ref<abcd::IShader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
    {
        auto shader = IShader::Create(filepath);
        Add(name, shader);
        return shader;
    }

    abcd::Ref<abcd::IShader> ShaderLibrary::Get(const std::string& name)
    {
        AB_CORE_ASSERT(Exists(name), "Shader not found!");
        return mShaders[name];
    }

    bool ShaderLibrary::Exists(const std::string& name) const
    {
        return mShaders.find(name) != mShaders.end();
    }
}