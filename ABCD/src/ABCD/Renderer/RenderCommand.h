#pragma once

#include "ABCD/Renderer/IRendererAPI.h"

namespace abcd 
{
    class RenderCommand
    {
    public:
        inline static void Init()
        {
            sRendererAPI->Init();
        }

        inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
        {
            sRendererAPI->SetViewport(x, y, width, height);
        }

        inline static void SetClearColor(const glm::vec4& color)
        {
            sRendererAPI->SetClearColor(color);
        }

        inline static void Clear()
        {
            sRendererAPI->Clear();
        }

        inline static void DrawIndexed(const Ref<IVertexArray>& vertexArray, uint32_t count = 0)
        {
            sRendererAPI->DrawIndexed(vertexArray, count);
        }

    private:
        static Scope<IRendererAPI> sRendererAPI;
    };

}