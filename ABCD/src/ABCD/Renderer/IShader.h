#pragma once

#include <string>

namespace abcd 
{
    class IShader
    {
    public:
        ~IShader() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        static IShader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);
    };
}