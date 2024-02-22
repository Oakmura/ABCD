#pragma once

#include <string>
#include <unordered_map>

namespace abcd 
{
    class IShader
    {
    public:
        ~IShader() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual const std::string& GetName() const = 0;

        static Ref<IShader> Create(const std::string& filepath);
        static Ref<IShader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
    };

    class ShaderLibrary
    {
    public:
        void Add(const std::string& name, const Ref<IShader>& shader);
        void Add(const Ref<IShader>& shader);
        Ref<IShader> Load(const std::string& filepath);
        Ref<IShader> Load(const std::string& name, const std::string& filepath);

        Ref<IShader> Get(const std::string& name);

        bool Exists(const std::string& name) const;
    private:
        std::unordered_map<std::string, Ref<IShader>> mShaders;
    };
}