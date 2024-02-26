#pragma once

#include <glm/glm.hpp>

#include "ABCD/Renderer/IVertexArray.h"

namespace abcd
{
    class IRendererAPI
    {
    public:
        enum class API
        {
            None = 0, OpenGL = 1
        };
    public:
        virtual void Init() = 0;
        virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
        virtual void SetClearColor(const glm::vec4& color) = 0;
        virtual void Clear() = 0;

        virtual void DrawIndexed(const Ref<IVertexArray>& vertexArray, uint32_t indexCount = 0) = 0;

        inline static API GetAPI() { return sAPI; }
        static Scope<IRendererAPI> Create();
    private:
        static API sAPI;
    };
}